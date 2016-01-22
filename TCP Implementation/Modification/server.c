#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define portno 4555
#define self_addr "127.0.0.1"


int main(){
	int sockfd,clientfd,clilen,t_count,count;
	int buffer[256];

	struct sockaddr_in serv_addr,cli_addr;

	int n;

	//Making of socket

		sockfd =socket(AF_INET,SOCK_STREAM,0);

		if(sockfd < 0){
			printf("Cannot open socket");
			return 0;
		}

	//Filling server address

		bzero((char *) &serv_addr,sizeof(serv_addr));

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port =htons(portno);
		serv_addr.sin_addr.s_addr = inet_addr(self_addr);
	
	//Binging socket to port

		if(bind(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))<0){
			printf("Cannot bind");
			return 0;
		}

	//Listen to port

		listen(sockfd,5);

	//Accepting connection from client

		clilen =sizeof(cli_addr);

		clientfd =accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
		if(clientfd < 0){
			printf("Cannot accept");
			return 0;
		}	

	//Reading size of array

		n=recv(clientfd,&t_count,4,0);

		if (n<0)
		{
			printf("Cannot read from socket");
			return 0;
		}

		printf("count = %d\n",t_count);

	//Reading the array

		n=recv(clientfd,buffer,255,0);

		if (n<0)
		{
			printf("Cannot read from socket");
			return 0;
		}

		printf("Array received ->\n");
		
		count=0;
		while(count<t_count){
			printf("%d\n",buffer[count]);
			count++;
		}	

	//Sorting array

		int i=0,j=0,c;

		while(i<t_count-1){
			j=0;
			while(j<t_count-1){
				if(buffer[j]>buffer[j+1]){
					c=buffer[j];
					buffer[j]=buffer[j+1];
					buffer[j+1]=c;
				}
				j++;
			}
			i++;
		}

/*	count=0;
	printf("\n");
	while(count<t_count){
		printf("%d\n",buffer[count] );
		count++;
	}		
*/
	// Returning the array

	n=send(clientfd,buffer,t_count*4,0);
	if(n<0){
		printf("Cannot write to socket");
		return 0;
	}

	return 0;


}
