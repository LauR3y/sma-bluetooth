
CXXFLAGS=-I /usr/include/libxml2 -fstack-protector-all -O2 -Wall -Werror --std=c++11

smatool: smatool.o repost.o sma_mysql.o almanac.o sb_commands.o sma_struct.hh
	gcc $(CXXFLAGS) smatool.o repost.o sma_mysql.o almanac.o sb_commands.o -lxml2 -L/usr/lib/x86_64-linux-gnu -lmariadb -lbluetooth -lcurl -lm -o smatool 
smatool.o: smatool.cc sma_mysql.hh
	gcc -O2 $(CXXFLAGS) -c smatool.cc
repost.o: repost.cc sma_mysql.hh
	gcc -O2 $(CXXFLAGS) -c repost.cc
sma_mysql.o: sma_mysql.cc
	gcc -O2 $(CXXFLAGS) -c sma_mysql.cc
almanac.o: almanac.cc
	gcc -O2 $(CXXFLAGS) -c almanac.cc
sma_pvoutput.o: sma_pvoutput.cc
	gcc -O2 $(CXXFLAGS) -c sma_pvoutput.cc
sb_commands.o: sb_commands.cc
	gcc -O2 $(CXXFLAGS) -c sb_commands.cc
clean:
	rm *.o
install:
	install -m 755 smatool /usr/local/bin
	install -m 644 sma.in.new /usr/local/bin
	install -m 644 smatool.conf.new /usr/local/etc
	install -m 644 smatool.xml /usr/local/bin

