all:
	g++ main.cpp -std=c++14 -pthread -lnana -lX11 -lpthread -lrt -lXft -lpng -lfontconfig -lstdc++fs
	./a.out
	
win:
	x86_64-w64-mingw32-g++ main.cpp -std=c++14 -pthread -lnana -lX11 -lpthread -lrt -lXft -lpng -lfontconfig -lstdc++fs
