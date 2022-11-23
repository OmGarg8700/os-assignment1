#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <unistd.h>

void rm_file(char filename[]){
    int val = unlink(filename);
    if(val != 0){
        perror(" Error ");
        return;
    }
}

void rm_directory(char filename[]){
    int val = rmdir(filename);

    if(val != 0){
        perror(" Error ");
        return;
    }
}

void rm_file_v(char filename[]){
    int val = unlink(filename);

    if(val != 0){
        perror(" Error ");
        return;
    }
    else{
        printf("removed '%s' \n", filename);
    }
}

int main(int argc, char** argv){

    if(argc == 3){
        rm_file(argv[2]);
    }
    else if(argc == 4){
        char* token = argv[2];
        if(token[0] == '-'){
            if(strcmp(token, "-d") == 0){
                rm_directory(argv[3]);
            }
            else if(strcmp(token, "-v") == 0){
                rm_file_v(argv[3]);
            }
            else{
                printf("Invalid Input -- %s \n", token);
            }
        }
        else{
            printf("Invalid Input -- %s \n", token);
        }
    }
    else{
        printf("Invalid Input");
    }
    return 0;
}