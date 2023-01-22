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
int fd1= open(argv[1], O_RDONLY);//open file 1
int fd2= open(argv[2], O_RDONLY);//open file 2
if ((fd1==(-1))||(fd2==(-1))) //check if one from the tow file isnt opened
exit (-1);// if wasnt opend return -1
int i=0;
int flag, readout1, readout2;
char read1[1];//buffer 1
char read2[1];//buffer 2
while(1) //a loop that scans the to files and compers between them character by character
{
 lseek(fd1,i,SEEK_SET);//put the pointer on the current character in file 1
 lseek(fd2,i,SEEK_SET);//same for file 2
 readout1 = read(fd1,read1,1);//read a charcter to the buffer from file 1
 readout2 = read(fd2,read2,1);//same from file 2
 if((readout1==-1)||(readout2==-1))//if something didnt work well in the reading
 {
    flag=7;
    break;
 }
 if ((readout1==0)&&(readout2==0))//if it done to read the two files without a different 
  {
    flag = 2;
    break;
  }
 if ((readout1!=readout2)||(read1[0]!=read2[0]))//if reading of one from the file was done, but the other wasnt or if a character from file 1 is different from file 2
  {
  flag=1;
  break;
  }
  
  i++;//go to the next character on the next interation in the loop
}
close(fd1);
close(fd2);
if (flag==1)//the files are different->return 1
{
exit (1);
}
if (flag==2)//the files are same->return 2
exit(2);
if(flag==(7))//there was some errors in the files readinf->return -1
exit(-1);
}