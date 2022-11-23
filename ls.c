#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <dirent.h>

void print_ls(){
    struct dirent **names;
    int n = scandir(".", &names, NULL, alphasort);

    if(n == -1){
        perror(" Error ");
        return;
    }

    for(int i=0;i<n;i++){
        if(names[i]->d_name[0] == '.'){
            continue;
        }
        printf("%s ", names[i]->d_name);
    }
    printf("\n");
    free(names);

    return;
}

void print_ls_a(){
    struct dirent **names;
    int n = scandir(".", &names, NULL, alphasort);

    if(n == -1){
        perror(" Error ");
        return;
    }

    for(int i=0;i<n;i++){
        printf("%s ", names[i]->d_name);
    }
    printf("\n");
    free(names);

    return;
}

void print_version(){
    printf("ls (GNU coreutils) 8.32 \nCopyright (C) 2020 Free Software Foundation, Inc. \nLicense GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>. \nThis is free software: you are free to change and redistribute it. \nThere is NO WARRANTY, to the extent permitted by law. \nWritten by Richard M. Stallman and David MacKenzie.\n");
}

void print_ls_m(){
    struct dirent **names;
    int n = scandir(".", &names, NULL, alphasort);

    if(n == -1){
        perror(" Error ");
        return;
    }

    for(int i=0;i<n;i++){
        printf("%s, ", names[i]->d_name);
    }
    printf("\n");
    free(names);

    return;
}

int main(int argc, char** argv){
    if(argc == 2){
        print_ls();
    }
    else if(argc == 3){
        char* temp = argv[2];
        if(temp[0] == '-'){
            if(strcmp(temp, "-a") == 0){
                print_ls_a();
            }
            else if(strcmp(temp, "-m") == 0){
                print_ls_m();
            }
            else if(strcmp(temp, "--version") == 0){
                print_version();
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
