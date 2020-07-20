#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<string.h>


//RUN THE CODE AFTER PLACING THE GIVEN .txt FILES IN THE SAME DIRECTORY!


void user();              //the function for the user
void manager();           //the function for the manager
int uniqueid();           //function to generate unique ids
void listbugs();          //function to generate various list of bugs acc. to the problem statement
void display(int id);     //displays the details of a bug by taking id as a parameter



//global variables are used because they are not changed by the users and are used by all the functions and it is pointless to
//pass it as a parameter

static char password[]="python";         //stores the password to access manager
static char filedata[]="database.txt";   //name of the file which stores the complete database
static char fileids[]="ids.txt";         //name of the file which stores the unique ids
static char filenames[]="names.txt";     //name of the file which stores the name
static char type[][20]= {"MAJOR   ","MINOR   ","COSMETIC"};//array which stores the bug types with additional spaces for smooth functioning
static char priority[][20]= {"LOW   ","MEDIUM","HIGH  "};//array which stores the bug priorities with additional spaces for smooth functioning
static char status[][20]= {"NOT ASSIGNED","ASSIGNED    ","BEING FIXED ","FIXED       ","DELIVERED   "};//array which stores the bug status with additional spaces for smooth functioning

int uniqueid()
{
    FILE *fid;
    fid=fopen(fileids,"r+");
    if (fid == NULL)
    {
        printf("WARNING! FILE NOT FOUND\nPLEASE SAVE THE FILE %s IN THE SAME DIRECTORY",fileids);
        exit(1);
    }
    int id;
    srand(time(0));  //seeds the random function to provide different patterns every time the program runs
    int flag=1;      //loop conditional variable
    int comp;        //reads the id from the file
    while(flag)
    {
        flag=0;
        id=rand()+1;         //generates a random number
        fseek(fid,0,SEEK_SET);
        while((fscanf(fid,"%d ",&comp)!=EOF))
        {

            if(comp==id)
            {
                flag=1;  //if id already exists in the file, the loop continues, generating another number
            }
        }
    }
    fseek(fid,0,SEEK_END);
    fprintf(fid,"%d ",id);
    fflush(fid);
    fclose(fid);
    return id;
}
void user()
{
    char name[20];         //stores the name
    int d,m,y;
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    d = local->tm_mday;             //stores the date
    m = local->tm_mon+1;            //stores the month
    y = local->tm_year-100;         //stores the year



    int id;
    id=uniqueid();                 //to generate id for the new user.

    char description[200];

    int choice;
    int flag=1;
    FILE *fdt;
    fdt=fopen(filedata,"a");
    if (fdt == NULL)
    {
        printf("WARNING! FILE NOT FOUND\nPLEASE SAVE THE FILE %s IN THE SAME DIRECTORY",filedata);
        exit(1);
    }
    FILE *fnt;
    fnt=fopen(filenames,"a");
    if (fnt == NULL)
    {
        printf("WARNING! FILE NOT FOUND\nPLEASE SAVE THE FILE %s IN THE SAME DIRECTORY",filenames);
        exit(1);
    }
    printf("Your unique id : %d \n",id);
    fprintf(fdt,"%d\n",id);
    fflush(fdt);
    printf("Enter your name(max. 20 char) :");
    getchar();
    gets(name);

    fprintf(fdt,"%s\n",name);
    fflush(fdt);
    fprintf(fnt,"%s\n",name);
    fflush(fnt);
    printf("\n0 - MAJOR\n1 - MINOR\n2 - COSMETIC\nSelect the TYPE of the bug : ");
    scanf("%d",&choice);
    while(flag)
    {
        switch(choice)
        {
        case 0 :
        {
            fprintf(fdt,"%s\n",type[0]);
            fflush(fdt);
            flag=0;
            break;
        }
        case 1 :
        {
            fprintf(fdt,"%s\n",type[1]);
            fflush(fdt);
            flag=0;
            break;
        }
        case 2:
        {
            fprintf(fdt,"%s\n",type[2]);
            fflush(fdt);
            flag=0;
            break;
        }
        default :
        {
            printf("Enter correct option : ");
            scanf("%d",&choice);

        }
        }
    }

    printf("Bug Description : ");
    getchar();
    gets(description);
    fprintf(fdt,"%s\n",description);
    fflush(fdt);
    flag=1;
    printf("\n0 - LOW\n1 - MEDIUM\n2 - HIGH\nSelect the PRIORITY of the bug : ");
    scanf("%d",&choice);
    while(flag)
    {
        switch(choice)
        {
        case 0 :
        {
            fprintf(fdt,"%s\n",priority[0]);
            fflush(fdt);
            flag=0;
            break;
        }
        case 1 :
        {
            fprintf(fdt,"%s\n",priority[1]);
            fflush(fdt);
            flag=0;
            break;
        }
        case 2:
        {
            fprintf(fdt,"%s\n",priority[2]);
            fflush(fdt);
            flag=0;
            break;
        }
        default :
        {
            printf("Enter correct option : ");
            scanf("%d",&choice);
        }
        }
    }


    fprintf(fdt,"%d/%d/%d\n",d,m,y);


    fprintf(fdt,"%s\n",status[0]);
    fflush(fdt);
    fprintf(fdt,"%s\n","TO BE ASSIGNED      ");
    fflush(fdt);
    fprintf(fdt,"End\n");

    fclose(fdt);
    fclose(fnt);

    printf("\n\n");

    display(id);

    main();
}
void manager()
{
    int choice;

repeat :
    {
        printf("                            HEY THERE MANAGER!!\n\n");
        printf("Enter 1 to get Unique IDs with Names\nEnter 2 to view status\nEnter 3 to assign\n");
        printf("Enter 4 to change status\nEnter 5 for menu\n");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1 :
        {
            //prints unique ids and their associated names
            FILE *fid;
            fid=fopen(fileids,"r");
            if (fid == NULL)
            {
                printf("WARNING! FILE NOT FOUND\nPLEASE SAVE THE FILE %s IN THE SAME DIRECTORY",fileids);
                exit(1);
            }
            FILE *fnt;
            fnt=fopen(filenames,"r");
            if (fnt == NULL)
            {
                printf("WARNING! FILE NOT FOUND\nPLEASE SAVE THE FILE %s IN THE SAME DIRECTORY",filenames);
                exit(1);
            }
            int sid,check=1;
            char sname[20];
            while(((fscanf(fid,"%d ",&sid)!=EOF)&(fgets(sname,20,fnt)!=EOF)))
            {
                check=0;
                printf("ID : %d\nNAME : ",sid);
                puts(sname);
            }
            if (check)
                printf("No IDs and Names exist.\n\n");
            fclose(fid);
            fclose(fnt);
            printf("\n\n");
            goto repeat;
            break;
        }
        case 2 :
        {
            int uid;
            printf("Enter your Unique ID : ");
            scanf("%d",&uid);
            display(uid);
            goto repeat;
            break;
        }
        case 3 :
        {
            int id;
            char exec[20];
            long ft;  //stores the file pointer at that specific time
            printf("Enter the id : ");
            scanf("%d",&id);

            FILE *fdt;
            fdt=fopen(filedata,"r+");
            if (fdt == NULL)
            {
                printf("WARNING! FILE NOT FOUND\nPLEASE SAVE THE FILE %s IN THE SAME DIRECTORY",filedata);
                exit(1);
            }
            char sid[20];
            char fid[20];
            char data[200];
            int check=1;
            sprintf(sid,"%d",id);
            strcat(sid,"\n");

            while(fgets(fid,20,fdt)!=NULL)
            {
                if(strcmp(fid,sid)==0)
                {
                    check=0;
                    printf("UNIQUE ID : %d \n\n",id);
                    for(int k=0; k<7; k++)
                    {
                        if(k==6)
                        {
                            ft=ftell(fdt);
                        }
                        fgets(data,200,fdt);

                    }


                    printf("EXECUTIVE : ");
                    puts(data);
                }
            }
            if(check)
            {
                printf("The id %d doesn't exist\n\n",id);
                goto repeat;
            }

            fseek(fdt,ft,SEEK_SET);
            printf("Enter the name of the EXECUTIVE(max 20 char) : ");
            getchar();
            gets(exec);

            for(int l=strlen(exec); l<20; l++)
            {
                strcat(exec," ");
            }

            fprintf(fdt,"%s\n",exec);
            fflush(fdt);
            printf("You have successfully assigned\n\n");
            fseek(fdt,0,SEEK_SET);

            while(fgets(fid,20,fdt)!=NULL)
            {
                if(strcmp(fid,sid)==0)
                {
                    printf("UNIQUE ID : %d \n\n",id);
                    for(int k=0; k<7; k++)
                    {
                        fgets(data,200,fdt);
                    }


                    printf("EXECUTIVE : ");
                    puts(data);
                }
            }

            fclose(fdt);
            printf("\n\n");
            goto repeat;
            break;
        }
        case 4 :
        {
            int id,c,check=1;

            long ft;
            printf("Enter the id : ");
            scanf("%d",&id);

            FILE *fdt;
            fdt=fopen(filedata,"r+");
            if (fdt == NULL)
            {
                printf("WARNING! FILE NOT FOUND\nPLEASE SAVE THE FILE %s IN THE SAME DIRECTORY",filedata);
                exit(1);
            }
            char sid[20];
            char fid[20];
            char data[200];
            sprintf(sid,"%d",id);
            strcat(sid,"\n");

            while(fgets(fid,20,fdt)!=NULL)
            {
                if(strcmp(fid,sid)==0)
                {
                    check=0;
                    printf("UNIQUE ID : %d \n\n",id);
                    for(int k=0; k<6; k++)
                    {
                        if(k==5)
                        {
                            ft=ftell(fdt);
                        }
                        fgets(data,200,fdt);

                    }


                    printf("STATUS : ");
                    puts(data);
                }
            }
            if (check)
            {
                printf("The ID %d doesn't exist!\n\n",id);
                goto repeat;
            }
            fseek(fdt,ft,SEEK_SET);



            int flag=1;
            while(flag)
            {
                printf("Enter the corresponding number : \n");
                printf("0 - NOT ASSIGNED\n");
                printf("1 - ASSIGNED\n");
                printf("2 - BEING FIXED\n");
                printf("3 - FIXED\n");
                printf("4 - DELIVERED\n");
                scanf("%d",&c);
                if((c==0)||(c==1)||(c==2)||(c==3)||(c==4))
                {
                    flag=0;
                }
                else
                {
                    printf("Enter a correct number!\n");
                }
            }

            fprintf(fdt,"%s\n",status[c]);
            fflush(fdt);




            printf("Status is changed successfully\n\n");
            fseek(fdt,0,SEEK_SET);

            while(fgets(fid,20,fdt)!=NULL)
            {
                if(strcmp(fid,sid)==0)
                {
                    printf("UNIQUE ID : %d \n\n",id);
                    for(int k=0; k<6; k++)
                    {
                        fgets(data,200,fdt);
                    }


                    printf("STATUS : ");
                    puts(data);
                }
            }

            fclose(fdt);
            printf("\n\n");
            goto repeat;
            break;
        }
        case 5:
        {
            main();
            break;
        }
        default:
        {
            printf("Enter the correct option!\n\n\n");
            goto repeat;
        }
        }
    }
    main();
}
void listbugs()
{
    printf("You are in listbugs successfully!!\n\n");
    int choice;
repeat:
    {
        printf("Enter 1 to get the list of bugs filed by the same person\n");
        printf("Enter 2 to get the list of bugs which have the same type\n");
        printf("Enter 3 to get the list of bugs which have the same status\n");
        printf("Enter 4 for main menu\n");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1 :
        {
            printf("Bugs entered by the same person\n");

            FILE *fdt;
            fdt=fopen(filedata,"r");
            if (fdt == NULL)
            {
                printf("WARNING! FILE NOT FOUND\nPLEASE SAVE THE FILE %s IN THE SAME DIRECTORY",filedata);
                exit(1);
            }

            char rname[20];
            char fname[20];
            char fid[20];
            char data[200];
            int check =1;
            printf("Enter the name of the person : ");
            getchar();
            gets(rname);

            strcat(rname,"\n");

            while(fgets(fid,20,fdt)!=NULL)
            {
                fgets(fname,20,fdt);
                if(strcmp(fname,rname)==0)
                {
                    check=0;
                    printf("\nUNIQUE ID : %s \n",fid);

                    printf("NAME : ");
                    puts(fname);
                    fgets(data,200,fdt);
                    printf("TYPE : ");
                    puts(data);
                    fgets(data,200,fdt);
                    printf("DESCRIPTION : ");
                    puts(data);
                    fgets(data,200,fdt);
                    printf("PRORITY : ");
                    puts(data);
                    fgets(data,200,fdt);
                    printf("DATE : ");
                    puts(data);
                    fgets(data,200,fdt);
                    printf("STATUS : ");
                    puts(data);
                    fgets(data,200,fdt);
                    printf("EXECUTIVE : ");
                    puts(data);
                    fgets(data,200,fdt);
                    puts(data);

                }
            }
            fclose(fdt);
            if(check)
            {
                printf("No such name exists!\n\n");
                goto repeat;
            }
            printf("\n\n");
            goto repeat;
            break;
        }
        case 2 :
        {
            FILE *fdt;
            fdt=fopen(filedata,"r");
            if (fdt == NULL)
            {
                printf("WARNING! FILE NOT FOUND\nPLEASE SAVE THE FILE %s IN THE SAME DIRECTORY",filedata);
                exit(1);
            }

            char rtype[20];
            char fname[20];
            char fid[20];
            char data[200];
            int c,check=1;
            int flag=1;
            while(flag)
            {
                printf("Enter the type of bug : \n");
                printf("0 - MAJOR\n1 - MINOR\n2 - COSMETIC\n");
                scanf("%d",&c);
                if((c==0)||(c==1)||(c==2))
                {
                    flag=0;
                }
                else
                {
                    printf("Enter the correct type!\n");
                }
            }
            strcpy(rtype,type[c]);

            strcat(rtype,"\n");

            while(fgets(fid,20,fdt)!=NULL)
            {
                fgets(fname,20,fdt);
                fgets(data,200,fdt);
                if(strcmp(rtype,data)==0)
                {
                    check=0;
                    printf("\nUNIQUE ID : %s \n",fid);

                    printf("NAME : ");
                    puts(fname);

                    printf("TYPE : ");
                    puts(data);
                    fgets(data,200,fdt);
                    printf("DESCRIPTION : ");
                    puts(data);
                    fgets(data,200,fdt);
                    printf("PRORITY : ");
                    puts(data);
                    fgets(data,200,fdt);
                    printf("DATE : ");
                    puts(data);
                    fgets(data,200,fdt);
                    printf("STATUS : ");
                    puts(data);
                    fgets(data,200,fdt);
                    printf("EXECUTIVE : ");
                    puts(data);
                    fgets(data,200,fdt);
                    puts(data);

                }
            }
            fclose(fdt);
            if(check)
            {
                printf("No bugs with this type! \n\n");
                goto repeat;
            }
            printf("\n\n");
            goto repeat;
            break;
        }
        case 3 :
        {
            FILE *fdt;
            fdt=fopen(filedata,"r");

            if (fdt == NULL)
            {
                printf("WARNING! FILE NOT FOUND\nPLEASE SAVE THE FILE %s IN THE SAME DIRECTORY",filedata);
                exit(1);
            }

            char rstatus[20];
            char fname[30];
            char fid[20];
            char ftype[30];
            char fdesc[200];
            char fpriority[30];
            char fdate[30];
            char fstatus[30];
            char fexec[30];
            char data[20];
            int c,check=1;
            int flag=1;
            while(flag)
            {
                printf("Enter the status : \n");
                printf("0 - NOT ASSIGNED\n1 - ASSIGNED\n2 - BEING FIXED\n3 - FIXED\n4 - DELIVERED\n");
                scanf("%d",&c);
                if((c==0)||(c==1)||(c==2)||(c==3)||(c==4))
                {
                    flag=0;
                }
                else
                {
                    printf("Enter the correct status!\n");
                }
            }
            strcpy(rstatus,status[c]);

            strcat(rstatus,"\n");

            while(fgets(fid,20,fdt)!=NULL)
            {
                fgets(fname,30,fdt);

                fgets(ftype,30,fdt);
                fgets(fdesc,200,fdt);
                fgets(fpriority,30,fdt);
                fgets(fdate,30,fdt);
                fgets(fstatus,30,fdt);
                if(strcmp(rstatus,fstatus)==0)
                {
                    check=0;
                    printf("\nUNIQUE ID : %s \n",fid);

                    printf("NAME : ");
                    puts(fname);

                    printf("TYPE : ");
                    puts(ftype);

                    printf("DESCRIPTION : ");
                    puts(fdesc);

                    printf("PRORITY : ");
                    puts(fpriority);

                    printf("DATE : ");
                    puts(fdate);

                    printf("STATUS : ");
                    puts(fstatus);
                    fgets(fexec,30,fdt);
                    printf("EXECUTIVE : ");
                    puts(fexec);
                    fgets(data,20,fdt);
                    puts(data);

                }
            }
            fclose(fdt);
            if(check)
            {
                printf("Bugs with this status doesn't exist!\n\n");
                goto repeat;
            }
            printf("\n\n");
            goto repeat;
            break;
        }
        case 4 :
        {
            main();
            break;
        }
        }
    }


    main();
}
void main()
{
    int choice;
    char pwdentry[50];
repeat :
    {
        printf("                                        WELCOME TO BUG TRACKERS! \n");
        printf("Enter 1 if you want to report a bug \nEnter 2 if you are the manager \nEnter 3 to get the list of bugs\n");
        printf("Enter 4 to get status on your report\nEnter 5 to exit\n");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1 :
        {
            user();
            goto repeat;
            break;
        }
        case 2 :
        {
            printf("Enter the password : ");
            scanf("%s",pwdentry);
            if(strcmp(pwdentry,password)==0)
                manager();
            else
            {
                printf("You have entered wrong password!\n\n\n");
                goto repeat;

            }
            break;
        }
        case 3 :
        {
            listbugs();
            goto repeat;
            break;
        }
        case 4 :
        {
            int uid;
            printf("Enter your Unique ID : ");
            scanf("%d",&uid);
            display(uid);
            goto repeat;
            break;
        }
        case 5:
        {
            printf("Thank you! Hope we resolved your issues!!");
            exit(0);
            break;
        }
        default:
        {
            printf("Enter the correct option!\n\n\n");
            goto repeat;
        }
        }
    }
}
void display(id)
{

    FILE *fdt;
    fdt=fopen(filedata,"r");
    if (fdt == NULL)
    {
        printf("WARNING! FILE NOT FOUND\nPLEASE SAVE THE FILE %s IN THE SAME DIRECTORY",filedata);
        exit(1);
    }
    char sid[20];
    char fid[20];
    char data[200];
    sprintf(sid,"%d",id);
    strcat(sid,"\n");
    int check=1;
    while(fgets(fid,20,fdt)!=NULL)
    {
        if(strcmp(fid,sid)==0)
        {
            check=0;
            printf("UNIQUE ID : %d \n\n",id);
            fgets(data,200,fdt);
            printf("NAME : ");
            puts(data);
            fgets(data,200,fdt);
            printf("TYPE : ");
            puts(data);
            fgets(data,200,fdt);
            printf("DESCRIPTION : ");
            puts(data);
            fgets(data,200,fdt);
            printf("PRORITY : ");
            puts(data);
            fgets(data,200,fdt);
            printf("DATE : ");
            puts(data);
            fgets(data,200,fdt);
            printf("STATUS : ");
            puts(data);
            fgets(data,200,fdt);
            printf("EXECUTIVE : ");
            puts(data);

        }
    }
    if(check)
        printf("%d DOES NOT EXIST!\n\n",id);
    fclose(fdt);
    printf("\n\n");
}
