#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_SIZE 300
#define MAX_OF_ADDRESS 30
#define MAX_OF_NAME 30
#define MAX_OF_SEX 7
#define MAX_OF_EMAIL 30
#define MAX_OF_YEAR 5
#define MAX_OF_FALCUTY 6
#define MAX_OF_CLASS_IN_FALCUTY 5
#define MAX_OF_STUDENTS_LIST 101   
#define MAX_OF_CLASS 30      
#define MAX_OF_ID 10
#define MAX_OF_PHONE_NUMBER 11
#define MAX_OF_CID 13 
#define MAX_OF_RE_CHOOSE 10

int Number_of_Class_in_School=0;		    
int Class_Index = 0;                         
int Number_of_Student_Index = 0;            
int re_choose[MAX_OF_RE_CHOOSE];              

typedef struct Date {     
    int Day;
    int Month;
    int Year;
} Date;


typedef struct Students{
    char Last_Name[MAX_OF_NAME];
    char First_Name[MAX_OF_NAME];
    char Sex[MAX_OF_SEX];
    Date Birth;
    char Address[MAX_OF_ADDRESS]; 
    char Student_ID[MAX_OF_ID];
    char Email[MAX_OF_EMAIL];
    char Falcuty[MAX_OF_FALCUTY];
	char Phone_Number[MAX_OF_PHONE_NUMBER];
	char Citizen_ID[MAX_OF_CID];
} Student;

Student* Students[MAX_OF_STUDENTS_LIST];  

typedef struct {
	int Check_Sort;            
    int Number_of_Student;      
	char Name_of_Class[MAX_OF_CLASS];                           
} Classe; 


struct University{
	char Check_ID_falcuty[MAX_OF_FALCUTY][MAX_OF_ID];         
	Classe Classroom[MAX_OF_CLASS];           
};
 
struct University University;	

void addStudent(); 
void sortStudent(); 
void searchStudent(); 
void removeStudent(); 
void printClass(); 
void checkID(); 
void checkEmail(); 
void reset(); 
char* nameStr(char *s); 
void rewiteStudents(int i , FILE *file); 
int readFile(char* name_class); 
void quickSortByLastName(Student* arr[], int low, int high); 
void quickSortByFirstName(Student* arr[], int low, int high); 
void QuickSortClass(Classe s[], int left, int right);
char* increase_String(char* s);  
int binarySearch(Student* arr[], int l, int r, Student* x); 
void conditionSearch() ;
void printStudent(int found); 
void searchStudent_ID(); 
void searchStudent_Info(); 
void searchStudent_Citizen_ID(); 
void searchStudent_Phone_Number(); 
void RemoveStudent_ID(); 
void RemoveStudent_Citizen_ID(); 
void free_Data(); 
void add_Data(); 
void logo();
void menu();

int main(){
	add_Data();
	reset();
	menu();
	free_Data();
	return 0;
}

void reset(){
    int i;
    for(i=0;i<MAX_OF_CLASS;i++){
        University.Classroom[i].Number_of_Student= 0;
		University.Classroom[i].Check_Sort=0;
    }

	for(i=0;i<=MAX_OF_ID;i++){
		strcpy(University.Check_ID_falcuty[i],"");
	}
}

char* nameStr(char *s){
	int i=0;
	while(s[i]==' ') i++;
	if(i>0) strcpy(&s[0],&s[i]);

	i=strlen(s)-1;
	while(s[i]==' ') i--;
	s[i+1]='\0';

	char *ptr=strstr(s,"  ");
	while(ptr!=NULL){
		strcpy(ptr,ptr+1);
		ptr=strstr(s,"  ");
	}

	strlwr(s);
	int L=strlen(s);
	for(i=0;i<L;i++){
		if(i==0 ||( i>0 && s[i-1]==' ')) s[i]=toupper(s[i]);
	}

	return s;
}

void rewiteStudents(int i , FILE *file){
	fprintf(file,"%s;;",Students[i]->Last_Name);
	fprintf(file,"%s;;",Students[i]->First_Name);
	fprintf(file,"%d;;",Students[i]->Birth.Day);
	fprintf(file,"%d;;",Students[i]->Birth.Month);
	fprintf(file,"%d;;",Students[i]->Birth.Year);
	fprintf(file,"%s;;",Students[i]->Sex);
	fprintf(file,"%s;;",Students[i]->Address);
	fprintf(file,"%s;;",Students[i]->Phone_Number);
	fprintf(file,"%s;;",Students[i]->Citizen_ID);
	fprintf(file,"%s;;",Students[i]->Student_ID);
	fprintf(file,"%s\n",Students[i]->Email);
}

