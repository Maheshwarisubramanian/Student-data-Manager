#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>
#define Student struct Stud

char password[30] = "mahi@21";
void add(FILE * fp);
void modify(FILE * fp);
void display(FILE * fp);
void Indivisual(FILE *fp);

FILE * del(FILE * fp);
void printChar(char ch,int n);
void title();
FILE *tp;

void gotoxy(int x,int y)
{
	COORD CRD;
    CRD.X = x;
    CRD.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),CRD);
}

struct pass
{
	char pass[25];
}pa;

struct Stud
{
    char name[100];
    char dept[50];
    int roll;
    float sgpa[12];
    float cgpa;
};

int main()
{

    int i;
    char c;
    SetConsoleTitle("Mahi's PRoject");
    FILE * fp;
    Student s;
    int option;
    char another;

    if((fp=fopen("db.txt","rb+"))==NULL && (fp=fopen("db.txt","wb+"))==NULL)
    {
            printf("Can't create or open Database.");
            return 0;
    }
    char dummy[7];
    int count = 3;
    int flag;
    int j;
    char ch1;
    title();

    gotoxy(12,9);
    printf ("Enter a Password: ");
    getch();
    for(j=0;j<7;j++)
    {
        ch1 = getch();
        dummy[j] = ch1;
        if(ch1 !=13)
        {
            printf("*");
        }
        else if(ch1 ==13)
        {
            break;
        }
    }
    dummy[j] = '\0';

    if(strcmp(password,dummy)== 0)
    {
        flag = 1;
        printf("Correct password");
        getch();
    }
    else if(strcmp(password,dummy)!= 0)
    {
            flag = 0;

        for(i=0;i<3;i++)
        {
            printf ("The password you entered is incorrect");
            printf ("\n %d tries left ",count);
            printf ("\nPassword: ");
            for(j=0;j<7;j++)
            {
            ch1 = getch();
            dummy[j] = ch1;
                if(ch1 !=13)
                {
                printf("*");
                }
                else if(ch1 ==13)
                {
                break;
                }

            }
            dummy[j] = '\0';


                if(strcmp(password,dummy)== 0)
                {

                flag = 1;
                 break;
                }
                count = count -1;

        }
    }

	if(flag == 1)
    {
		system("cls");
		gotoxy(10,3);
		printf("<<<< Loading Please Wait >>>>");
		printf("\n\n\n\n\n\t\t\t\t\tPress any key to continue...... ");
		getch();

    title();
    printf("\n\n\n\t\t\t       press any key to Enter");
    getch();

    while(1)
    {
        title();
        printf("\n\t");
        printChar('*',64);

        printf("\n\n\t\t\t\t1. Add Student");
        printf("\n\n\t\t\t\t2. Modify Student");
        printf("\n\n\t\t\t\t3. Show All Student");
        printf("\n\n\t\t\t\t4. Individual View");
        printf("\n\n\t\t\t\t5. Remove Student");
        printf("\n\n\t\t\t\t6. Logout\n\t");
        printChar('*',64);
        printf("\n\n\t\t\t\tEnter Your Option :--> ");
        scanf("%d",&option);

        switch(option)
        {
            case 1:
                add(fp);
                break;
            case 2:
                modify(fp);
                break;
            case 3:
                display(fp);
                getch();
                break;
            case 4:
                Indivisual(fp);
                break;
            case 5:
                fp=del(fp);
                break;

            case 6:
                return 1;
                break;
            default:
                printf("\n\t\tNo Action Detected");
                printf("\n\t\tPress Any Key\n\n\n");
                getch();
                system("pause");
        }
    }
        return 1;
    }
}

void printChar(char ch,int n)
{
    while(n--)
    {
        putchar(ch);
    }
}

void title()
{
    system("cls");
    printf("\n\n\t");
    printChar('=',33);
    printf("Meera Krish Womens College");
    printChar('=',33);
    printf("\n");
}

 void add(FILE * fp)
{
    title();
    char another='y';
    Student s;
    int i;
    float cgpa;
    fseek(fp,0,SEEK_END);
    while(another=='y'||another=='Y')
    {
        printf("\n\n\t\tEnter Full Name of Student: ");
        fflush(stdin);
        fgets(s.name,sizeof(s.name),stdin);

        printf("\n\n\t\tEnter Depertment Name: ");
        fflush(stdin);
        fgets(s.dept,sizeof(s.dept),stdin);

        printf("\n\n\t\tEnter Roll number: ");
        scanf("%d",&s.roll);

        printf("\n\n\tEnter SGPA for 6 semesters\n");
        for(i=0,cgpa=0; i<6; i++)
        {
            scanf("%f",&s.sgpa[i]);
            cgpa+=s.sgpa[i];
        }

        cgpa/=6.0;
        s.cgpa=cgpa;
        fwrite(&s,sizeof(s),1,fp);
        printf("\n\n\t\tAdd another student?(Y/N)?");
        fflush(stdin);
        another = getchar();
    }
}

