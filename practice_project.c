#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "inttypes.h"
#include "unistd.h"

extern int convert_option = 3;

int typezero_input(int pos, char* binary_buffer, FILE* pointer);
void convert_to_typeOne(FILE* pointer,  uint8_t amount, uint16_t numbers[]);
int typefirst_input(int pos, char* binary_buffer, FILE *pointer);
void convert_to_typeZero(FILE* pointer, short amount, short numbers[]);




int main(){
	int length_of_file;
   
	FILE *ptr;
    FILE *ptr1;
	
	ptr = fopen("practice_project_test_file_1","rb");
    ptr1 = fopen("practice_project_write_file_2","wb+");
    fseek(ptr1, 0, SEEK_SET);
	fseek(ptr, 0, SEEK_END);
	length_of_file = ftell(ptr);
	printf("The length of file is %d\n",length_of_file);
	rewind(ptr);
	char buffer[length_of_file];
	int num_of_bytes = fread(buffer, length_of_file, 1, ptr);
	int j = 0;
    int i = 0;
    










