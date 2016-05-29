.SUFFIXES : .c .o 

KERNEL = ./kernel
COMPILE = ./compiles

SRCS = main.c \
	$(KERNEL)/fork.c \

OBJECTS = $(SRCS:.c=.o)

TARGET = run
CC = gcc
CFLAGS = -O2 -g

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

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