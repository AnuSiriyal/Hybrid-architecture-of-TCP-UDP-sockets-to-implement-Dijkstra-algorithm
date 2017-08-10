#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <limits.h>
#define PORT "25009"  // the port users will be connecting to
#define PORT_A "21009"
#define PORT_B "22009"
#define PORT_C "23009"
#define PORT_D "24009"
#define BACKLOG 10	 // how many pending connections queue will hold
#define V 5
#define MAXDATA1 100

void sigchld_handler(int s)
{
	while(waitpid(-1, NULL, WNOHANG) > 0);
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}//Beej tutorial

int main(void)
{
	int sockfd, sockfd_A, sockfd_B, sockfd_C, sockfd_D, new_fd;  // listen on sock_fd, new connection on new_fd
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage client_addr; // connector's address information
	socklen_t sin_size;
	int info;int anu=0;int count;
 int locallen;
 int port;
	int min,noteq,u,v,a,b,span[10]={0};
	int mincost=0;
	int numbytes;int ne=0;
	struct sigaction sa;
	char str1[2]=" ";
	int yes=1,i,j,flag=0,t=0;
	int x=0,y=0;
	struct sockaddr_in local;
	//char send_UDP[sizeof(int)]={};
	char linki,linkj;
	char ipstr[INET6_ADDRSTRLEN];
	char temp[100]={};
	char temp1[100]={};
	char temp2[100]={};
	char temp3[100]={};
	char link_send[100];
	int rv;int c[4][4];
	int data[4][4]={},P_data[4][4]={};
	char *token=malloc(sizeof(char)*1024);
    char *token1=malloc(sizeof(char)*1024);
	char *token2=malloc(sizeof(char)*1024);
	char *sending_UDP=malloc(sizeof(char)*1024);
	char *token3=malloc(sizeof(char)*1024);
    char user1[80],pass1[80],user2[80],pass2[80];
    char str[1024],avl_1[50],avl_2[50],avl_3[50],avl_4[50],avl_5[50],avl_6[50];
	char chunk[5]={};
    int num_bytes;
	int index_int;char keep[100];
    char buf[MAXDATA1],buf1[MAXDATA1],buf2[MAXDATA1],buf12[MAXDATA1];
	char var1[5],var2[5],var3[5],var4[5],var5[5],var6[5];
	char name1[10],name2[10],name3[10],name4[10],name5[10],name6[10];
    char index[MAXDATA1];
	char name[4] = {'A','B','C','D'};	
    FILE *f,*f1;
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;//TCP SOCKET
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = getaddrinfo("nunki.usc.edu",PORT, &hints, &servinfo)) != 0) 
        {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
		}//Beej tutorial

      
//----to print IP address--------------------------------------------------------------------------
       
      for(p=servinfo;p!=NULL;p=p->ai_next)
    {
		void *addr;
		char *ipver;

		if(p->ai_family==AF_INET)
		{
			struct sockaddr_in *ipv4=(struct sockaddr_in *)p->ai_addr;
			addr=&(ipv4->sin_addr);
			ipver="IPv4";
		}//Beej Tutorial

		else
		{
			struct sockaddr_in6 *ipv6=(struct sockaddr_in6 *)p->ai_addr;
			addr=&(ipv6->sin6_addr);
			ipver="IPv6";
		}
//-convert IP to a string and print it------------------------------------------------------
		inet_ntop(p->ai_family,addr,ipstr,sizeof (ipstr));
		printf("The Client has TCP port number %s and IP address %s\n",PORT,ipstr);
	}
//---------------- loop through all the results and bind to the first we can---------------------
	for(p = servinfo; p != NULL; p = p->ai_next) 
    {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) 
        {
			perror("client: socket");
			continue;
		}//Beej
               // printf("created");
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
				sizeof(int)) == -1) 
        {
			perror("setsockopt");
			exit(1);
		}//Beej

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
			close(sockfd);
			perror("client: bind");
			continue;
		}//Beej
		break;
	}

	if (p == NULL)  
    {
		fprintf(stderr, "client: failed to bind\n");
		return 2;
	}
    
	freeaddrinfo(servinfo); // all done with this structure
