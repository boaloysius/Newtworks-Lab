#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define portno 4555
#define dest_addr "127.0.0.1"


int main(){

	int sockfd,n,t_count,count;
	struct sockaddr_in serv_addr;
	
	int buffer[256];

	//Making Socket

		sockfd =socket(AF_INET,SOCK_STREAM,0);

		if(sockfd < 0){
			printf("Cannot open socket");
			return 0;
		}

	// Filling address structure

	bzero((char *) &serv_addr,sizeof(serv_addr));

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr=inet_addr(dest_addr);
		serv_addr.sin_port =htons(portno);

	//Connecting to server

		if(connect(sockfd,&serv_addr,sizeof(serv_addr))<0){
			printf("Cannot connect");
			return 0;
		}
	
	//Getting count from user






	FILE * fp;
	fp=fopen("sample.txt","r");
	
	int i=0;
	t_count=0;

	char a[20];
	while(!feof(fp)){
	
		i=0;
		
		while(1){
			a[i]=fgetc(fp);
			if(a[i] == ' '|| feof(fp)){
				a[i]='\0';
				break;
			}
			i++;
		}
	
		//printf("%s\n",a);
		buffer[t_count]=atoi(a);
		t_count++;
	
	}
	
	
	fclose(fp);
	
	
	//Sending count to server

		n=send(sockfd,&t_count,4,0);
		
		if(n<0){
			printf("Socket writing problem");
			return 0;
		}

	
	//Sending the array to server

		n=send(sockfd,buffer,t_count*4,0);
		if(n<0){
			printf("Cannot write to socket");
			return 0;
		}

	//Recieving Sorted arrayback

		n=recv(sockfd,buffer,255,0);
	
	//Printing sorted array

		fp=fopen("output.txt","w");
	
		count=0;
		while(count<t_count){
			fprintf(fp,"%d ",buffer[count] );
			count++;
		}
		
		fclose(fp);

	return 0;	


}
