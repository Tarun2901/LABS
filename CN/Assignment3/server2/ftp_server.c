#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
 
/*for getting file size using stat()*/
#include<sys/stat.h>
 
/*for sendfile()*/
#include<sys/sendfile.h>
 
/*for O_RDONLY*/
#include<fcntl.h>

int main(int argc,char *argv[])
{
  struct sockaddr_in server, client;
  struct stat obj;
  int sock1, sock2;
  char buf[100], command[5], filename[20];
  int k, i, size, len, c;
  int filehandle;
  
  sock1 = socket(AF_INET, SOCK_STREAM, 0);
  
  if(sock1 == -1)
    {
      printf("Socket creation failed");
      exit(1);
    }
    bzero(&server, sizeof(server));
  server.sin_port = atoi(argv[1]);
  
  server.sin_addr.s_addr = 0;
  
  k = bind(sock1,(struct sockaddr*)&server,sizeof(server));
  if(k == -1)
    {
      printf("Binding error");
      exit(1);
    }
  
  k = listen(sock1,1);
  if(k == -1)
    {
      printf("Listen failed");
      exit(1);
    }
  
  len = sizeof(client);
  sock2 = accept(sock1,(struct sockaddr*)&client, &len);
  i = 1;

  while(1)
    {
      recv(sock2, buf, 100, 0); //recieve the request from client in buf
      sscanf(buf, "%s", command); //buf is the source string and will be copied to command(only the first word)
      printf("\nThe request recieved is: %s\n",buf);

    if(!strcmp(command, "ls"))
	{
	  //For ls we send the entire file because 	
	  system("pwd | ls >temps.txt");
	  i = 0;
	  stat("temps.txt",&obj);	//System call for status of a file
	  size = obj.st_size;
	  send(sock2, &size, sizeof(int),0);
	  filehandle = open("temps.txt", O_RDONLY);
	  sendfile(sock2,filehandle,NULL,size);

	}

    else if(!strcmp(command,"get"))
	{
	  sscanf(buf, "%s%s", filename, filename); //two filename arguements to get the second word in the buffer
	  // printf("%s \t %s \n ",buf,filename);
	  stat(filename, &obj);
	  filehandle = open(filename, O_RDONLY);
	  size = obj.st_size;
	  if(filehandle == -1)
	      size = 0;
	  send(sock2, &size, sizeof(int), 0);
	  if(size){
	   printf("Sending the file %s to the client\n",filename); 
	   sendfile(sock2, filehandle, NULL, size); //sock2 is the destination file descriptor and filehandler is the
	   printf("The file has been sent successfully\n");
	  }										  //source file descriptor. NULL:offset 	
      
	}
     
    else if(!strcmp(command, "put"))
    {
	  int c = 0, len;
	  char *f;
	  sscanf(buf+strlen(command), "%s", filename);
	  recv(sock2, &size, sizeof(int), 0);
	  printf("The size of the file being recieved at the server is: %d\n",size);
	  i = 1;
	  while(1)
	    {
		    filehandle = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0666);
		    if(filehandle == -1)
			{
			  sprintf(filename + strlen(filename), "%d", i);
			  i++; //To handle if file with given name already exists
			}
		    else
			  break;
	    }
	  f = malloc(size);
	  recv(sock2, f, size, 0);
	  c = write(filehandle, f, size);
	  close(filehandle);
	  send(sock2, &c, sizeof(int), 0);
	  if(c)
	  	printf("File successfully copied to the server\n");
	  else
	  	printf("File couldn't be copied to the server\n");
    }


    else if(!strcmp(command, "pwd"))
	{
	  system("pwd>temp.txt");
	  i = 0;
          FILE*f = fopen("temp.txt","r");
          while(!feof(f))
            buf[i++] = fgetc(f);
          buf[i-1] = '\0';
	  fclose(f);
          send(sock2, buf, 100, 0);
	}
      
    else if(!strcmp(command, "cd"))
    {
       if(chdir(buf+3) == 0)
	    c = 1;
	   else
	    c = 0;
          send(sock2, &c, sizeof(int), 0);
    }
 	
 
      else if(!strcmp(command, "bye") || !strcmp(command, "quit"))
	{
	  printf("FTP server quitting..\n");
	  i = 1;
	  send(sock2, &i, sizeof(int), 0);
	  exit(0);
	}
    }
  return 0;
}
