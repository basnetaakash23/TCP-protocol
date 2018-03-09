//
//  helper.c
//  TCP_PROGRAMMING
//
//  Created by AakashBasnet on 3/7/18.
//

#include "helper.h"
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>


/*  Read a line from a socket  */

ssize_t Readline(int sockd, void *vptr, size_t maxlen) {
    ssize_t n, rc;
    char    c, *buffer;
    
    buffer = vptr;
    
    for ( n = 0; n < maxlen; n++ ) {
        
        if ( (rc = read(sockd, &c, 1)) == 1 ) {
            buffer[n] = c;
            if ( c == '\n' )
                break;
        }
        else if ( rc == 0 ) {
            if ( n == 1 )
                return 0;
            else
                break;
        }
        else {
            if ( errno == EINTR )
                continue;
            return -1;
        }
    }
    
    *buffer = 0;
    return n;
}


/*  Write a line to a socket  */

ssize_t Writeline(int sockd, const void *vptr, size_t n) {
    size_t      nleft;
    ssize_t     nwritten;
    const char *buffer;
    
    buffer = vptr;
    nleft  = n;
    
    while ( nleft > 0 ) {
        if ( (nwritten = write(sockd, buffer, nleft)) <= 0 ) {
            if ( errno == EINTR )
                nwritten = 0;
            else
                return -1;
        }
        nleft  -= nwritten;
        buffer += nwritten;
    }
    
    return n;
}

void convert_to_typeOne(FILE* pointer, uint8_t amount, uint16_t numbers[]){
    if(convert_option == 3 || convert_option == 2){
        printf("Converting \n");
        uint8_t type = 0;
        //        uint8_t* t = type;
        //        uint8_t *a = amount;
        fwrite(&type, sizeof(uint8_t), 1, pointer);
        fwrite(&amount, sizeof(uint8_t),1, pointer);
        fwrite(numbers, sizeof(uint16_t), amount, pointer);
        
        //        fprintf(pointer, "%d", type);
        //        fprintf(pointer, "%d", amount);
        //        int i = 0;
        //        while(i<amount){
        //            fprintf(pointer, "%d",numbers+i);
        //            i++;
        //        }
    }
    else{
        printf("Just write whatever files we read onto the writefile\n");
    }
    printf("Converted\n");
    
}


void convert_to_typeTwo(FILE* pointer,  uint8_t amount, short first_input){
    
    if(convert_option == 3 || convert_option == 1){
        //        printf("Trying to convert files\n");
        //        int type = 1;
        //        int *tp = &type;
        //        fwrite(tp, sizeof(char), 1, pointer);
        uint8_t type = 1;
        printf("I am inside the conversion function\n");
        fwrite(&type, sizeof(uint8_t), 1, pointer);
        //fprintf(pointer,"%d",type);
        printf("I was just about to convert it\n");
        //        fwrite(&amount, sizeof(uint8_t), 1, pointer);
        fprintf(pointer, "%d", amount);
        int i = 0;
        while(i<amount){
            //fwrite(amount, sizeof(char),3, pointer);
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



//int main(){
//    int length_of_file;
//
//    FILE *ptr;
//    FILE *ptr1;
//
//    ptr = fopen("practice_project_test_file_1","rb");
//    ptr1 = fopen("practice_project_write_file3","wb+");
//    fseek(ptr1, 0, SEEK_SET);
//    fseek(ptr, 0, SEEK_END);
//    length_of_file = ftell(ptr);
//    printf("The length of file is %d\n",length_of_file);
//    rewind(ptr);
//    char buffer[length_of_file];
//    int num_of_bytes = fread(buffer, length_of_file, 1, ptr);
//    int j = 0;
//    int i = 0;
void process_file(char* buffer, int length_of_file){
    
    while(i < length_of_file){
        printf("The value in buffer is %u\n",buffer[i]);
        if(buffer[i] == 0){
            //printf("Buffer i is %02x and index is %u\n",buffer[i], i);
            printf("The index here in type 1 is %d\n", i);
            i = first_input_type_to_second(i, buffer,ptr1);
            printf("The index returned here in type 1 is %d\n",i);
            
        }
        else if(buffer[i] == 1){
            printf("The index here in type 2 is %d\n",i);
            i = second_input_type_to_first(i,buffer, ptr1);
            printf("The index returned here in type 2 is %d\n",i);
        }
        
    }
    //    printf("The index here in type 2 is %d\n",i);
    //    i = second_input_type_to_first(6,buffer, ptr1);
    //    printf("The index returned here in type 2 is %d\n",i);
    
    //    printf("The index here in type 1 is %d\n", i);
    //    i = first_input_type_to_second(23, buffer,ptr1);
    //    printf("The index returned here in type 1 is %d\n",i);
    fclose(ptr);
    fclose(ptr1);
    printf("Succesfully converted and written into the file\n");
    return 0;
}


int first_input_type_to_second(int pos, char* binary_buffer, FILE* pointer){
    
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
    convert_to_typeTwo(ptr, amount, first_input);
    printf("I think I did not reach here\n");
    //fwrite(first_input, sizeof(short), num_of_units/2 , pointer);  //
    //printf("The index before returning to main from type 1 is %d\n", count );
    return count;
}



int second_input_type_to_first(int pos, char* binary_buffer, FILE *pointer){
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
            convert_to_typeOne(ptr, amount, second_input);
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
