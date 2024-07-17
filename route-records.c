#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "route-records.h"

RouteRecord* createRecords( FILE* fileIn ) {
    int count = 0;
    char buffer[300];

    while(fgets(buffer,sizeof(buffer),fileIn)){
        count++;
    }
    count --;

    RouteRecord* records = (RouteRecord*)malloc(count*sizeof(RouteRecord));
    if(!records) {
        printf("Error allocating memory\n");
        return NULL;
    }

    for(int i = 0; i < count; ++i) {
        for(int j = 0; j < 6; ++j) {
            records[i].passengers[j] = 0;
        }
    }
    rewind(fileIn);
    return records;
}

int findAirlineRoute(
            RouteRecord* r,
            int length,
            const char* origin,
            const char* destination,
            const char* airline,
            int index )
{
    if(index >= length) {
        return -1;
    }
    if(strcmp(r[index].origin,origin) == 0 && strcmp(r[index].destination,destination) == 0 && strcmp(r[index].airline,airline) == 0) {
        return index;
    }
    return findAirlineRoute(r,length,origin,destination,airline,index +1);
}


int fillRecords(
    RouteRecord* r,
    FILE* fileIn )
{

    char buffer[300];
    char origin[4];
    char destination[4];
    char airline[3];
    int passengers,month;
    int records = 0;

    fgets(buffer,sizeof(buffer),fileIn);


    while(fgets(buffer, sizeof(buffer),fileIn)) {
        sscanf(buffer,"%d,%3s,%3s,%2s,,%d",&month,origin,destination,airline,&passengers);
        int  index =  findAirlineRoute(r,records,origin,destination,airline,0);
        // if -1 then there is already a route with data, input passengers into that route
        if(index != -1) {
            r[index].passengers[month-1] = passengers;
        }
        else {
            strcpy(r[records].origin, origin);
            strcpy(r[records].destination,destination);
            strcpy(r[records].airline,airline);
            r[records].passengers[month -1] = passengers;
            ++records;
        }
    }
    return records;
}

void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st) {
    int totalPassengers = 0;
    int monthPassengers[6] = {0};
    int matches = 0;

    for (int i = 0; i < length; i++) {
        int match = 0;

        switch (st) {
            case ROUTE:
                if (strcmp(r[i].origin, key1) == 0 && strcmp(r[i].destination, key2) == 0) {
                    match = 1;
                }
                break;
            case ORIGIN:
                if (strcmp(r[i].origin, key1) == 0) {
                    match = 1;
                }
                break;
            case DESTINATION:
                if (strcmp(r[i].destination, key1) == 0) {
                    match = 1;
                }
                break;
            case AIRLINE:
                if (strcmp(r[i].airline, key1) == 0) {
                    match = 1;
                }
                break;
            default:
                match = 0;
                break;
        }

        if (match) {
            matches++;

//            totalPassengers += r[i].passengers[0] + r[i].passengers[1] + r[i].passengers[2] +
//                               r[i].passengers[3] + r[i].passengers[4] + r[i].passengers[5];
            for (int j = 0; j < 6; j++) {
                monthPassengers[j] += r[i].passengers[j];
            }
            printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
        }
    }
    printf("\n");
    totalPassengers += r->passengers[0] + r->passengers[1] + r->passengers[2] +
                       r->passengers[3] + r->passengers[4] + r->passengers[5];

    if (matches > 0) {
        printf("%d matches were found.\n", matches);
        printf("Statistics\n");
        printf("Total Passengers: %d\n", totalPassengers);
        for (int i = 0; i < 6; i++) {
            printf("Total Passengers in Month %d: %d\n", i + 1, monthPassengers[i]);
        }
        printf("Average Passengers per Month: %d\n", totalPassengers / 6);
    } else {
        printf("No matches found.\n");
    }
}


void printMenu() { // print the menu, kinda obvious lol
    printf("\n\n######### Airline Route Records Database MENU #########\n");
    printf("1. Search by Route\n");
    printf("2. Search by Origin Airport\n");
    printf("3. Search by Destination Airport\n");
    printf("4. Search by Airline\n");
    printf("5. Quit\n");
    printf("Enter your selection: ");
}