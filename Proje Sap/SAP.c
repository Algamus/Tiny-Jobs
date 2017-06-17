/*
==================================================================================================================
 Name        : SUPER ARCHIVING PROGRAM (SAP)
 Author      : Gokhan Gobus
 Version     : 
 Copyright   : Gokhan Gobus
 Description : It is a basic file archiving program
 Commands    : SAP.exe CREATE xxxx.saf filename1.extension ... filenameN.extansion
			   SAP.exe PRINT xxx.saf
			   SAP.exe EXTRACT ALL xxx.saf
			   SAP.exe EXTRACT xxx.saf filename1.extension
			   SAP.exe ADD xxx.saf filename1.extension ... filenameN.extension
 =================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>//exit(1) konutu için	
#include <string.h>// strcmp ve strcpy için
int uzunluk(FILE *fp){//dosyanın uzunluğunu hesapliyor
	int len;
	fseek(fp,0,SEEK_END);
	len=ftell(fp);
	fseek(fp,0,SEEK_SET);
	return len;
}
void create(int argc,char arg[][32]){//create fonksiyonu
	FILE *dosya[argc-1];
	char saf[]={'S','A','F'};
	int i,k,okuncak=0,x,byte;
	for(i=3;i<argc;i++){
		okuncak++;
		if((dosya[i-2]=fopen(arg[i],"rb"))==NULL){
			printf("Error-- %s diye bir dosya yok!\n",arg[i]);
			exit(1);
		}
	}
	if((dosya[0]=fopen(arg[2],"wb"))==NULL){
		printf("Error-- %s oluşumda hata oldu!\n",arg[2]);
		exit(1);
	}
	fwrite(saf,sizeof(char),3,dosya[0]);
	fwrite(&okuncak,sizeof(int),1,dosya[0]);
	for(k=0;k<okuncak;k++){
		fwrite(arg[k+3],sizeof(char),32,dosya[0]);
		byte=uzunluk(dosya[k+1]);
		fwrite(&byte,sizeof(int),1,dosya[0]);
		for(i=0;i<byte;i++){
			fread(&x,sizeof(char),1,dosya[k+1]);
			x=x^255;
			fwrite(&x,sizeof(char),1,dosya[0]);
		}
		fclose(dosya[k+1]);
	}
	fclose(dosya[0]);
}
void checksaf(FILE *file){//SAF controlu
	char saf[]={'S','A','F'},x;
	int t=0,i;
	for(i=0;i<3;i++){
		fread(&x,sizeof(char),1,file);
		if(x==saf[i]){
			t++;
		}
	}
	if(t!=3){
		printf("ERROR:This type is not .saf");
		exit(1);
	}
}
void add(int argc,char arg[][32]){// ADD fonksiyonu
	FILE *dosya[argc-1];
	int i,k,okuncak=0,x,byte,olan;
	for(i=3;i<argc;i++){
		okuncak++;
		if((dosya[i-2]=fopen(arg[i],"rb"))==NULL){
			printf("Error-- %s diye bir dosya yok!\n",arg[i]);
			exit(1);
		}
	}
	if((dosya[0]=fopen(arg[2],"rb+"))==NULL){
		printf("Error--%s diye bir dosya yok! \n",arg[2]);
		exit(1);
	}
	checksaf(dosya[0]);//SAF controlu
	fread(&olan,sizeof(int),1,dosya[0]);
	fseek(dosya[0],-sizeof(int),SEEK_CUR);
	olan=okuncak+olan;           // içindeki dosya sayısı kısmını güncel liyor
	fwrite(&olan,sizeof(int),1,dosya[0]);
	fseek(dosya[0],0,SEEK_END);
	for(k=0;k<okuncak;k++){
		fwrite(arg[k+3],sizeof(char),32,dosya[0]);
		byte=uzunluk(dosya[k+1]);
		fwrite(&byte,sizeof(int),1,dosya[0]);
		for(i=0;i<byte;i++){
			fread(&x,sizeof(char),1,dosya[k+1]);
			x=x^255;
			fwrite(&x,sizeof(char),1,dosya[0]);
		}
		fclose(dosya[k+1]);
	}
	fclose(dosya[0]);
}
void extract_all(char arg[][32]){ //EXTRACT ALL fonksiyonu
	FILE *dosya;
	int olan,i,k,x,byte;
	char name[32];
	if((dosya=fopen(arg[3],"rb"))==NULL){
		printf("Error--%s diye bir dosya yok!\n",arg[3]);
		exit(1);
	}
	checksaf(dosya);//SAF controlu
	fread(&olan,sizeof(int),1,dosya);
	FILE *bas[olan];
	for(i=0;i<olan;i++){
		fread(name,sizeof(char),32,dosya);
		fread(&byte,sizeof(int),1,dosya);
		if((bas[i]=fopen(name,"wb"))==NULL){
			printf("Error--%s oluşumda hata oldu!\n",name);
			exit(1);
		}
		for(k=0;k<byte;k++){
			fread(&x,sizeof(char),1,dosya);
			x=x^255;
			fwrite(&x,sizeof(char),1,bas[i]);
		}
		fclose(bas[i]);
	}
	fclose(dosya);
}
void extract(char arg[][32]){ //EXTRACT fonksiyonu
	FILE *dosya;
	int olan,i,k,x,byte;
	char name[32];
	if((dosya=fopen(arg[2],"rb"))==NULL){
		printf("Error--%s diye bir dosya yok!\n",arg[2]);
		exit(1);
	}
	checksaf(dosya); //SAF controlu
	fread(&olan,sizeof(int),1,dosya);
	FILE *bas[olan];
	for(i=0;i<olan;i++){
		fread(name,sizeof(char),32,dosya);
		fread(&byte,sizeof(int),1,dosya);
		if(!(strcmp(name,arg[3]))){
			if((bas[i]=fopen(name,"wb"))==NULL){
				printf("Error--%s oluşumda hata oldu!\n",name);
				exit(1);
			}
			for(k=0;k<byte;k++){
				fread(&x,sizeof(char),1,dosya);
				x=x^255;
				fwrite(&x,sizeof(char),1,bas[i]);
			}
			fclose(bas[i]);
	 	}else{
			fseek(dosya,sizeof(char)*byte,SEEK_CUR);
		}
	}
	fclose(dosya);
}
void inside(char arg[][32]){// PRINT fonksiyonu
	FILE *dosya;
	int olan,i,k,x,byte;
	char name[32];
	if((dosya=fopen(arg[2],"rb"))==NULL){
		printf("Error--%s diye bir dosya yok!\n",arg[2]);
		exit(1);
	}
	checksaf(dosya);// SAF controlu
	fread(&olan,sizeof(int),1,dosya);
	FILE *bas[olan];
	printf("%s içinde %d.dosya var\n",arg[2],olan);
	for(i=0;i<olan;i++){
		fread(name,sizeof(char),32,dosya);
		fread(&byte,sizeof(int),1,dosya);
		printf("File.%d : %s  Byte %d ",i+1,name,byte-1);
		for(k=0;k<byte;k++){
			fread(&x,sizeof(char),1,dosya);
			x=x^255;
		}
		printf("\n");
		
	}
	fclose(dosya);
}
int main(int argc,char *arg[]){//MAIN fonksiyonu
	int i;
	char gobus[argc][32];
	for(i=0;i<argc;i++){ //burası da kartvizit
		strcpy(gobus[i],arg[i]);
	}
	if(!(strcmp(arg[1],"CREATE"))){
		create(argc,gobus);
	}else if(!(strcmp(arg[1],"ADD"))){
		add(argc,gobus);
	}else if(!(strcmp(arg[1],"EXTRACT"))){
		if(!(strcmp(arg[2],"ALL"))){
			extract_all(gobus);
		}else{
			extract(gobus);
		}
	}else if(!(strcmp(arg[1],"PRINT"))){
		inside(gobus);
	}
	return 0;
}