//-------------------------------listen to the servers------------------------------------
	if (listen(sockfd, BACKLOG) == -1)
       {
		perror("listen");
		exit(1);
	}//Beej

	sa.sa_handler = sigchld_handler; // reap all the dead processes
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) 
	{
		perror("sigaction");
		exit(1);
	}//Beej
	  // main accept() loop
	while(anu<4) 
	{  
		sin_size = sizeof client_addr;
		new_fd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
		if (new_fd == -1)
		{
			
			continue;
		}//Beej

		inet_ntop(client_addr.ss_family,
		get_in_addr((struct sockaddr *)&client_addr),
		ipstr, sizeof ipstr);
		struct sockaddr_in *soc=(struct sockaddr_in *)&client_addr;	
		
		memset(buf,0,sizeof(buf));
        if ((num_bytes = recv(new_fd, buf, MAXDATA1-1, 0)) == -1) 
           {
	            perror("recv");
	            exit(1);
	        }//Beej

	    buf[num_bytes] = '\0';
        if(flag==0)
		{
			strcpy(buf1,buf);
			printf("The Client receives neighbor information from the Server A with TCP port number %d and IP address %s.\n",htons(soc->sin_port),ipstr);
		printf("Buffer %s\n",buf1);
			//strcpy(temp,strdup(buf));
			//printf("Temp %s\n",temp);
			token=strtok(buf1,str1);
			printf("token %s\n",token);
			data[0][0]=atoi(token);
			token1=strtok(NULL,str1);
			printf("token1 %s\n",token1);
			data[0][1]=atoi(token1);
			token2=strtok(NULL,str1);
			printf("token2 %s\n",token2);
			data[0][2]=atoi(token2);
			token3=strtok(NULL,str1);
			printf("token3 %s\n",token3);
			data[0][3]=atoi(token3);
	
			printf("The Server A has the following neighbor information:\n");
			printf("Neighbor------Cost\n");
			for(j=0;j<4;j++)
			{
				switch(j)
				{
					case 0: if(data[0][j]!=0)
							printf("serverA\t%d\n",data[0][j]);
							break;
					case 1: if(data[0][j]!=0)
							printf("serverB\t%d\n",data[0][j]);
							break;
					case 2: if(data[0][j]!=0)
							printf("serverC\t%d\n",data[0][j]);
							break;
					case 3: if(data[0][j]!=0)
							printf("serverD\t%d\n",data[0][j]);
							break;
				}
			}
			printf("For this connection with Server A, ");
			flag=1;
			//memset(buf,0,sizeof(buf));
			}
		else if(flag==1)
		   {
			   printf("The Client receives neighbor information from the Server B with TCP port number %d and IP address %s\n",htons(soc->sin_port),ipstr);
			   // strcat(temp1,strdup(buf));
			   strcpy(buf2,buf);
			   printf("buffer %s\n",buf2);
			    token=strtok(buf2,str1);
				printf("token %s\n",token);
				data[1][0]=atoi(token);
					
				token1=strtok(NULL,str1);
				data[1][1]=atoi(token1);
					printf("token1 %s\n",token1);
				token2=strtok(NULL,str1);
				data[1][2]=atoi(token2);
					printf("token2 %s\n",token2);
				token3=strtok(NULL,str1);
				printf("token3 %s\n",token3);
				data[1][3]=atoi(token3);
				printf("The Server B has the following neighbor information:\n");
				printf("Neighbor------Cost\n");
				for(j=0;j<4;j++)
					{
						switch(j)
						{
							case 0: if(data[1][j]!=0)
									printf("serverA\t%d\n",data[1][j]);
									break;
							case 1: if(data[1][j]!=0)
									printf("serverB\t%d\n",data[1][j]);
									break;
							case 2: if(data[1][j]!=0)
									printf("serverC\t%d\n",data[1][j]);
									break;
							case 3: if(data[1][j]!=0)
									printf("serverD\t%d\n",data[1][j]);
									break;
						}
					}
					printf("For this connection with Server B, ");
				   
				flag=2;
			}
			else if(flag==2)
				{
				    printf("The Client receives neighbor information from the Server C with TCP port number %d and IP address %s\n",htons(soc->sin_port),ipstr);
				   //strcat(temp2,strdup(buf));
					token=strtok(buf,str1);
					data[2][0]=atoi(token);
					printf("data[2][0]: %d \n",data[2][0]);
					token1=strtok(NULL,str1);
					data[2][1]=atoi(token1);
					printf("data[2][1]: %d \n",data[2][1]);
					token2=strtok(NULL,str1);
					data[2][2]=atoi(token2);
					printf("data[2][2]: %d \n",data[2][2]);
					token3=strtok(NULL,str1);
					data[2][3]=atoi(token3);
					printf("data[2][3]: %d \n",data[2][3]);
					printf("The Server C has the following neighbor information:\n");
					printf("Neighbor------Cost\n");
					for(j=0;j<4;j++)
					{
						switch(j)
						{
							case 0: if(data[2][j]!=0)
										printf("serverA\t%d\n",data[2][j]);
									break;
							case 1: if(data[2][j]!=0)
									printf("serverB\t%d\n",data[2][j]);
									break;
							case 2: if(data[2][j]!=0)
									printf("serverC\t%d\n",data[2][j]);
									break;
							case 3: if(data[2][j]!=0)
									printf("serverD\t%d\n",data[2][j]);
									break;
						}
					}
					printf("For this connection with Server C, ");
				   
				  flag=3;
			   }
			   else
			   {
				   printf("The Client receives neighbor information from the Server D with TCP port number %d and IP address %s\n",htons(soc->sin_port),ipstr);
				   strcat(temp3,strdup(buf));
				   token=strtok(temp3,str1);
					data[3][0]=atoi(token);
					
					token1=strtok(NULL,str1);
					data[3][1]=atoi(token1);
					
					token2=strtok(NULL,str1);
					data[3][2]=atoi(token2);
					
					token3=strtok(NULL,str1);
					data[3][3]=atoi(token3);
					printf("The Server D has the following neighbor information:\n");
					printf("Neighbor------Cost\n");
					for(j=0;j<4;j++)
					{
						switch(j)
						{
							case 0: if(data[3][j]!=0)
										printf("serverA\t%d\n",data[3][j]);
									break;
							case 1: if(data[3][j]!=0)
									printf("serverB\t%d\n",data[3][j]);
									break;
							case 2: if(data[3][j]!=0)
									printf("serverC\t%d\n",data[3][j]);
									break;
							case 3: if(data[3][j]!=0)
									printf("serverD\t%d\n",data[3][j]);
									break;
						}
					}
					printf("For this connection with Server D, ");
				   flag=4;
				   for(i=0;i<4;i++)
					for(j=0;j<4;j++)
						P_data[i][j]=data[i][j];
					  
				}
			   printf("The Client has TCP port number %s and IP address %s.",PORT,ipstr);
			   
			   for(i=0;i<4;i++)
			   {   for(j=0;j<4;j++)
				   {	if(i==0) linki='A';
						if(i==1) linki='B';
						if(i==2) linki='C';
						if(i==3) linki='D';
						if(j==0) linkj='A';
						if(j==1) linkj='B';
						if(j==2) linkj='C';
						if(j==3) linkj='D';
					//	keep='\0';
			   	   if((i<=j) && (P_data[i][j]!=0))
					   {
						   printf("%c%c\t%d\n",linki,linkj,P_data[i][j]);
						   sprintf(keep,"%c%c\t%d\n",linki,linkj,P_data[i][j]);
						   strcat(sending_UDP,keep);
					   }
					}
					printf("\n%s",sending_UDP);	   
				}
			   	  printf("\n");
				  
				anu++; 
			}

		//serverA send	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;//UDP SOCKET
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = getaddrinfo("nunki.usc.edu",PORT_A, &hints, &servinfo)) != 0) 
        {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}//Beej tutorial

      
