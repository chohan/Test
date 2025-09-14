#!/usr/bin/python
##########################################################################################
#
# Desc: This receives multicast data and prints it.
# Auth: Salah Chohan
# Date: 14-09-2022
# Usage: python multicast_rx.py <MC IP> <port>
#
##########################################################################################
import os, sys, datetime
import socket, struct

if len(sys.argv) != 3:
  print(sys.argv)
  print("No of inputs: " + str(len(sys.argv)))
  print("Please enter IP and port: multicast_rx.py 1.2.3.4 5555")
  sys.exit(-1)

#multicast _group = '227.1.1.11'
#server_address = ('', 4441)
IP = sys.argv[1]
PORT = int(sys.argv[2])

# Create the socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(('', PORT))

# Tell the operating system to add the socket to the multicast group on all the interfaces
group = socket.inet_aton(IP)
mreg = struct.pack('4sL', group, socket.INADDR_ANY)
sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)

# Receive/respond loop
while True:
  print >>sys.stderr, '\nwaiting to receive message'
  data, address = sock.recvfrom(1024)

  print >>sys.stderr, 'receive %s bytes from %s' % (len(data), address)
  print >>sys.stderr, data

