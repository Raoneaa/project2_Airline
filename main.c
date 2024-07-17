/*
this project was written by Julian solis on July 10, 2024
it takes in a csv file from the command line then reads the data
it then allows the user to search the data using origin and destinations
then outputing the data found
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route-records.h"

int main(int argc, char *argv[]) {
//tell user to input file if 2 arguemnts are not read
    if (argc != 2) {
        printf("Please input file into command line when starting program");
        return 1;
    }
// create file pointer and open file from the command line using argv[1]
    FILE *fileIn = fopen(argv[1], "r");
// if it count open the file given in the comand line then give error message
    if (!fileIn) {
        fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
        return 1;
    }
// creating pointer for records by calling the createRecords function
    RouteRecord* records = createRecords(fileIn);
// fill in the records from read data and assign recordCount int to what is returned from function
    int recordCount = fillRecords(records, fileIn);

    printf("Unique routes operated by airlines: %d\n", recordCount);
    fclose(fileIn);
    int choice;
// initializing the keys and setting their max size including the null terminator
    char key1[4], key2[4];
// infinite loop that repeats until the user inputs 5 to exit
    do {
// calls the print menu
        printMenu();

        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input\n");
            while (getchar() != '\n'); // Clear the buffer
            continue;
        }
// switcase statement comparing the choice from the user
        switch (choice) {
            case 1:
                printf("Enter origin airport: ");
                scanf("%3s", key1);
                printf("Enter destination airport: ");
                scanf("%3s", key2);
                searchRecords(records, recordCount, key1, key2, ROUTE);
                break;
            case 2:
                printf("Enter origin airport: ");
                scanf("%3s", key1);
                searchRecords(records, recordCount, key1, NULL, ORIGIN);
                break;
            case 3:
                printf("Enter destination airport: ");
                scanf("%3s", key1);
                searchRecords(records, recordCount, key1, NULL, DESTINATION);
                break;
            case 4:
                printf("Enter airline code: ");
                scanf("%2s", key1);
                searchRecords(records, recordCount, key1, NULL, AIRLINE);
                break;
            case 5:
                printf("Goodbye!\n");
                break;
// if any input that is not the case then it gives an error message then scans again
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 5);
// frees the database
    free(records);
    return 0;
}
