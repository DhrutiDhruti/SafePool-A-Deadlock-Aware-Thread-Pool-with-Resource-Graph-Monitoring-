CC=gcc
CFLAGS=-Wall -pthread
OBJS=safepool.o thpool.o rag.o logger.o job_definitions.o

all: safepool

safepool: $(OBJS)
	$(CC) -o safepool $(OBJS) $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o safepool log.txt rag.dot
