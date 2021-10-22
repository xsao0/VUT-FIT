-- uart_fsm.vhd: UART controller - finite state machine
-- Author(s): xzalez01
--
library ieee;
use ieee.std_logic_1164.all;

-------------------------------------------------
entity UART_FSM is
port(
   CLK       : in std_logic;
   RST       : in std_logic;
   DIN       : in std_logic;
   CNT_1 : in std_logic_vector(4 downto 0);
   CNT_2 : in std_logic_vector(3 downto 0);
   VLD       : out std_logic;
   RX_EN     : out std_logic;
   CNT_EN    : out std_logic
   );
end entity UART_FSM;

-------------------------------------------------
architecture behavioral of UART_FSM is
type T_STATE is (START, WAIT_FIRST, DATA, WAIT_LAST, VALID);
signal state : T_STATE := START;
begin
   process (CLK) begin
      if RST = '1' then
         state <= START;
         VLD <= '0';
         RX_EN <= '0';
         CNT_EN <= '0';
      else
         if rising_edge(CLK) then
            case state is
               when START => VLD <= '0';
                              if DIN = '0' then
                                 state <= WAIT_FIRST;
                              end if;
               when WAIT_FIRST => CNT_EN <= '1';
                                    if CNT_1 = "10110" then
                                       state <= DATA;
                                    end if;
               when DATA => RX_EN <= '1';
                                 if CNT_2 = "1000" then
                                    state <= WAIT_LAST;    
                                 end if;
               when WAIT_LAST => RX_EN <= '0';
                                    CNT_EN <= '0';
                                    if DIN = '1' then                     
                                      state <= VALID;
                                    end if;
               when VALID => VLD <= '1';
                                 state <= START;
               when others => null;
            end case;
         end if;
      end if;
   end process;
end behavioral;
