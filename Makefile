CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c2x -Ofast
LIBS= 

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
LIBS += -lvector
else
LIBS += -l:libvector.so
endif


TARGET=ecc
CACHE=.cache
OUTPUT=$(CACHE)/release

MODULES += main.o
MODULES += lexer.o
MODULES += parser.o
MODULES += debug.o

OBJ=$(addprefix $(CACHE)/,$(MODULES))


all: env $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(OUTPUT)/$(TARGET)


%.o:
	$(CC) $(CFLAGS) -c $< -o $@


-include dep.list


exec: all
	$(OUTPUT)/$(TARGET)


.PHONY: env dep clean


dep:
	$(CC)  -MM  app/*.c src/*.c | sed 's|[a-zA-Z0-9_-]*\.o|$(CACHE)/&|' > dep.list


env:
	mkdir -pv $(CACHE)
	mkdir -pv $(OUTPUT)


clean: 
	rm -rvf $(OUTPUT)
	rm -vf $(CACHE)/*.o