void addStudent(){
	int choose,i;
	char choose_falcuty[MAX_OF_FALCUTY];
	char choose_year[MAX_OF_YEAR];
		
	do{	
		printf("Enter Year School   : ");
		do{
			fflush(stdin);
       		gets(choose_year);
			if(strlen(choose_year) !=2 || (atoi(choose_year)<1 ||atoi(choose_year)>99) ) printf("Re-enter            : ");
		} while(strlen(choose_year) !=2 || (atoi(choose_year)<1 ||atoi(choose_year)>99));
		
		printf("Enter ID Falcuty    : ");
		fflush(stdin);
		do{
			gets(choose_falcuty);
			if(strcmp(choose_falcuty,"102")!=0 && strcmp(choose_falcuty,"107")!=0 && strcmp(choose_falcuty,"105")!=0 && strcmp(choose_falcuty,"123")!=0 && strcmp(choose_falcuty,"121")!=0) 
				printf("Re-enter            : ");
		}
		while(strcmp(choose_falcuty,"102")!=0 && strcmp(choose_falcuty,"107")!=0 && strcmp(choose_falcuty,"105")!=0 && strcmp(choose_falcuty,"123")!=0 && strcmp(choose_falcuty,"121")!=0);
		
		do{
			char name_class[MAX_OF_CLASS];
		    char create[MAX_OF_NAME];
		    sprintf(create,"%s%s_",choose_year,choose_falcuty);       
		    switch (atoi(choose_falcuty)) {
			case 102:
				strcat(create, "IT1");
				break;
			case 107:
				strcat(create, "H1");
				break;
			case 105:
				strcat(create, "E1");
				break;
			case 123:
				strcat(create, "PFIEV1");
				break;
			case 121:
				strcat(create, "KT1");
				break;
			}
		    
		    printf("**************************************************************************************\n");
		    printf("*  1. %-15s                                                                *\n",create);
		    for(i=2;i<=MAX_OF_CLASS_IN_FALCUTY;i++){
		        create[strlen(create)-1]++;
		        printf("*  %d. %-15s                                                                *\n",i,create);
		    }
		    printf("**************************************************************************************\n");
		
		    int choose_class;
		    printf("Please choose number: ");
		
		    do{
				scanf("%d",&choose_class);
		        if(choose_class<1 || choose_class>5) printf("Re-enter            : ");
		    }	
		    while(choose_class<1 || choose_class>5);
			system("cls");
		
		    create[strlen(create)-1]='\0';
		    sprintf(name_class,"%s%d",create,choose_class);
		
			int found = 0;
			for(i=0;i<=Number_of_Class_in_School;i++){
				if(strcmp(University.Classroom[i].Name_of_Class, name_class) == 0){
					found = 1;
					Class_Index = i;	
					break;
				}
			}
			if(found==0){
				Number_of_Class_in_School++;
				Class_Index = Number_of_Class_in_School;
				strcpy(University.Classroom[Class_Index].Name_of_Class, name_class);	
			}

			Number_of_Student_Index =University.Classroom[Class_Index].Number_of_Student;

			do{
				if(Number_of_Student_Index == MAX_OF_STUDENTS_LIST - 1){
					printf("\n");
					printf("Class is full...\n\n");
					printf("Please choose another Class...\n");
					printf("\nPress any key to continue...");
					getch();
					system("cls");
					break;
				}	
				Number_of_Student_Index++;
				
				printf("Entering for the %s class...\n\n", name_class);
				
				printf("Enter Lastname of Student            : ");
				fflush(stdin);
				gets(Students[Number_of_Student_Index]->Last_Name);
				nameStr(Students[Number_of_Student_Index]->Last_Name);
		
				printf("Enter Firstname of Student           : ");  
				fflush(stdin);
				gets(Students[Number_of_Student_Index]->First_Name);
				nameStr(Students[Number_of_Student_Index]->First_Name);
		
				printf("Enter Date of Birth of Student       : ");  
				int day,month,year;
				do{
					scanf("%d%d%d",&day,&month,&year);
					if(day<1 || day>31 || month<1 || month>12 ){
						printf("Re-enter Date of Birth of Student    : ");
					}
				} 
				while(day<1 || day>31 || month<1 || month>12);
				Students[Number_of_Student_Index]->Birth.Day=day;
				Students[Number_of_Student_Index]->Birth.Month=month;
				Students[Number_of_Student_Index]->Birth.Year=year;

				printf("Choose Gender:\n1. Male\n2. Female\n");
				printf("Please choose number                 : ");
				int choose_sex;
				do{
					scanf("%d",&choose_sex);
					if(choose_sex!=1 && choose_sex!=2){
						printf("Re-choose Gender                     : ");	
					}
				}while(choose_sex!=1 && choose_sex!=2);
				
				if(choose_sex==1) strcpy(Students[Number_of_Student_Index]->Sex,"Male");
				else strcpy(Students[Number_of_Student_Index]->Sex, "Female");

				printf("Enter Address of Student             : ");
				fflush(stdin);
				gets(Students[Number_of_Student_Index]->Address);
				nameStr(Students[Number_of_Student_Index]->Address);

				printf("Enter Phone Number of Student        : ");
				fflush(stdin);
				gets(Students[Number_of_Student_Index]->Phone_Number);
				nameStr(Students[Number_of_Student_Index]->Phone_Number);

				printf("Enter Citizen ID of Student          : ");
				fflush(stdin);
				gets(Students[Number_of_Student_Index]->Citizen_ID);
				nameStr(Students[Number_of_Student_Index]->Citizen_ID);
				
				do{
					printf("\n**** Please Check the information of Student *****************************************\n");
					printf("*    1. Re-enter the information of Student.                                         *\n");
					printf("*    2. Confirm the information of Student.                                          *\n");
					printf("**************************************************************************************\n");
					printf("Please choose number                 : ");
					do{
						scanf("%d",&choose);
						if(choose!=1 && choose!=2) printf("Re-enter                             : ");
					}while (choose!=1 && choose!=2);

				
					if(choose==1){
						printf("\n**** Enter the information of Student again ******************************************\n");
						printf("*    1. Re-enter Lastname of Student.                                                *\n");
						printf("*    2. Re-enter Firstname of Student.                                               *\n");
						printf("*    3. Re-enter Date of Birth of Student.                                           *\n");
						printf("*    4. Re-enter Gender of Student.                                                  *\n");
						printf("*    5. Re-enter Address of Student.                                                 *\n");
						printf("*    6. Re-enter Phone Number of Student.                                            *\n");
						printf("*    7. Re-enter Citizen ID of Student.                                              *\n");
						printf("**************************************************************************************\n");
						printf("Please enter numbers separated by spaces. When you want to finish, enter the number 0: ");
						
						int j, count, check;
						do{
							count=0,check=0;
							do{
								scanf("%d",&re_choose[count]);
								count++;
							} while(re_choose[count-1]!=0);

							for(i=0; i<=count; i++){
								if(re_choose[i]>7 || re_choose[i]<0){
								printf("Enter again                                                                          : ");
									check=1;
									break;
								}
							}
						} while(check==1);

						for(i=0;i<MAX_OF_RE_CHOOSE;i++){
							if(re_choose[i]==0) break;
							
							printf("\n");
							if(re_choose[i]==1){
								
								printf("Enter Lastname of Student            : ");
								fflush(stdin);
								gets(Students[Number_of_Student_Index]->Last_Name);
								nameStr(Students[Number_of_Student_Index]->Last_Name);
							}
							else if(re_choose[i]==2){
								printf("Enter Firstname of Student           : ");  
								fflush(stdin);
								gets(Students[Number_of_Student_Index]->First_Name);
								nameStr(Students[Number_of_Student_Index]->First_Name);
							}
							else if(re_choose[i]==3){
								printf("Enter Date of Birth of Student       : ");  
								int day,month,year;
								do{
									scanf("%d%d%d",&day,&month,&year);
									if(day<1 || day>31 || month<1 || month>12 ){
										printf("Re-enter Date of Birth of Student    : ");
									}
								} 
								while(day<1 || day>31 || month<1 || month>12);
								Students[Number_of_Student_Index]->Birth.Day=day;
								Students[Number_of_Student_Index]->Birth.Month=month;
								Students[Number_of_Student_Index]->Birth.Year=year;
							}
							else if(re_choose[i]==4){
								printf("Choose Gender:\n1. Male\n2. Female\n");
								printf("Please choose number                 : ");
								do{
									scanf("%d",&choose_sex);
									if(choose_sex!=1 && choose_sex!=2){
									printf("Re-choose Gender                     : ");	
									}
								}while(choose_sex!=1 && choose_sex!=2);
								if(choose_sex==1) strcpy(Students[Number_of_Student_Index]->Sex,"Male");
								else strcpy(Students[Number_of_Student_Index]->Sex, "Female");
							}
							else if(re_choose[i]==5){
								printf("Enter Address of Student             : ");
								fflush(stdin);
								gets(Students[Number_of_Student_Index]->Address);
								nameStr(Students[Number_of_Student_Index]->Address);
							}
							else if(re_choose[i]==6){
								printf("Enter Phone Number of Student        : ");
								fflush(stdin);
								gets(Students[Number_of_Student_Index]->Phone_Number);
								nameStr(Students[Number_of_Student_Index]->Phone_Number);
							}
							else if(re_choose[i]==7){
								printf("Enter Citizen ID of Student          : ");
								fflush(stdin);
								gets(Students[Number_of_Student_Index]->Citizen_ID);
								nameStr(Students[Number_of_Student_Index]->Citizen_ID);
							}
						}					
					}
				} while(choose==1);

				strcpy(Students[Number_of_Student_Index]->Email, "x");
				strcpy(Students[Number_of_Student_Index]->Student_ID, "x");
				FILE *file;
				if ((file = fopen(University.Classroom[Class_Index].Name_of_Class,"a")) == NULL){
					fprintf(stderr,"Cannot open file!!!\n");
					exit(1);
				}
				rewiteStudents(Number_of_Student_Index, file);
				fclose(file);

				University.Classroom[Class_Index].Check_Sort= 0;
				system("cls");
		
				printf("**************************************************************************************\n");
				printf("*  1. Enter another Student in class.                                                *\n");
				printf("*  2. Exit.                                                                          *\n");
				printf("**************************************************************************************\n");
				printf("Please choose number: ");
				do{
					scanf("%d",&choose);
					if(choose!=1 && choose!=2) printf("Re-enter            : ");
				}
				while(choose!=1 && choose!=2);
				system("cls");
			}
			while(choose==1);

		}
		while(Number_of_Student_Index == MAX_OF_STUDENTS_LIST);
		University.Classroom[Class_Index].Number_of_Student =Number_of_Student_Index;

			printf("**************************************************************************************\n");
			printf("*  1. Enter a new Student.                                                           *\n");
			printf("*  2. Exit.                                                                          *\n");
			printf("**************************************************************************************\n");
			printf("Please choose number: ");
		do{
			scanf("%d",&choose);
			if(choose!=1 && choose!=2) printf("Re-enter            : ");      
		}
		while(choose!=1 && choose!=2);
		system("cls");
	}
	while(choose==1);
}

