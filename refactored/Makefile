test: sb_context.o sb_connection.o bt_addr.o main.o sb_message.o sb_message_ping.o sb_message_request.o message_bytes.o sb_l2_packet.o
	g++ -g sb_context.o sb_connection.o bt_addr.o main.o sb_message.o sb_message_ping.o sb_message_request.o message_bytes.o sb_l2_packet.o -Wall -lbluetooth -o test
sb_connection.o: sb_connection.cpp sb_connection.h bt_addr.h
	g++  $(INC) -g -c sb_connection.cpp
sb_context.o: sb_context.cpp sb_context.h bt_addr.h
	g++  $(INC) -g -c sb_context.cpp
sb_message.o: sb_message.cpp sb_message.h bt_addr.h
	g++  $(INC) -g -c sb_message.cpp
sb_message_ping.o: sb_message_ping.cpp sb_message_ping.h bt_addr.h
	g++  $(INC) -g -c sb_message_ping.cpp
sb_message_request.o: sb_message_request.cpp sb_message_request.h bt_addr.h
	g++  $(INC) -g -c sb_message_request.cpp
bt_addr.o: bt_addr.cpp bt_addr.h
	g++  $(INC) -g -c bt_addr.cpp
sb_l2_packet.o: sb_l2_packet.cpp sb_l2_packet.h
	g++  $(INC) -g -c sb_l2_packet.cpp
message_bytes.o: message_bytes.cpp message_bytes.h
	g++  $(INC) -g -c message_bytes.cpp
main.o: main.cpp bt_addr.h sb_connection.h
	g++  $(INC) -g -c main.cpp

clean: 
	rm *.o
	rm test
