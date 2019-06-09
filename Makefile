ARCH := $(shell getconf LONG_BIT)
C_FLAGS_64 := -L/usr/lib64/mysql -I/usr/include/libxml2
C_FLAGS_32 := -L/usr/lib/mysql
CXXFLAGS=-I /usr/include/libxml2 -D_GNU_SOURCE -fstack-protector-all -O2 -Wall $(C_FLAGS_$(ARCH)) -Werror --std=c++11 -L /usr/lib/x86_64-linux-gnu


smatool: smatool.o repost.o sma_mysql.o almanac.o sb_commands.o sma_struct.h
	gcc $(CXXFLAGS) smatool.o repost.o sma_mysql.o almanac.o sb_commands.o -lxml2 -lmariadb -lbluetooth -lcurl -lm -o smatool 
smatool.o: smatool.c sma_mysql.h
	gcc $(CXXFLAGS) -c smatool.c
repost.o: repost.c sma_mysql.h
	gcc $(CXXFLAGS) -c repost.c
sma_mysql.o: sma_mysql.c
	gcc $(CXXFLAGS) -c sma_mysql.c
almanac.o: almanac.c
	gcc $(CXXFLAGS) -c almanac.c
sma_pvoutput.o: sma_pvoutput.c
	gcc $(CXXFLAGS) -c sma_pvoutput.c
sb_commands.o: sb_commands.c
	gcc $(CXXFLAGS) -c sb_commands.c
clean:
	rm *.o
install:
	install -m 755 smatool /usr/local/bin
	install -m 644 sma.in.new /usr/local/bin
	install -m 644 smatool.conf.new /usr/local/etc
	install -m 644 smatool.xml /usr/local/bin

