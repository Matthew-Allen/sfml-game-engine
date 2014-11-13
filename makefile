cledefault:
	make build
build:

	g++ -c main.cpp
	g++ -c mathvector.cpp
	g++ -c collision.cpp
	g++ -o sfml-app main.o mathvector.o collision.o -lsfml-graphics -lsfml-window -lsfml-system

	make clean

#	g++ -v main.cpp mathvector.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
#	g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
test:
	make build
	make run
run:
	./sfml-app
fullclean:
	rm ./sfml-app
	make clean

clean:
	rm ./main.o
	rm ./mathvector.o
	rm ./collision.o