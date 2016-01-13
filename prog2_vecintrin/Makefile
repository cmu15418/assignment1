all: myexp

logger.o: logger.cpp logger.h CMU418intrin.h CMU418intrin.cpp
	g++ -c logger.cpp

CMU418intrin.o: CMU418intrin.cpp CMU418intrin.h logger.cpp logger.h
	g++ -c CMU418intrin.cpp

myexp: CMU418intrin.o logger.o main.cpp
	g++ -I../common logger.o CMU418intrin.o main.cpp -o myexp

clean:
	rm -f *.o myexp
