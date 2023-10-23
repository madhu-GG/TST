BIN_DIR=~/bin
LIB_DIR=~/lib

SRC_DIR=$(PWD)
SRC=$(impl)
BINARY_NAME=TST
INC_FLAG=

BIN=$(BIN_DIR)/$(BINARY_NAME)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(INC_FLAG)

clean:
	rm -f $(BIN) $(SRC_DIR)/*.o

debug: CFLAGS+=-g
debug: $(BIN)
	
.PHONY:  clean debug
