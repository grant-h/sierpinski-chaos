.PHONY: all clean

EXE=chaos
OBJECTS=main.o

all: $(OBJECTS) $(EXE)

%.o : %.cpp
	g++ -c $< -o $@

$(EXE) : $(OBJECTS)
	g++ -o $(EXE) $(OBJECTS) -lSDL2

run: $(EXE)
	-./$(EXE)

clean:
	rm -f $(OBJECTS) 
	rm -f $(EXE)

