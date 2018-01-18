usage:
1、build library:
	make
2、install library
	make install
3、update library libmodbus.so
	ldconfig
4、build test examples
	gcc master-example.c -o master-example -lmodbus
	gcc slave-example.c -o slave-example -lmodbus

	
