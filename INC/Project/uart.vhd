-- uart.vhd: UART controller - receiving part
-- Author(s): xzalez01 
--
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

-------------------------------------------------
entity UART_RX is
port(	
    	CLK: 	    in std_logic;
	RST: 	    in std_logic;
	DIN: 	    in std_logic;
	DOUT: 	    out std_logic_vector(7 downto 0);
	DOUT_VLD: 	out std_logic
);
end UART_RX;  

-------------------------------------------------
architecture behavioral of UART_RX is
signal cnt : std_logic_vector(4 downto 0) := "00000";
signal cnt2 : std_logic_vector(3 downto 0) := "0000";
signal cnt_en : std_logic := '0';
signal cnt2_en : std_logic := '0';
begin
	FSM: entity work.UART_FSM(behavioral)
	port map (
        	CLK => CLK,
        	RST => RST,
        	DIN => DIN,
        	CNT => cnt,
		CNT2 => cnt2,
        	VLD => DOUT_VLD,
		CNT_EN => cnt_en,
		CNT2_EN => cnt2_en
    	);
    	process (CLK) begin
        	if RST = '1' then
            		cnt <= "00000";
			cnt2 <= "0000";
            		DOUT <= "00000000";
        	else
            		if rising_edge(CLK) then
				if cnt_en = '1' then
					cnt <= cnt + 1;
				else
                    			cnt <= "00000";
                    			cnt2 <= "0000";
                		end if;
                		if cnt2_en = '1' then
                    			if cnt > 14 then
                        			cnt <= "00000";
                        			case cnt2 is
                           				when "0111" => DOUT(7) <= DIN;
                            				when "0110" => DOUT(6) <= DIN;
                            				when "0101" => DOUT(5) <= DIN;
                            				when "0100" => DOUT(4) <= DIN;
                            				when "0011" => DOUT(3) <= DIN;
                            				when "0010" => DOUT(2) <= DIN;
                            				when "0001" => DOUT(1) <= DIN;
                            				when "0000" => DOUT(0) <= DIN;
                            				when others => null;
                        			end case;
                        			cnt2 <= cnt2 + 1;
                    			end if;
                		end if;
            		end if;
        	end if;
    	end process;
	
end behavioral;
