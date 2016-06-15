
SRC = src
INC = include
OBJ = obj
BIN = bin
LIB = lib

CXX = g++
CPPFLAGS = -Wall -g -c -std=c++11 -I$(INC)



all: $(BIN)/arteASCII2 $(BIN)/testimagen $(BIN)/suma


# *************** SUMA IMAGENES
$(BIN)/suma :  $(OBJ)/suma.o $(LIB)/libimagen.a
	$(CXX) -o $@ $^

$(OBJ)/suma.o : $(SRC)/suma.cpp $(INC)/imagen.h 
	$(CXX) $(CPPFLAGS) $< -o $@

# *************** arte ascii v2
$(BIN)/arteASCII2 :  $(OBJ)/arteASCII2.o $(LIB)/libimagen.a
	$(CXX) -o $@ $^

$(OBJ)/arteASCII2.o : $(SRC)/arteASCII2.cpp $(INC)/imagen.h $(INC)/lista.h 
	$(CXX) $(CPPFLAGS) $< -o $@

# *************** arte ascii
$(BIN)/arteASCII :  $(OBJ)/arteASCII.o $(LIB)/libimagen.a
	$(CXX) -o $@ $^

$(OBJ)/arteASCII.o : $(SRC)/arteASCII.cpp $(INC)/imagen.h
	$(CXX) $(CPPFLAGS) $< -o $@

# *************** test arte ascii
$(BIN)/testarteASCII : $(OBJ)/testarteASCII.o $(LIB)/libimagen.a
	$(CXX) -o $@ $^

$(OBJ)/testarteASCII.o : $(SRC)/testarteASCII.cpp $(INC)/imagen.h
	$(CXX) $(CPPFLAGS) $< -o $@

# *************** test plano
$(BIN)/testplano : $(OBJ)/testplano.o $(LIB)/libimagen.a
	$(CXX) -o $@ $^

$(OBJ)/testplano.o : $(SRC)/testplano.cpp $(INC)/imagen.h
	$(CXX) $(CPPFLAGS) $< -o $@

# *************** test imagen
$(BIN)/testimagen : $(OBJ)/testimagen.o $(LIB)/libimagen.a
	$(CXX) -o $@ $^

$(OBJ)/testimagen.o : $(SRC)/testimagen.cpp $(INC)/imagen.h
	$(CXX) $(CPPFLAGS) $< -o $@

# ***************** Biblioteca ********

$(LIB)/libimagen.a: $(OBJ)/imagen.o $(OBJ)/pgm.o $(OBJ)/byte.o $(OBJ)/lista.o
	ar -rvs $@ $^

$(OBJ)/byte.o : $(SRC)/byte.cpp $(INC)/byte.h
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/imagen.o : $(SRC)/imagen.cpp $(INC)/imagen.h $(INC)/pgm.h $(INC)/byte.h $(INC)/lista.h
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/pgm.o : $(SRC)/pgm.cpp $(INC)/pgm.h
	$(CXX) $(CPPFLAGS) $< -o $@

$(OBJ)/lista.o : $(SRC)/lista.cpp $(INC)/lista.h
	$(CXX) $(CPPFLAGS) $< -o $@


# ***********Miscelanea ***********


# ************ documentación *******

documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Limpieza ************

clean :
	@ echo "Limpiando..."
	rm -f $(OBJ)/*.o $(BIN)/* $(LIB)/*.a *.pgm *[0-9].txt

