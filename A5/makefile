
turtix: main.o game.o Enemy.o movable_back.o BabyTurtle.o BonusObject.o player.o
	g++ main.o game.o Enemy.o movable_back.o BabyTurtle.o BonusObject.o player.o -lsfml-graphics -lsfml-window -lsfml-system -o turtix
main.o: main.cpp
	g++ -c main.cpp
game.o: game.cpp game.hpp 
	g++ -c game.cpp
Enemy.o: Enemy.cpp Enemy.hpp
	g++ -c Enemy.cpp
movable_back.o: movable_back.cpp movable_back.hpp
	g++ -c movable_back.cpp
BabyTurtle.o: BabyTurtle.cpp BabyTurtle.hpp
	g++ -c BabyTurtle.cpp
BonusObject.o: BonusObject.cpp BonusObject.hpp
	g++ -c BonusObject.cpp
player.o: player.cpp player.hpp
	g++ -c player.cpp
clean:
	rm *.o turtix
