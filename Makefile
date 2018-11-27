CC			= gcc
TARGET		= game
SRCDIR 		= src

math		= $(wildcard $(SRCDIR)/math/*.c)
util		= $(wildcard $(SRCDIR)/util/*.c)

dungeon		= $(wildcard $(SRCDIR)/dungeon/*.c)

entity		= $(wildcard $(SRCDIR)/object/entity/*.c)
object		= $(wildcard $(SRCDIR)/object/*.c) $(entity)

SRC			= $(wildcard $(SRCDIR)/*.c) $(math) $(util) $(dungeon) $(object)

OBJ			= $(SRC:.c=.o)
LIB 		= -lncurses

# builds game objects
build: clean $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIB)

.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)