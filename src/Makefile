CC=gcc
OPTS=-g -std=c99 -Werror

all: main.o predictor.o predictorTest.o
	$(CC) $(OPTS) -lm -o predictor main.o predictor.o predictorTest.o

main.o: main.c predictor.h
	$(CC) $(OPTS) -c main.c

predictorTest.o: predictor.h
	$(CC) $(OPTS) -c predictorTest.c

predictor.o: predictor.h predictor.c
	$(CC) $(OPTS) -c predictor.c


clean:
	rm -f *.o predictor;
