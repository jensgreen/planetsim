
all : planetsim

planetsim: planetsim.c GL_utilities.c VectorUtils3.c loadobj.c LoadTGA.c MicroGlut-linux.c
	gcc -Wall -std=c99 -o planetsim -DGL_GLEXT_PROTOTYPES planetsim.c GL_utilities.c VectorUtils3.c loadobj.c LoadTGA.c MicroGlut-linux.c  -lGL -lglut -lm

clean :
	rm planetsim
