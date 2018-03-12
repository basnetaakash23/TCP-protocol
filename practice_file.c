//
//  practice_file.c
//  
//
//  Created by AakashBasnet on 3/8/18.
//

#include <stdio.h>
#include <stdlib.h>
//#include "inttypes.h"

int main(){
    FILE *fp = NULL;
    FILE *fp1 = NULL;
    
    uint8_t type = 0;
    uint8_t amount = 2;
    uint16_t nums[2] = {258,772};
    short result[3];
//    for(int i =0; i<3;i++){
//        nums[i] = nums[i]>>8|nums[i]<<8;
//    }
    
    int c;
    int d;
    fp = fopen("file1", "wb+");
    //fp1 = fopen("file3.txt", "w");
    
    /**
     <#Description#>

     @param nums <#nums description#>
     @param int <#int description#>
     @return <#return value description#>
     */
//    uint8_t t = 0;
//    uint8_t a = 3;
//    fwrite(&t, sizeof(uint8_t),1,fp);
//    fwrite(&a, sizeof(uint8_t),1,fp);
//    int r = 21;
//    int ta = 3;
//    fwrite(&r, sizeof(int),1,fp);
//    fwrite(&ta, sizeof(int),1,fp);
    char amount_[3] ;
    amount_[0] = 48;
    amount_[1] = 48;
    amount_[2] = amount;
    amount_[3] = '\0';
    
    fwrite(&type, sizeof(uint8_t),1, fp);
    fprintf(fp,"%s",amount_);
//    fwrite(nums, sizeof(short), 3, fp);
//    rewind(fp);
//    fread(result, sizeof(int), 4, fp);
   int i =0;
    int j = 0;
    //memcpy(result+2,nums+4,2);
    //printf("%d\n",result[2]);
    while(i<amount){
        //memcpy(result+i,nums+j,2);
        //result[i] = result[i]>>8|result[i]<<8;
        fprintf(fp, "%d", nums[i]);
        //fwrite(result+i, sizeof(short),1,fp);
        i++;
        
    }
    
//
//    printf("Result\n");
//    for(int i = 0; i<3; i++){
//        printf("%d = %d\n",i, nums[i]);
//    }
//
    
//    while(1){
//        c = fgetc(fp);
//        //d = fgetc(fp1);
//        if(feof(fp)){
//            break;
//        }
//        printf("%d\n", c);
//        //printf("%d asdas\n",d);
//    }
    
    fclose(fp);
    
    return 0;
}
