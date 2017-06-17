/*
==================================================================================================================
 Name        : GuessMyNumber
 Author      : Gokhan Gobus
 Version     : 
 Copyright   : Gokhan Gobus
 Description : The computer generate a number between 4 and 11 and  user  guess that number. 
 =================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>

#define END 1111

bool isEnd=false;
int x;

int game(void)
{
	int n;
	while(!isEnd){
		scanf("%d",&n);
		if(n==END){
			printf("YOU ARE ENDED THE GAME\n");
			isEnd=true;
			return 1; 
		}else{
			if(n!=x){
				if(((x-3)<=n) && (n<=(x+3))){
					printf("TOO CLOSE, PLEASE TRY AGAIN\n");
				}else{
					printf("YOU CAN NOT FIND THE NUMBER.PLEASE TRY AGAIN.\n");
				}
				printf("Enter a number between 4 and 11 to find the defined number.\nEnter 1111 to exit.\n>>");
				
			}else{
				printf("CONGRATULATIONS !!\n");
				isEnd=true;
				return 0;
			}
		}
	}
}
int main(void)
{
	x=rand()%7+4;
	printf("Enter a number between 4 and 11 to find the defined number.\nEnter 1111 to exit.\n>>");
	game();
	return 0;
}