FILE * del(FILE * fp)
{
    title();
    Student s;
    int flag=0,tempRoll,siz=sizeof(s);
    FILE *ft;
    if((ft = fopen("temp.txt","wb+")) == NULL)
    {
        printf("\n\n\t\t\t\\t!!! ERROR !!!\n\t\t");
        return fp;
    }
    printf("\n\n\tEnter Roll number of Student to Delete the Record");
    printf("\n\n\t\t\tRoll No. : ");
    scanf("%d",&tempRoll);
    rewind(fp);
    while((fread(&s,siz,1,fp))==1)
    {
        if(s.roll==tempRoll)
        {
            flag=1;
            printf("\n\tRecord Deleted for");
            printf("\n\n\t\t%s\n\n\t\t%s\n\n\t\t%d\n\t",s.name,s.dept,s.roll);
            continue;
        }

        fwrite(&s,siz,1,ft);
    }


    fclose(fp);
    fclose(ft);

    remove("db.txt");
    rename("temp.txt","db.txt");
    if(flag==0)

        printf("\n\n\t\tNO STUDENT FOUND WITH THE INFORMATION\n\t");
    printChar('-',65);
    printf("\n\t");
    system("pause");
    return fp;
}


void modify(FILE * fp)
{
    title();
    Student s;
    int i,flag=0,tempRoll,siz=sizeof(s);
    float cgpa;

    printf("\n\n\tEnter Roll Number of Student to MODIFY the Record : ");
    scanf("%d",&tempRoll);
    rewind(fp);

    while((fread(&s,siz,1,fp))==1)
    {
        if(s.roll==tempRoll)
        {
            flag=1;
            break;
        }
    }

    if(flag==1)
    {
        fseek(fp,-siz,SEEK_CUR);
        printf("\n\n\t\t\t\tRecord Found\n\t\t\t");
        printChar('=',38);
        printf("\n\n\t\t\tStudent Name: %s",s.name);
        printf("\n\n\t\t\tStudent Roll: %d\n\t\t\t",s.roll);
        printChar('=',38);
        printf("\n\n\t\t\tEnter New Data for the student");

        printf("\n\n\t\t\tEnter Full Name of Student: ");
        fflush(stdin);
        fgets(s.name,sizeof(s.name),stdin);

        printf("\n\n\t\t\tEnter Department: ");
        fflush(stdin);
        fgets(s.dept,sizeof(s.dept),stdin);

        printf("\n\n\t\t\tEnter Roll number: ");
        scanf("%d",&s.roll);

        printf("\n\n\t\tEnter SGPA for 6 semesters\n");
        for(i=0,cgpa=0; i<6; i++)
        {
            scanf("%f",&s.sgpa[i]);
            cgpa+=s.sgpa[i];

        }
        cgpa=cgpa/6.0;


        fwrite(&s,sizeof(s),1,fp);
    }

    else if (flag==0)
    {
        printf("\n\n\t!!!! ERROR !!!! RECORD NOT FOUND");
    }
    printf("\n\n\t");

}

void display(FILE * fp)
{
    title();
    Student s;
    int i,siz=sizeof(s);
    rewind(fp);

    while((fread(&s,siz,1,fp))==1)
    {
        printf("\n\t\tNAME : %s",s.name);
        printf("\n\n\t\tDepertment : %s",s.dept);
        printf("\n\n\t\tROLL : %d",s.roll);
        printf("\n\n\tSGPA: ");

        for(i=0; i<9; i++)
            printf("| %.2f |",s.sgpa[i]);
        printf("\n\n\t\tCGPA : %.2f\n\t",s.cgpa);
        printChar('-',65);
    }

    printf("\n\n\n\t");
    printChar('*',65);
    printf("\n\n\t");
    system("pause");
}

void Indivisual(FILE *fp)
{
    title();
    int tempRoll,flag,siz,i;
    Student s;
    char another='y';
    siz=sizeof(s);

    while(another=='y'||another=='Y')
    {
        printf("\n\n\tEnter Roll Number: ");
        scanf("%d",&tempRoll);
        rewind(fp);

        while((fread(&s,siz,1,fp))==1)
        {
            if(s.roll == tempRoll)
            {
                flag=1;
                break;
            }
        }

        if(flag==1)
        {
            printf("\n\t\tNAME : %s",s.name);
            printf("\n\n\t\tDepartment : %s",s.dept);
            printf("\n\n\t\tROLL : %d",s.roll);
            printf("\n\n\tSGPA: ");

            for(i=0; i<6; i++)
            {
                printf("| %.2f |",s.sgpa[i]);
            printf("\n\n\t\tCGPA : %.2f\n\t",s.cgpa);
            printChar('-',65);
            }
        }

        else if(flag==0)
        {
            printf("\n\n\t\t!!!! ERROR RECORD NOT FOUND !!!!");
        }

        printf("\n\n\t\tShow another student information? (Y/N)?");
        fflush(stdin);
        another=getchar();
    }
}

