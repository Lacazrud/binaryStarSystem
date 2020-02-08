CFLAGS = -O3 
#CFLAGS = -g -O0

RogueSim: RogueSim.o
	c++ $(CFLAGS) -o RogueSim RogueSim.o -lpgplot -lcpgplot -lX11  -lm  -ltrapfpe 

RogueSim.o: RogueSim.cpp
	c++ $(CFLAGS) -c RogueSim.cpp

