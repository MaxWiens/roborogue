CC			= gcc
TARGET		= game
SRCDIR 		= src

dungeon		= $(wildcard $(SRCDIR)/dungeon/*.c)
math		= $(wildcard $(SRCDIR)/math/*.c)
object		= $(wildcard $(SRCDIR)/object/*.c) $(character) $(entity)
	character	= $(wildcard $(SRCDIR)/object/character/*.c)
	entity		= $(wildcard $(SRCDIR)/object/entity/*.c) $(component)
		component	= $(wildcard $(SRCDIR)/object/entity/component/*.c)
util		= $(wildcard $(SRCDIR)/util/*.c)
collections = $(wildcard $(SRCDIR)/collections/*.c)

SRC			= $(wildcard $(SRCDIR)/*.c) $(dungeon) $(math) $(object) $(util) $(collections)

OBJ			= $(SRC:.c=.o)
LIB 		= -lncurses

# builds game
build: clean $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIB)

.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)