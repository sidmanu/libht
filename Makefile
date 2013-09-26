###########################################################
# This code is written by Siddharth Manu
###########################################################


targets: libht.so
OBJS := ht.o

CCFLAGS = -g  -Wall

libht.so: ht.lo
	gcc -shared -Wl,-soname,libht.so -o libht.so $(OBJS)
	cp libht.so /usr/lib/libht.so
	ldconfig

ht.lo: ht.h 
	gcc -fPIC -c ht.c 

clean:
	rm -rf *.lo *.so  *.out  test

####################TESTAPP###############################h

test: test.o
	gcc -lht -I. -fPIC -o test test.c
	
