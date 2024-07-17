Airline: main.o route-records.o
	gcc  main.o route-records.o -o Airline
main.o: main.c route-records.h
	gcc -c main.c
route-records.o: route-records.c route-records.h
	gcc -c route-records.c -o route-records.o
clean:
	rm *.o
	rm Airline
