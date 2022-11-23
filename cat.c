#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <fcntl.h>
#include<sys/wait.h>

void read_file(char filename[]){
    FILE* input = fopen(filename, "r");
    if(input == NULL){
        printf("No file exsits\n");
        return ;
    }

    int count = 1;
    char ch;
    size_t value = fread(&ch, sizeof(char), count, input);
    while(value == count){
        printf("%c", ch);
        value = fread(&ch, sizeof(char), count, input);
    }
    printf("\n");

    fclose(input);
}

void read_file_E(char filename[]){
    FILE* input = fopen(filename, "r");
    if(input == NULL){
        printf("No file exsits\n");
        return ;
    }

    int count = 1;
    char ch;
    size_t value = fread(&ch, sizeof(char), count, input);
    while(value == count){
        if(ch == '\n'){
            printf("$");
        }
        printf("%c", ch);
        value = fread(&ch, sizeof(char), count, input);
    }
    printf("\n");

    fclose(input);
}

void read_file_T(char filename[]){
    FILE* input = fopen(filename, "r");
    if(input == NULL){
        printf("No file exsits\n");
        return ;
    }

    int count = 1;
    char ch;
    size_t value = fread(&ch, sizeof(char), count, input);
    while(value == count){
        if(ch == '\t'){
            printf("^I");
        }
        else{
            printf("%c", ch);
        }
        value = fread(&ch, sizeof(char), count, input);
    }
    printf("\n");

    fclose(input);
}

int main(int argc, char** argv){
    
    if(argc == 3){
        read_file(argv[2]);
    }
    else if(argc == 4){
        char* token = argv[2];
        if(token[0] == '-'){
            if(strcmp(token, "-T") == 0){
                read_file_T(argv[3]);
            }
            else if(strcmp(token, "-E") == 0){
                read_file_E(argv[3]);
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