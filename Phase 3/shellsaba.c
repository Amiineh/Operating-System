#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <getopt.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>


//Macros
#define DEFAULT_COMMAND_SIZE (size_t) 20
#define DEFAULT_ARGUMENT_COUNT 10

//Global Variables
char *shell_name;
char *shell_version;

static int init_shell(char name[], char version[], size_t **command_size, char ***argv, int argument_count_coeff){
	shell_name    = (char *) malloc(strlen(name) * sizeof(char));
	shell_version = (char *) malloc(strlen(version) * sizeof(char));

	strcpy(shell_name, name);//set the shell name
	strcpy(shell_version, version);//set the shell version
	
	//(**lineptr) = (char *) malloc(DEFAULT_COMMAND_SIZE);
	(*command_size) = (size_t *) malloc(sizeof(int));
	(**command_size) = DEFAULT_COMMAND_SIZE;

	(*argv) = (char **) malloc((argument_count_coeff) * DEFAULT_ARGUMENT_COUNT * sizeof(char *));//malloc for argv for stdin argumans 

	return 0;
}

int main(int argc, char* argv[]){ 
	int retval;
	int arg_counter;
	int argument_count_coeff = 1;

	size_t *command_size;

	char *delimiter = " ";// the delimiter here is space
	char **lineptr = (char**) malloc(sizeof(char*)); //pointer to string 
	(*lineptr) = (char*) malloc(DEFAULT_COMMAND_SIZE);
	char * command_line;
	char* username = (char*)malloc(sizeof(char) * 20);
	char* machinename = (char*) malloc(sizeof(char) * 20);
	username = getlogin();//get username
	gethostname(machinename, 20);
	init_shell("shellsaba", "0.1", /*&command_line,*/ &command_size , /*&lineptr,*/ &argv, argument_count_coeff);
	fprintf(stdout, "Welcome to \"%s-v%s\"\n", shell_name, shell_version);
	do{	
		arg_counter = 0;
		fprintf(stdout, "%s$%s ", username, machinename);
		retval = getline(lineptr, command_size, stdin);
		(*lineptr)[retval-1] = '\0';
		
		for(argv[arg_counter] = strtok(*lineptr, delimiter) ; argv[arg_counter] != NULL ; arg_counter++, argv[arg_counter] = strtok(NULL, delimiter)){
			if(arg_counter == DEFAULT_ARGUMENT_COUNT - 1)//strtok take argumans at first we mention *lineptr because of command 
				argv = realloc(argv, (++argument_count_coeff) * DEFAULT_ARGUMENT_COUNT * sizeof(char *));//if the space was not enough it may allocate extra space
		}
		pid_t pid = fork();//for executing the command we must have another process 
		if (pid == 0) { //if we were in child's process
				if (strcmp(argv[0], "echo") == 0 && arg_counter> 2) {//if the command was echo and the argumans was more than 2 we must open a file and write in it
					int fd = open(argv[3], O_CREAT | O_RDWR, S_IRWXU);
					int len = strlen(argv[1]);
					 write(fd, argv[1], len);
					close(fd);
				}
			   	else {
					execvp(argv[0], argv);//if the command was'nt echo it execute that
					fprintf(stderr, "No such program!\n");//if the command was'nt find it prints error
				}
		}
	   	else {
			int status;
			wait(&status);//if we were in parent's process it waits untill the child's process will be terminated
		}

	}while(strcmp(*lineptr, "exit") != 0);		
	return 0;
}
