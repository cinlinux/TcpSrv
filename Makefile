

all: tcpSrv

tcpSrv: build/main.o
	gcc build/main.o -o tcpSrv

build:
	mldir build

build/main.o: main.c
	gcc -c -I /usr/include/linux main.c
