# Example 13
EXE=gravity

# Main target
all: $(EXE)

#  OSX
CFLG=-O3 -Wall

# Compile rules
.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<

#  Clean
clean:
	$(CLEAN)