//----to print IP address--------------------------------------------------------------------------
       
      for(p=servinfo;p!=NULL;p=p->ai_next)
     {
   void *addr;
   char *ipver;

  if(p->ai_family==AF_INET)
   {
  struct sockaddr_in *ipv4=(struct sockaddr_in *)p->ai_addr;
  addr=&(ipv4->sin_addr);
   ipver="IPv4";
   }//Beej Tutorial

else
{
struct sockaddr_in6 *ipv6=(struct sockaddr_in6 *)p->ai_addr;
addr=&(ipv6->sin6_addr);
ipver="IPv6";
}
//-convert IP to a string and print it------------------------------------------------------
inet_ntop(p->ai_family,addr,ipstr,sizeof (ipstr));
printf("The Client has sent the network topology to the network topology to the Server A with UDP port number %s and IP address %s as follows:\nEdge------Cost\n",PORT_A,ipstr);
}
//---------------- loop through all the results and bind to the first we can---------------------
	for(p = servinfo; p != NULL; p = p->ai_next) 
           {
		if ((sockfd_A = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) 
                {
			perror("client: socket");
			continue;
		}//Beej
               // printf("created");
		if (setsockopt(sockfd_A, SOL_SOCKET, SO_REUSEADDR, &yes,
				sizeof(int)) == -1) 
                {
			perror("setsockopt");
			exit(1);
		}//Beej

		if (bind(sockfd_A, p->ai_addr, p->ai_addrlen) == -1)
                {
			close(sockfd_A);
			perror("client: bind");
			continue;
		}//Beej

            //   printf("binded");
		break;
	}

	if (p == NULL)  
       {
		fprintf(stderr, "client: failed to bind\n");
		return 2;
		}
		printf("%s\n",sending_UDP);
		memset(local.sin_zero, 0,sizeof (local.sin_zero));
	getsockname(sockfd_A,(struct sockaddr *)&local,&(locallen));
    port=ntohs(local.sin_port);
    
		printf("For this connection with Server A, The Client has UDP port number %s and IP address %s.\n",PORT,ipstr);
    if ((numbytes = sendto(sockfd_A, sending_UDP, strlen(sending_UDP), 0,
             p->ai_addr, p->ai_addrlen)) == -1) {
        perror("talker: sendto");
        exit(1);
    }
		

    freeaddrinfo(servinfo);
	
	
   // printf("talker: sent %d bytes to %s\n", numbytes, sending_UDP);
    close(sockfd_A);
	
	//serverB send
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;//UDP SOCKET
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = getaddrinfo("nunki.usc.edu",PORT_B, &hints, &servinfo)) != 0) 
        {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}//Beej tutorial

      