int readFile(char* name_class){
	FILE *file;
	if ((file = fopen(name_class,"r")) == NULL){
		fprintf(stderr,"Cannot open file...\n");
		exit(1);
	}
	
	Number_of_Student_Index= 0;
	
	char s[MAX_SIZE];
	while(fgets(s,MAX_SIZE,file)!=NULL){
		Number_of_Student_Index++;
		char *token = strtok(s,";;");
		strcpy(Students[Number_of_Student_Index]->Last_Name,token);
		token = strtok(NULL,";;");
		strcpy(Students[Number_of_Student_Index]->First_Name,token);
		token = strtok(NULL,";;");
		Students[Number_of_Student_Index]->Birth.Day = atoi(token);
		token = strtok(NULL,";;");
		Students[Number_of_Student_Index]->Birth.Month = atoi(token);
		token = strtok(NULL,";;");
		Students[Number_of_Student_Index]->Birth.Year = atoi(token);
		token = strtok(NULL,";;");
		strcpy(Students[Number_of_Student_Index]->Sex,token);
		token = strtok(NULL,";;");
		strcpy(Students[Number_of_Student_Index]->Address,token);
		token = strtok(NULL,";;");
		strcpy(Students[Number_of_Student_Index]->Phone_Number,token);
		token = strtok(NULL,";;");
		strcpy(Students[Number_of_Student_Index]->Citizen_ID,token);
		token = strtok(NULL,";;");
		strcpy(Students[Number_of_Student_Index]->Student_ID,token);
		token = strtok(NULL,";;");
		strcpy(Students[Number_of_Student_Index]->Email,token);
		Students[Number_of_Student_Index]->Email[strcspn(Students[Number_of_Student_Index]->Email, "\n")] = '\0';
		}
	fclose(file);
return Number_of_Student_Index;
}

void quickSortByLastName(Student* arr[], int low, int high) {
    if (low < high) {
		Student* pivot = arr[high];
		int i = (low - 1);
		int j;

		for ( j = low; j <= high - 1; j++) {
			if (strcmp(arr[j]->Last_Name, pivot->Last_Name)< 0) {
				i++;
				Student *temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp; 
			}
		}

		Student *temp = arr[i + 1];
		arr[i + 1] = arr[high];
		arr[high] = temp;
        int pi = i+1;

        quickSortByLastName(arr, low, pi - 1);
        quickSortByLastName(arr, pi + 1, high);
    }
}

void quickSortByFirstName(Student* arr[], int low, int high) {
    if (low < high) {
        Student* pivot = arr[high];
		int i = (low - 1);
		int j;

		for ( j = low; j <= high - 1; j++) {
			if (strcmp(arr[j]->First_Name, pivot->First_Name)  < 0) {
				i++;

				Student *temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp; 
			}
		}
		Student *temp = arr[i + 1];
		arr[i + 1] = arr[high];
		arr[high] = temp;
		int pi= i + 1;
        quickSortByFirstName(arr, low, pi - 1);
        quickSortByFirstName(arr, pi + 1, high);
    }
}
	
void QuickSortClass(Classe s[], int left, int right){
    int i,j;
    Classe x;
    x = s[(left+right)/2];
    i = left;
    j = right;
    do{
        while(strcmp(s[i].Name_of_Class,x.Name_of_Class)<0) i++;
        while(strcmp(s[j].Name_of_Class,x.Name_of_Class)>0) j--;
        if(i<=j){
            Classe temp;
            temp = s[i];
            s[i] = s[j];
            s[j] = temp;
            i++;
            j--;
        }
    }
    while(i<=j);
    if(left<j) QuickSortClass(s,left,j);
    if(i<right) QuickSortClass(s,i,right);
}

char* increase_String(char* s){ 
    int length = strlen(s);
    int i;
    for(i = length - 1; i >= 0; i--) {
        if(s[i] < '9') {
            s[i]++;
            break;
        } else {
            s[i] = '0';
        }
    }
	return s;
}

