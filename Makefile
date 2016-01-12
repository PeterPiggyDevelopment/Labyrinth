GHC=ghc
CC=gcc
CFLAGS=-ggdb -ansi -pedantic -Wall -Werror
HFLAGS=

main: clean build_s build_c build_f

build_s: build_f
	$(GHC) $(HFLAGS) src/server/server.hs build/find_way.o build/serialization.o build/list_funcs.o -o build/server

build_f:
	$(CC) $(CFLAGS) -c src/server/find_way.c -o build/find_way.o
	$(CC) $(CFLAGS) -c src/server/serialization.c -o build/serialization.o
	$(CC) $(CFLAGS) -c src/server/list_funcs.c -o build/list_funcs.o

build_c:
	$(CC) $(CFLAGS) src/client/net_client.c src/client/eller_lab.c src/client/list_funcs.c -o build/client

clean: 
	rm -rf build/* src/server/server.hi src/server/server.o
