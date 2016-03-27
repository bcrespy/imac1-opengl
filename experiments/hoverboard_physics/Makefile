CC       =  gcc
CFLAGS   = -Wall -O2 -g
LIB      = -lSDL -lGLU -lGL -lm
INCLUDES =

OBJ      = simple-moves.o
RM       = rm -f
BIN      = simple-moves
DIRNAME  = $(shell basename $$PWD)
BACKUP   = $(shell date +`basename $$PWD`-%m.%d.%H.%M.tgz)
STDNAME  = $(DIRNAME).tgz

all : $(BIN)

$(BIN) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) $(INCLUDES)  -o $(BIN)
	@echo "--------------------------------------------------------------"
	@echo "                 to execute type: ./$(BIN) &"
	@echo "--------------------------------------------------------------"

simple-moves.o : simple-moves.c
	@echo "compile simple-moves"
	$(CC) $(CFLAGS) -c $<
	@echo "done..."

clean :
	@echo "**************************"
	@echo "CLEAN"
	@echo "**************************"
	$(RM) *~ $(OBJ) $(BIN)

tar : clean
	@echo "**************************"
	@echo "TAR"
	@echo "**************************"
	cd .. && tar cvfz $(BACKUP) $(DIRNAME)
