# algo
Implement a list of algorithms in C++ smart pointer, and create a static library for using.
# testing
make

g++ test_auto.o algo.a -o tests

Please Note: Undirected is just two direction directed, and current implementation provide reset(directed and undirected) without add edge again.
But if directed path can be a circle A-B = 10 B-A = 12; the undirected will only take value from latter. e.g. AB=12.