void sortStudent(){
	int i,j,choose,choose1,a[Number_of_Class_in_School+1], count;
	char falcuty[MAX_OF_FALCUTY], year[MAX_OF_YEAR];

	if (Number_of_Class_in_School==0){
		printf("\nNo classes have been created yet!!!\n");	
		printf("\nPress any key to continue...");
		getch();
		system("cls");
		return;
	}
	
	do{
		count=0;j=1;
		QuickSortClass(University.Classroom,1,Number_of_Class_in_School);
		
		for(i=1;i<=Number_of_Class_in_School;i++)
			if(University.Classroom[i].Check_Sort==0){
				if (count==0) {
					printf("**************************************************************************************\n");
					count=1;
					}
				printf("*  %d. %-15s                                                                *\n",j,University.Classroom[i].Name_of_Class);
				a[j]=i;
				j++;
				}
		if(count==1) 	printf("**************************************************************************************\n");
		else{
			printf("\n");
			printf("All Classes have been sorted.\n");
			printf("\nPress any key to continue...");
			getch();
			system("cls");
			return;
		}
		printf("Please choose class (enter number): ");
		do{
			scanf("%d",&choose);
			if(choose<1 || choose>=j) printf("Re-enter                          : ");
		}	
		while(choose<1 || choose>=j);
	
	
		readFile(University.Classroom[a[choose]].Name_of_Class);
	
		quickSortByLastName(Students,1,Number_of_Student_Index);
		quickSortByFirstName(Students,1,Number_of_Student_Index);
		printf("\nClass has sorted successfully...\n");
		printf("\nPress any key to continue...");
	
		University.Classroom[a[choose]].Check_Sort=1;
	
		sprintf(falcuty,"%c%c%c",University.Classroom[choose].Name_of_Class[2],University.Classroom[choose].Name_of_Class[3],University.Classroom[choose].Name_of_Class[4]);
		sprintf(year,"%c%c",University.Classroom[choose].Name_of_Class[0],University.Classroom[choose].Name_of_Class[1]);
		int k;
		switch (atoi(falcuty)) {
			case 102:
				k=1;
				break;
			case 107:
				k=2;
				break;
			case 105:
				k=3;
				break;
			case 123:
				k=4;
				break;
			case 121:
				k=5;
				break;
		}

		if (strcmp(University.Check_ID_falcuty[k],"")==0) sprintf(University.Check_ID_falcuty[k],"%s%s0000",falcuty,year);
		for(i=1;i<=Number_of_Student_Index;i++){
			if(strcmp(Students[i]->Student_ID,"x")==0){
					increase_String(University.Check_ID_falcuty[k]);
					strcpy(Students[i]->Student_ID,University.Check_ID_falcuty[k]);
					strcpy(Students[i]->Email, Students[i]->Student_ID);
					strcat(Students[i]->Email,"@sv1.dut.udn.vn");
				}	
		}
	
		FILE *file;
		if ((file = fopen(University.Classroom[a[choose]].Name_of_Class,"w")) == NULL){
			fprintf(stderr,"Cannot open the file!!!\n");
			exit(1);
		}
		for(i=1;i<=Number_of_Student_Index;i++) rewiteStudents(i,file);
		fclose(file);
		
		getch();
		system("cls");
		printf("**************************************************************************************\n");
		printf("*  1. Sort another class.                                                            *\n");
		printf("*  2. Exit.                                                                          *\n");
		printf("**************************************************************************************\n");
		printf("Please choose number: ");
		do{
			scanf("%d",&choose1);
			if(choose1!=1 && choose1!=2) printf("Re-enter            : ");
		}
		while (choose1!=1 && choose1!=2);
		system("cls");
	}
	while(choose1==1);
}
	
int binarySearch(Student* arr[], int l, int r, Student* x) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        int res = strcmp(arr[mid]->Last_Name, x->Last_Name);
		if(res==0) res=strcmp(arr[mid]->First_Name, x->First_Name);
        if (res == 0)
            return mid;

        else if (res < 0 )
            return binarySearch(arr, mid + 1, r, x);

        else return binarySearch(arr, l, mid - 1, x);
    }
	return -1;
}

void printStudent(int found){
	int j;
	for(j=0; j<=MAX_OF_RE_CHOOSE; j++){
		if(re_choose[j] == 0) break;
		
		switch(re_choose[j]){
			case 1:
				printf("| %-20s| %-8s ",Students[found]->Last_Name, Students[found]->First_Name);
				break;
			case 2:
				printf("| %02d-%02d-%d ",Students[found]->Birth.Day,Students[found]->Birth.Month,Students[found]->Birth.Year);
				break;
			case 3:
				printf("| %-6s ",Students[found]->Sex);
				break;
			case 4:
				printf("| %-15s ",Students[found]->Address);
				break;
			case 5:
				printf("| %-10s   ",Students[found]->Phone_Number);
				break;
			case 6:
				printf("| %-13s ",Students[found]->Citizen_ID);
				break;
			case 7:
				printf("| %-9s ",Students[found]->Student_ID);
				break;
			case 8:
				printf("| %-25s",Students[found]->Email);
				break;
			case 9:
				printf("| %-20s",Students[found]->Last_Name);
				printf("| %-8s ",Students[found]->First_Name);
				printf("| %02d-%02d-%d ",Students[found]->Birth.Day,Students[found]->Birth.Month,Students[found]->Birth.Year);
				printf("| %-6s ",Students[found]->Sex);	
				printf("| %-15s ",Students[found]->Address);
				printf("| %-10s   ",Students[found]->Phone_Number);
				printf("| %-13s ",Students[found]->Citizen_ID);
				printf("| %-9s ",Students[found]->Student_ID);
				printf("| %-25s",Students[found]->Email);
				break;
		}
	}
	printf("|\n");

	for(j=0; j<MAX_OF_RE_CHOOSE;j++){
		if(re_choose[j]==0) break;
		
		switch(re_choose[j]){
			case 1:
				printf("_________________________________");
				break;
			case 2:
				printf("_____________");
				break;
			case 3:
				printf("_________");
				break;
			case 4:
				printf("__________________");
				break;
			case 5:
				printf("_______________");
				break;
			case 6:
				printf("________________");
				break;
			case 7:
				printf("____________");
				break;
			case 8:
				printf("___________________________");
				break;
			case 9:
				printf("________________________________________________________________________________________________________________________________________________");
				break;
		}
	}
	printf("\n");
}

