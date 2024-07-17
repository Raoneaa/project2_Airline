#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include"route-records.h" //make sure to create this file


//
// int main(int argc, char *argv[]) {
//
//     // 1. Declare variables here
//
//     // 2. Check command line arguments here. If a command line argument (for the file name) is missing, print out the following: ERROR: Missing file name and end the program
//
//     // 3. Attempt to open the file. Print out Opening <filename>... before you call fopen().
//
//     // 4. Check to see if the file opens. If it does not open, print out ERROR: Could not open file and end the program.
//
//     /* 5. Do the following to load the records into an array of RouteRecords
//
//     		5.1 Call createRecords(), which will read through the file once to find the total number of lines/records in the file. Use this count, to dynamically allocate memory for an array of RouteRecords. It returns a pointer to that array. Don't forget to rewind the file pointer.
//
//     		5.2 Call fillRecords() to go through the CSV file again to fill in the values. It will then return the actual number of items the array has. Recall that not all records in the original CSV file will be entered into the array. Print the number of unique routes operated by different airlines: Unique routes operated by airlines: ???
//
//     		5.3 Close the the file.
//     */
//
//     /* 6. Create an infinite loop that will do the following:
//
//     		6.1 Call printMenu()
//
//     		6.2 Ask the user to input a value for the menu
//
//     		6.3 Handle the case in which a non-integer value is entered
//
//     		6.4 Create a switch/case statement to handle all the menu options
//
// 	    		6.4.1 Each option requires the user to enter a search key
//
// 	    		6.4.2 Quit needs to free the array
//     */
//
//     //7. Free the records, print goodbye
//
//     printf("Goodbye.\n");
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route-records.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *fileIn = fopen(argv[1], "r");
    if (!fileIn) {
        fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
        return 1;
    }

    RouteRecord* records = createRecords(fileIn);
    int recordCount = fillRecords(records, fileIn);

    printf("Unique routes operated by airlines: %d\n", recordCount);

    int choice;
    char key1[4], key2[4];

    do {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input\n");
            while (getchar() != '\n'); // Clear the buffer
            continue;
        }

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
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 5);

    free(records);
    fclose(fileIn);
    return 0;
}
