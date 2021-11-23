all:
	g++ -c main.cpp -std=c++17 -Wall -Werror -Wextra -O2 -o main.o
	g++ -c Matrix.cpp -std=c++17 -Wall -Werror -Wextra -O2 -o Matrix.o
	g++ -c Vector.cpp -std=c++17 -Wall -Werror -Wextra -O2 -o Vector.o
	g++ main.o Matrix.o Vector.o -o exefile
	rm *.o
	./exefile

