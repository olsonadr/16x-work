CC=g++
LIB_NAME=panels
LIB_DIR=cpp_panels
LIB_MAKE_DIR=$(LIB_DIR)
LIB_OUT_SRC=$(LIB_DIR)/bin
LIB_HPP_SRC=$(LIB_DIR)/include
LIB_OUT_DEST=.
LIB_HPP_DEST=include

all: $(LIB_HPP_DEST) $(LIB_OUT_DEST)
	make -C$(LIB_MAKE_DIR) shared
	cp $(LIB_OUT_SRC)/lib$(LIB_NAME).so $(LIB_OUT_DEST)
	cp $(LIB_HPP_SRC)/* $(LIB_HPP_DEST)
	make -C$(LIB_MAKE_DIR) clean

$(LIB_OUT_DEST):
	mkdir $(LIB_OUT_DEST)

$(LIB_HPP_DEST):
	mkdir $(LIB_HPP_DEST)

clean:
	rm -r -f $(LIB_HPP_DEST) lib$(LIB_NAME).so
