-- cpu.vhd: Simple 8-bit CPU (BrainLove interpreter)
-- Copyright (C) 2021 Brno University of Technology,
--                    Faculty of Information Technology
-- Author(s): Daniel Záležák - xzalez01
--

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

-- ----------------------------------------------------------------------------
--                        Entity declaration
-- ----------------------------------------------------------------------------
entity cpu is
 port (
   CLK   : in std_logic;  -- hodinovy signal
   RESET : in std_logic;  -- asynchronni reset procesoru
   EN    : in std_logic;  -- povoleni cinnosti procesoru
 
   -- synchronni pamet ROM
   CODE_ADDR : out std_logic_vector(11 downto 0); -- adresa do pameti
   CODE_DATA : in std_logic_vector(7 downto 0);   -- CODE_DATA <- rom[CODE_ADDR] pokud CODE_EN='1'
   CODE_EN   : out std_logic;                     -- povoleni cinnosti
   
   -- synchronni pamet RAM
   DATA_ADDR  : out std_logic_vector(9 downto 0); -- adresa do pameti
   DATA_WDATA : out std_logic_vector(7 downto 0); -- ram[DATA_ADDR] <- DATA_WDATA pokud DATA_EN='1'
   DATA_RDATA : in std_logic_vector(7 downto 0);  -- DATA_RDATA <- ram[DATA_ADDR] pokud DATA_EN='1'
   DATA_WREN  : out std_logic;                    -- cteni z pameti (DATA_WREN='0') / zapis do pameti (DATA_WREN='1')
   DATA_EN    : out std_logic;                    -- povoleni cinnosti
   
   -- vstupni port
   IN_DATA   : in std_logic_vector(7 downto 0);   -- IN_DATA obsahuje stisknuty znak klavesnice pokud IN_VLD='1' a IN_REQ='1'
   IN_VLD    : in std_logic;                      -- data platna pokud IN_VLD='1'
   IN_REQ    : out std_logic;                     -- pozadavek na vstup dat z klavesnice
   
   -- vystupni port
   OUT_DATA : out  std_logic_vector(7 downto 0);  -- zapisovana data
   OUT_BUSY : in std_logic;                       -- pokud OUT_BUSY='1', LCD je zaneprazdnen, nelze zapisovat,  OUT_WREN musi byt '0'
   OUT_WREN : out std_logic                       -- LCD <- OUT_DATA pokud OUT_WREN='1' a OUT_BUSY='0'
 );
end cpu;


-- ----------------------------------------------------------------------------
--                      Architecture declaration
-- ----------------------------------------------------------------------------
architecture behavioral of cpu is

	signal pc_reg : std_logic_vector(11 downto 0);
	signal pc_inc, pc_dec : std_logic;

	signal ptr_reg : std_logic_vector(9 downto 0);
	signal ptr_inc, ptr_dec	: std_logic;

	signal cnt_reg	: std_logic_vector(7 downto 0);
	signal cnt_inc, cnt_dec	: std_logic;

	signal mux_sel : std_logic_vector(1 downto 0);

	

	-- Stavy automatu
	type fsm_state is (
		state_start, 
		state_fetch,
		state_decode,
		state_p_inc,
		state_p_dec,
		state_v_inc, 
		state_v_inc_do,
		state_v_dec, 
		state_v_dec_do,
		state_get,
		state_put,
		state_while_start_1, state_while_start_2, state_while_start_3, state_while_start_4,
		state_while_break_1, state_while_break_2, state_while_break_3,
		state_while_end_1, state_while_end_2, state_while_end_3, state_while_end_4, state_while_end_5,
		state_null,
		state_others
	);

	signal present_state, next_state : fsm_state;

