all: compile run
	Objects :=  ./user.o ./item.o ./data.o ./driver.o

compile:
	g++ -o ./user.o -c ./user.cpp
	g++ -o ./item.o -c ./item.cpp
	g++ -o ./data.o -c ./data.cpp
	g++ -o ./driver.o -c ./driver.cpp
	g++ -o ./main.o -c ./main.cpp
	g++ -o Auction_app ./user.o ./item.o ./data.o ./driver.o ./main.o
	
run:
	./Auction_app resources/users.txt resources/items.txt resources/daily_transaction.txt