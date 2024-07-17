
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
