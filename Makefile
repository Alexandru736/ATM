CC = gcc
CFLAGS = -g -Wall
HEADERS = 
OBJECTS = ATM.o ATMfunctii.o
EXEC = atm

.PHONY = default build clean

build: atm

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

run: build
	./$(EXEC)

clean:
	-rm -f $(OBJECTS)
	-rm -f $(EXEC)
