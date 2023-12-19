----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 27.04.2021 17:42:57
-- Design Name: 
-- Module Name: test1 - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity test1 is
	generic (
		-- Users to add parameters here

		-- User parameters ends
		-- Do not modify the parameters beyond this line


		-- Parameters of Axi Slave Bus Interface S00_AXI
		C_S00_AXI_DATA_WIDTH	: integer	:= 32;
		C_S00_AXI_ADDR_WIDTH	: integer	:= 17
	);
--  Port ( );
end test1;

architecture Behavioral of test1 is

        signal hsync :  std_logic;
        signal vsync :  std_logic;
        signal red : std_logic_vector (3 downto 0);
        signal green: std_logic_vector (3 downto 0);
        signal blue: std_logic_vector (3 downto 0);

		-- User ports ends
		-- Do not modify the ports beyond this line


		-- Ports of Axi Slave Bus Interface S00_AXI
		signal s00_axi_aclk	:  std_logic;
		signal s00_axi_aresetn	:  std_logic;
		signal s00_axi_awaddr	:  std_logic_vector(C_S00_AXI_ADDR_WIDTH-1 downto 0);
		signal s00_axi_awprot	:  std_logic_vector(2 downto 0);
		signal s00_axi_awvalid	:  std_logic;
		signal s00_axi_awready	:  std_logic;
		signal s00_axi_wdata	:  std_logic_vector(C_S00_AXI_DATA_WIDTH-1 downto 0);
		signal s00_axi_wstrb	:  std_logic_vector((C_S00_AXI_DATA_WIDTH/8)-1 downto 0);
		signal s00_axi_wvalid	:  std_logic;
		signal s00_axi_wready	:  std_logic;
		signal s00_axi_bresp	:  std_logic_vector(1 downto 0);
		signal s00_axi_bvalid	:  std_logic;
		signal s00_axi_bready	:  std_logic;
		signal s00_axi_araddr	:  std_logic_vector(C_S00_AXI_ADDR_WIDTH-1 downto 0);
		signal s00_axi_arprot	:  std_logic_vector(2 downto 0);
		signal s00_axi_arvalid	:  std_logic;
		signal s00_axi_arready	:  std_logic;
		signal s00_axi_rdata	:  std_logic_vector(C_S00_AXI_DATA_WIDTH-1 downto 0);
		signal s00_axi_rresp	:  std_logic_vector(1 downto 0);
		signal s00_axi_rvalid	:  std_logic;
		signal s00_axi_rready	:  std_logic;


	-- component declaration
	component vga_control_v1_0_S00_AXI is
		generic (
		C_S_AXI_DATA_WIDTH	: integer	:= C_S00_AXI_DATA_WIDTH;
		C_S_AXI_ADDR_WIDTH	: integer	:= C_S00_AXI_ADDR_WIDTH
		);
		port (
        hsync : out std_logic;
        vsync : out std_logic;
        red : out std_logic_vector (3 downto 0);
        green: out std_logic_vector (3 downto 0);
        blue: out std_logic_vector (3 downto 0);

		S_AXI_ACLK	: in std_logic;
		S_AXI_ARESETN	: in std_logic;
		S_AXI_AWADDR	: in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
		S_AXI_AWPROT	: in std_logic_vector(2 downto 0);
		S_AXI_AWVALID	: in std_logic;
		S_AXI_AWREADY	: out std_logic;
		S_AXI_WDATA	: in std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
		S_AXI_WSTRB	: in std_logic_vector((C_S_AXI_DATA_WIDTH/8)-1 downto 0);
		S_AXI_WVALID	: in std_logic;
		S_AXI_WREADY	: out std_logic;
		S_AXI_BRESP	: out std_logic_vector(1 downto 0);
		S_AXI_BVALID	: out std_logic;
		S_AXI_BREADY	: in std_logic;
		S_AXI_ARADDR	: in std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
		S_AXI_ARPROT	: in std_logic_vector(2 downto 0);
		S_AXI_ARVALID	: in std_logic;
		S_AXI_ARREADY	: out std_logic;
		S_AXI_RDATA	: out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
		S_AXI_RRESP	: out std_logic_vector(1 downto 0);
		S_AXI_RVALID	: out std_logic;
		S_AXI_RREADY	: in std_logic
		);
	end component vga_control_v1_0_S00_AXI;

begin

-- Instantiation of Axi Bus Interface S00_AXI
vga_ctrl_v1_0_S00_AXI_inst : vga_control_v1_0_S00_AXI
	generic map (
		C_S_AXI_DATA_WIDTH	=> C_S00_AXI_DATA_WIDTH,
		C_S_AXI_ADDR_WIDTH	=> C_S00_AXI_ADDR_WIDTH
	)
	port map (
	    hsync	=> hsync,
        vsync	=> vsync,
        red	    => red,
        green	=> green,
        blue	=> blue,

		S_AXI_ACLK	=> s00_axi_aclk,
		S_AXI_ARESETN	=> s00_axi_aresetn,
		S_AXI_AWADDR	=> s00_axi_awaddr,
		S_AXI_AWPROT	=> s00_axi_awprot,
		S_AXI_AWVALID	=> s00_axi_awvalid,
		S_AXI_AWREADY	=> s00_axi_awready,
		S_AXI_WDATA	=> s00_axi_wdata,
		S_AXI_WSTRB	=> s00_axi_wstrb,
		S_AXI_WVALID	=> s00_axi_wvalid,
		S_AXI_WREADY	=> s00_axi_wready,
		S_AXI_BRESP	=> s00_axi_bresp,
		S_AXI_BVALID	=> s00_axi_bvalid,
		S_AXI_BREADY	=> s00_axi_bready,
		S_AXI_ARADDR	=> s00_axi_araddr,
		S_AXI_ARPROT	=> s00_axi_arprot,
		S_AXI_ARVALID	=> s00_axi_arvalid,
		S_AXI_ARREADY	=> s00_axi_arready,
		S_AXI_RDATA	=> s00_axi_rdata,
		S_AXI_RRESP	=> s00_axi_rresp,
		S_AXI_RVALID	=> s00_axi_rvalid,
		S_AXI_RREADY	=> s00_axi_rready
	);

	-- Add user logic here
    process is
    begin
        loop
        s00_axi_aclk<='1';
        wait for 5 ns;
        s00_axi_aclk<='0';
        wait for 5 ns;
        end loop;
    end process;

   process is
    begin
        s00_axi_aresetn <='0';
        wait for 100 ns;
        s00_axi_aresetn <='1';
        wait;
    end process;
    s00_axi_wdata<=(others=>'1');
   process is
    begin
        s00_axi_awvalid <='0';
        s00_axi_wvalid <='0';   
        s00_axi_rready  <='0';
        s00_axi_arvalid <='0';
        wait for 2000 ns;
        s00_axi_awvalid <='1';
        wait for 200 ns;
        s00_axi_wvalid <='1';        
       wait for 200 ns;
        s00_axi_awvalid <='0';
        s00_axi_wvalid <='0';   
        wait;
    end process;    
 	-- User logic ends

end Behavioral;
