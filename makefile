CC = g++

main: main.o
	$(CC) main.o -o main -std=c++11

main.o: main.cpp
	$(CC) -c main.cpp -std=c++11


clean:
	@rm -f *.o
	@rm main
