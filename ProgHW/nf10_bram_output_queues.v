`uselib lib=unisims_ver
`uselib lib=proc_common_v3_00_a
`uselib lib=nf10_proc_common_v1_00_a


module nf10_bram_output_queues
#(
  parameter C_FAMILY              = "virtex5",
  parameter C_S_AXI_DATA_WIDTH    = 32,          
  parameter C_S_AXI_ADDR_WIDTH    = 32,          
  parameter C_USE_WSTRB           = 0,
  parameter C_DPHASE_TIMEOUT      = 0,
  parameter C_BASEADDR            = 32'hFFFFFFFF,
  parameter C_HIGHADDR            = 32'h00000000,
  parameter C_S_AXI_ACLK_FREQ_HZ  = 100,
  parameter C_M_AXIS_DATA_WIDTH	  = 256,
  parameter C_S_AXIS_DATA_WIDTH	  = 256,
  parameter C_M_AXIS_TUSER_WIDTH  = 128,
  parameter C_S_AXIS_TUSER_WIDTH  = 128,
  parameter NUM_QUEUES=5  //4 Ethernet + 1 DMA
)
(
  // Slave AXI Ports (includes both read ports and write ports)
  input      [C_S_AXI_ADDR_WIDTH-1 : 0]     S_AXI_AWADDR,
  input                                     S_AXI_AWVALID,
  input      [C_S_AXI_DATA_WIDTH-1 : 0]     S_AXI_WDATA,  //write
  input      [C_S_AXI_DATA_WIDTH/8-1 : 0]   S_AXI_WSTRB,
  input                                     S_AXI_WVALID,
  input                                     S_AXI_BREADY,
  input      [C_S_AXI_ADDR_WIDTH-1 : 0]     S_AXI_ARADDR,
  input                                     S_AXI_ARVALID,
  input                                     S_AXI_RREADY,
  output                                    S_AXI_ARREADY,
  output     [C_S_AXI_DATA_WIDTH-1 : 0]     S_AXI_RDATA,  //read
  output     [1 : 0]                        S_AXI_RRESP,
  output                                    S_AXI_RVALID,
  output                                    S_AXI_WREADY,
  output     [1 :0]                         S_AXI_BRESP,
  output                                    S_AXI_BVALID,
  output                                    S_AXI_AWREADY,

  // Slave Stream Ports (interface to data path)
  input [C_S_AXIS_DATA_WIDTH - 1:0] s_axis_tdata,
  input [((C_S_AXIS_DATA_WIDTH / 8)) - 1:0] s_axis_tstrb,
  input [C_S_AXIS_TUSER_WIDTH - 1:0] s_axis_tuser,
  input s_axis_tvalid,
  output s_axis_tready,
  input s_axis_tlast,

  // Master Stream Ports (interface to TX queues)
  output [C_M_AXIS_DATA_WIDTH - 1:0] m_axis_tdata_0,
  output [((C_M_AXIS_DATA_WIDTH / 8)) - 1:0] m_axis_tstrb_0,
  output [C_M_AXIS_TUSER_WIDTH-1:0] m_axis_tuser_0,
  output  m_axis_tvalid_0,
  input m_axis_tready_0,
  output  m_axis_tlast_0,

  output [C_M_AXIS_DATA_WIDTH - 1:0] m_axis_tdata_1,
  output [((C_M_AXIS_DATA_WIDTH / 8)) - 1:0] m_axis_tstrb_1,
  output [C_M_AXIS_TUSER_WIDTH-1:0] m_axis_tuser_1,
  output  m_axis_tvalid_1,
  input m_axis_tready_1,
  output  m_axis_tlast_1,

  output [C_M_AXIS_DATA_WIDTH - 1:0] m_axis_tdata_2,
  output [((C_M_AXIS_DATA_WIDTH / 8)) - 1:0] m_axis_tstrb_2,
  output [C_M_AXIS_TUSER_WIDTH-1:0] m_axis_tuser_2,
  output  m_axis_tvalid_2,
  input m_axis_tready_2,
  output  m_axis_tlast_2,

  output [C_M_AXIS_DATA_WIDTH - 1:0] m_axis_tdata_3,
  output [((C_M_AXIS_DATA_WIDTH / 8)) - 1:0] m_axis_tstrb_3,
  output [C_M_AXIS_TUSER_WIDTH-1:0] m_axis_tuser_3,
  output  m_axis_tvalid_3,
  input m_axis_tready_3,
  output  m_axis_tlast_3,

  output [C_M_AXIS_DATA_WIDTH - 1:0] m_axis_tdata_4,
  output [((C_M_AXIS_DATA_WIDTH / 8)) - 1:0] m_axis_tstrb_4,
  output [C_M_AXIS_TUSER_WIDTH-1:0] m_axis_tuser_4,
  output  m_axis_tvalid_4,
  input m_axis_tready_4,
  output  m_axis_tlast_4,

 // misc
  input axi_aclk,
  input axi_resetn
);

  //tfang
  localparam NUM_RW_REGS       = 1 + 1; // 1(IPD_value) + 1(original)  
  localparam NUM_RO_REGS       = 5 + 40; // 5(rcv_timer_record) + 40(original)
  localparam TIME_DIVISION_RATIO = 125; // target unit( 1 us ) / src unit( (1/125MHz)s ) == 125

  // -- Signals

  wire                                            Bus2IP_Clk;
  wire                                            Bus2IP_Resetn;
  wire     [C_S_AXI_ADDR_WIDTH-1 : 0]             Bus2IP_Addr;
  wire     [0:0]                                  Bus2IP_CS;
  wire                                            Bus2IP_RNW;
  wire     [C_S_AXI_DATA_WIDTH-1 : 0]             Bus2IP_Data;
  wire     [C_S_AXI_DATA_WIDTH/8-1 : 0]           Bus2IP_BE;
  wire     [C_S_AXI_DATA_WIDTH-1 : 0]             IP2Bus_Data;
  wire                                            IP2Bus_RdAck;
  wire                                            IP2Bus_WrAck;
  wire                                            IP2Bus_Error;
  
  wire     [NUM_RW_REGS*C_S_AXI_DATA_WIDTH-1 : 0] rw_regs;  //each register has 32 bits
  wire     [NUM_RO_REGS*C_S_AXI_DATA_WIDTH-1 : 0] ro_regs;
  
  wire     [C_S_AXI_DATA_WIDTH-1 : 0]             bytes_stored;
  reg      [C_S_AXI_DATA_WIDTH-1 : 0]             bytes_stored_cntr [NUM_QUEUES-1:0];

  wire     [NUM_QUEUES-1:0]                       pkt_stored;
  reg      [C_S_AXI_DATA_WIDTH-1 : 0]             pkt_stored_cntr [NUM_QUEUES-1:0];

  wire                                            pkt_removed_0;
  wire                                            pkt_removed_1;
  wire                                            pkt_removed_2;
  wire                                            pkt_removed_3;
  wire                                            pkt_removed_4;
  reg      [C_S_AXI_DATA_WIDTH-1 : 0]             pkt_removed_cntr [NUM_QUEUES-1:0];  //cntr stands for counter, one bit to mark a byte of a channel?

  wire     [C_S_AXI_DATA_WIDTH-1 : 0]             bytes_removed_0;
  wire     [C_S_AXI_DATA_WIDTH-1 : 0]             bytes_removed_1;
  wire     [C_S_AXI_DATA_WIDTH-1 : 0]             bytes_removed_2;
  wire     [C_S_AXI_DATA_WIDTH-1 : 0]             bytes_removed_3;
  wire     [C_S_AXI_DATA_WIDTH-1 : 0]             bytes_removed_4; 
  reg      [C_S_AXI_DATA_WIDTH-1 : 0]             bytes_removed_cntr [NUM_QUEUES-1:0];

  reg      [C_S_AXI_DATA_WIDTH-1 : 0]             pkt_in_queue_cntr [NUM_QUEUES-1:0];
  reg      [C_S_AXI_DATA_WIDTH-1 : 0]             bytes_in_queue_cntr [NUM_QUEUES-1:0];

  wire     [NUM_QUEUES-1:0]                       pkt_dropped;
  reg      [C_S_AXI_DATA_WIDTH-1 : 0]             pkt_dropped_cntr [NUM_QUEUES-1:0];

  wire     [C_S_AXI_DATA_WIDTH-1 : 0]             bytes_dropped;
  reg      [C_S_AXI_DATA_WIDTH-1 : 0]             bytes_dropped_cntr [NUM_QUEUES-1:0];
  
  //--------- tfang -------------
  // RW registers:
  wire [C_S_AXI_DATA_WIDTH-1 : 0] IPD_value;

  // RO registers:
  localparam NUM_RCV_TIME = 8;
  reg [C_S_AXI_DATA_WIDTH-1 : 0] rcv_timer_record [NUM_RCV_TIME-1:0];
  reg [2:0] rcv_timer_index;
  
  reg [C_S_AXI_DATA_WIDTH-1 : 0] clk_conversion_cnrt;
  reg utimer_clk;
		
  reg [C_S_AXI_DATA_WIDTH-1:0] rcv_timer;
  
  wire						  rst_cntrs;
  integer i;
 
  // -- AXILITE IPIF where this module acts as a AXI slave
  axi_lite_ipif_1bar #
  (
    .C_S_AXI_DATA_WIDTH (C_S_AXI_DATA_WIDTH),
    .C_S_AXI_ADDR_WIDTH (C_S_AXI_ADDR_WIDTH),
	.C_USE_WSTRB        (C_USE_WSTRB),
	.C_DPHASE_TIMEOUT   (C_DPHASE_TIMEOUT),
    .C_BAR0_BASEADDR    (C_BASEADDR),
    .C_BAR0_HIGHADDR    (C_HIGHADDR)
  ) axi_lite_ipif_inst
  (
    .S_AXI_ACLK          ( axi_aclk       ),
    .S_AXI_ARESETN       ( axi_resetn     ),
    .S_AXI_AWADDR        ( S_AXI_AWADDR   ),
    .S_AXI_AWVALID       ( S_AXI_AWVALID  ),
    .S_AXI_WDATA         ( S_AXI_WDATA    ),
    .S_AXI_WSTRB         ( S_AXI_WSTRB    ),
    .S_AXI_WVALID        ( S_AXI_WVALID   ),
    .S_AXI_BREADY        ( S_AXI_BREADY   ),
    .S_AXI_ARADDR        ( S_AXI_ARADDR   ),
    .S_AXI_ARVALID       ( S_AXI_ARVALID  ),
    .S_AXI_RREADY        ( S_AXI_RREADY   ),
    .S_AXI_ARREADY       ( S_AXI_ARREADY  ),
    .S_AXI_RDATA         ( S_AXI_RDATA    ),
    .S_AXI_RRESP         ( S_AXI_RRESP    ),
    .S_AXI_RVALID        ( S_AXI_RVALID   ),
    .S_AXI_WREADY        ( S_AXI_WREADY   ),
    .S_AXI_BRESP         ( S_AXI_BRESP    ),
    .S_AXI_BVALID        ( S_AXI_BVALID   ),
    .S_AXI_AWREADY       ( S_AXI_AWREADY  ),
	
	// Controls to the IP/IPIF modules
    .Bus2IP_Clk          ( Bus2IP_Clk     ),
    .Bus2IP_Resetn       ( Bus2IP_Resetn  ),
    .Bus2IP_Addr         ( Bus2IP_Addr    ),
    .Bus2IP_RNW          ( Bus2IP_RNW     ),
    .Bus2IP_BE           ( Bus2IP_BE      ),
    .Bus2IP_CS           ( Bus2IP_CS      ),
    .Bus2IP_Data         ( Bus2IP_Data    ),
    .IP2Bus_Data         ( IP2Bus_Data    ),
    .IP2Bus_WrAck        ( IP2Bus_WrAck   ),
    .IP2Bus_RdAck        ( IP2Bus_RdAck   ),
    .IP2Bus_Error        ( IP2Bus_Error   )
  );
  
  // -- IPIF REGS
  ipif_regs #
  (
    .C_S_AXI_DATA_WIDTH (C_S_AXI_DATA_WIDTH),          
    .C_S_AXI_ADDR_WIDTH (C_S_AXI_ADDR_WIDTH),   
    .NUM_RW_REGS        (NUM_RW_REGS),
    .NUM_RO_REGS        (NUM_RO_REGS)
  ) ipif_regs_inst
  (   
    .Bus2IP_Clk     ( Bus2IP_Clk     ),
    .Bus2IP_Resetn  ( Bus2IP_Resetn  ), 
    .Bus2IP_Addr    ( Bus2IP_Addr    ),
    .Bus2IP_CS      ( Bus2IP_CS[0]   ),
    .Bus2IP_RNW     ( Bus2IP_RNW     ),
    .Bus2IP_Data    ( Bus2IP_Data    ),
    .Bus2IP_BE      ( Bus2IP_BE      ),
    .IP2Bus_Data    ( IP2Bus_Data    ),
    .IP2Bus_RdAck   ( IP2Bus_RdAck   ),
    .IP2Bus_WrAck   ( IP2Bus_WrAck   ),
    .IP2Bus_Error   ( IP2Bus_Error   ),
	
	 .rw_regs        ( rw_regs ),  //writte by software and read by both HW/SW
    .ro_regs        ( ro_regs )  //written by hardware and read by software 
  );
  
  
  // -- Register assignments
  assign rst_cntrs = rw_regs[0];
 
  assign ro_regs[(NUM_RO_REGS - NUM_RCV_TIME)*C_S_AXI_DATA_WIDTH-1 : 0] = {
                    bytes_in_queue_cntr[4],   //output queue registers, each one is 32-bit
                    pkt_in_queue_cntr[4],
		    bytes_dropped_cntr[4],
		    pkt_dropped_cntr[4],
		    bytes_removed_cntr[4],
		    pkt_removed_cntr[4],
		    bytes_stored_cntr[4],
		    pkt_stored_cntr[4],
                    bytes_in_queue_cntr[3],
                    pkt_in_queue_cntr[3],
		    bytes_dropped_cntr[3],
		    pkt_dropped_cntr[3],
		    bytes_removed_cntr[3],
		    pkt_removed_cntr[3],
		    bytes_stored_cntr[3],
		    pkt_stored_cntr[3],
                    bytes_in_queue_cntr[2],
                    pkt_in_queue_cntr[2],
		    bytes_dropped_cntr[2],
		    pkt_dropped_cntr[2],
		    bytes_removed_cntr[2],
		    pkt_removed_cntr[2],
		    bytes_stored_cntr[2],
		    pkt_stored_cntr[2],
                    bytes_in_queue_cntr[1],
                    pkt_in_queue_cntr[1],
		    bytes_dropped_cntr[1],
		    pkt_dropped_cntr[1],
		    bytes_removed_cntr[1],
		    pkt_removed_cntr[1],
		    bytes_stored_cntr[1],
		    pkt_stored_cntr[1],
		    bytes_in_queue_cntr[0],
		    pkt_in_queue_cntr[0],		    
		    bytes_dropped_cntr[0],
		    pkt_dropped_cntr[0],
		    bytes_removed_cntr[0],
		    pkt_removed_cntr[0],
		    bytes_stored_cntr[0],
		    pkt_stored_cntr[0]};
			 
  // tfang additional registers  
  assign IPD_value = rw_regs[NUM_RW_REGS*C_S_AXI_DATA_WIDTH-1 : (NUM_RW_REGS-1)*C_S_AXI_DATA_WIDTH]; 
  
  // tfang generate ro registers
  genvar rcvIndex; 
  generate 
   for(rcvIndex = 0; rcvIndex < NUM_RCV_TIME; rcvIndex = rcvIndex + 1) begin
	   assign ro_regs[(NUM_RO_REGS-rcvIndex)*C_S_AXI_DATA_WIDTH-1 : (NUM_RO_REGS-rcvIndex-1)*C_S_AXI_DATA_WIDTH] = rcv_timer_record[NUM_RCV_TIME - 1 - rcvIndex];
	end					  
  endgenerate			 
  
  // -- Learning CAM Switch
  bram_output_queues #
  (
    .C_M_AXIS_DATA_WIDTH  (C_M_AXIS_DATA_WIDTH),
    .C_S_AXIS_DATA_WIDTH  (C_S_AXIS_DATA_WIDTH),
    .C_M_AXIS_TUSER_WIDTH (C_M_AXIS_TUSER_WIDTH),
    .C_S_AXIS_TUSER_WIDTH (C_S_AXIS_TUSER_WIDTH),
    .NUM_QUEUES    (NUM_QUEUES)
   ) bram_output_queues
  (
    // Global Ports
    .axi_aclk      (axi_aclk),
    .axi_resetn    (axi_resetn),
	 
	 //tfang
	 .utimer_clk     (utimer_clk),

    // Slave Stream Ports (interface to data path)
    .s_axis_tdata  (s_axis_tdata),
    .s_axis_tstrb  (s_axis_tstrb),
    .s_axis_tuser  (s_axis_tuser),
    .s_axis_tvalid (s_axis_tvalid),
    .s_axis_tready (s_axis_tready),
    .s_axis_tlast  (s_axis_tlast),

    // Master Stream Ports (interface to TX queues)
    .m_axis_tdata_0 (m_axis_tdata_0),
    .m_axis_tstrb_0 (m_axis_tstrb_0),
    .m_axis_tuser_0 (m_axis_tuser_0),
    .m_axis_tvalid_0(m_axis_tvalid_0),
    .m_axis_tready_0(m_axis_tready_0),
    .m_axis_tlast_0 (m_axis_tlast_0),

    .m_axis_tdata_1 (m_axis_tdata_1),
    .m_axis_tstrb_1 (m_axis_tstrb_1),
    .m_axis_tuser_1 (m_axis_tuser_1),
    .m_axis_tvalid_1(m_axis_tvalid_1),
    .m_axis_tready_1(m_axis_tready_1),
    .m_axis_tlast_1 (m_axis_tlast_1),

    .m_axis_tdata_2 (m_axis_tdata_2),
    .m_axis_tstrb_2 (m_axis_tstrb_2),
    .m_axis_tuser_2 (m_axis_tuser_2),
    .m_axis_tvalid_2(m_axis_tvalid_2),
    .m_axis_tready_2(m_axis_tready_2),
    .m_axis_tlast_2 (m_axis_tlast_2),

    .m_axis_tdata_3 (m_axis_tdata_3),
    .m_axis_tstrb_3 (m_axis_tstrb_3),
    .m_axis_tuser_3 (m_axis_tuser_3),
    .m_axis_tvalid_3(m_axis_tvalid_3),
    .m_axis_tready_3(m_axis_tready_3),
    .m_axis_tlast_3 (m_axis_tlast_3),

    .m_axis_tdata_4 (m_axis_tdata_4),
    .m_axis_tstrb_4 (m_axis_tstrb_4),
    .m_axis_tuser_4 (m_axis_tuser_4),
    .m_axis_tvalid_4(m_axis_tvalid_4),
    .m_axis_tready_4(m_axis_tready_4),
    .m_axis_tlast_4 (m_axis_tlast_4),


    .bytes_stored   (bytes_stored),
    .pkt_stored     (pkt_stored),
  
    .pkt_removed_0  (pkt_removed_0),
    .pkt_removed_1  (pkt_removed_1),
    .pkt_removed_2  (pkt_removed_2),
    .pkt_removed_3  (pkt_removed_3),
    .pkt_removed_4  (pkt_removed_4),

    .bytes_removed_0  (bytes_removed_0),
    .bytes_removed_1  (bytes_removed_1),
    .bytes_removed_2  (bytes_removed_2),
    .bytes_removed_3  (bytes_removed_3),
    .bytes_removed_4  (bytes_removed_4),

    .pkt_dropped    (pkt_dropped),
    .bytes_dropped  (bytes_dropped),
	 .IPD_value   (IPD_value)
  );
    
	 //---------------------------------------------------------------------
  	 //tfang create 1us timer
	 always @(posedge axi_aclk) begin
	  if (~axi_resetn) begin
        clk_conversion_cnrt <= 0;
		  utimer_clk <= 0;
	  end
	  else if ( clk_conversion_cnrt == (TIME_DIVISION_RATIO - 1) ) begin
		  clk_conversion_cnrt <= 0;
		  utimer_clk <= 1;
	  end	  
	  else begin
	     clk_conversion_cnrt <= clk_conversion_cnrt + 1;
		  utimer_clk <= 0;
	  end
	 end
	 
	 //tfang update rcv_timer
    always @(posedge axi_aclk) begin
	    if(~axi_resetn) begin
		    rcv_timer <= 0;
		 end
		 else if(utimer_clk) begin
		    rcv_timer <= rcv_timer + 1;
		 end
		 else begin
		     rcv_timer <= rcv_timer;
		 end    
	 end
	 
	 always @(posedge axi_aclk) begin
	    if(~axi_resetn) begin
		    rcv_timer_index <= 0;
		 end
		 else if(pkt_stored[3]) begin //nf3
		    rcv_timer_record[rcv_timer_index] <= rcv_timer;
		    rcv_timer_index <= rcv_timer_index + 1;
       end
		 else begin
		    rcv_timer_record[rcv_timer_index] <= rcv_timer_record[rcv_timer_index];
		    rcv_timer_index <= rcv_timer_index;
		 end 
	 end
    //---------------------------------------------------------------------

		
  
  // Output Queues counters
  always @ (posedge axi_aclk) begin
    for(i=0;i<NUM_QUEUES;i=i+1) begin
	     pkt_in_queue_cntr[i] <= pkt_stored_cntr[i] - pkt_removed_cntr[i];   //each var is 32-bit, stored is the absolute store #pkts,  removed is read out
	     bytes_in_queue_cntr[i] <= bytes_stored_cntr[i] - bytes_removed_cntr[i];  //each var is 32-bit
    end
    if (~axi_resetn) begin  //reset all axi-accessible registers
    	for(i=0;i<NUM_QUEUES;i=i+1) begin
		      bytes_stored_cntr[i]  <= {C_S_AXI_DATA_WIDTH{1'b0}};
	  	      pkt_stored_cntr[i] <= {C_S_AXI_DATA_WIDTH{1'b0}};
          	pkt_removed_cntr[i]  <= {C_S_AXI_DATA_WIDTH{1'b0}};
          	bytes_removed_cntr[i]  <= {C_S_AXI_DATA_WIDTH{1'b0}};
          	pkt_dropped_cntr[i] <= {C_S_AXI_DATA_WIDTH{1'b0}};
          	bytes_dropped_cntr[i] <= {C_S_AXI_DATA_WIDTH{1'b0}};
	   end
    end
    else if (rst_cntrs) begin //reset counters
         for(i=0;i<NUM_QUEUES;i=i+1) begin
                bytes_stored_cntr[i]  <= {C_S_AXI_DATA_WIDTH{1'b0}};
                pkt_stored_cntr[i] <= {C_S_AXI_DATA_WIDTH{1'b0}};
                pkt_removed_cntr[i]  <= {C_S_AXI_DATA_WIDTH{1'b0}};
                bytes_removed_cntr[i]  <= {C_S_AXI_DATA_WIDTH{1'b0}};
                pkt_dropped_cntr[i] <= {C_S_AXI_DATA_WIDTH{1'b0}};
                bytes_dropped_cntr[i] <= {C_S_AXI_DATA_WIDTH{1'b0}};
         end
    end
    else begin
		 for(i=0;i<NUM_QUEUES;i=i+1) begin
			if(pkt_stored[i]) begin
				pkt_stored_cntr[i]    <= pkt_stored_cntr[i] + 1;
				bytes_stored_cntr[i]  <= bytes_stored_cntr[i] + bytes_stored;
			end
			if(pkt_dropped[i]) begin
				pkt_dropped_cntr[i]   <= pkt_dropped_cntr[i] + 1;
				bytes_dropped_cntr[i] <= bytes_dropped_cntr[i] + bytes_dropped;
			end
		 end //for
	    if(pkt_removed_0) begin
		  	 pkt_removed_cntr[0]  <= pkt_removed_cntr[0] + 1;
			 bytes_removed_cntr[0]  <= bytes_removed_cntr[0] + bytes_removed_0;
		 end
		 if(pkt_removed_1) begin
			 pkt_removed_cntr[1]  <= pkt_removed_cntr[1] + 1;
			 bytes_removed_cntr[1]  <= bytes_removed_cntr[1] + bytes_removed_1;
		 end
		 if(pkt_removed_2) begin
			 pkt_removed_cntr[2]  <= pkt_removed_cntr[2] + 1;
			 bytes_removed_cntr[2]  <= bytes_removed_cntr[2] + bytes_removed_2;
		 end
		 if(pkt_removed_3) begin
			 pkt_removed_cntr[3]  <= pkt_removed_cntr[3] + 1;
			 bytes_removed_cntr[3]  <= bytes_removed_cntr[3] + bytes_removed_3;
		 end
		 if(pkt_removed_4) begin
			 pkt_removed_cntr[4]  <= pkt_removed_cntr[4] + 1;
			 bytes_removed_cntr[4]  <= bytes_removed_cntr[4] + bytes_removed_4;
		 end

	 end
   end
  
endmodule

