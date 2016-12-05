.PHONY: clean

CC=g++
CPPFLAGS=-Wall -g
BIN=main
OBJS=main.o add.o sub.o

$(BIN): $(OBJS)
	$(CC) $(CPPFLAGS) $^ -o $@
	rm -f $(OBJS)
%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $^ -o $@

clean:
	rm -f *.o $(BIN)
