GHC=ghc
CC=gcc
CFLAGS=-ggdb -ansi -pedantic -Wall -Werror
HFLAGS=

main: clean build_s build_c

build_s: 
	$(GHC) $(HFLAGS) src/server/server.hs -o build/server

build_c:
	$(CC) $(CFLAGS) src/client/net_client.c src/client/eller_lab.c src/client/list_funcs.c src/server/find_way.c src/server/serialization.c -o build/client

clean: 
	rm -rf build/* src/server/server.hi src/server/server.o
