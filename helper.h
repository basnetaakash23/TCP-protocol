/*

  HELPER.H
  ========
  (c) Paul Griffiths, 1999
  Email: paulgriffiths@cwcom.net

  Interface to socket helper functions. 

  Many of these functions are adapted from, inspired by, or 
  otherwise shamelessly plagiarised from "Unix Network 
  Programming", W Richard Stevens (Prentice Hall).

*/


#ifndef PG_SOCK_HELP
#define PG_SOCK_HELP


#include <unistd.h>             /*  for ssize_t data type  */
#include <stdio.h>

#define LISTENQ        (1024)   /*  Backlog for listen()   */


/*  Function declarations  */
void process_file(char* buffer, int length_of_file, FILE* pointer);
int typezero_input(int pos, char* binary_buffer, FILE* pointer);
void convert_to_typeOne(FILE* pointer,  int amount, short first_input);
int typefirst_input(int pos, char* binary_buffer, FILE *pointer);
void convert_to_typeZero(FILE* pointer, short amount, short numbers[]);


ssize_t Readline(int fd, void *vptr, size_t maxlen);
ssize_t Writeline(int fc, const void *vptr, size_t maxlen);


#endif  /*  PG_SOCK_HELP  */

