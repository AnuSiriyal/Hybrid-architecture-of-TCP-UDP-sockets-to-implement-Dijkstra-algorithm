all: client serverA serverB serverC serverD

client:client.c
	gcc -o client client.c -lsocket -lresolv -lnsl
	
serverA:serverA.c
	gcc -o serverA serverA.c -lsocket -lresolv -lnsl
	
serverB:serverB.c
	gcc -o serverB serverB.c -lsocket -lresolv -lnsl

serverC:serverC.c
	gcc -o serverC serverC.c -lsocket -lresolv -lnsl

serverD:serverD.c
	gcc -o serverD serverD.c -lsocket -lresolv -lnsl


