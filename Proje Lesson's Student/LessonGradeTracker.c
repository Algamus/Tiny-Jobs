/*
==================================================================================================================
 Name        : LessonGradeTracker
 Author      : Gokhan Gobus
 Version     : 
 Copyright   : Gokhan Gobus
 Description : Keeps track of student data. Each student have these data : ID, Name, Surname and three exam grades(Midterm 1 & 2 and Final).
			   Program keeps track of 100 students at most. 
 =================================================================================================================
*/

#include <stdio.h>
#include <string.h>

struct student{
	int id;
	char name[32];
	char surname[32];
	int mt1;
	int mt2;
	int final;
};


void readData(struct student *);
void addStudent(struct student *, int);
void removeStudent(struct student *, int);
void findAverage(struct student *);
void printAll(struct student *);
void writeData(struct student *);


int main(void){

	struct student list[100];
	int choice;
	int id;

	readData(list);

	do{
		printf( "1) Add Student\n2) Delete Student\n3) Calculate Average\n4) Print All\n5) Exit\n");

		printf("Your choice : ");
		scanf("%d", &choice);

		switch(choice){
		case 1:

			printf("Enter the new student's id : ");
			scanf("%d", &id);

			addStudent(list, id);
			break;

		case 2:

			printf("Enter the id of the student to be deleted : ");
			scanf("%d", &id);

			removeStudent(list, id);
			break;

		case 3:

			findAverage(list);
			break;

		case 4:

			printAll(list);
			break;
		case 5:
			writeData(list);
			return 0;
		default:
			printf("Invalid choice : %d\n\n", choice);
			break;
		}

	}while(1);

	return 0;


}


void readData(struct student * l){

	FILE * f;
	int i;

	for(i=0; i<100; i++){
		l[i].id = -1;		// Invalidate all 100 entries
	}

	f = fopen("data.txt","r");

	if(f==NULL){
		return;
	}

	i = 0;
	while(!feof(f)){
		fscanf(f, "%d\n", &(l[i].id));
		fgets(l[i].name, 256, f);
		l[i].name[strlen(l[i].name)-1] = '\0';	// gets reads the '\n' character too. This line removes it.
		fgets(l[i].surname, 256, f);
		l[i].surname[strlen(l[i].surname)-1] = '\0';	// gets reads the '\n' character too. This line removes it.
		fscanf(f, "%d\n", &(l[i].mt1));
		fscanf(f, "%d\n", &(l[i].mt2));
		fscanf(f, "%d\n", &(l[i].final));
		i++;
	}

	fclose(f);

	return;

}



void addStudent(struct student * l, int id){

	int i;

	/* If a student with same id already exists */
	for(i=0; i<100; i++){
		if(l[i].id == id){
			printf("A student with id %d already exists\n\n", id);
			return;
		}
	}

	/* Find first empty space */
	for(i=0; i<100; i++){
		if(l[i].id == -1)
			break;
	}

	if(i == 100){
		printf("No space left\n");
		return;
	}

	l[i].id = id;
	
	printf("Enter name : ");
	fflush(stdin);
	gets(l[i].name);
	
	printf("Enter surname : ");
	fflush(stdin);
	gets(l[i].surname);

	printf("Enter first midterm grade : ");
	scanf("%d", &(l[i].mt1));

	printf("Enter second midterm grade : ");
	scanf("%d", &(l[i].mt2));

	printf("Enter final exam grade : ");
	scanf("%d", &(l[i].final));

	printf("\n");

	return;

}


void removeStudent(struct student * l, int id){

	int i;

	for(i=0; i<100; i++){
		if(l[i].id == id){
			l[i].id = -1;
			return;
		}
	}

	printf("No student found with the id %d\n\n", id);

	return;

}



void findAverage(struct student * l){

	int i;
	int count;
	float sum;

	sum = 0.0;
	count = 0;
	for(i=0; i<100; i++){
		if(l[i].id != -1){
			sum += l[i].mt1 * 0.3 + l[i].mt2 * 0.3 + l[i].final * 0.4;
			count++;
		}
	}

	printf("The average grade is : %f with %d students\n\n", sum/count, count);

	return;

}

void printAll(struct student * l){
	int i;
	printf("\n\n");
	for(i=0; i<100;i++){
		if(l[i].id != -1){
			printf("%d  %s %s :: Midterm 1: %d , Midterm 2: %d , Final: %d\n",   l[i].id,
													l[i].name,
													l[i].surname,
													l[i].mt1,
													l[i].mt2,
													l[i].final);
		}
	}
	printf("\n\n");
	return;

}
void writeData(struct student * l){

	FILE * f;
	int i;

	f = fopen("data.txt", "w");

	for(i=0; i<100;i++){
		if(l[i].id != -1){
			fprintf(f,"%d\n%s\n%s\n%d\n%d\n%d\n",   l[i].id,
													l[i].name,
													l[i].surname,
													l[i].mt1,
													l[i].mt2,
													l[i].final);
		}
	}

	fclose(f);

	return;

}