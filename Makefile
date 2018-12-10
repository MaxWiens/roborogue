CC			= gcc
TARGET		= game
SRCDIR 		= src

SRC			= $(wildcard $(SRCDIR)/*.c) $(collections) $(dungeon) $(object) $(util) $(gui)
  gui 		= $(wildcard $(SRCDIR)/gui/*.c)
	collections = $(wildcard $(SRCDIR)/collections/*.c)
	dungeon		= $(wildcard $(SRCDIR)/dungeon/*.c)
	object		= $(wildcard $(SRCDIR)/object/*.c) $(character) $(entity) $(tile)
		character	= $(wildcard $(SRCDIR)/object/character/*.c)
		entity		= $(wildcard $(SRCDIR)/object/entity/*.c) $(component) $(item)
			component	= $(wildcard $(SRCDIR)/object/entity/component/*.c)
			item		= $(wildcard $(SRCDIR)/object/entity/item/*.c)
		tile		= $(wildcard $(SRCDIR)/object/tile/*.c)
	util		= $(wildcard $(SRCDIR)/util/*.c)


OBJ			= $(SRC:.c=.o)
LIB 		= -lncurses

# builds game
build: clean $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIB)

.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)
