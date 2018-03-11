/*

  ECHOCLNT.C
  ==========
  (c) Paul Griffiths, 1999
  Email: mail@paulgriffiths.net
  
  Simple TCP/IP echo client.

*/


#include <sys/socket.h>       /*  socket definitions        */
#include <sys/types.h>        /*  socket types              */
#include <arpa/inet.h>        /*  inet (3) funtions         */
#include <unistd.h>           /*  misc. UNIX functions      */

#include "helper.h"           /*  Our own helper functions  */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string.h>

/*  Global constants  */

#define MAX_LINE           (1000)


/*  Function declarations  */


int ParseCmdLine(int argc, char *argv[], char **szAddress, char **szPort);


/*  main()  */

int main(int argc, char *argv[]) {

    int       conn_s;                /*  connection socket         */
    short int port;                  /*  port number               */
    struct    sockaddr_in servaddr;  /*  socket address structure  */
    char      buffer[MAX_LINE];      /*  character buffer          */
    char     *szAddress;             /*  Holds remote IP address   */
    char     *szPort;                /*  Holds remote port         */
    char     *endptr;                /*  for strtol()              */


    /*  Get command line arguments  */

    ParseCmdLine(argc, argv, &szAddress, &szPort);


    /*  Set the remote port  */

    port = strtol(szPort, &endptr, 0);
    if ( *endptr ) {
	printf("ECHOCLNT: Invalid port supplied.\n");
	exit(EXIT_FAILURE);
    }
	

    /*  Create the listening socket  */

    if ( (conn_s = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
	fprintf(stderr, "ECHOCLNT: Error creating listening socket.\n");
	exit(EXIT_FAILURE);
    }


    /*  Set all bytes in socket address structure to
        zero, and fill in the relevant data members   */

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_port        = htons(port);


    /*  Set the remote IP address  */

    if ( inet_aton(szAddress, &servaddr.sin_addr) <= 0 ) {
	printf("ECHOCLNT: Invalid remote IP address.\n");
	exit(EXIT_FAILURE);
    }

    
    /*  connect() to the remote echo server  */

    if ( connect(conn_s, (struct sockaddr *) &servaddr, sizeof(servaddr) ) < 0 ) {
	printf("ECHOCLNT: Error calling connect()\n");
	exit(EXIT_FAILURE);
    }


    /*  Get string to echo from user  */

    printf("Enter the string to echo: \n");
    char buffer1[10] = {'a','b','c','d','e','f','g','h','i','j'};
//    fgets(buffer, MAX_LINE, stdin);
    FILE* fp = fopen("practice_project_test_file_1","rb");
    fseek(fp,0,SEEK_END);
    uint8_t file_length = ftell(fp);
    rewind(fp);
    
    
    char file_buffer[file_length];
    
    
    int num_of_items = fread(file_buffer, file_length, 1, fp);
    
    printf("The file _length is %d\n",file_length);
    memcpy(buffer,&file_length,sizeof(int));
    memcpy(buffer+sizeof(uint8_t),file_buffer, file_length);
    write(conn_s, buffer, file_length);
    //Writeline(conn_s, &size, sizeof(size));
   
    
     //Readline(conn_s, &size, sizeof(size));
    
    

    /*  Send string to echo server, and retrieve response  */
   
    read(conn_s, file_buffer,file_length);

   
//    Readline(conn_s, buffer1, size);


    /*  Output echoed string  */

    printf("Echo response: %s \n", buffer1);
    
    
    return EXIT_SUCCESS;
}


int ParseCmdLine(int argc, char *argv[], char **szAddress, char **szPort) {

    int n = 1;

    while ( n < argc ) {
	if ( !strncmp(argv[n], "-a", 2) || !strncmp(argv[n], "-A", 2) ) {
	    *szAddress = argv[++n];
	}
	else if ( !strncmp(argv[n], "-p", 2) || !strncmp(argv[n], "-P", 2) ) {
	    *szPort = argv[++n];
	}
	else if ( !strncmp(argv[n], "-h", 2) || !strncmp(argv[n], "-H", 2) ) {
	    printf("Usage:\n\n");
	    printf("    timeclnt -a (remote IP) -p (remote port)\n\n");
	    exit(EXIT_SUCCESS);
	}
	++n;
    }

    return 0;
}

