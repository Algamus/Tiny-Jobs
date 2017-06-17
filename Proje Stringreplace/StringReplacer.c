/*
==================================================================================================================
 Name        : String replacer on Word.
 Author      : Gokhan Gobus
 Version     : 
 Copyright   : Gokhan Gobus
 Description : Program find all occurances of string2 in string1, and replace them with string3.
			   The string substituting task is case insensitive. 
 
 =================================================================================================================
*/
#include <stdio.h>
#define SIZE 100 
int len(char array[SIZE])
{
	int i;
	for(i=0;array[i]!='\0';i++){
	}
	return i;
}
void cevir(char arraya[SIZE],int sizea,char arrayb[SIZE],int sizeb,char arrayc[SIZE],int sizec)
{
	char result[SIZE];
	int i,y,k,count;
	for(i=0,k=0;i<sizea;){
		if(arraya[i]==arrayb[0] || arraya[i]==arrayb[0]+('a'-'A') || arraya[i]==arrayb[0]-('a'-'A')){
			for(count=1,y=1;y<sizeb && i+y<sizea;y++){
				if(arraya[i+y]==arrayb[y] || arraya[i+y]==arrayb[y]+('a'-'A') || arraya[i+y]==arrayb[y]-('a'-'A')){
					count++;
				}
			}
			if(count==sizeb){
				for(y=0;y<sizec;y++,k++){
					result[k]=arrayc[y];
				}
				i+=sizeb;
			}else{
				result[k]=arraya[i];
				i++;
				k++;
			}
		}else{
			result[k]=arraya[i];
			i++;
			k++;
		}
	}
	result[k]='\0';
	printf("%s\n",result);
}
int main(void)
{
	printf("!! Uyarı türkçe karakterler sıkıntı çıkarabilir. !!\n");
	char arraya[SIZE],arrayb[SIZE],arrayc[SIZE];
	printf("Enter the main string (Max 100 char) : ");
	gets(arraya);
	printf("Enter the string to repleaced (Max 100 char) : ");
	scanf("%s",arrayb);
	printf("Enter the new string (Max 100 char) : ");
	scanf("%s",arrayc);
	cevir(arraya,len(arraya),arrayb,len(arrayb),arrayc,len(arrayc));
	return 0;
}