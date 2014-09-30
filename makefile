default:
	make build
build:
	g++ -c main.cpp
	g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
test:
	make build
	make run
run:
	./sfml-app
clean:
	rm main.o
	rm sfml-app