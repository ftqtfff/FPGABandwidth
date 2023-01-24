// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Version: 2021.1
// Copyright (C) Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

(* CORE_GENERATION_INFO="ethernet_header_inserter_ethernet_header_inserter,hls_ip_2021_1,{HLS_INPUT_TYPE=cxx,HLS_INPUT_FLOAT=0,HLS_INPUT_FIXED=0,HLS_INPUT_PART=xcu280-fsvh2892-2L-e,HLS_INPUT_CLOCK=3.100000,HLS_INPUT_ARCH=dataflow,HLS_SYN_CLOCK=2.815938,HLS_SYN_LAT=9,HLS_SYN_TPT=1,HLS_SYN_MEM=0,HLS_SYN_DSP=0,HLS_SYN_FF=13960,HLS_SYN_LUT=7480,HLS_VERSION=2021_1}" *)

module ethernet_header_inserter (
// synthesis translate_off
    kernel_block,
// synthesis translate_on
        dataIn_TDATA,
        dataIn_TKEEP,
        dataIn_TSTRB,
        dataIn_TLAST,
        dataOut_TDATA,
        dataOut_TKEEP,
        dataOut_TSTRB,
        dataOut_TLAST,
        arpTableReplay_V_TDATA,
        arpTableRequest_V_TDATA,
        myMacAddress,
        regSubNetMask,
        regDefaultGateway,
        ap_clk,
        ap_rst_n,
        dataIn_TVALID,
        dataIn_TREADY,
        arpTableRequest_V_TVALID,
        arpTableRequest_V_TREADY,
        arpTableReplay_V_TVALID,
        arpTableReplay_V_TREADY,
        dataOut_TVALID,
        dataOut_TREADY
);


// synthesis translate_off
output kernel_block;
// synthesis translate_on
input  [511:0] dataIn_TDATA;
input  [63:0] dataIn_TKEEP;
input  [63:0] dataIn_TSTRB;
input  [0:0] dataIn_TLAST;
output  [511:0] dataOut_TDATA;
output  [63:0] dataOut_TKEEP;
output  [63:0] dataOut_TSTRB;
output  [0:0] dataOut_TLAST;
input  [127:0] arpTableReplay_V_TDATA;
output  [31:0] arpTableRequest_V_TDATA;
input  [47:0] myMacAddress;
input  [31:0] regSubNetMask;
input  [31:0] regDefaultGateway;
input   ap_clk;
input   ap_rst_n;
input   dataIn_TVALID;
output   dataIn_TREADY;
output   arpTableRequest_V_TVALID;
input   arpTableRequest_V_TREADY;
input   arpTableReplay_V_TVALID;
output   arpTableReplay_V_TREADY;
output   dataOut_TVALID;
input   dataOut_TREADY;

 reg    ap_rst_n_inv;
wire    broadcaster_and_mac_request_U0_ap_start;
wire    broadcaster_and_mac_request_U0_ap_done;
wire    broadcaster_and_mac_request_U0_ap_continue;
wire    broadcaster_and_mac_request_U0_ap_idle;
wire    broadcaster_and_mac_request_U0_ap_ready;
wire   [1023:0] broadcaster_and_mac_request_U0_ip_header_out_din;
wire    broadcaster_and_mac_request_U0_ip_header_out_write;
wire   [1023:0] broadcaster_and_mac_request_U0_no_ip_header_out_din;
wire    broadcaster_and_mac_request_U0_no_ip_header_out_write;
wire    broadcaster_and_mac_request_U0_start_out;
wire    broadcaster_and_mac_request_U0_start_write;
wire    broadcaster_and_mac_request_U0_dataIn_TREADY;
wire   [31:0] broadcaster_and_mac_request_U0_arpTableRequest_V_TDATA;
wire    broadcaster_and_mac_request_U0_arpTableRequest_V_TVALID;
wire    compute_and_insert_ip_checksum_U0_ap_start;
wire    compute_and_insert_ip_checksum_U0_ap_done;
wire    compute_and_insert_ip_checksum_U0_ap_continue;
wire    compute_and_insert_ip_checksum_U0_ap_idle;
wire    compute_and_insert_ip_checksum_U0_ap_ready;
wire    compute_and_insert_ip_checksum_U0_ip_header_out_read;
wire   [1023:0] compute_and_insert_ip_checksum_U0_ip_header_checksum_din;
wire    compute_and_insert_ip_checksum_U0_ip_header_checksum_write;
wire    handle_output_U0_ap_start;
wire    handle_output_U0_ap_done;
wire    handle_output_U0_ap_continue;
wire    handle_output_U0_ap_idle;
wire    handle_output_U0_ap_ready;
wire    handle_output_U0_no_ip_header_out_read;
wire    handle_output_U0_ip_header_checksum_read;
wire    handle_output_U0_arpTableReplay_V_TREADY;
wire   [511:0] handle_output_U0_dataOut_TDATA;
wire    handle_output_U0_dataOut_TVALID;
wire   [63:0] handle_output_U0_dataOut_TKEEP;
wire   [63:0] handle_output_U0_dataOut_TSTRB;
wire   [0:0] handle_output_U0_dataOut_TLAST;
wire    ip_header_out_full_n;
wire   [1023:0] ip_header_out_dout;
wire    ip_header_out_empty_n;
wire    no_ip_header_out_full_n;
wire   [1023:0] no_ip_header_out_dout;
wire    no_ip_header_out_empty_n;
wire    ip_header_checksum_full_n;
wire   [1023:0] ip_header_checksum_dout;
wire    ip_header_checksum_empty_n;
wire   [0:0] start_for_compute_and_insert_ip_checksum_U0_din;
wire    start_for_compute_and_insert_ip_checksum_U0_full_n;
wire   [0:0] start_for_compute_and_insert_ip_checksum_U0_dout;
wire    start_for_compute_and_insert_ip_checksum_U0_empty_n;

