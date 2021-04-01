main: main.o selectionSort.o insertionSort.o mergeSort.o quickSort.o utility.o
	g++ main.o selectionSort.o insertionSort.o mergeSort.o quickSort.o utility.o -o main

main.o: main.cpp sort.h utility.h
	g++ -c main.cpp

selectionSort.o: selectionSort.cpp utility.h
	g++ -c selectionSort.cpp

insertionSort.o: insertionSort.cpp 
	g++ -c insertionSort.cpp 

mergeSort.o: mergeSort.cpp 
	g++ -c mergeSort.cpp 

quickSort.o: quickSort.cpp utility.h
	g++ -c quickSort.cpp

utility.o: utility.cpp
	g++ -c utility.cpp

clean:
	rm *.o main
	