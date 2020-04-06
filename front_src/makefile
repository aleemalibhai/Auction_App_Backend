all: compile run
	Objects :=  ./lib/user.o ./lib/item.o ./lib/data.o ./lib/driver.o

compile:
	g++ -o ./lib/user.o -c ./user.cpp
	g++ -o ./lib/item.o -c ./item.cpp
	g++ -o ./lib/data.o -c ./data.cpp
	g++ -o ./lib/driver.o -c ./driver.cpp
	g++ -o ./lib/main.o -c ./main.cpp
	g++ -o Auction_app ./lib/user.o ./lib/item.o ./lib/data.o ./lib/driver.o ./lib/main.o
	
run:
	./Auction_app resources/users.txt resources/items.txt resources/daily_transaction.txt