ethernet_header_inserter_broadcaster_and_mac_request broadcaster_and_mac_request_U0(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst_n_inv),
    .ap_start(broadcaster_and_mac_request_U0_ap_start),
    .start_full_n(start_for_compute_and_insert_ip_checksum_U0_full_n),
    .ap_done(broadcaster_and_mac_request_U0_ap_done),
    .ap_continue(broadcaster_and_mac_request_U0_ap_continue),
    .ap_idle(broadcaster_and_mac_request_U0_ap_idle),
    .ap_ready(broadcaster_and_mac_request_U0_ap_ready),
    .dataIn_TVALID(dataIn_TVALID),
    .arpTableRequest_V_TREADY(arpTableRequest_V_TREADY),
    .ip_header_out_din(broadcaster_and_mac_request_U0_ip_header_out_din),
    .ip_header_out_full_n(ip_header_out_full_n),
    .ip_header_out_write(broadcaster_and_mac_request_U0_ip_header_out_write),
    .no_ip_header_out_din(broadcaster_and_mac_request_U0_no_ip_header_out_din),
    .no_ip_header_out_full_n(no_ip_header_out_full_n),
    .no_ip_header_out_write(broadcaster_and_mac_request_U0_no_ip_header_out_write),
    .start_out(broadcaster_and_mac_request_U0_start_out),
    .start_write(broadcaster_and_mac_request_U0_start_write),
    .dataIn_TDATA(dataIn_TDATA),
    .dataIn_TREADY(broadcaster_and_mac_request_U0_dataIn_TREADY),
    .dataIn_TKEEP(dataIn_TKEEP),
    .dataIn_TSTRB(dataIn_TSTRB),
    .dataIn_TLAST(dataIn_TLAST),
    .arpTableRequest_V_TDATA(broadcaster_and_mac_request_U0_arpTableRequest_V_TDATA),
    .arpTableRequest_V_TVALID(broadcaster_and_mac_request_U0_arpTableRequest_V_TVALID),
    .regSubNetMask(regSubNetMask),
    .regDefaultGateway(regDefaultGateway)
);

ethernet_header_inserter_compute_and_insert_ip_checksum compute_and_insert_ip_checksum_U0(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst_n_inv),
    .ap_start(compute_and_insert_ip_checksum_U0_ap_start),
    .ap_done(compute_and_insert_ip_checksum_U0_ap_done),
    .ap_continue(compute_and_insert_ip_checksum_U0_ap_continue),
    .ap_idle(compute_and_insert_ip_checksum_U0_ap_idle),
    .ap_ready(compute_and_insert_ip_checksum_U0_ap_ready),
    .ip_header_out_dout(ip_header_out_dout),
    .ip_header_out_empty_n(ip_header_out_empty_n),
    .ip_header_out_read(compute_and_insert_ip_checksum_U0_ip_header_out_read),
    .ip_header_checksum_din(compute_and_insert_ip_checksum_U0_ip_header_checksum_din),
    .ip_header_checksum_full_n(ip_header_checksum_full_n),
    .ip_header_checksum_write(compute_and_insert_ip_checksum_U0_ip_header_checksum_write)
);

ethernet_header_inserter_handle_output handle_output_U0(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst_n_inv),
    .ap_start(handle_output_U0_ap_start),
    .ap_done(handle_output_U0_ap_done),
    .ap_continue(handle_output_U0_ap_continue),
    .ap_idle(handle_output_U0_ap_idle),
    .ap_ready(handle_output_U0_ap_ready),
    .no_ip_header_out_dout(no_ip_header_out_dout),
    .no_ip_header_out_empty_n(no_ip_header_out_empty_n),
    .no_ip_header_out_read(handle_output_U0_no_ip_header_out_read),
    .ip_header_checksum_dout(ip_header_checksum_dout),
    .ip_header_checksum_empty_n(ip_header_checksum_empty_n),
    .ip_header_checksum_read(handle_output_U0_ip_header_checksum_read),
    .arpTableReplay_V_TVALID(arpTableReplay_V_TVALID),
    .dataOut_TREADY(dataOut_TREADY),
    .arpTableReplay_V_TDATA(arpTableReplay_V_TDATA),
    .arpTableReplay_V_TREADY(handle_output_U0_arpTableReplay_V_TREADY),
    .myMacAddress(myMacAddress),
    .dataOut_TDATA(handle_output_U0_dataOut_TDATA),
    .dataOut_TVALID(handle_output_U0_dataOut_TVALID),
    .dataOut_TKEEP(handle_output_U0_dataOut_TKEEP),
    .dataOut_TSTRB(handle_output_U0_dataOut_TSTRB),
    .dataOut_TLAST(handle_output_U0_dataOut_TLAST)
);

