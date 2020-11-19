FLAGS = -pedantic-errors -std=c++11

pc_debating.o : pc_debating.cpp 
	g++ $(FLAGS) -c $<

player_debating.o : player_debating.cpp 
	g++ $(FLAGS) -c $<

process.o : process.cpp game.h
	g++ $(FLAGS) -c $<

game: process.o pc_debating.o player_debating.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f game *.o

tar:
	tar -czvf *.cpp *.h

.PHONY: clean tar  
