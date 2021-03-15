main: NumberToText.o
	g++ NumberToText.o -o main

NumberToText.o: NumberToText.cpp NumberToText.h English.h Vietnamese.h
	g++ -c NumberToText.cpp
	
clean:
	rm *.o