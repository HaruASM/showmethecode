.SUFFIXES : .c .o 

KERNEL = ./kernel
COMPILE = ./compiles
LIB = ./lib

SRCS = main.c 

DIRS = $(wildcard $(KERNEL)/*.c) \
		$(wildcard $(LIB)/*.c)

OBJECTS = $(SRCS:.c=.o) \
			$(DIRS:.c=.o)

TARGET = run
CC = gcc

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^  -lpthread

clean:
	-rm -f $(OBJECTS) $(TARGET)
#	-rm -f $(COMPILE)/*.o

dep:
	$(CC) -M $(SRCS)

#$(OBJECTS) : ./lib/users.h

#main.o : main.c

#$(KERNEL)/fork.o : $(KERNEL)/fork.c

#$(COMPILES)/main.o : ./main.c
#	gcc -c -o $(COMPILES)/main.o main.c

#$(COMPILES)/fork.o : ./kernel/fork.c ./lib/users.h
#	gcc -c -o $(COMPILES)/fork.o ./kernel/fork.c