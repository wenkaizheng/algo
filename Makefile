VER = -std=c++11
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:cpp=o)
algo.a:	$(OBJS)
	ar -c -r -s algo.a *.o

%.o: %.cpp graph_algo.hpp
	g++ -c $< $(VER)

.PHONY: clean
clean:
	rm -f *.o
	rm -f algo.a