void conditionSearch(){
	printf("\n***** Information Needed to Print ****************************************************\n");
	printf("*     1. Print Name of Student.                                                      *\n");
	printf("*     2. Print Date of Birth of Student.                                             *\n");
	printf("*     3. Print Gender of Student.                                                    *\n");
	printf("*     4. Print Address of Student.                                                   *\n");
	printf("*     5. Print Phone Number of Student.                                              *\n");
	printf("*     6. Print Citizen ID of Student.                                                *\n");
	printf("*     7. Print Student ID of Student.                                                *\n");
	printf("*     8. Print Email of Student.                                                     *\n");
	printf("*     9. Print all information of Student.                                           *\n");
	printf("**************************************************************************************\n");

	printf("Please enter numbers separated by spaces. When you want to finish, enter the number 0: ");
	
	int i, count, check;
	do{
		count=0,check=0;
		do{
			scanf("%d",&re_choose[count]);
			count++;
		} while(re_choose[count-1]!=0);

		for(i=0; i<=count; i++){
			if(re_choose[i]>9 || re_choose[i]<0){
			printf("Enter again                                                                          : ");
				check = 1;
				break;
			}
		}
	} while(check==1);
	
	printf("\n\n");

	for(i=0; i<MAX_OF_RE_CHOOSE;i++){
		if(re_choose[i]==0) break;
		switch(re_choose[i]){
			case 1:
				printf("_________________________________");
				break;
			case 2:
				printf("_____________");
				break;
			case 3:
				printf("_________");
				break;
			case 4:
				printf("__________________");
				break;
			case 5:
				printf("_______________");
				break;
			case 6:
				printf("________________");
				break;
			case 7:
				printf("____________");
				break;
			case 8:
				printf("___________________________");
				break;
			case 9:
				printf("________________________________________________________________________________________________________________________________________________");
				break;
		}
	}
	printf("\n");

	for(i=0; i<MAX_OF_RE_CHOOSE; i++){
		if(re_choose[i]==0) break;
		switch(re_choose[i]){
			case 1:
				printf("| LASTNAME            | FIRSTNAME");
				break;
			case 2:
				printf("| BIRTH      "); 
				break;
			case 3:
				printf("| SEX    ");
				break;
			case 4:
				printf("| ADDRESS         ");
				break;
			case 5:
				printf("| PHONE NUMBER ");
				break;
			case 6:
				printf("| CITIZEN ID    ");
				break;
			case 7:
				printf("| STUDENT ID");
				break;
			case 8:
				printf("| EMAIL                    ");
				break;
			case 9:
				printf("| LASTNAME            | FIRSTNAME| BIRTH      | SEX    | ADDRESS         | PHONE NUMBER | CITIZEN ID    | STUDENT ID| EMAIL                    ");  
		}
	}
	printf("|\n");

	for(i=0; i<MAX_OF_RE_CHOOSE;i++){
		if(re_choose[i]==0) break;
		switch(re_choose[i]){
			case 1:
				printf("_________________________________");
				break;
			case 2:
				printf("_____________");
				break;
			case 3:
				printf("_________");
				break;
			case 4:
				printf("__________________");
				break;
			case 5:
				printf("_______________");
				break;
			case 6:
				printf("________________");
				break;
			case 7:
				printf("____________");
				break;
			case 8:
				printf("___________________________");
				break;
			case 9:
				printf("________________________________________________________________________________________________________________________________________________");
				break;
		}
	}
	printf("\n");
}

void searchStudent_ID(){
	int i,j,found=-1,choose;
	char ID[MAX_OF_ID];
	char name_class[MAX_OF_CLASS];

	do{
		printf("Enter ID Student: ");
		do{
			fflush(stdin);
			gets(ID);
			if(strlen(ID)+1!=MAX_OF_ID){
				printf("Re-enter        : ");
			} 
			 
		}while(strlen(ID)+1!=MAX_OF_ID);

		char falcuty[MAX_OF_FALCUTY];
		sprintf(falcuty,"%c%c%c",ID[0],ID[1],ID[2]);

		char name[MAX_OF_NAME];
		sprintf(name,"%c%c%s",ID[3],ID[4],falcuty);

		int k;
		switch (atoi(falcuty)) {
			case 102:
				k=1;
				break;
			case 107:
				k=2;
				break;
			case 105:
				k=3;
				break;
			case 123:
				k=4;
				break;
			case 121:
				k=5;
				break;
		}

		if(strcmp(University.Check_ID_falcuty[k],ID)>=0){
			 for(i=1; i<=Number_of_Class_in_School;i++){    //i=0
				sprintf(name_class,"%c%c%c%c%c",University.Classroom[i].Name_of_Class[0],University.Classroom[i].Name_of_Class[1],University.Classroom[i].Name_of_Class[2],University.Classroom[i].Name_of_Class[3],University.Classroom[i].Name_of_Class[4]);
				if(strcmp(name_class,name)!=0) continue;
				readFile(University.Classroom[i].Name_of_Class);

				for(j=1;j<=Number_of_Student_Index;j++){
					if(strcmp(Students[j]->Student_ID,ID)==0){
						found=j;
						break;
					} 
				}
				if(found != -1) break; 
			}
		}
		
		if(found!=-1){
			conditionSearch();
			printStudent(found);
		}
		else{
			printf("\nNot found student with this ID...\n");	
		}
		

		printf("\nPress any key to continue...");
		getch();
		system("cls");
		printf("**************************************************************************************\n");
		printf("*  1. Search another Student.                                                        *\n");
		printf("*  2. Exit.                                                                          *\n");
		printf("**************************************************************************************\n");
		printf("Please choose number: ");
		
		do{
			scanf("%d",&choose);
			if(choose!=1 && choose!=2) printf("Re-enter            : ");
		}
		while (choose!=1 && choose!=2);
		system("cls");
	}
	while(choose==1);
	
}

void searchStudent_Info(){
	int i,choose;
	int check[MAX_OF_CLASS];
	do{
		int found=-1, count=0,j=0;
		printf("Enter Year school of Student: ");
		char year[MAX_OF_YEAR];
		do{
			fflush(stdin);
			gets(year);
			if(strlen(year)!=2 || (atoi(year)<1 || atoi(year)>99)) printf(".Enter again                : ");
		} while(strlen(year)!=2 || (atoi(year)<1 || atoi(year)>99));
		
		printf("Enter ID Falcuty of Student : ");
		char falcuty[MAX_OF_FALCUTY];
		fflush(stdin);
		do{
			gets(falcuty);
			if(strcmp(falcuty,"102")!=0 && strcmp(falcuty,"107")!=0 && strcmp(falcuty,"105")!=0 && strcmp(falcuty,"123")!=0 && strcmp(falcuty,"121")!=0) printf("Re-enter                    : ");
		}
		while(strcmp(falcuty,"102")!=0 && strcmp(falcuty,"107")!=0 && strcmp(falcuty,"105")!=0 && strcmp(falcuty,"123")!=0 && strcmp(falcuty,"121")!=0);
		
		char name[MAX_OF_NAME];
		sprintf(name,"%s%s",year,falcuty);
		
		Student *x = (Student *)malloc(sizeof(Student));
		
		printf("Enter Lastname of Student   : ");
		fflush(stdin);
		gets(x->Last_Name);
		nameStr(x->Last_Name);

		printf("Enter Firstname of Student  : ");
		fflush(stdin);
		gets(x->First_Name);
		nameStr(x->First_Name);
		
		for(i=1;i<=Number_of_Class_in_School;i++){
			char name_class[MAX_OF_NAME];
			sprintf(name_class,"%c%c%c%c%c",University.Classroom[i].Name_of_Class[0],University.Classroom[i].Name_of_Class[1],University.Classroom[i].Name_of_Class[2],University.Classroom[i].Name_of_Class[3],University.Classroom[i].Name_of_Class[4]);
			
			if (strcmp(name,name_class)!=0) continue;
			
			if(University.Classroom[i].Check_Sort==0){
				check[j]=i;
				j++;
				continue;
			}
			
			readFile(University.Classroom[i].Name_of_Class);
			
			binarySearch(Students, 1, Number_of_Student_Index, x);
			
			found = binarySearch(Students, 1, Number_of_Student_Index, x);
			
			if(found!=-1){
				if(count==0){
					conditionSearch();
					count=1;
				}
				printStudent(found);
				
				int found_adj1=found+1;
				int found_adj2=found-1;
				while(found_adj1 <= Number_of_Student_Index && strcmp(Students[found_adj1]->Last_Name,x->Last_Name)==0 && strcmp(Students[found_adj1]->First_Name,x->First_Name)==0) {
					if (strcmp(Students[found_adj1]->Last_Name,x->Last_Name)==0 && strcmp(Students[found_adj1]->First_Name,x->First_Name)==0) {
						 printStudent(found_adj1);
	 				}
					found_adj1++;
				}
	
				while(found_adj2 > 0 && strcmp(Students[found_adj2]->Last_Name,x->Last_Name)==0 && strcmp(Students[found_adj2]->First_Name,x->First_Name)==0){
					if (strcmp(Students[found_adj2]->Last_Name,x->Last_Name)==0 && strcmp(Students[found_adj2]->First_Name,x->First_Name)==0){
						printStudent(found_adj2);
					}
					found_adj2--;
				}
			}
		}

		if(j!=0){
			for(i=0;i<j;i++)
			printf("\nClass %s is not sorted, please SORT before search Student!!!\n",University.Classroom[check[i]].Name_of_Class);
		}

		if(count==0) printf("\nNot found student with this Infomation...\n");
		
		free(x);
		printf("\nPress any key to continue...");
		
		getch();
		system("cls");
		
		printf("**************************************************************************************\n");
		printf("*  1. Search another Student.                                                        *\n");
		printf("*  2. Exit.                                                                          *\n");
		printf("**************************************************************************************\n");
		printf("Please choose number: ");
		do{
			scanf("%d",&choose);
			if(choose!=1 && choose!=2) printf("Re-enter            : ");
		}
		while (choose!=1 && choose!=2);
		system("cls");
	}
	while(choose==1);
}

