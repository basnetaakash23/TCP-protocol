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




/*  main()  */

int main(int argc, char *argv[]) {

    int       conn_s;                /*  connection socket         */
    short int port;                  /*  port number               */
    struct    sockaddr_in servaddr;  /*  socket address structure  */
    char      buffer[MAX_LINE];      /*  character buffer          */
    char     *szAddress;             /*  Holds remote IP address   */
    char     *szPort;                /*  Holds remote port         */
    char     *endptr;                /*  for strtol()              */
    char     *filepath;              /*  Holds the file path       */
    char     *toFormat;              /*  Holds the value of target file conversion format*/
    char     *toName;                /*  Holds the name for targetfile */


    /*  Get command line arguments  */
    if(argc != 6){
        printf("Incomplete Command Line arguments\n");
        exit(EXIT_FAILURE);
        return -1;
    }
    szAddress = argv[1];
    szPort = argv[2];
    filepath = argv[3];
    toFormat = argv[4];
    toName = argv[5];
    
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

//    printf("Enter the string to echo: \n");
//    char buffer1[10] = {'a','b','c','d','e','f','g','h','i','j'};
//    fgets(buffer, MAX_LINE, stdin);
    //store the file length so that can be sent to the client and later use to allocate the length for filename in server
    uint8_t filename_length = strlen(toName);

    //open the file that we are reading from
    FILE* fp = fopen(filepath,"rb");
    fseek(fp,0,SEEK_END);
    int file_length = ftell(fp);
    rewind(fp);


    printf("%d\n", file_length);


    char file_buffer[file_length];


    int num_of_items = fread(file_buffer, 1, file_length, fp);
    

    //just reading the file
    for (int j=0; j<num_of_items; j++) {
        printf("%d == %d\n", j+1,file_buffer[j]);
    }

    //printf("%d\n", num_of_items);

    if (num_of_items <= 1) {
        printf("Error reading file\n");
    }


    //printf("%c\n", file_buffer[0]);
    printf("%d the filename length\n",filename_length);

    //copying the address of meta information of the file and the required specification to the server
    memcpy(buffer, toFormat,1);
    memcpy(buffer+1, &filename_length,1);
    memcpy(buffer+2, toName, filename_length);
    memcpy(buffer+2+filename_length, &file_length, 4);
    memcpy(buffer+6+filename_length, file_buffer, num_of_items);

    // printf("The file _length is %d\n",file_length);
    // memcpy(buffer,&file_length,sizeof(uint8_t));
    // memcpy(buffer+sizeof(uint8_t),&toFormat,sizeof(char));
    // memcpy(buffer+sizeof(uint8_t)+sizeof(char),&filename_length, sizeof(uint8_t));
    // memcpy(buffer+ 2* sizeof(uint8_t)+sizeof(char), toName, filename_length);
    
    // memcpy(buffer+2*sizeof(uint8_t)+1+filename_length,file_buffer, file_length);
    
    write(conn_s, buffer, MAX_LINE);
    /*  Send string to echo server, and retrieve response  */
    char connection_response[100];
   
    read(conn_s, connection_response,100);
    /*  Output echoed string  */

    printf("Echo response: %s \n", connection_response);
    return EXIT_SUCCESS;
}




