/*

  HELPER.C
  ========
  (c) Paul Griffiths, 1999
  Email: mail@paulgriffiths.net

  Implementation of sockets helper functions.

  Many of these functions are adapted from, inspired by, or 
  otherwise shamelessly plagiarised from "Unix Network 
  Programming", W Richard Stevens (Prentice Hall).

*/

//
//  serv_helper.c
//
//
//  Created by AakashBasnet on 3/10/18.
//
#include "stdint.h"
#include "inttypes.h"
#include "helper.h"
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


extern int convert_option = 3;




void process_file(char* buffer, int length_of_file, FILE* pointer){
    int i = 0;
    
    while(i < length_of_file){
        printf("The value in buffer is %u\n",buffer[i]);
        if(buffer[i] == 0){
            //printf("Buffer i is %02x and index is %u\n",buffer[i], i);
            printf("The index here in type 1 is %d\n", i);
            i = zero_input_type_to_first(i, buffer,pointer);
            printf("The index returned here in type 1 is %d\n",i);
            
        }
        else if(buffer[i] == 1){
            printf("The index here in type 2 is %d\n",i);
            i = first_input_type_to_zero(i,buffer, pointer);
            printf("The index returned here in type 2 is %d\n",i);
        }
        
    }
    
    printf("Succesfully converted and written into the file\n");
    
}


int typezero_input(int pos, char* binary_buffer, FILE* pointer){
    
    FILE* ptr = pointer;
    printf("The index before entering type 1 is %d\n", pos);
    int size_of_unit = 2;
    int amount = binary_buffer[pos+1];
    int num_of_units = size_of_unit * binary_buffer[pos+1];
    
    short int first_input[num_of_units/2];
    printf("The number of amount is %d\n",binary_buffer[pos+1]);
    int count = pos+2;
    int inner_count = 0;
    int i = 0;
    
    while(inner_count < num_of_units){
        printf("The binary_buffer is %d\n",binary_buffer[count]);
        printf("The binary_buffer+1 is %d\n",binary_buffer[count+1]);
        memcpy(first_input+i, (binary_buffer+count), 2);
        i = i + 1;
        count = count + 2;
        inner_count = inner_count + 2;
    }
    printf("I fot out of while loop\n");
    convert_to_typeOne(ptr, amount, first_input);
    printf("I think I did not reach here\n");
    
    return count;
}

void convert_to_typeOne(FILE* pointer,  int amount, short first_input){
    
    if(convert_option == 3 || convert_option == 1){
        
        uint8_t type = 1;
        printf("I am inside the conversion function\n");
        fwrite(&type, sizeof(uint8_t), 1, pointer);
        //fprintf(pointer,"%d",type);
        printf("I was just about to convert it\n");
        //        fwrite(&amount, sizeof(uint8_t), 1, pointer);
        int threebyte_amount = amount;
        char amount_array[4];
        uint8_t num;
        for(int i =3; i>0; --i){
            num = threebyte_amount % 10;
            num = num+48;
            threebyte_amount = threebyte_amount /10;
            amount_array[i-1] = num;
            
        }
        amount_array[3] = '\0' ; //null character
        for(int i =0; i<3; i++){
            fprintf(pointer, "%c", amount_array[i]);
        }
        
        fprintf(pointer, "%d", (short)amount);
        int i = 0;
        while(i<amount){
            
            printf("Trying to write files\n");
            fprintf(pointer,"%d",first_input+i);
            printf("Not sure if it was succesful\n");
            if(i<=amount-2){   //if condition to insert comma
                fprintf(pointer,"%s",",");
            }
            i++;
        }
    }
    printf("I think I converted it\n");
}



int typefirst_input(int pos, char* binary_buffer, FILE *pointer){
    printf("The index before entering type 2 is %d\n", pos);
    FILE* ptr = pointer;
    int i = pos;
    int amount = (binary_buffer[i+1]-48)*100 + (binary_buffer[i+2]-48)*10 + binary_buffer[i+3]-48;
    printf("The amount is %d\n",amount);
    int second_input[amount];    //this is where we store asccii values so that they can be written later on on file
    
    i = i + 4;
    int count = 1;
    //for counting the numbers of unit of the type 1 and we assume that there is at least one such unit until we find either 0 or a comma.
    int j  = 0; //working around with concatenating the bytes of ascii values
    long value = 0;      //this is the variable where we temporarily store the asccii value
    int num_of_units = 0;
    int comma = 44;
    int type0 = 0;
    int type1 = 1;     //assigning value to type 1
    int ind = 0;      //this for storing values of numbers in character array
    
    while(num_of_units<amount){
        if(binary_buffer[i] == comma){
            num_of_units = num_of_units + 1;
            printf("The value of value is %ld\n",value);
            second_input[ind] = value;
            ind = ind + 1;
            i = i+1;
            j=0;
        }
        else if(binary_buffer[i] == type0 | binary_buffer[i] == type1){
            
            printf("The index before returning to main from type 2 is %d\n", i);
            convert_to_typeZero(ptr, amount, second_input);
            return i;
        }
        else{
            if(j>0){
                value = value*10 + (binary_buffer[i]-48);
                printf("just the value is for the so on and so forth %ld\n", value);
                i = i + 1;
                j = j + 1;
            }
            else{
                value = binary_buffer[i]-48;
                printf("just the value is for the first time is  %ld\n", value);
                j = j+1;
                i = i+1;
            }
        }
    }
}

void convert_to_typeZero(FILE* pointer, short amount, short numbers[]){
    if(convert_option == 3 || convert_option == 2){
        printf("Converting \n");
        uint8_t type = 0;
        uint8_t amount = (uint8_t) amount;
        
        fwrite(&type, sizeof(uint8_t), 1, pointer);
        fwrite(&amount, sizeof(uint8_t),1, pointer);
        fwrite(numbers, sizeof(short), amount, pointer);
        
        
    }
    else{
        printf("Just write whatever files we read onto the writefile\n");
    }
    printf("Converted\n");
    
}


//ssize_t Readline(int sockd, void *vptr, size_t maxlen) {
//    ssize_t n, rc;
//    char    c, *buffer;
//
//    buffer = vptr;
//
//    for ( n = 1; n < maxlen; n++ ) {
//
//        if ( (rc = read(sockd, &c, 1)) == 1 ) {
//            *buffer++ = c;
//            if ( c == '\n' )
//                break;
//        }
//        else if ( rc == 0 ) {
//            if ( n == 1 )
//                return 0;
//            else
//                break;
//        }
//        else {
//            if ( errno == EINTR )
//                continue;
//            return -1;
//        }
//    }
//
//    *buffer = 0;
//    return n;
//}
//
//
///*  Write a line to a socket  */
//
//ssize_t Writeline(int sockd, const void *vptr, size_t n) {
//    size_t      nleft;
//    ssize_t     nwritten;
//    const char *buffer;
//
//    buffer = vptr;
//    nleft  = n;
//
//    while ( nleft > 0 ) {
//        if ( (nwritten = write(sockd, buffer, nleft)) <= 0 ) {
//            if ( errno == EINTR )
//                nwritten = 0;
//            else
//                return -1;
//        }
//        nleft  -= nwritten;
//        buffer += nwritten;
//    }
//
//    return n;
//}