void searchStudent_Citizen_ID(){
	int i,j,found,choose;
	char Citizen_ID[MAX_OF_CID];

	do{
		found=-1;
		printf("Enter Citizen ID Student: ");
		fflush(stdin);
		gets(Citizen_ID);

		for(i=1; i<=Number_of_Class_in_School;i++){
			readFile(University.Classroom[i].Name_of_Class);

			for(j=1;j<=Number_of_Student_Index;j++){
				if(strcmp(Students[j]->Citizen_ID,Citizen_ID)==0){
					found=j;
					break;			
				} 
			}
			if (found!=-1) break;
		}
		if(found!=-1){
			conditionSearch();
			printStudent(found);
		} else printf("\nNot found student with this Citizen ID...\n");

		printf("\nPress any key to continue...");
		getch();
		system("cls");
		printf("**************************************************************************************\n");
		printf("*  1. Search another Student.                                                        *\n");
		printf("*  2. Exit.                                                                          *\n");
		printf("**************************************************************************************\n");
		printf("Please choose number: ");
		do{
			scanf("%d",&choose);
			if(choose!=1 && choose!=2) printf("Re-enter            : ");
		}while (choose!=1 && choose!=2);
		system("cls");
	}while(choose==1);
}	

void searchStudent_Phone_Number(){
	int i,j,found,choose;
	char Phone_Number[MAX_OF_PHONE_NUMBER];

	do{
		found=-1;
		printf("Enter Phone Number Student: ");
		fflush(stdin);
		gets(Phone_Number);

		for(i=1; i<=Number_of_Class_in_School;i++){
			readFile(University.Classroom[i].Name_of_Class);

			for(j=1;j<=Number_of_Student_Index;j++){
				if(strcmp(Students[j]->Phone_Number,Phone_Number)==0){
					found=j;
					break;
				} 		
			}
			if (found!=-1) break;
		}
			if(found!=-1){
				conditionSearch();
				printStudent(found);
			}	
			else printf("\nNot found student with this Phone Number...\n");

			printf("\nPress any key to continue...");
			getch();
			system("cls");
			printf("**************************************************************************************\n");
			printf("*  1. Search another Student.                                                        *\n");
			printf("*  2. Exit.                                                                          *\n");
			printf("**************************************************************************************\n");
			printf("Please choose number: ");
			do{
				scanf("%d",&choose);
				if(choose!=1 && choose!=2) printf("Re-enter            : ");
			}
			while (choose!=1 && choose!=2);
			system("cls");
	}while(choose==1);
}

void searchStudent(){

	if(Number_of_Class_in_School==0){
		printf("No have Classes are created!!!\n");
		printf("\nPress any key to continue...");
		getch();
		system("cls");
		return;
	}

	int choose;
	do{
		printf("**************************************************************************************\n");
		printf("*  1. Search by ID Student.                                                          *\n");
		printf("*  2. Search by Student's Infomation.                                                *\n");
		printf("*  3. Search by Citizen ID Student.                                                  *\n");
		printf("*  4. Search by Phone Number Student.                                                *\n");
		printf("*  5. Exit.                                                                          *\n");
		printf("**************************************************************************************\n");
		printf("Please choose number: ");
		do{
			scanf("%d",&choose);
			if(choose<1 || choose>6) printf("Re-enter            : ");
		}
		while(choose<1 || choose>6);
		system("cls");

		switch(choose){
			case 1:
				searchStudent_ID();
				break;
			case 2:
				searchStudent_Info();
				break;
			case 3:
				searchStudent_Citizen_ID();
				break;
			case 4:
				searchStudent_Phone_Number();
				break;
			case 5:
				break;		
		}
	}
	while(choose!=5);
}

