//Asaf Ben Or 
#include <stdio.h>
#include <sys/fcntl.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
int main(int argc, char* argv[])
{
char* configfile=argv[1];//the paths name of the configuration file
char students[50];//the paths name of the student dir
char input[50];//the paths name of the inputs file
char output[50];//the pats name of the outputs file
int size;
int fdgrades = open("grades.cvs",O_RDONLY|O_WRONLY);//create the cvs file of the resulsts
int fdconfig = open(configfile, O_RDONLY);//open the cunfiguration file
char copy[1];// abuffer
int red;
copy[0]='b';
size=0;
while (copy[0]!='\n')//this loop reads the first line from the configuration text which means the student dir
{
red=read(fdconfig,copy,1);
size++;
}
lseek (fdconfig,0,SEEK_SET);
red=read(fdconfig,students,size-1);
write(2,students,strlen(students));
printf("\n");

int instart = size;
lseek(fdconfig,instart,SEEK_SET);
size=0;
copy[0]='a';
while (copy[0]!='\n')//this while reads the second line from the configuration line which means the input file
{
red=read(fdconfig,copy,1);
size++;
}
lseek (fdconfig,instart,SEEK_SET);
red=read(fdconfig,input,size-1);
write(2,input,strlen(input));
printf("\n");

int outstart = instart+ size;//this while reads the third line from the configuration line which means the output file
lseek(fdconfig,outstart,SEEK_SET);
size=0;
copy[0]='a';
while (red!=0)
{
red=read(fdconfig,copy,1);
size++;
}
lseek (fdconfig,outstart,SEEK_SET);
red=read(fdconfig,output,size-2);
write(2,output,strlen(output));
printf("\n");

int status;
DIR* dirpointer;
int pid=fork();//make a son
if (pid==0)//in this son we use the ls command to write the names of the students (the files name of users dir) to a new file which we call studentlist.txt
{
dirpointer=opendir(students);
char *const arguments[]={"ls",students,NULL};
close(1);
int fdstudentlist=open("studentlist.txt", O_CREAT|O_WRONLY,777);
dup (fdstudentlist);
execvp("ls" ,arguments);
}
else//continue the father
{
 wait(&status);
 int outputopen;
 int fdstudentslist= open("studentlist.txt", O_RDONLY,777);
 copy[0]='a';
 int read1=2;
 int i;
 while (read1 != 0){//in this big loop we every time use an other student name from the list
    char name[50];
    i=0;
    while(1)//in this while we put the students name in name
       {
                read1 = read(fdstudentslist, copy, 1);
                if ((copy[0]=='\n')||(read1==0))
                break;
                name[i] = copy[0];
                i++;
                
        }
    if (read1==0)
    break;
    char* path1=malloc(50*sizeof(char));
    strcat(path1,students);//from hear we make the path to the student compilated file
    strcat(path1,"/");
    strcat(path1,name);
    
    strcat(path1,"/main.out");


    int pid2=fork(); //in this son we run the student code and put the output to the new file which named by newoutput.txt 
    if(pid2==0){
        int inputopen=open(input, O_RDONLY);
        close(0);
        dup(inputopen);
        
        close(1);
        outputopen=open("newoutput.txt", O_CREAT|O_RDONLY|O_WRONLY|O_TRUNC, 0666);
        dup(outputopen);
        char* runcomp[] = {path1, NULL};

        execvp(path1,runcomp);
        exit(-1);
        }
    else
    {
    wait(&status);
    int pid3=fork();//in this son we compare from the expected output from the output.txt and the students output from the new output.txt by the function from ex1
        if(pid3==0)
            {
            char *thecompare[] ={"/home/asaf/Desktop/comp.out",output,"/home/asaf/Desktop/newoutput.txt",NULL};
            execvp(thecompare[0],thecompare);
            exit(-1);
             }
        else{
        wait(&status);
        //here we create the result.cvs which put 100 for a student if the compare func rutrned 2 (which means a succes), and else he gets a zero
        int openresult=open("result.csv", O_CREAT | O_WRONLY | O_APPEND, 0777);
        close(1);
        dup(openresult);
        if(WEXITSTATUS(status)==2)
            {
            printf("%s,100\n",name);
            }
        else
            printf("%s,0\n",name);
        

         }





    }
    
}
}
return 0;
}
