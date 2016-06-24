#.SUFFIXES : .c .o 

#KERNEL = ./kernel
#COMPILE = ./compiles
#LIB = ./lib

#SRCS = main.c 

DIRS = $(wildcard ./*.c)

OBJECTS = $(DIRS:.c=.o)

SERVER = server
CLIENT = client
SRC = ala
CC = gcc

all: $(SERVER) $(CLIENT) 

run: $(SRC)
	./$(SRC)

$(SRC) : run.o
	gcc -o $@ $^ -lpthread

$(SERVER) : server.o
	gcc -o $@ $^ -lpthread
	
$(CLIENT) : client.o
	gcc -o $@ $^ -lpthread

$(OBJECTS) : $(DIRS)
	gcc -c $^

clean:
	-rm -f $(OBJECTS) $(SERVER) $(CLIENT) $(SRC)


#dep:
#	$(CC) -M $(SRCS)

#$(OBJECTS) : ./lib/users.h

#main.o : main.c

#$(KERNEL)/fork.o : $(KERNEL)/fork.c

#$(COMPILES)/main.o : ./main.c
#	gcc -c -o $(COMPILES)/main.o main.c

#$(COMPILES)/fork.o : ./kernel/fork.c ./lib/users.h
#	gcc -c -o $(COMPILES)/fork.o ./kernel/fork.c