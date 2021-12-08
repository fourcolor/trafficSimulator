INCLUDE = -I/usr/X11R6/include/
LIBDIR  = -L/usr/X11R6/lib
BINARY := trafficAgent
FLAGS = -Wall
CC = g++                                  # change to gcc if using C
CFLAGS = $(FLAGS) $(INCLUDE)
LIBS =  -lglut -lGL -lGLU -lGLEW -lm

All: trafficAgent                             # change your_app.

trafficAgent: trafficAgent.o
	$(CC) $(CFLAGS) -o $@ $(LIBDIR) $< $(LIBS) 

rm:
	rm -f *.o $(BINARY)