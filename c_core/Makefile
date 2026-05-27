CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pthread

all:
	$(CC) $(CFLAGS) -o process_manager \
	process_manager.c ipc_shared.c

clean:
	rm -f process_manager