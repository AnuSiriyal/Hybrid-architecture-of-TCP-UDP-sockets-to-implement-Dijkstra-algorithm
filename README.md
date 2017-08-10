# Hybrid-architecture-of-TCP-UDP-sockets-to-implement-Dijkstra-algorithm
Extracted data on client side containing neighbor information to map a network using TCP and UDP sockets.
Read me file for Socket Programming


Name:-        Socket Program
Author:-      Anu Siriyal
Date:-         November 19, 2015



=====================================
1) Introduction

This project simulates a network topology containing a client and 4 servers. There is data exachange between client and servers using TCP and UDP sockets. The project is divided into 3 phases.
Phase 1: Creation of TCP sockets to listen for incoming connections from servers.
Phase 2: Read the neighbor information and share it with the client. The client will calculate the adjacency matrix and the edges and share the topology with the servers by UDP connection.
Phase 3: Calculate minimum spanning tree containing all servers

Phase 1 has been developed with TCP sockets. Phase 2 has 2 parts. Firstly the neighbour information shared by all the servers to the client through TCP. Once the topology has been created, it is shared by the client to all the servers using UDP.Phase 3 consists of calculating the minimum spanning tree of the given topology.

2)Makefile

make command will build client, serverA, serverB, serverC, serverD

3)Usage
client 
syntax: ./client
For server A, server B,server C and server D
syntax: ./serverA , ./serverB , ./serverC and ./serverD

4)Packaged files

The following files have been included in the folder EE450

client.c  			  %client
serverA.c             %ServerA
serverB.c             %ServerB
serverC.c             %ServerC
serverD.c             %ServerD
serverA.txt           %text file which contains the information of neighbouring info of serverA
serverB.txt           %text file which contains the information of neighbouring info of serverB
serverC.txt           %text file which contains the information of neighbouring info of serverC
serverD.txt           %text file which contains the information of neighbouring info of serverD




5) Idiosyncrasy: 
The program was executed without any errors.
Separate compilation has been made.
The program should be run in the following order:
1)client
2)serverA
3)serverB
4)serverC
5)serverD

The execution is not slow and of moderate speed.



6)Format of the messages exchanged

a)Client------
nunki.usc.edu(2): ./client
UDP Port number is 25009

b)Server A--------------------------------------------
nunki.usc.edu(2): ./serverA
UDP port number is 21009

c)Server B---------------------------------------------------------------------
nunki.usc.edu(3): ./serverB
UDP port number is 22009

d)Server C-----------------------------------------------------------------
nunki.usc.edu(4): ./serverC
UDP port number is 23009

e)Server D-----------------------------------------------------------------
nunki.usc.edu(5): ./serverD
UDP port number is 24009

7)Copyrights and Licensing
The program has been majorly inspired by blocks of code from Beej's guide to Network programming and the copied parts have been given as comment in the program.