ethernet_header_inserter_fifo_w1024_d16_A ip_header_out_U(
    .clk(ap_clk),
    .reset(ap_rst_n_inv),
    .if_read_ce(1'b1),
    .if_write_ce(1'b1),
    .if_din(broadcaster_and_mac_request_U0_ip_header_out_din),
    .if_full_n(ip_header_out_full_n),
    .if_write(broadcaster_and_mac_request_U0_ip_header_out_write),
    .if_dout(ip_header_out_dout),
    .if_empty_n(ip_header_out_empty_n),
    .if_read(compute_and_insert_ip_checksum_U0_ip_header_out_read)
);

ethernet_header_inserter_fifo_w1024_d16_A no_ip_header_out_U(
    .clk(ap_clk),
    .reset(ap_rst_n_inv),
    .if_read_ce(1'b1),
    .if_write_ce(1'b1),
    .if_din(broadcaster_and_mac_request_U0_no_ip_header_out_din),
    .if_full_n(no_ip_header_out_full_n),
    .if_write(broadcaster_and_mac_request_U0_no_ip_header_out_write),
    .if_dout(no_ip_header_out_dout),
    .if_empty_n(no_ip_header_out_empty_n),
    .if_read(handle_output_U0_no_ip_header_out_read)
);

ethernet_header_inserter_fifo_w1024_d16_A ip_header_checksum_U(
    .clk(ap_clk),
    .reset(ap_rst_n_inv),
    .if_read_ce(1'b1),
    .if_write_ce(1'b1),
    .if_din(compute_and_insert_ip_checksum_U0_ip_header_checksum_din),
    .if_full_n(ip_header_checksum_full_n),
    .if_write(compute_and_insert_ip_checksum_U0_ip_header_checksum_write),
    .if_dout(ip_header_checksum_dout),
    .if_empty_n(ip_header_checksum_empty_n),
    .if_read(handle_output_U0_ip_header_checksum_read)
);

ethernet_header_inserter_start_for_compute_and_insert_ip_checksum_U0 start_for_compute_and_insert_ip_checksum_U0_U(
    .clk(ap_clk),
    .reset(ap_rst_n_inv),
    .if_read_ce(1'b1),
    .if_write_ce(1'b1),
    .if_din(start_for_compute_and_insert_ip_checksum_U0_din),
    .if_full_n(start_for_compute_and_insert_ip_checksum_U0_full_n),
    .if_write(broadcaster_and_mac_request_U0_start_write),
    .if_dout(start_for_compute_and_insert_ip_checksum_U0_dout),
    .if_empty_n(start_for_compute_and_insert_ip_checksum_U0_empty_n),
    .if_read(compute_and_insert_ip_checksum_U0_ap_ready)
);

always @ (*) begin
    ap_rst_n_inv = ~ap_rst_n;
end

assign arpTableReplay_V_TREADY = handle_output_U0_arpTableReplay_V_TREADY;

assign arpTableRequest_V_TDATA = broadcaster_and_mac_request_U0_arpTableRequest_V_TDATA;

assign arpTableRequest_V_TVALID = broadcaster_and_mac_request_U0_arpTableRequest_V_TVALID;

assign broadcaster_and_mac_request_U0_ap_continue = 1'b1;

assign broadcaster_and_mac_request_U0_ap_start = 1'b1;

assign compute_and_insert_ip_checksum_U0_ap_continue = 1'b1;

assign compute_and_insert_ip_checksum_U0_ap_start = start_for_compute_and_insert_ip_checksum_U0_empty_n;

assign dataIn_TREADY = broadcaster_and_mac_request_U0_dataIn_TREADY;

assign dataOut_TDATA = handle_output_U0_dataOut_TDATA;

assign dataOut_TKEEP = handle_output_U0_dataOut_TKEEP;

assign dataOut_TLAST = handle_output_U0_dataOut_TLAST;

assign dataOut_TSTRB = handle_output_U0_dataOut_TSTRB;

assign dataOut_TVALID = handle_output_U0_dataOut_TVALID;

assign handle_output_U0_ap_continue = 1'b1;

assign handle_output_U0_ap_start = 1'b1;

assign start_for_compute_and_insert_ip_checksum_U0_din = 1'b1;


// synthesis translate_off
`include "ethernet_header_inserter_hls_deadlock_detector.vh"
`include "ethernet_header_inserter_hls_deadlock_kernel_monitor_top.vh"
// synthesis translate_on

endmodule //ethernet_header_inserter

