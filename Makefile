all:
	g++ src/main.cpp -I inc/ -lstdc++ -g -Wall -Werror

clean:
	rm -rf a.out