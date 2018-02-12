test: sb_context.o sb_connection.o bt_addr.o main.o
	g++ sb_context.o sb_connection.o bt_addr.o main.o -O2 -Wall -lbluetooth -o test
sb_context.o: sb_context.cpp sb_context.h
	g++ -O2 $(INC) -c sb_context.cpp
sb_connection.o: sb_connection.cpp sb_connection.h
	g++ -O2 $(INC) -c sb_connection.cpp
bt_addr.o: bt_addr.cpp bt_addr.h
	g++ -O2 $(INC) -c bt_addr.cpp
main.o: main.cpp 
	g++ -O2 $(INC) -c main.cpp
