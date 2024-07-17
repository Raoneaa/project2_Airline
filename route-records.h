//
// Created by Julian Solis on 7/11/24.
//

#ifndef ROUTE_RECORDS_H
#define ROUTE_RECORDS_H
// defining struct and enums
typedef struct {
    char origin[4];
    char destination[4];
    char airline[4];
    int passengers[6];
}RouteRecord;

typedef enum  {
    ROUTE,
    ORIGIN,
    DESTINATION,
    AIRLINE
} SearchType;
// defining the functions
RouteRecord* createRecords( FILE* );
int fillRecords( RouteRecord* r, FILE* fileIn );
int findAirlineRoute( RouteRecord*, int, const char*, const char*, const char*,int);
void searchRecords( RouteRecord* r, int length, const char* key1, const char* key2, SearchType st );
void printMenu();

#endif //ROUTE_RECORDS_H