//----to print IP address--------------------------------------------------------------------------
       
      for(p=servinfo;p!=NULL;p=p->ai_next)
     {
   void *addr;
   char *ipver;

  if(p->ai_family==AF_INET)
   {
  struct sockaddr_in *ipv4=(struct sockaddr_in *)p->ai_addr;
  addr=&(ipv4->sin_addr);
   ipver="IPv4";
   }//Beej Tutorial

else
{
struct sockaddr_in6 *ipv6=(struct sockaddr_in6 *)p->ai_addr;
addr=&(ipv6->sin6_addr);
ipver="IPv6";
}
//-convert IP to a string and print it------------------------------------------------------
inet_ntop(p->ai_family,addr,ipstr,sizeof (ipstr));
printf("The Client has sent the network topology to the network topology to the Server B with UDP port number %s and IP address %s as follows:\nEdge------Cost\n",PORT_B,ipstr);
}
//---------------- loop through all the results and bind to the first we can---------------------
	for(p = servinfo; p != NULL; p = p->ai_next) 
           {
		if ((sockfd_A = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) 
                {
			perror("client: socket");
			continue;
		}//Beej
               // printf("created");
		if (setsockopt(sockfd_A, SOL_SOCKET, SO_REUSEADDR, &yes,
				sizeof(int)) == -1) 
                {
			perror("setsockopt");
			exit(1);
		}//Beej

		if (bind(sockfd_A, p->ai_addr, p->ai_addrlen) == -1)
                {
			close(sockfd_A);
			perror("client: bind");
			continue;
		}//Beej

            //   printf("binded");
		break;
	}
//printf("%s",sending_UDP);
	if (p == NULL)  
       {
		fprintf(stderr, "client: failed to bind\n");
		return 2;
		}
    if ((numbytes = sendto(sockfd_A, sending_UDP, strlen(sending_UDP), 0,
             p->ai_addr, p->ai_addrlen)) == -1) {
        perror("talker: sendto");
        exit(1);
    }
		

    freeaddrinfo(servinfo);
	printf("%s\n",sending_UDP);
		memset(local.sin_zero, 0,sizeof (local.sin_zero));
	getsockname(sockfd_A,(struct sockaddr *)&local,&(locallen));
    port=ntohs(local.sin_port);
    
	printf("For this connection with Server B, The Client has UDP port number %d and IP address %s.\n",PORT,ipstr);
	
    //printf("talker: sent %d bytes to %s\n", numbytes, sending_UDP);
    close(sockfd_A);
	//serverC send
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;//UDP SOCKET
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = getaddrinfo("nunki.usc.edu",PORT_C, &hints, &servinfo)) != 0) 
        {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}//Beej tutorial

      
