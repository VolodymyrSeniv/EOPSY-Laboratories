

//The following programs copies one file to another, either with memory mapping or with read and write instructions.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 8192
//open - opens a file or creates it. 
//Arguments in the first case a showing the path name and the mode of reading the file. In the secong case we are oppening the file in the mode of writting reading  it or creating
// open fucntion returns the file descriptor (non negative integer) or a negative integer in a case of failing. The file descriptor could be used in the system calls like read(), write(), lseek(), fcntl().


//getopt - parses the command line arguments. If everything is successful, then this fucntion returns the option carracter. When all the command line options are parsed it returns -1. 
//If it finds the arguments which was not metioned in the 3 argument (opstring) then it returns a question mark.

//ssize_t is the same as a size_t but also covers the signed numbers. It is used to represent the the size of an allocated memory block. So for read and write it is important to use ssize_t type

//read - reads from a file descriptor. Reads from a file descriptor from argument 1, to a buffer from argument 2, up to the size mentioned in the argument 3.
//If it succeds the number of bytes is returned and zero endicates the end of the file. In a case of error -1 is returned 

//write - writes to a file descriptor. Writes from the buffer to the file descriptor up to the size mentioned in the argument 3    

//close - closes the file descriptor indicated by the argument containing the variable which containes the file descriptor. Returns 0 on success and -1 if an error ocures. 

//stat - data type for a file status
//fstat - the same as a stat but the file is specified by a file descriptor from which the information is retrieved 
//struct stat{
//dev_t st_dev;
//ino_t st_ino;
//mode_t st_mode;
//nlink_t st_nlink;
//uid_t st_uid;
//gid_t st_gid;
//dev_t st_rdev;
//off_t st_size;
//blksize_t st_blksize;
//blkcnt_t st_blocks;
//}

//mmap - creates  a new mapping in the virtual adress space of the calling process
//returns a pointer to the mapped area when succeds or the flag MAP_FAILED is returned

//munmap - unmaps the specified mapping in the virtual adress space
//returns 0 on success or -1 when failes 

//memcpy - just copies the specified memorry area 
//returns a pointer do the destination 

//ftruncate - truncates a file to a specified size

//Essential functions definitions
void copy_read_write(int fd_from, int fd_to);
void copy_mmap(int fd_from, int fd_to);
void help();


int main(int argc, char **argv){
	//initializing variables
	int opt = 0;
	int fd_from, fd_to;
	
	//I have to check the number of arguments given, so that I can save the correct filename in the correct variable
	//Opening the files, both input and output and checking for errors
	//Always the last argument is the second file and the second from the end, the first file

	if (argc>2){
		fd_from = open (argv[argc-2], O_RDONLY); 
    	if (fd_from == -1) {
           	perror ("Error opening source file\n");
           	return 2;
    	}
		fd_to = open(argv[argc-1], O_RDWR | O_CREAT, 0666);
    	if (fd_to == -1){
        	perror("Error opening destination file\n");
        	return 3;
    	}
	}

	//Start getting the option arguments. As long as it is not returning -1 there are arguments available to check
	//We are checking for - and -m, and if there are not arguments, there is the execution of the function out of the while loop
	//After each function's execution we exit the program, so there is no case of executing more than one function

	while ((opt = getopt(argc, argv, ":mh::")) != -1) {
		switch(opt){
			case 'h':
				help(); //we do not need to have a break, since there is exit() in the function called
			case 'm':
				copy_mmap(fd_from, fd_to);
			default:
				printf("Wrong option. Check ./copy -h for more information\n");
				exit(0);
		}
	}
	if (argc>2){
		//since we do not have any options but we have arguments, we want the copy function with read-write
		copy_read_write(fd_from, fd_to);
	}
	else{//when the program is called without any arguments, just print some information
		help();
	}
	//successful return
	return 0;
}

//Copy functions implementations
void copy_read_write(int fd_from, int fd_to){
	char buffer[BUF_SIZE];      /* Character buffer */

	ssize_t filesize_from, filesize_out;    /* Number of bytes returned by read() and write() */

	/* Copy process */
    while((filesize_from = read (fd_from, &buffer, BUF_SIZE)) > 0){ //as long as we haven't reached the end, keep reading
            filesize_out = write (fd_to, &buffer, (ssize_t) filesize_from);
            if(filesize_out != filesize_from){
	      printf("Problem with copying\n");
	      exit(0); // when the number of bytes are not equal the error should happen 
            }
    }
 
    /* Close file descriptors */
    close (fd_from);
    close (fd_to);

    printf("File copying has been successfully complete\n");

    exit(1);
}

void copy_mmap(int fd_from, int fd_to){
	struct stat st;
	fstat(fd_from, &st); //return the status of the source file to the struct st

	char* target;
	target=mmap(0, st.st_size, PROT_READ, MAP_SHARED, fd_from, 0); //maps in the virtual address space 
	if (target==MAP_FAILED){ //system calls' error check
    	printf("Error mapping target\n");
    	exit(6);
	}

	char* destination;
		ftruncate(fd_to, st.st_size); //pre-size the destination file to the size of the source file
	destination=mmap(0, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_to, 0);
	if (destination == MAP_FAILED){
    	printf("Error mapping destination\n");
    	exit(5);
	}

	memcpy(destination, target, st.st_size); //copy the memory area between source and destination
	munmap(destination, st.st_size); //unmap files from memory since the copy has been done
	munmap(target, st.st_size);

	/* Close file descriptors */
    close (fd_from);
    close (fd_to);

    printf("File copying has been successfully complete\n");

    exit(1);
}

void help(){
	printf("\nThis program copies one file to another. \nSyntax is as follows:\n\n");
	printf("./lab6.c -m [source_file] [destination_file] -- copy the files by memory mapping\n");
	printf("./lab6.c [source_file] [destination_file] -- copy the files by reading and writing\n");
	printf("./lab6.c -h -- provide help for this program\n\n");
	exit(1);
}
