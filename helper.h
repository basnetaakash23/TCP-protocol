//
//  helper.h
//  TCP_PROGRAMMING
//
//  Created by AakashBasnet on 3/7/18.
//

#ifndef helper_h
#define helper_h

#include <stdio.h>

#include <unistd.h>             /*  for ssize_t data type  */

#define LISTENQ        (1024)   /*  Backlog for listen()   */


/*  Function declarations  */

ssize_t Readline(int fd, void *vptr, size_t maxlen);
ssize_t Writeline(int fc, const void *vptr, size_t maxlen);
void convert_to_typeOne(FILE* pointer, uint8_t amount, uint16_t numbers[]);
void convert_to_typeTwo(FILE* pointer,  uint8_t amount, short first_input);
void process_file(char* buffer, int length_of_file);
int first_input_type_to_second(int pos, char* binary_buffer, FILE* pointer);
int second_input_type_to_first(int pos, char* binary_buffer, FILE *pointer);


#endif  /*  PG_SOCK_HELP  */