//----to print IP address--------------------------------------------------------------------------
       
      for(p=servinfo;p!=NULL;p=p->ai_next)
     {
   void *addr;
   char *ipver;

  if(p->ai_family==AF_INET)
   {
  struct sockaddr_in *ipv4=(struct sockaddr_in *)p->ai_addr;
  addr=&(ipv4->sin_addr);
   ipver="IPv4";
   }//Beej Tutorial

else
{
struct sockaddr_in6 *ipv6=(struct sockaddr_in6 *)p->ai_addr;
addr=&(ipv6->sin6_addr);
ipver="IPv6";
}
//-convert IP to a string and print it------------------------------------------------------
inet_ntop(p->ai_family,addr,ipstr,sizeof (ipstr));
printf("The Client has sent the network topology to the network topology to the Server B with UDP port number %s and IP address %s as follows:\nEdge------Cost\n",PORT_C,ipstr);
}
//---------------- loop through all the results and bind to the first we can---------------------
	for(p = servinfo; p != NULL; p = p->ai_next) 
           {
		if ((sockfd_A = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) 
                {
			perror("client: socket");
			continue;
		}//Beej
               // printf("created");
		if (setsockopt(sockfd_A, SOL_SOCKET, SO_REUSEADDR, &yes,
				sizeof(int)) == -1) 
                {
			perror("setsockopt");
			exit(1);
		}//Beej

		if (bind(sockfd_A, p->ai_addr, p->ai_addrlen) == -1)
                {
			close(sockfd_A);
			perror("client: bind");
			continue;
		}//Beej

            //   printf("binded");
		break;
	}

	if (p == NULL)  
       {
		fprintf(stderr, "client: failed to bind\n");
		return 2;
		}
    if ((numbytes = sendto(sockfd_A, sending_UDP, strlen(sending_UDP), 0,
             p->ai_addr, p->ai_addrlen)) == -1) {
        perror("talker: sendto");
        exit(1);
    }
		

    freeaddrinfo(servinfo);
	
	printf("%s\n",sending_UDP);
		memset(local.sin_zero, 0,sizeof (local.sin_zero));
	getsockname(sockfd_A,(struct sockaddr *)&local,&(locallen));
    port=ntohs(local.sin_port);
    
	printf("For this connection with Server C, The Client has UDP port number %s and IP address %s.\n",PORT,ipstr);
	
    //printf("talker: sent %d bytes to %s\n", numbytes, sending_UDP);
    close(sockfd_A);
	
	
	//serverD send
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;//UDP SOCKET
	hints.ai_flags = AI_PASSIVE; // use my IP

	if ((rv = getaddrinfo("nunki.usc.edu",PORT_D, &hints, &servinfo)) != 0) 
        {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}//Beej tutorial

      
//----to print IP address--------------------------------------------------------------------------
       
      for(p=servinfo;p!=NULL;p=p->ai_next)
     {
   void *addr;
   char *ipver;

  if(p->ai_family==AF_INET)
   {
  struct sockaddr_in *ipv4=(struct sockaddr_in *)p->ai_addr;
  addr=&(ipv4->sin_addr);
   ipver="IPv4";
   }//Beej Tutorial

else
{
struct sockaddr_in6 *ipv6=(struct sockaddr_in6 *)p->ai_addr;
addr=&(ipv6->sin6_addr);
ipver="IPv6";
}
//-convert IP to a string and print it------------------------------------------------------
inet_ntop(p->ai_family,addr,ipstr,sizeof (ipstr));
printf("The Client has sent the network topology to the network topology to the Server D with UDP port number %s and IP address %s as follows:\nEdge------Cost\n",PORT_D,ipstr);
}
//---------------- loop through all the results and bind to the first we can---------------------
	for(p = servinfo; p != NULL; p = p->ai_next) 
           {
		if ((sockfd_A = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) 
                {
			perror("client: socket");
			continue;
		}//Beej
               // printf("created");
		if (setsockopt(sockfd_A, SOL_SOCKET, SO_REUSEADDR, &yes,
				sizeof(int)) == -1) 
                {
			perror("setsockopt");
			exit(1);
		}//Beej

		if (bind(sockfd_A, p->ai_addr, p->ai_addrlen) == -1)
                {
			close(sockfd_A);
			perror("client: bind");
			continue;
		}//Beej

            //   printf("binded");
		break;
	}

	if (p == NULL)  
       {
		fprintf(stderr, "client: failed to bind\n");
		return 2;
		}
    if ((numbytes = sendto(sockfd_A, sending_UDP, strlen(sending_UDP), 0,
             p->ai_addr, p->ai_addrlen)) == -1) {
        perror("talker: sendto");
        exit(1);
    }
		

    freeaddrinfo(servinfo);
	
		printf("%s\n",sending_UDP);
		memset(local.sin_zero, 0,sizeof (local.sin_zero));
	getsockname(sockfd_A,(struct sockaddr *)&local,&(locallen));
    port=ntohs(local.sin_port);
    
	printf("For this connection with Server D, The Client has UDP port number %s and IP address %s.\n",PORT,ipstr);

//    printf("talker: sent %d bytes to %s\n", numbytes, sending_UDP);
    close(sockfd_A);
	
	span[0]=1;noteq=0;
		//printf("1");
		for(i=0;i<4;i++)
		{
		//printf("2");
		for(j=0;j<4;j++)
		{	
			//	printf("3");
				if(P_data[i][j]==0)
				{
				//	printf("4");
				P_data[i][j]=999;}
				
				// printf("5");
			}
		}	// printf("6");
printf("The Client has calculated a tree.\nEdge------Cost\n");		
	span[0]=1;
		while(ne<4)
		{
			//printf("7");
			for(i=0,min=999;i<4;i++)
			{
				// printf("8");
				for(j=0;j<4;j++)
				{
					// printf("9");
					if(P_data[i][j]<min)
					{
						// printf("10");
						if(span[i]!=0)
						{
							// printf("11");
							min=P_data[i][j];
							a=u=i;
							b=v=j;
						}
			
			
			
			//printf("12");
						if((span[u]==0)||(span[v]==0))
			{
				//printf("13");
				printf("%c%c \t %d\n",name[a],name[b],min);
				mincost+=min;
				//printf("14");
				span[b]=1;
			
			}
			P_data[i][j]=P_data[j][i]=999;
			//printf("15");
			ne++;
		}
		}
		}
		}
		printf("The tree cost is :%d\n",mincost);
	 
}
