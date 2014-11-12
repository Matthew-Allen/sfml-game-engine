default:
	make build
build:

	g++ -c main.cpp
	g++ -c mathvector.cpp
	g++ -o sfml-app main.o mathvector.o -lsfml-graphics -lsfml-window -lsfml-system

#	g++ -v main.cpp mathvector.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
#	g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
test:
	make build
	make run
run:
	./sfml-app
clean:
	rm ./sfml-app
	rm ./*.o