//
//  client.c
//  TCP_PROGRAMMING
//
//  Created by AakashBasnet on 3/6/18.
//




#include <sys/socket.h>       /*  socket definitions        */
#include <sys/types.h>        /*  socket types              */
#include <arpa/inet.h>        /*  inet (3) funtions         */
#include <unistd.h>           /*  misc. UNIX functions      */

#include "helper.h"           /*  Our own helper functions  */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*  Global constants  */

#define MAX_LINE           (1000)

char const *fileName = "/Users/aakashbasnet/Desktop/ComputerNetworks/TCP_PROGRAMMING/TCP_PROGRAMMING/practice_project_test_file_1";



/*  Function declarations  */




/*  main()  */

int main(int argc, char *argv[]) {
    
    int       conn_s;                /*  connection socket         */
    short int port;                  /*  port number               */
    struct    sockaddr_in servaddr;  /*  socket address structure  */
    char      buffer[MAX_LINE];      /*  character buffer          */
    char     szAddress;             /*  Holds remote IP address   */
    char     szPort;                /*  Holds remote port         */
    char     *endptr;                /*  for strtol()              */
    char     filepath;
    char     toformat;
    char     toName;
    
    
    /*  Get command line arguments  */
    int n = 1;
    while ( n < argc ) {
        szAddress = argv[++n];
        szPort = argv[++n];
        filepath = argv[++n];
        toformat = argv[++n];
        toName = argv[++n];
        ++n;
    }
    
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
    
//    printf("Enter the string to echo: ");
//    fgets(buffer, MAX_LINE, stdin);
//
    FILE *fp = fopen(fileName, "rb");
    if(fp == NULL){
        perror("Error");
        return -1;
    }
    fseek(fp, 0, SEEK_END);
    int file_length = ftell(fp);
    rewind(fp);
    char file_buffer[file_length];
    int num_of_items = fread(file_buffer, 1, file_length, fp);
    if(num_of_items!= file_length){
        printf("File size mismatch!");
    }
    
    /*  Send string to echo server, and retrieve response  */
    Writeline(conn_s, &file_length, sizeof(int));
    
    Writeline(conn_s, file_buffer, file_length);
    Readline(conn_s, buffer, MAX_LINE-1);
    
    
    /*  Output echoed string  */
    
    //printf("Echo response: %s\n", buffer);
    
    return EXIT_SUCCESS;
}


