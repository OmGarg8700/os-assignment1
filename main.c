#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<wait.h>
#include<pthread.h>

// commands included -- cd, echo, pwd, exit, mkdir, rm, date, cat, ls

char** arguments;
int count = 0;

char* comm;
int comm_i = 0;

char** arg;

void make_arguments(char* line){
    char* token = strtok(line, " \n");

    while(token != NULL){
        // if(strcmp(token, "") == 0){
        //     printf("Hello");
        //     token = strtok(NULL, " \n");
        //     continue;
        // }
        arguments[count] = token;
        token = strtok(NULL, " \n");
        count++;

    }

    free(token);
}

void cd_L(char* path){
    
    int val = chdir(path);
    if(val == -1){
        perror(" Error ");
        return;
    }
}

void cd_P(char* path){
    char a[100];
    char* real_path = realpath(path, a);

    int val = chdir(a);
    if(val == -1){
        perror(" Error ");
        return;
    }
}

void cd_help(){
    printf("cd: cd [-L|[-P [-e]] [-@]] [dir] \nChange the shell working directory. \n\nChange the current directory to DIR.  The default DIR is the value of the\nHOME shell variable.\n\nThe variable CDPATH defines the search path for the directory containing\nDIR.  Alternative directory names in CDPATH are separated by a colon (:).\nA null directory name is the same as\nthe current directory.  If DIR begins\nwith a slash (/), then CDPATH is not used.\n\nIf the directory is not found, and\nthe shell option cdable_vars is set,\nthe word is assumed to be  a variable name.  If that variable has a value,\nits value is used for DIR.\n\nOptions:\n  -L	force symbolic links to be followed: resolve symbolic\n    links in DIR after processing instances of '..');\n  -P	use the physical directory structure without following\n    symbolic links: resolve symbolic links in DIR before\n    processing instances of '..'\n  -e	if the -P option is supplied, and the current working\n    directory cannot be determined successfully, exit with\n    a non-zero status\n  -@	on systems that support it, present a file with extended\n    attributes as a directory containing the file attributes\n\nThe default is to follow symbolic links, as if '-L' were specified.\n'..' is processed by removing the immediately previous pathname component\nback to a slash or the beginning of DIR.\n\nExit Status:\nReturns 0 if the directory is changed, and if $PWD is set successfully when\n-P is used; non-zero otherwise. \n");
}

void cd(int val){
    char* temp = arguments[1 + val];
    if(temp != NULL){ 
        if(temp[0] == '-'){
            if(strcmp(temp, "-L") == 0){
                temp = arguments[2 + val];
                if(temp != NULL){
                    cd_L(temp);
                }
                else{
                    printf("Invalid Input");
                }
            }
            else if(strcmp(temp, "-P") == 0){
                temp = arguments[2 + val];
                if(temp != NULL){
                    cd_P(temp);
                }
                else{
                    printf("Invalid Input");
                }
            }
            else if(strcmp(temp, "--help") == 0){
                cd_help();
            }
            else{
                printf("Invalid Input -- %s \n", temp);
            }
        }
        else{
            if(chdir(temp) == -1){
                perror(" Error ");
                return;
            }
        }
    }
    else{
        if(chdir(getenv("HOME")) == -1){
            perror(" Error ");      // here error should be corrected depending on the error which should come
            return;
        }
    }

}

// The default DIR is the value of the HOME shell variable.

void echo_n(int val){
    for(int i=2+val;i<count;i++){
        printf("%s ", arguments[i]);
    }
}

void echo_E(int val){

    for(int j=2+val;j<count;j++){
        char* output = arguments[j];
        for(int i=0;i<strlen(output);i++){
            if(output[i] == '\0'){
                break;
            }
            else if(output[i] == '/'){      // instead of \ we have used /
                continue;
            }
            else{
                printf("%c", output[i]);
            }
        }
    }

    printf("\n");
}

void echo(int val){
    char* temp = arguments[1 + val];
    // token = strtok(NULL, " \n");
    if(temp != NULL){
        
        if(temp[0] == '-'){
            if(strcmp(temp, "-n") == 0){
                temp = arguments[2 + val];
                if(temp != NULL){
                    echo_n(val);
                }
                else{
                    printf("Invalid Input");
                }
            }
            else if(strcmp(temp, "-E") == 0){
                temp = arguments[2 + val];
                if(temp != NULL){
                    echo_E(val);
                }
                else{
                    printf("Invalid Input");
                }
            }
            else{
                printf("Invalid token -- %s \n", temp);
            }
        }
        else{
            for(int i=1 + val;i<count;i++){
                printf("%s ", arguments[i]);
            }
            printf("\n");
        }
    }
    else{
        printf("\n");
    }
}

void pwd_L(){
    char* line = malloc(sizeof(char)*100);
    size_t n = 100;
    getcwd(line, n);

    printf("%s \n", line); 
    free(line); 
}

void pwd_P(){
    char* line = malloc(sizeof(char)*100);
    size_t n = 100;
    getcwd(line, n);

    printf("%s \n", line); 
    free(line); 
}

