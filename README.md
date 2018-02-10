# sma-bluetooth
A C program to connect to sma inverters and export data.

Mailing list sma-bluetooth@googlegroups.com

Issues - use github issue tracker.

# Building on a pi (Jesse LITE)
> sudo apt-get install libbluetooth-dev
> sudo apt-get install libcurl4-openssl-dev
> sudo apt-get install default-libmysqlclient-dev
> sudo apt-get install libxml2-dev
> make

(needed to add -I/usr/include/libxml2 to gcc compile flags)

