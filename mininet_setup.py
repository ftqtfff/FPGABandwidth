#!/usr/bin/env python
from mininet.topo import Topo
from mininet.net import Mininet
from mininet.node import Node, Controller
from mininet.cli import CLI
from mininet.log import setLogLevel, info
from mininet.link import Intf
from mininet.link import Link, TCIntf, TCLink
import time

def bassNet():
    info('*** Adding controller\n')
    net = Mininet( controller=Controller, link=TCLink )

    info('*** Adding cross traffic hosts\n' )
    h1 = net.addHost('h1', ip = "10.0.1.1/24", mac="00:00:00:00:01:01")
    h2 = net.addHost('h2', ip = "10.0.2.1/24", mac="00:00:00:00:01:02")

    info('*** Adding routers\n')
    r1 = net.addHost('r1')
    r2 = net.addHost('r2')
    r3 = net.addHost('r3')
    r4 = net.addHost('r4')

    info('*** Adding probing traffic hosts\n')
    p1 = net.addHost('p1', ip = "10.0.3.1/24", mac="00:00:00:00:01:03")
    p2 = net.addHost('p2', ip = "10.0.4.1/24", mac="00:00:00:00:01:04")

    """
    info('*** Adding physical interface\n')
    Intf('eth0', node=p1)
    Intf('eth1', node=r1)
    Intf('eth2', node=r2) 
    Intf('eth3', node=p2)
    """


    info('*** Adding links\n')
    net.addLink(h1, r1, intfName1='h1-eth0', intfName2='r1-eth0', params1={'ip': '10.0.1.1/24'}, params2={'ip': '10.0.1.2/24'}, bw=12000, delay='1ms' ) #The unit of bandwidth is Mbps
    net.addLink(h2, r2, intfName1='h2-eth0', intfName2='r2-eth0', params1={'ip': '10.0.2.1/24'}, params2={'ip': '10.0.2.2/24'}, bw=12000, delay='1ms' )
    net.addLink(r1, r3, intfName1='r1-eth1', intfName2='r3-eth1', params1={'ip': '10.0.5.1/24'}, params2={'ip': '10.0.5.2/24'}, bw=12000, delay='10ms' )
    net.addLink( r3, r4, intfName1='r3-eth2', intfName2='r4-eth2', params1={'ip': '10.0.6.1/24'}, params2={'ip': '10.0.6.2/24'}, bw=1000, delay='10ms' )
    net.addLink( r4, r2, intfName1='r4-eth1', intfName2='r2-eth1', params1={'ip': '10.0.7.1/24'}, params2={'ip': '10.0.7.2/24'}, bw=13000, delay='10ms' )
    net.addLink( p1, r3, intfName1='p1-eth0', intfName2='r3-eth0', params1={'ip': '10.0.3.1/24'}, params2={'ip': '10.0.3.2/24'}, bw=10000, delay='1ms' )
    net.addLink( p2, r4, intfName1='p2-eth0', intfName2='r4-eth0', params1={'ip': '10.0.4.1/24'}, params2={'ip': '10.0.4.2/24'}, bw=10000, delay='1ms' )
   # Already Physical Connected: 
    info('*** \n')
    
    info( '*** Starting network\n')
    net.start()
    
    info('** setting ip address of routers\n')
    r1.cmd('ifconfig r1-eth0 10.0.1.2 netmask 255.255.255.0')
    r1.cmd('ifconfig r1-eth1 10.0.5.1 netmask 255.255.255.0')
    r2.cmd('ifconfig r2-eth0 10.0.2.2 netmask 255.255.255.0')
    r2.cmd('ifconfig r2-eth1 10.0.7.2 netmask 255.255.255.0')
    r3.cmd('ifconfig r3-eth0 10.0.3.2 netmask 255.255.255.0')
    r3.cmd('ifconfig r3-eth1 10.0.5.2 netmask 255.255.255.0')
    r3.cmd('ifconfig r3-eth2 10.0.6.1 netmask 255.255.255.0')
    r4.cmd('ifconfig r4-eth0 10.0.4.2 netmask 255.255.255.0')
    r4.cmd('ifconfig r4-eth1 10.0.7.1 netmask 255.255.255.0')
    r4.cmd('ifconfig r4-eth2 10.0.6.2 netmask 255.255.255.0')

    info( '*** Setting routing tables\n')
    h1.cmd("route add -net 0.0.0.0 netmask 0.0.0.0 gw 10.0.1.2")  #default route
    r1.cmd("route add -net 10vetmask 255.255.255.0 gw 10.0.5.2")
    r1.cmd("route add -net 10.0.5.0 netmask 255.255.255.0 gw 10.0.5.2")
    
    r3.cmd("route add -net 10.0.1.0 netmask 255.255.255.0 gw 10.0.5.1")
    r3.cmd("route add -net 10.0.2.0 netmask 255.255.255.0 gw 10.0.6.2")
    r3.cmd("route add -net 10.0.4.0 netmask 255.255.255.0 gw 10.0.6.2")
    r3.cmd("route add -net 10.0.6.0 netmask 255.255.255.0 gw 10.0.6.2")
    
    r4.cmd("route add -net 10.0.2.0 netmask 255.255.255.0 gw 10.0.7.2")
    r4.cmd("route add -net 10.0.1.0 netmask 255.255.255.0 gw 10.0.6.1")
    r4.cmd("route add -net 10.0.3.0 netmask 255.255.255.0 gw 10.0.6.1")
    r4.cmd("route add -net 10.0.6.0 netmask 255.255.255.0 gw 10.0.6.1")

    h2.cmd("route add -net 0.0.0.0 netmask 0.0.0.0 gw 10.0.2.2")
    r2.cmd("route add -net 10.0.1.0 netmask 255.255.255.0 gw 10.0.7.1")
    r2.cmd("route add -net 10.0.7.0 netmask 255.255.255.0 gw 10.0.7.1")

  
    p1.cmd("route add -net 0.0.0.0 netmask 0.0.0.0 gw 10.0.3.2")
    p2.cmd("route add -net 0.0.0.0 netmask 0.0.0.0 gw 10.0.4.2")

    info( '*** Running CLI ...\n')
    CLI(net)

    info( '*** Stopping network' )
    net.stop()


if __name__ == '__main__':
   setLogLevel('info')
   bassNet()

