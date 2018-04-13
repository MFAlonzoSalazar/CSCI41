a.out: main.cc splash.h
	g++ -std=c++11 main.cc -lncurses
clean: 
	rm a.out
