test: sb_context.o sb_connection.o bt_addr.o main.o
	g++ -g sb_context.o sb_connection.o bt_addr.o main.o -Wall -lbluetooth -o test
sb_context.o: sb_context.cpp sb_context.h
	g++  $(INC) -g -c sb_context.cpp
sb_connection.o: sb_connection.cpp sb_connection.h bt_addr.h
	g++  $(INC) -g -c sb_connection.cpp
bt_addr.o: bt_addr.cpp bt_addr.h
	g++  $(INC) -g -c bt_addr.cpp
main.o: main.cpp bt_addr.h sb_connection.h
	g++  $(INC) -g -c main.cpp

clean: 
	rm *.o
	rm test
