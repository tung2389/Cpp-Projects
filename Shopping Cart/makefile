main: main.o ItemToPurchase.o ShoppingCart.o Manager.o
	g++ main.o ItemToPurchase.o ShoppingCart.o Manager.o -o main

main.o: main.cpp Manager.h ShoppingCart.h ItemToPurchase.h 
	g++ -c main.cpp

Manager.o: Manager.cpp Manager.h ItemToPurchase.h 
	g++ -c Manager.cpp

ShoppingCart.o: ShoppingCart.cpp ShoppingCart.h ItemToPurchase.h 
	g++ -c ShoppingCart.cpp

ItemToPurchase.o: ItemToPurchase.cpp ItemToPurchase.h 
	g++ -c ItemToPurchase.cpp

clean:
	rm *.o main
	