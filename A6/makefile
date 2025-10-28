
main: main.o Driver.o Mission.o Processing.o TaxiCompany.o 
	g++ -std=c++11 main.o Driver.o Mission.o Processing.o TaxiCompany.o -o main

main.o: main.cpp
	g++ -std=c++11 -c main.cpp
	
Taxicompany.o: TaxiCompany.cpp TaxiCompany.h
	g++ -std=c++11 -c TaxiCompany.cpp
	
Mission.o: Mission.cpp Mission.h
	g++ -std=c++11 -c Mission.cpp

Processing.o: Processing.cpp Processing.h
	g++ -std=c++11 -c Processing.cpp

Driver.o: Driver.cpp Driver.h
	g++ -std=c++11 -c Driver.cpp



clean:
	rm *.o
