#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define MY_NAME "Victor Muñoz"

int main(int argc, char const *argv[]) {
     /* code */
     char msg [100];
     char buffer [27];
     int sprintfBytes = -1;
     int writeBytes = -1;
     int readBytes = -1;
     int totalWrittenBytes = 0;
     char copyFromFile[50];
     char copyToFile[50];
     int copyFromFileDescriptor = -1;
     int copyToFileDescriptor = -1;


     //prints first line
     sprintfBytes = sprintf(msg, "Welcome to the File Copy Program by %s!\n", MY_NAME);
          //check if sprintf is working
          if (sprintfBytes == -1){
               perror("ERROR running sprintf:");
          }
     writeBytes = write(STDOUT_FILENO, msg, sprintfBytes);
          //check if write is working
          if (writeBytes == -1){
               perror("ERROR running write:");
          }


     //prints second line
     sprintfBytes = sprintf(msg, "Enter the name of the file to copy from:\n");
          //check if sprintf is working
          if (sprintfBytes == -1){
               perror("ERROR running sprintf:");
          }
     writeBytes = write(STDOUT_FILENO, msg, sprintfBytes);
          //check if write is working
          if (writeBytes == -1){
               perror("ERROR running write:");
          }
     scanf("%s", copyFromFile);

     //open file
     copyFromFileDescriptor = open(copyFromFile, O_RDONLY, 0);
          if (copyFromFileDescriptor == -1) {
               perror("ERROR file does not exist:");
               return -1;
          }


     //prints third line
     sprintfBytes = sprintf(msg, "Enter the name of the file to copy to:\n");
          //check if sprintf is working
          if (sprintfBytes == -1){
               perror("ERROR running sprintf:");
          }
     writeBytes = write(STDOUT_FILENO, msg, sprintfBytes);
          //check if write is working
          if (writeBytes == -1){
               perror("ERROR running write:");
          }
     scanf("%s", copyToFile);


     //open files
     copyToFileDescriptor = open(copyToFile, O_WRONLY | O_TRUNC , 0);
          if (copyToFileDescriptor == -1) {
               perror("ERROR file does not exist:");
               return -1;
          }


     //read and write to file one byte at a time
     //read() returns 0 when end of line character is reached
     //hence, keep writing until the end of line character is found
     //write() returns the number of bytes written, which is at most 27 bytes for each loop
     //because we are reading one byte at a time.
     while (readBytes != 0 ) {

     readBytes = read(copyFromFileDescriptor, buffer, sizeof(buffer));
          if (readBytes == -1) {
               perror("ERROR reading file:");
               break;
          }
     writeBytes = write(copyToFileDescriptor, buffer, readBytes);
          if (writeBytes == -1) {
               perror("ERROR writing to file:");
               break;
          }
     totalWrittenBytes += writeBytes;
     }


     //close files
     copyFromFileDescriptor = close(copyFromFileDescriptor);
          if (copyFromFileDescriptor == -1) {
               perror("ERROR closing copy from file:");
          }
     copyToFileDescriptor = close(copyToFileDescriptor);
          if (copyToFileDescriptor == -1) {
               perror("ERROR closing copy to file:");
          }


     //print last line
     sprintfBytes = sprintf(msg, "File Copy Successful, %d bytes copied\n", totalWrittenBytes);
          //check if sprintf is working
          if (sprintfBytes == -1){
               perror("ERROR running sprintf:");
          }
     writeBytes = write(STDOUT_FILENO, msg, sprintfBytes);
          //check if write is working
          if (writeBytes == -1){
               perror("ERROR running write:");
          }

     return 0;
}