-- ----------------------------------------------------------------------------
--                      Components
-- ----------------------------------------------------------------------------
begin

	-- -----------------------------------------
	--           	PC
	-- -----------------------------------------
	PC_proc: process (RESET, CLK)
	begin
		if (RESET = '1') then
			pc_reg <= (others => '0');
		elsif rising_edge(CLK) then
			if (pc_inc = '1') then		
				pc_reg <= pc_reg + 1;
			elsif (pc_dec = '1') then	
				pc_reg <= pc_reg - 1;
			end if;
		end if;
	end process PC_proc;

	-- -----------------------------------------
	--          	PTR
	-- -----------------------------------------
	PTR_proc: process (RESET, CLK)
	begin
		if (RESET = '1') then
			ptr_reg <= (others => '0');
		elsif rising_edge(CLK) then
			if (ptr_inc = '1') then		
				ptr_reg <= ptr_reg + 1;
			elsif (ptr_dec = '1') then	
				ptr_reg <= ptr_reg - 1;
			end if;
		end if;
	end process PTR_proc;

	-- -----------------------------------------
	--          	CNT
	-- -----------------------------------------
	CNT_proc: process (RESET, CLK)
	begin
		if (RESET = '1') then
			cnt_reg <= (others => '0');
		elsif rising_edge(CLK) then
			if (cnt_inc = '1') then		
				cnt_reg <= cnt_reg + 1;
			elsif (cnt_dec = '1') then	
				cnt_reg <= cnt_reg - 1;
			end if;
		end if;
	end process CNT_proc;

	
	DATA_ADDR <= ptr_reg;
	CODE_ADDR <= pc_reg;

	-- -----------------------------------------
	--         	MUX
	-- -----------------------------------------
	mux_proc: process(CLK, mux_sel, DATA_RDATA, IN_DATA)
	begin
		case mux_sel is
			when "00" => DATA_WDATA <= IN_DATA;
			when "01" => DATA_WDATA <= DATA_RDATA + "00000001"; 
			when "10" => DATA_WDATA <= DATA_RDATA - "00000001"; 
			when "11" => DATA_WDATA <= X"00";
			when others => 
		end case;
	end process mux_proc;

	-- -----------------------------------------
	--          	FSM present state
	-- -----------------------------------------
	fsm_present_state_proc: process(RESET, CLK)
	begin
		if (RESET = '1') then 
			present_state <= state_start;
		elsif rising_edge(CLK) and (EN = '1') then	
			present_state <= next_state;
		end if;
	end process fsm_present_state_proc;

	-- -----------------------------------------
	--          	FSM next state
	-- -----------------------------------------
	fsm_next_state_proc : process(CLK, RESET, EN, CODE_DATA, IN_VLD, IN_DATA, DATA_RDATA, OUT_BUSY, present_state, CODE_DATA, cnt_reg, mux_sel)
	begin
		next_state <= state_start;
		CODE_EN	<= '1';
		DATA_EN	<= '0';
		DATA_WREN <= '0';
		IN_REQ <= '0';
		OUT_WREN <= '0';
		pc_inc <= '0';
		pc_dec <= '0';
		ptr_inc	<= '0';
		ptr_dec	<= '0';
		cnt_inc	<= '0';
		cnt_dec	<= '0';
		mux_sel <= "00";

		case present_state is
			-- IDLE
			when state_start => next_state <= state_fetch;

			-- FETCH
			when state_fetch =>				
				next_state <= state_decode;
				CODE_EN	<= '1';

			-- DECODE
			when state_decode =>
				case CODE_DATA is
					when X"3E" => next_state <= state_p_inc;
					when X"3C" => next_state <= state_p_dec;
					when X"2B" => next_state <= state_v_inc;
					when X"2D" => next_state <= state_v_dec;
					when X"5B" => next_state <= state_while_start_1;
					when X"7E" => next_state <= state_while_break_1;
					when X"5D" => next_state <= state_while_end_1;
					when X"2E" => next_state <= state_put;
					when X"2C" => next_state <= state_get;
					when X"00" => next_state <= state_null;
					when others => next_state <= state_others;
				end case;

			-- POINTER_INC | >
			when state_p_inc =>
				next_state <= state_fetch;
				ptr_inc <= '1';			
				pc_inc <= '1';			

			-- POINTER_DEC | <
			when state_p_dec =>
				next_state <= state_fetch;
				ptr_dec	<= '1';
				pc_inc	<= '1';

			-- VALUE_INC | +
			when state_v_inc =>
				next_state <= state_v_inc_do;
				DATA_WREN <= '0';			
				DATA_EN	<= '1';
			when state_v_inc_do =>			
				next_state <= state_fetch;
				DATA_EN	<= '1';
				DATA_WREN <= '1';		
				pc_inc <= '1';
				mux_sel <= "01";

			-- VALUE_DEC | -
			when state_v_dec =>
				next_state <= state_v_dec_do;
				DATA_WREN <= '0';
				DATA_EN	 <= '1';
			when state_v_dec_do =>
				next_state <= state_fetch;
				DATA_WREN <= '1';
				DATA_EN	<= '1';
				pc_inc <= '1';
				mux_sel <= "10";

			-- PUTCHAR | .
			when state_put =>
				if(OUT_BUSY = '1') then
					next_state <= state_put;
				else
					next_state <= state_fetch;
					OUT_DATA <= DATA_RDATA;
					DATA_WREN <= '0';
					OUT_WREN <= '1';
					pc_inc <= '1';
				end if;

			-- GETCHAR | ,
			when state_get =>
				next_state <= state_get;
				IN_REQ <= '1';		
				if (IN_VLD = '1') then
					next_state <= state_fetch;
					DATA_EN <= '1';
					DATA_WREN <= '1';
					pc_inc <= '1';
					IN_REQ <= '0';
					mux_sel <= "00";
				end if;

			-- WHILE_START | [
			when state_while_start_1 =>
				next_state <= state_while_start_2;
				pc_inc <= '1';
				DATA_EN <= '1';
				DATA_WREN <= '0';
			when state_while_start_2 =>
				if (DATA_RDATA = "00000000") then
					next_state <= state_while_start_3;
				else
					next_state <= state_fetch;			
				end if;
			when state_while_start_3 =>
				if (cnt_reg = "00000000") then
					next_state <= state_fetch;
					cnt_inc <= '1';
				else
					next_state <= state_while_start_4;
					CODE_EN	<= '1';
				end if;
			when state_while_start_4 =>
				next_state <= state_while_start_3;
				pc_inc <= '1';
				if (CODE_DATA = X"5B") then
					cnt_inc	<= '1';
				else
					cnt_dec	<= '1';
				end if;

			-- WHILE_BREAK | ~
			when state_while_break_1 =>
				next_state <= state_while_break_2;
				pc_inc <= '1';
				cnt_inc	<= '1';
			when state_while_break_2 =>
				if (cnt_reg /= "00000000") then
					CODE_EN	<= '1';
					next_state <= state_while_break_3;
				else
					next_state <= state_fetch;
				end if;
			when state_while_break_3 =>
				next_state <= state_while_break_2;
				pc_inc <= '1';
				if (CODE_DATA = X"5B") then
					cnt_inc <= '1';
				elsif (CODE_DATA = X"5D") then
					cnt_dec <= '1';
				end if;

			-- WHILE_END | ]
			when state_while_end_1 =>
				next_state <= state_while_end_2;
				DATA_WREN <= '0';
				DATA_EN	<= '1';
			when state_while_end_2 =>
				if (DATA_RDATA = "00000000") then
					next_state <= state_fetch;
					pc_inc <= '1';
				else
					next_state <= state_while_end_3;
					cnt_inc	<= '1';
					pc_dec <= '1';
				end if;
			when state_while_end_3 =>
				if (cnt_reg = "00000000") then
					next_state <= state_fetch;
				else
					next_state <= state_while_end_4;
					CODE_EN	<= '1';
				end if;
			when state_while_end_4 =>
				next_state <= state_while_end_5;
				if (CODE_DATA = X"5B") then		
					cnt_dec	<= '1';
				elsif (CODE_DATA = X"5D") then	
					cnt_inc	<= '1';
				end if;
			when state_while_end_5 =>
				next_state <= state_while_end_3;
				if (cnt_reg = "00000000") then 
					pc_inc <= '1';
				else 
					pc_dec <= '1';
				end if;

			-- NULL
			when state_null => next_state <= state_null;

			
			when state_others =>
				next_state <= state_fetch;
				pc_inc <= '1';

			
			when others => null;
		end case;
	end process fsm_next_state_proc;



end behavioral;
 