void pwd_help(){
    printf("pwd: pwd [-LP] \n\tPrint the name of the current working directory.\n \n\tOptions: \n\t-L	print the value of $PWD\n\tif it names the current working\n\t\tdirectory\n\t-P	print the physical directory, without any symbolic links\n\n\tBy default, `pwd' behaves as if `-L' were specified.\n\n\tExit Status:\n\n\tReturns 0 unless an invalid option is\n\tgiven or the current directory\n\tcannot be read.\n");
}

void pwd(int val){
    char* temp = arguments[1 + val];
    if(temp != NULL){
        // if(strcmp(temp, "") == 0){
        //     pwd_L();
        // }
        if(strcmp(temp, "--help") == 0){
            pwd_help();
        }
        else if(temp[0] == '-'){
            if(strcmp(temp, "-L") == 0){
                pwd_L();
            }
            else if(strcmp(temp, "-P") == 0){
                pwd_P();
            }
            else{
                printf("Invalid Input -- %s \n", temp);
            }
        }
        else{
            printf("Invalid Input");
        }
    }
    else{
        char* line = malloc(sizeof(char)*100);
        size_t n = 100;
        if(getcwd(line, n) == NULL){
            printf("Error");
        };

        printf("%s \n", line); 
        free(line);  
    }

}

// This is for fork and execvp
void make_external_commands(char* file){
    arg[0] = file;
    for(int i=0;i<count;i++){
        arg[i+1] = arguments[i];
    }
    

    pid_t pid = fork();
    if(pid == 0){
        int val = execvp(file, arg);
        if(val == -1){
            perror(" Error ");
        }
    }
    else{
        wait(NULL);
    }

    return;
}

// This is for pthreading -- pthread and system
void* make_call(void* argv){
    if(system(comm) == -1){
        printf("Error");
    }

    pthread_exit(0);
    return NULL;
}

void make_external_commands_threads(char* file){
    // appending file
    for(int i=0;i<strlen(file);i++){
        comm[comm_i++] = file[i];
    }

    // i = 1 for commands execution 
    for(int i=1;i<count;i++){
        // for space
        comm[comm_i++] = ' ';
        for(int j=0;j<strlen(arguments[i]);j++){
            comm[comm_i++] = arguments[i][j];
        }
    }
    
    pthread_t pthread;
    pthread_create(&pthread, NULL, make_call, NULL);

    pthread_join(pthread, NULL);

    free(comm);
}

// to free the arguments
void free_arguments(){
    for(int i=0;i<100;i++){
        comm[i] = ' ';
    }

    for(int i=0;i<=count;i++){
        arg[i] = NULL;
    }

    for(int i=0;i<count;i++){
        arguments[i] = NULL;
    }
    comm_i = 0;
    count = 0;
}

int main(){
    arguments = (char**)malloc(100*sizeof(char*));
    arg = (char**)malloc(sizeof(char*)*100);
    comm = malloc(sizeof(char)*100);

    char* line = NULL;
    size_t n = 0;

    int val = 0;    // this is for program to tell whether to use fork or pthreads
    while(1){
        printf("@>");
        getline(&line, &n, stdin);
        if(strcmp(line, "\n") == 0){
            continue;
        }

        make_arguments(line);

        if(strcmp(arguments[0], "&t") == 0){
            // printf("In the pthread\n");
            val = 1;
        }
        else{
            val = 0;
        }

        // Internal commands
        // echo
        if(strcmp(arguments[0 + val], "echo") == 0){
            echo(val);
        }

        // pwd
        else if(strcmp(arguments[0 + val], "pwd")==0){
            pwd(val);
        }

        // cd
        else if(strcmp(arguments[0 + val], "cd") == 0){
            cd(val);        
        }

        // External commands
        else if(strcmp(arguments[0 + val], "cat") == 0){
            if(val == 1){
                make_external_commands_threads("./cat");
            }
            else{
                make_external_commands("./cat");
            }
        }

        else if(strcmp(arguments[0 + val], "date") == 0){
            if(val == 1){
                make_external_commands_threads("./date");
            }
            else{
                make_external_commands("./date");
            }
        }
        
        else if(strcmp(arguments[0 + val], "ls") == 0){
            if(val == 1){
                make_external_commands_threads("./ls");
            }
            else{
                make_external_commands("./ls");
            }
        }

        else if(strcmp(arguments[0 + val],"mkdir") == 0){
            if(val == 1){
                make_external_commands_threads("./mkdir");
            }
            else{
                make_external_commands("./mkdir");
            }
        }

        else if(strcmp(arguments[0 + val], "rm") == 0){
            if(val == 1){
                make_external_commands_threads("./rm");
            }
            else{
                make_external_commands("./rm");
            }
        }

        else if(strcmp(arguments[0 + val], "exit") == 0){
            break;
        }

        else{
            printf("Wrong Command \n");
        }

        // clearing the arguments that was passed earlier
        free_arguments();
    }

    free(arguments);
    free(arg);
    free(comm);
    return 0;
}