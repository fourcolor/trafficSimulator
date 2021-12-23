BINARY := trafficAgent
CC = g++                                  # change to gcc if using C
CFLAGS = -std=c++11 -Wall
LIBS =  -lglut -lGL -lGLU -lGLEW -lm

All: trafficAgent                             # change your_app.

trafficAgent: *.cpp 
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) 


rm:
	rm -f *.o