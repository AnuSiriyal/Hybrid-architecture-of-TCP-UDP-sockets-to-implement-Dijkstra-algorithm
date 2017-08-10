#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define MAXBUFLEN 100
#define PORT_A "21009"
#define PORT "25009" // the port client will be connecting to 
#define MAXDATASIZE 100 // max number of bytes we can get at once 

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) 
        {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}//Beej

int main(int argc, char *argv[])
{       
    char *x=malloc(sizeof(char)*1024);
	int client1,sockfd_A, numbytes; 
    char buf[MAXDATASIZE],buf10[MAXDATASIZE],IP[MAXDATASIZE];
    char invalid[MAXDATASIZE];
	char send_cost[100]={};
    struct sockaddr_in local;
	struct addrinfo hints, *servinfo, *p;
	int rv,i;
	char s[INET6_ADDRSTRLEN];
    FILE *fp,*F2;
    char *send_msg=malloc(sizeof(char)*1024);
    char str[1024]={},str4[1024],str2[1024],str3[1024];
    char *token=malloc(sizeof(char)*1024);
    char *token1=malloc(sizeof(char)*1024);
	char *token2=malloc(sizeof(char)*1024);
	char *token3=malloc(sizeof(char)*1024);
    char str1[2]=" ";
    char port_sent[15];
    char index_sent[15];
    int app_index;
    int locallen;
    char *name;
	int client1_UDP;
    char UDP_sent[15];
    struct sockaddr_in UDP;
    int port_UDP;
	int port;
    int len_UDP;	
    struct addrinfo hints1, *servinfo1, *p1;
	char ipstr[INET6_ADDRSTRLEN];
    int rv1;
    int numbytes1;
    int buf_int;
    struct sockaddr_storage their_address;
    int addr_len = sizeof their_address;
	
	char aa[1024];
	char line[100]={};
	size_t len = 0;
	ssize_t read;
	
	//TCP connection: Sending data from serverA to client
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;


	if ((rv = getaddrinfo("nunki.usc.edu", PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}//Beej

	// loop through all the results and connect to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next)
              {
		if ((client1 = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1)
               {
			perror("ServerA: socket");
			continue;
		}//Beej
       
        
//-------------connect to the client----------------------------------------------------------------
          
         if (connect(client1, p->ai_addr, p->ai_addrlen) == -1) 
            {
			perror("serverA: connect");
			continue;
		}

		break;
	    }
        


	if (p == NULL)
        {
		fprintf(stderr, "ServerA: failed to connect\n");
		return 2;
	}

        
       

	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
			s, sizeof s);
	
	printf("The Server A is up and running\n");
    memset(local.sin_zero, 0,sizeof (local.sin_zero));
	printf("Here\n");
	getsockname(client1,(struct sockaddr *)&local,&(locallen));
    port=ntohs(local.sin_port);
	printf("Here\n");
    freeaddrinfo(servinfo); // all done with this structure
//------------------------opening a file-------------------------------------------------------------
        fp=fopen("serverA.txt","r");
        if(fp==NULL)
        {
        perror("error opening file");
        return (-1);
        }
        
		fgets(str,sizeof(str),fp);
	 
	 
	// printf(" first fgets %s\n",str);
       // while(fgets(line,sizeof line,fp)!=NULL)
	   // {
		   // strcat(str,line);
		   // strcat(str," ");
	   // }
    	// printf("rearranging: %s",str);
		//fclose(fp);
	//int data[4];
	char *temp,*tokenx;
	char tokena[80],tokenb[80],tokenc[80],tokend[80];
	temp=strtok(str," ");
	strcpy(tokena,temp);//token 1 has serverB
	
	//printf("Here 2 %s and %s\n",token1,temp);
	temp=strtok(NULL,str1); //token2 has 20
	strcpy(tokenb,temp);
	// printf("Here 21 %s\n",tokenb);
	 
	
    strcat(send_msg,tokena);
	// printf("Here 23\n");
	strcat(send_msg,"\t");
	// printf("Here 24\n");
	strcat(send_msg,tokenb);
	// printf("Here 25\n");
	strcat(send_cost,"0");
	// printf("Here 26\n");
	strcat(send_cost," ");
	// printf("Here 27\n");
	strcat(send_cost,tokenb);
	// printf("Here 28\n");
	strcat(send_cost," ");
	// printf("Here 29\n");
	strcat(send_msg,"\n");
	// printf("Here 30\n");
    // printf("Message is %s\n",send_msg);
	
	*(tokenb+strlen(tokenb-1))='\0';
	fgets(str,sizeof(str),fp);
	//printf("Here 22\n");
	temp=strtok(str," ");
	strcpy(tokenc,temp);
	// printf("HHHH %s\n",tokenc);
	temp=strtok(NULL," ");
	strcpy(tokend,temp);//tokend has 30
	// printf("Here 31 %s\n",tokend);
	
    strcat(send_msg,tokenc);
	// printf("Here 33\n");
	strcat(send_msg,"\t");
	// printf("Here 34\n");
	//token3=strtok(NULL,str1);//cost
	//*(token3+strlen(token3))='\0';
    strcat(send_msg,tokend);
	strcat(send_cost,tokend);
	strcat(send_cost," ");
	strcat(send_cost,"0");
	 *(tokend+strlen(tokend-1))='\0';
	 fclose(fp);
	  printf("\nThe Server A has the following neighbor information:\n");
	  printf("Neighbor------Cost\n");
	  printf("%s",send_msg);
	  sprintf(port_sent,"%d",port);
	  send(client1,send_cost,strlen(send_cost),0);
	printf("\nThe Server A finishes sending its neighbor information to the Client with TCP port number %s and IP address %s\n",PORT,s);
	printf("\nFor this connection with the Client, the Server A has TCP port number %d and IP address %s.",port,s);
	close(client1);
	memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
	
	
if ((rv = getaddrinfo("nunki.usc.edu", PORT_A, &hints, &servinfo)) != 0) 
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }//Beej
//---------------------to print the IP Address-------------------------------------------------

   for(p=servinfo;p!=NULL;p=p->ai_next)
     {
   void *addr;
   char *ipver;

  if(p->ai_family==AF_INET)
   {
  struct sockaddr_in *ipv4=(struct sockaddr_in *)p->ai_addr;
  addr=&(ipv4->sin_addr);
   ipver="IPv4";
   }

else
{
struct sockaddr_in6 *ipv6=(struct sockaddr_in6 *)p->ai_addr;
addr=&(ipv6->sin6_addr);
ipver="IPv6";
}//Beej
//---convert IP to a string and print it--------------------------------------------------------------------------------------
inet_ntop(p->ai_family,addr,ipstr,sizeof (ipstr));

}
 memset(local.sin_zero, 0,sizeof (local.sin_zero));
		getsockname(client1_UDP,(struct sockaddr *)&local,&(locallen));
        port=ntohs(local.sin_port);
//-----------------------creation of socket--------------------------------------------------------------------------------
    for(p = servinfo; p != NULL; p = p->ai_next) 
     {
        if ((client1_UDP = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) 
        {
            perror("listener: socket");
            continue;
        }//beej

        if (bind(client1_UDP, p->ai_addr, p->ai_addrlen) == -1)
       {
            close(client1_UDP);
            perror("listener: bind");
            continue;
        }//Beej

        break;
    }

    if (p == NULL) 
   {
        fprintf(stderr, "listener: failed to bind socket\n");
        return 2;
    }

    freeaddrinfo(servinfo);
 // ("listener: waiting to recvfrom...");


        addr_len = sizeof UDP;
    if ((numbytes = recvfrom(client1_UDP, buf, MAXBUFLEN-1 , 0,
        (struct sockaddr *)&UDP, &addr_len)) == -1) {
        perror("recvfrom");//receiving port number from patient
        exit(1);
    }
	buf[numbytes]='\0';
	printf("\nThe server A has received the network topology from the Client with UDP port number %s and IP address %s as follows:\nEdge------Cost\n",PORT,s);
	printf("%s",buf);
	printf("For this connection with Client, The Server A has UDP port number %s and IP address %s.\n",PORT_A,s);
        
   

}
