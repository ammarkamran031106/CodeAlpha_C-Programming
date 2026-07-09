// Student Managment Sytem
// Create a menu-driven C program to manage student records
// Features: Add, Delete, Update, Search, Display Records
// Use structures+ file handling to store data permanently.

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

struct Student{
	int id;
	char name[50];
	int age;
	float cgpa;
}; 

void addStudent()
{
    FILE *fp = fopen("students.dat", "rb+");

    if(fp == NULL)
    {
        printf("Cannot open file!\n");
        return;
    }

    Student s,temp;

    printf("Enter Student ID: ");
    scanf("%d", &s.id);
    
    rewind(fp);

    while (fread(&temp, sizeof(Student), 1, fp))
    {
        if (temp.id == s.id)
        {
            printf("\nStudent ID already exists!\n");
            fclose(fp);
            return;
        }
    }

    printf("Enter Name: ");
    scanf("%s", s.name);
   

    printf("Enter Age: ");
    scanf("%d", &s.age);
    

    printf("Enter CGPA: ");
    scanf("%f", &s.cgpa);
    
	fseek(fp, 0, SEEK_END);
    fwrite(&s, sizeof(Student), 1, fp);
    

    fclose(fp);

    printf("Student Added Successfully!\n");
}
void displayStudents(){
	
	FILE *fp = fopen("students.dat","rb");
	if(fp == NULL){
	
		printf("\n No Record Found! \n");
		return ;
	}
	
	Student s;
	
	printf(" \n ======================= \n");
	
	while(fread(&s, sizeof(Student), 1, fp)){
		printf("ID   : %d\n", s.id);
        printf("Name : %s\n", s.name);
        printf("Age  : %d\n", s.age);
        printf("CGPA : %.2f\n", s.cgpa);
        printf("------------------------------\n");
        
	}
	
	fclose(fp);
}


void searchStudent(){
	
	
	FILE *fp = fopen("students.dat","rb");
	
	if(fp == NULL){
		printf(" \n No Record Found \n");
		return;
		
	}
	
	Student s;
	int id;
	int found = 0;
	
	printf("Enter Student ID: ");
	scanf("%d",&id);
	
	while(fread(&s,sizeof(Student),1,fp)){
		if (s.id == id ){
			printf("\nRecord Found\n");
            printf("ID   : %d\n", s.id);
            printf("Name : %s\n", s.name);
            printf("Age  : %d\n", s.age);
            printf("CGPA : %.2f\n", s.cgpa);
            
            found = 1;
            break;
            
		}
	}
	
	if( !found){
		printf(" \n Student Not Found \n");
	}
	
	fclose(fp);
	
}

void updateStudent(){
	FILE *fp = fopen("students.dat","rb");
	FILE *temp = fopen("temp.dat", "wb");
	
	if(fp ==NULL){
		
		printf(" \n No Record Found! \n");
		return;
	}
	
	Student s;
	int id;
	int found = 0;
	
	printf("Enter Student ID  to update: ");
	scanf(" %d", &id);
	
	while(fread(&s, sizeof(Student),1, fp)){
		if(s.id == id){
			found = 1;
			
			printf("\nEnter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Age: ");
            scanf("%d", &s.age);

            printf("Enter New CGPA: ");
            scanf("%f", &s.cgpa);
		}
		
		fwrite(&s, sizeof(Student), 1, temp);
		
	}
	
	fclose(fp);
	fclose(temp);
	
	remove("students.dat");
	rename("temp.dat", "students.dat");
	
	if(found){
		printf (" \n Record Deleted Succesfully! \n");
		
	}
	else{
		printf(" \n Student Not Found ! \n ");
		
	}
}

void deleteStudent()
{
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    Student s;
    int id;
    int found = 0;

    printf("Enter Student ID to Delete: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(Student), 1, fp))
    {
        if (s.id == id)
        {
            found = 1;
            continue;
        }

        fwrite(&s, sizeof(Student), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("\nRecord Deleted Successfully!\n");
    else
        printf("\nStudent Not Found!\n");
}


int main()
{
    int choice;

    do
    {
        printf("\n========== STUDENT MANAGEMENT ==========\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("\nGood Bye!\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    } 
	while (choice != 6);

    return 0;
}
