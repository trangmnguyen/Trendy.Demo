OBJ = solver.o prog8.o
OPTS = -g -c -Wall -Werror

wordlist: $(OBJ)
	g++ -o wordlist $(OBJ)

prog8.o: solver.h prog8.cc
	g++ $(OPTS) prog8.cc

solver.o: solver.cc solver.h
	g++ $(OPTS) solver.cc

clean:
	rm -f *.o *~ wordlist