void RemoveStudent_ID(){
	int i,j,found,choose;
	char ID[MAX_OF_ID];
	char name_class[MAX_OF_NAME];

	do{
		found=-1;
		printf("Enter ID Student    : ");
		do{
			fflush(stdin);
			gets(ID);
			if(strlen(ID)+1!=MAX_OF_ID){
				printf("Re-enter            : ");
			}
		}while(strlen(ID)+1!=MAX_OF_ID);
		
		char falcuty[MAX_OF_FALCUTY];
		sprintf(falcuty,"%c%c%c",ID[0],ID[1],ID[2]);

		char name[MAX_OF_NAME];
		sprintf(name,"%c%c%s",ID[3],ID[4],falcuty);

		int k;
		switch (atoi(falcuty)) {
			case 102:
				k=1;
				break;
			case 107:
				k=2;
				break;
			case 105:
				k=3;
				break;
			case 123:
				k=4;
				break;
			case 121:
				k=5;
				break;
		}

		if(strcmp(University.Check_ID_falcuty[k],"") >= 0){
		 	for(i=1; i<=Number_of_Class_in_School;i++){
				strcpy(name_class,University.Classroom[i].Name_of_Class);
				name_class[5]='\0';
				if(strcmp(name_class,name)!=0) continue;
				readFile(University.Classroom[i].Name_of_Class);
	
				for(j=1;j<=Number_of_Student_Index;j++){
					if(strcmp(Students[j]->Student_ID,ID)==0){
						found=j;
						break;
					} 
				}
				if(found != -1) break;
			}		 
		}
			
		if(found != -1){
			printf("\nInfomation of student need delete: \n");
			re_choose[0]=9;
			re_choose[1]=0;
			printf("________________________________________________________________________________________________________________________________________________\n");
			printf("| LASTNAME            | FIRSTNAME| BIRTH      | SEX    | ADDRESS         | PHONE NUMBER | CITIZEN ID    | STUDENT ID| EMAIL                    |\n");
			printf("________________________________________________________________________________________________________________________________________________\n");
			printStudent(found);
			printf("\n**** Are you sure want to delete this student?******************\n");
			printf("*      1.  Yes                                                 *\n");
			printf("*      2.  No                                                  *\n");
			printf("****************************************************************\n");
			printf("Please choose number: ");
			do{
				scanf("%d",&choose);
				if(choose!=1 && choose!=2) printf("Re-enter            : ");
			} while(choose!=1 && choose!=2);

			if(choose == 1){
				FILE *file;
				if ((file = fopen(University.Classroom[i].Name_of_Class,"w")) == NULL){
					fprintf(stderr,"\nCannot open file!!!\n");
					exit(1);
				}
							
				for(j=1;j<=Number_of_Student_Index;j++){
					if(j!=found) rewiteStudents(j,file);
				}
				
				fclose(file);
				printf("\nDelete Student successfully...\n");
				
			} else  printf("\nThe student has not been deleted...\n");
			
		} else printf("\nNot found student with this ID...\n");
			
		
		printf("\nPress any key to continue...");
		getch();
		system("cls");
		printf("**************************************************************************************\n");
		printf("*  1. Delete another Student.                                                        *\n");
		printf("*  2. Exit.                                                                          *\n");
		printf("**************************************************************************************\n");
		printf("Please choose number: ");
		do{
			scanf("%d",&choose);
			if(choose!=1 && choose!=2) printf("Re-enter            : ");
		}
		while (choose!=1 && choose!=2);
		system("cls");
	}
	while(choose==1);

}

void RemoveStudent_Citizen_ID(){
	int i,j,found,choose;
	char Citizen_ID[MAX_OF_CID];

	do{
		found = -1;
		printf("Enter Citizen ID Student: ");
		fflush(stdin);
		gets(Citizen_ID);

		for(i=1; i<=Number_of_Class_in_School;i++){
			readFile(University.Classroom[i].Name_of_Class);

			for(j=1;j<=Number_of_Student_Index;j++){
				if(strcmp(Students[j]->Citizen_ID,Citizen_ID)==0){
					found=j;
					break;
				} 
			}
			
			if (found!=-1) break;
		}	

		if(found!=-1){
			printf("\nInfomation of student need delete\n");
			re_choose[0]=9;
			re_choose[1]=0;
			printf("________________________________________________________________________________________________________________________________________________");
			printf("| LASTNAME            | FIRSTNAME| BIRTH      | SEX    | ADDRESS         | PHONE NUMBER | CITIZEN ID    | STUDENT ID| EMAIL                    |\n");
			printf("________________________________________________________________________________________________________________________________________________");
			printStudent(found);
			printf("\n**** Are you sure want to delete this student?******************\n");
			printf("*      1.  Yes                                                 *\n");
			printf("*      2.  No                                                  *\n");
			printf("****************************************************************\n");
			printf("Please choose number    : ");
			do{
				scanf("%d",&choose);
				if(choose!=1 && choose!=2) printf("Re-enter                : ");
			} while(choose!=1 && choose!=2);
		 	if (choose == 1){
				FILE *file;
				if ((file = fopen(University.Classroom[i].Name_of_Class,"w")) == NULL){
					fprintf(stderr,"Cannot open file!!!\n");
					exit(1);
				}else {
					for(j=1;j<=Number_of_Student_Index;j++){
						if(j!=found) rewiteStudents(j,file);
					}
					fclose(file);
					printf("\nDelete Student successfully...\n");
				}
			}else printf("\nThe student has not been deleted...\n");
		}else printf("\nNot found student with this Citizen ID...\n");

		printf("\nPress any key to continue...");
		getch();
		system("cls");
		printf("**************************************************************************************\n");
		printf("*  1. Delete another Student.                                                        *\n");
		printf("*  2. Exit.                                                                          *\n");
		printf("**************************************************************************************\n");
		printf("Please choose number: ");
		do{
			scanf("%d",&choose);
			if(choose!=1 && choose!=2) printf("Re-enter            : ");
		}
		while (choose!=1 && choose!=2);
		system("cls");

	}while(choose==1);
}		

void removeStudent(){
	if(Number_of_Class_in_School==0){
		printf("No have Classes are created!!!\n");
		printf("\nPress any key to continue...");
		getch();
		system("cls"); 
		return;
	}
	
	int choose;
	do{
		printf("**************************************************************************************\n");
		printf("*  1. Delete by ID Student.                                                          *\n");
		printf("*  2. Delete by Citizen ID Student.                                                  *\n");
		printf("*  3. Exit.                                                                          *\n");
		printf("**************************************************************************************\n");
		printf("Please choose number: ");
		do{
			scanf("%d",&choose);
			if(choose!=1 && choose!=2 && choose!=3) printf("Re-enter            : ");
		}
		while(choose!=1 && choose!=2 && choose!=3);
		system("cls");

		switch(choose){
			case 1:
				RemoveStudent_ID();
				break;
			case 2:
				RemoveStudent_Citizen_ID();
				break;
			case 3:
				break;	
		}
	}
	while(choose!=3);

}

void printClass(){

	if (Number_of_Class_in_School==0){
		printf("No have Classes are created!!!\n");
		printf("\nPress any key to continue..."); 
		getch();
		system("cls");
		return;
	}

	int i,choose;
	do{
		QuickSortClass(University.Classroom,1,Number_of_Class_in_School);
		printf("**************************************************************************************\n");
		for(i=1;i<=Number_of_Class_in_School;i++)
		printf("*  %d. %-15s                                                                *\n",i,University.Classroom[i].Name_of_Class);
		printf("**************************************************************************************\n");
		printf("Please choose number: ");
		do{
			scanf("%d",&choose);
			if(choose<1 || choose>Number_of_Class_in_School) printf("Re-enter            : ");
		}	
		while(choose<1 || choose>Number_of_Class_in_School);;

		Class_Index=choose;

		readFile(University.Classroom[Class_Index].Name_of_Class);
		
		conditionSearch();
		for(i=1;i<=Number_of_Student_Index;i++){
			printStudent(i);
		}

		printf("\nPress any key to continue...");
		getch();
		system("cls");
		printf("**************************************************************************************\n");
		printf("*  1. View information of another Class.                                             *\n");
		printf("*  2. Exit.                                                                          *\n");
		printf("**************************************************************************************\n");
		printf("Please choose number: ");
		do{
			scanf("%d",&choose);
			if(choose!=1 && choose!=2) printf("Re-enter            : ");
		}
		while (choose!=1 && choose!=2);
		system("cls");
	}
	while(choose==1);
}

