#!/usr/bin/env python

from NFTest import *
import sys
import os
from scapy.layers.all import Ether, IP, TCP
from reg_defines_reference_nic_nf1_cml import *

conn = ('../connections/conn', [])
nftest_init(sim_loop = ['nf0', 'nf1', 'nf2', 'nf3'], hw_config = [conn])

if isHW():
     # asserting the reset_counter to 1 for clearing the registers
     hwRegLib.regwrite(XPAR_NF10_INPUT_ARBITER_0_RESET_CNTRS(), 0x1) 
     hwRegLib.regwrite(XPAR_NF10_BRAM_OUTPUT_QUEUES_0_RESET_CNTRS(), 0x1)
    # asserting the reset_counter to 0 for enable the counters to increment
     hwRegLib.regwrite(XPAR_NF10_INPUT_ARBITER_0_RESET_CNTRS(), 0x0)
     hwRegLib.regwrite(XPAR_NF10_BRAM_OUTPUT_QUEUES_0_RESET_CNTRS(), 0x0)

     #Set IPD
     hwRegLib.regwrite(XPAR_NF10_BRAM_OUTPUT_QUEUES_0_IPD_VALUE(), 0x5)
     

nftest_start()

# set parameters
# DA == dest MAC addr
# SA == src MAC addr
SA = "aa:bb:cc:dd:ee:ff"
TTL = 64
DST_IP = "192.168.1.1"
SRC_IP = "192.168.0.1"
nextHopMAC = "dd:55:dd:66:dd:77"
if isHW(): #HW test or SIM test
    NUM_PKTS = 8
else:
    NUM_PKTS = 5

pkts = []

print "Sending now: "
totalPktLengths = [0,0,0,0]
# send NUM_PKTS from ports nf2c0...nf2c3
# connections on NF1-CML are :  nf0 : nf3
#                               nf1 : nf2
for i in range(NUM_PKTS):
    sys.stdout.write('\r'+str(i))
    sys.stdout.flush()
    if isHW():
        for port in range(4):
            DA = "00:ca:fe:00:00:%02x"%port
            pkt = make_IP_pkt(dst_MAC=DA, src_MAC=SA, dst_IP=DST_IP,
                             src_IP=SRC_IP, TTL=TTL,
                             pkt_len=1514)
            totalPktLengths[port] += len(pkt)

            nftest_send_dma('nf' + str(port), pkt)
            if port == 0:
                nftest_expect_dma('nf3', pkt)
            elif port == 1:
                nftest_expect_dma('nf2', pkt)
            elif port == 2:
                nftest_expect_dma('nf1', pkt)
            else:
                nftest_expect_dma('nf0', pkt)
    
    else:
        DA = "00:ca:fe:00:00:00"
        pkt = make_IP_pkt(dst_MAC=DA, src_MAC=SA, dst_IP=DST_IP,
                             src_IP=SRC_IP, TTL=TTL,
                             pkt_len=1514) 
        pkt.time = (i*(1e-8))
        pkts.append(pkt)

if not isHW():
    nftest_send_phy('nf0', pkts) 
    nftest_expect_dma('nf0', pkts) 

print ""
# iterate through each register by reading the address
for i in range(0x76600000, 0x76600129, 4):
	hwRegLib.regread_expect(i, 0x31)
mres=[]
nftest_finish(mres)

