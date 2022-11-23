#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void make_dir(char filename[]){
    int val = mkdir(filename, 0777);
    if(val == -1){
        perror(" Error ");
        return;
    }
}

void make_dir_v(char filename[]){
    int val = mkdir(filename, 0777);
    if(val == -1){
        perror(" Error ");
        return;
    }
    else{
        printf("mkdir: created directory '%s'", filename);
        printf("\n");
    }
}

void mkdir_version(){
    printf("mkdir (GNU coreutils) 8.32 \nCopyright (C) 2020 Free Software Foundation, Inc. \nLicense GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>. \nThis is free software: you are free to change and redistribute it. \nThere is NO WARRANTY, to the extent permitted by law. \nWritten by David MacKenzie.\n");
}

int main(int argc, char** argv){
    
    if(argc == 3){
        if(strcmp(argv[2], "--version") == 0){
            printf("\n");
            mkdir_version();
        }
        else{
            make_dir(argv[2]);
        }
    }
    else if(argc == 4){
        char* temp = argv[2];
        if(temp[0] == '-'){
            if(strcmp(temp, "-v") == 0){
                make_dir_v(argv[3]);
            }
            else{
                printf("Invalid Input -- %s \n", temp);
            }
        }
        else{
            printf("Invalid Input -- %s \n", temp);
        }
    }
    else{
        printf("Invalid Input");
    }

    return 0;
}