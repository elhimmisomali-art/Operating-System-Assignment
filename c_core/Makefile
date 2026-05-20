
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pthread -Iinclude

TARGET = eduos

SRCS = \
process_manager.c \
thread_manager.c \
race_demo.c \
producer_consumer.c \
deadlock_demo.c \
ipc_shared.c

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET) *.exe
