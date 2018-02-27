CUR_PATH := $(shell pwd)
CPPFLAG := -DCURPATH=\"$(CUR_PATH)\"

all:
	g++ -I/usr/include/python2.7/ gito.cpp -o gito -L/usr/lib/python2.7/ -lpython2.7 $(CPPFLAG)
#	g++ -g -Wall -c  gito.cpp -I/usr/include/python2.7/

clean:
	@rm -rf *.o *.pyc gito
