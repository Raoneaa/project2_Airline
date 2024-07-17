#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "route-records.h"

RouteRecord* createRecords(
 FILE* fileIn )
 {
// count is the number of lines in the file
    int count = 0;
    char buffer[300];
// read the number of lines updating count to reflect the lines read
    while(fgets(buffer,sizeof(buffer),fileIn)){
        count++;
    }
    count --;
// initialize the array using the number of lines(count) * the size of the strict RouteRecord
    RouteRecord* records = (RouteRecord*)malloc(count*sizeof(RouteRecord));
    if(!records) {
        printf("Error allocating memory\n");
        return NULL;
    }
// set all passengers to 0
    for(int i = 0; i < count; ++i) {
        for(int j = 0; j < 6; ++j) {
            records[i].passengers[j] = 0;
        }
    }
//rewind to the top of the file and return the record pointer
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
// basecase, if it doesnt find anthing before getting to negative index then return -1 to
// give no found message
    if(index >= length) {
        return -1;
    }
// if found the return the index that its at
    if(strcmp(r[index].origin,origin) == 0 && strcmp(r[index].destination,destination) == 0 && strcmp(r[index].airline,airline) == 0) {
        return index;
    }
// recurse if its not found
    return findAirlineRoute(r,length,origin,destination,airline,index +1);
}


int fillRecords(
    RouteRecord* r,
    FILE* fileIn )
{
// initialize the variables
    char buffer[300];
    char origin[4];
    char destination[4];
    char airline[3];
    int passengers,month;
    int records = 0;
// skip the header line
    fgets(buffer,sizeof(buffer),fileIn);

// read the file and input the data from the buffer until it reaches the end of the file
    while(fgets(buffer, sizeof(buffer),fileIn)) {
        sscanf(buffer,"%d,%3s,%3s,%2s,,%d",&month,origin,destination,airline,&passengers);
// after scanning in it doesnt assign it untit verified that that route doesnt already exists
        int  index =  findAirlineRoute(r,records,origin,destination,airline,0);
        // if -1 then there is already a route with data, input passengers into that route
        if(index != -1) {
            r[index].passengers[month-1] = passengers;
        }
// if no route is found then it makes a new record for that route
        else {
            strcpy(r[records].origin, origin);
            strcpy(r[records].destination,destination);
            strcpy(r[records].airline,airline);
            r[records].passengers[month -1] = passengers;
// update the record count by 1
            ++records;
        }
    }
// return the number of records
    return records;
}

void searchRecords(
        RouteRecord* r,
        int length,
        const char* key1,
        const char* key2,
        SearchType st)
     {
// initialize the variables that are needed to see if there is a match
    int totalPassengers = 0;
    int monthPassengers[6] = {0};
    int matches = 0;
// loop throught the whole thing using length and comparing to the sent data
    for (int i = 0; i < length; i++) {
// match is used as a true false statement
        int match = 0;
// switch case to check what searchtype is being done, then compares to see if there is anthing that
// matches the search type and keys
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
// if  there is a match it adds 1 to the number of mathces and prints out the route
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
    // assigning total passengers to the whatever is in the records and index of each
    totalPassengers += r->passengers[0] + r->passengers[1] + r->passengers[2] +
                       r->passengers[3] + r->passengers[4] + r->passengers[5];
// if matches is greater then 0, meaning some where found, then it outputs that data
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