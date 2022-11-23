#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>
    //hello
        //hello
void print_date(){
    time_t t = time(NULL);
    if(t == -1){
        perror(" Error ");
        return;
    }

    struct tm* present;
    present = localtime(&t);
    if(present == NULL){
        perror(" Error ");
        return;
    }

    char day[10], month[10], tm[20], zone[10];

    strftime(day, 10, "%A", present);
    strftime(month, 10, "%B", present);
    strftime(tm, 20, "%r", present);
    strftime(zone, 10, "%Z", present);
    //  %02d converts 5 -> 05 and 22 ->22 : just add 0 to numbers < 10
    
    printf("%s %02d %s %d %s %s \n", day, present->tm_mday, month, present->tm_year + 1900, tm, zone);

    return;
}

void print_dateU(){
    time_t t = time(NULL);
    if(t == -1){
        perror(" Error ");
        return;
    }

    struct tm* present;
    present = gmtime(&t);
    if(present == NULL){
        perror(" Error ");
        return;
    }

    char day[10], month[10], tm[20], zone[10];

    strftime(day, 10, "%A", present);
    strftime(month, 10, "%B", present);
    strftime(tm, 20, "%r", present);

    //  %02d converts 5 -> 05 and 22 ->22 : just add 0 to numbers < 10
    
    printf("%s %02d %s %d %s UTC \n", day, present->tm_mday, month, present->tm_year + 1900, tm);

    return;
}

void print_dateR(){
    time_t t = time(NULL);
    if(t == -1){
        perror(" Error ");
        return;
    }

    struct tm* present;
    present = localtime(&t);
    if(present == NULL){
        perror(" Error ");
        return;
    }

    char day[10], month[10], tm[20], zone[10];
    strftime(day, 10, "%a", present);
    strftime(month, 10, "%b", present);
    strftime(tm, 20, "%X", present);
    strftime(zone, 10, "%z", present);
    //  %02d converts 5 -> 05 and 22 ->22 : just add 0 to numbers < 10
    
    printf("%s, %02d %s %d %s %s \n", day, present->tm_mday, month, present->tm_year + 1900, tm, zone);

    return;
}

int main(int argc, char** argv){

    if(argc == 2){
        print_date();
    }
    else if(argc == 3){
        char* temp = argv[2];
        if(temp[0] == '-'){
            if(strcmp(temp, "-U") == 0){
                print_dateU();
            }
            else if(strcmp(temp, "-R") == 0){
                print_dateR();
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