void checkID(){
	
	if (Number_of_Class_in_School==0){
		printf("No have Classes are created!!!\n");
		printf("\nPress any key to continue..."); 
		getch();
		system("cls");
		return;
	}

	int i,choose;
	do{
		QuickSortClass(University.Classroom,1,Number_of_Class_in_School);
		printf("**************************************************************************************\n");
		for(i=1;i<=Number_of_Class_in_School;i++)
			printf("*  %d. %-15s                                                                *\n",i,University.Classroom[i].Name_of_Class);
		printf("**************************************************************************************\n");
		printf("Please choose number: ");
		do{
			scanf("%d",&choose);
			if(choose<1 || choose>Number_of_Class_in_School) printf("Re-enter            : ");
		}	
		while(choose<1 || choose>Number_of_Class_in_School);

		if(University.Classroom[choose].Check_Sort==0) printf("\nERROR: Class is not sorted!!!\n");
		else printf("\nClass has been successfully assigned ID...\n");

		printf("\nPress any key and continue...");
		getch();
		system("cls");
		printf("**************************************************************************************\n");
		printf("*  1. Add ID for another Class.                                                      *\n");
		printf("*  2. Exit.                                                                          *\n");
		printf("**************************************************************************************\n");
		printf("Please choose number: ");
		do{
			scanf("%d",&choose);
			if(choose!=1 && choose!=2) printf("Re-enter            : ");
		}
		while (choose!=1 && choose!=2);
		system("cls");
	}
	while(i==1);

}

void checkEmail(){
	
	if (Number_of_Class_in_School==0){
		printf("No have Classes are created!!!\n");
		printf("\nPress any key to continue..."); 
		getch();
		system("cls");
		return;
	}

	int i,choose;
	do{
		QuickSortClass(University.Classroom,1,Number_of_Class_in_School);
		printf("**************************************************************************************\n");
		for(i=1;i<=Number_of_Class_in_School;i++)
			printf("*  %d. %-15s                                                                *\n",i,University.Classroom[i].Name_of_Class);
		printf("**************************************************************************************\n");
		printf("Please choose number: ");
		do{
			scanf("%d",&choose);
			if(choose<1 || choose>Number_of_Class_in_School) printf("Re-enter            : ");
		}	
		while(choose<1 || choose>Number_of_Class_in_School);

		if(University.Classroom[choose].Check_Sort==0) printf("\nERROR: Class is not sorted!!!\n");
		else printf("\nClass has been successfully assigned Email...\n");
	
		printf("\nPress any key to continue...");
		getch();
		system("cls");
		printf("**************************************************************************************\n");
		printf("*  1. Assign Email for another Class.                                                *\n");
		printf("*  2. Exit.                                                                          *\n");
		printf("**************************************************************************************\n");
		printf("Please choose number: ");

		do{
			scanf("%d",&choose);
			if(choose!=1 && choose!=2) printf("Re-enter            : ");
		}
		while (choose!=1 && choose!=2);
		system("cls");
	}
	while(i==1);

}

void logo()
{
    printf("\n _____________________________________________________________________________________________________________________ \n");
    printf("|                                       |                                                                             |\n");
    printf("|     D                                 |                       MINISTRY OF EDUCATION AND TRAINING                    |\n");
    printf("|                                       |          UNIVERSITY OF SCIENCE AND TECHNOLOGY-UNIVERSITY OF DA NANG         |\n");
    printf("| B   A   C   H   K   H   O   A         |                              _________________                              |\n");
    printf("|         ___________________________   |                                                                             |\n");
    printf("|     N  |          ...              |  |                  Lecturer       : Tran Ho Thuy Tien                         |\n");
    printf("|        |            ....           |  |                                                                             |\n");
    printf("|     A  |             ......        |  |                  Project        : PBL1-Quan Ly Sinh Vien                    |\n");
    printf("|        |              .......      |  |                                                                             |\n");
    printf("|     N  |              .........    |  |                  Students       : Ngo Van Huy                               |\n");
    printf("|        |             ...........   |  |                                   Nguyen Huu Hoang Luan                     |\n");
    printf("|     G  |            .............  |  |                                                                             |\n");
    printf("|        |          ...............  |  |                  Section Class  : 23.99A                                    |\n");
    printf("|        |       ..................  |  |                                                                             |\n");
    printf("|        |    ....................   |  |                  Activity Class : 23T_Nhat1                                 |\n");
    printf("|        |.......................    |  |                                                                             |\n");
    printf("|        |.....................      |  |                      Da Nang, ngay 26 thang 06 nam 2024                     |\n");
    printf("|        |___________________________|  |                                                                             |\n");
    printf("|_______________________________________|_____________________________________________________________________________|\n"); 
	printf("\n\n");     
}

void menu(){

	logo();
	int choose;
	do{
		printf("***** MENU ************************************************************************************************************\n");
		printf("*     1. Add a Student.                                                                                               *\n");
		printf("*     2. Sort Students in a Class.                                                                                    *\n");
		printf("*     3. Find Information of a Student in a Class.                                                                    *\n");
		printf("*     4. Remove a Student.                                                                                            *\n");
		printf("*     5. View Information of a Class.                                                                                 *\n");
		printf("*     6. Assign ID Student.                                                                                           *\n");
		printf("*     7. Assign Mail Student.                                                                                         *\n");
		printf("*     8. Exit.                                                                                                        *\n");
		printf("***********************************************************************************************************************\n");
		printf("Please choose number: ");
		do{
			scanf("%d",&choose);
			if(choose<1 || choose>8) printf("Re-enter            : ");
		}
		while(choose<1 || choose>8);
		system("cls");
		
		switch(choose){
			case 1:
				addStudent();
				break;
			case 2:
				sortStudent();
				break;
			case 3:
				searchStudent();
				break;
			case 4:
				removeStudent();
				break;
			case 5:
				printClass();
				break;
			case 6:
				checkID();
				break;
			case 7:
				checkEmail();
				break;
		}

		
	}
	while(choose!=8);
}

void free_Data(){
	int i;
	for( i = 0; i < MAX_OF_STUDENTS_LIST; i++) {
        free(Students[i]);
    }
}

void add_Data() {
	int i;
	for( i = 0; i < MAX_OF_STUDENTS_LIST; i++) {
        Students[i] = malloc(sizeof(Student));
        if(Students[i] == NULL) {
            fprintf(stderr, "Cannot supply data for Student [%d]!!!\n", i);
            exit(1);
        }
    }
}

