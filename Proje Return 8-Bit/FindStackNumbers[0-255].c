/*
==================================================================================================================
 Name        : FindStackNumbers[0-255]
 Author      : Gokhan Gobus
 Version     : 
 Copyright   : Gokhan Gobus
 Description : The program find the stack numbers between [0-255] and print them on the screen with their bit configurations. 
		Stack number Rules: 
• The bits must start with 1 and end with 0 
• Number of 1s must be equal to number of 0s 
• Start from left to right to sum the values of these bits, count 1 for 1s and count -1 for zeros.
• The sum must never be less than zero at any bit until the end of bits. 
 =================================================================================================================
*/

#include <stdio.h>
int main(void)
{
	int i,bs,number,k,ss,sum=0,b[8];
	for(number=0;number<=255;number+=1){
		for(i=7,k=number;i>=0;i-=1,k=k>>1){
			b[i]=k&1;
		}
		for(bs=0,ss=0,sum=0,i=0;i<8;i++){
			if(b[i]==0){
				sum-=1;
				ss+=1;
			}else{
				sum+=1;
				bs+=1;
			}
		}
		if(sum==0 && bs==ss && b[0]==1 && b[7]==0){
			printf("%d  %d%d%d%d%d%d%d%d\n",number,b[0],b[1],b[2],b[3],b[4],b[5],b[6],b[7]);
		}
	}
	return 0;
}
