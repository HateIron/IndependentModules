CC	= gcc
#CFLAGS	= -Wall -O3
#CFLAGS	= -Wall -O3 -fPIC
CFLAGS	= -Wall -O3 -fpic

all: libmodbus

libmodbus: commun.o  mbs.o mbm.o
	$(CC) $(CFLAGS) -o libmodbus.so commun.o mbs.o  mbm.o -lpthread  -shared -I.


commun.o: commun.c modbus.h
	$(CC) $(CFLAGS) -c commun.c -I.


mbs.o: mbs.c modbus.h 
	$(CC) $(CFLAGS) -c  mbs.c -I.

mbm.o: mbm.c modbus.h 
	$(CC) $(CFLAGS) -c  mbm.c -I.

clean:
	rm -f  ~* *~ *.ASV *.bak *.o core> /dev/null

install:
	chown root.root libmodbus.so
	cp libmodbus.so /usr/lib/
	cp modbus.h /usr/include
	mkdir -p /usr/doc
	mkdir /usr/doc/libmodbus
	cp README /usr/doc/libmodbus
	cp AUTHORS /usr/doc/libmodbus
	cp COPYING /usr/doc/libmodbus
uninstall:
	rm /usr/lib/libmodbus.so
	rm /usr/include/modbus.h
	rm /usr/doc/libmodbus -rf
