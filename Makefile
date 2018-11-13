CC			= gcc
TARGET		= game
SRCDIR 		= src
SRC			= $(wildcard $(SRCDIR)/*.c)
OBJDIR		= obj
OBJ			= $(wildcard $(OBJDIR)/*.o)
LIB 		= -lncurses

all: comp build

# compiles objects
comp: $(SRC)
	$(CC) -c $^ -Wall -o $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $^)

# builds game objects
build: $(OBJ)
	$(CC) $^ $(LIB) -o $(TARGET)



.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)