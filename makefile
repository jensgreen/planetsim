
all : planetsim

planetsim: planetsim.c GL_utilities.c VectorUtils3.c loadobj.c LoadTGA.c MicroGlut.c
	gcc -Wall -std=c99 -o planetsim -DGL_GLEXT_PROTOTYPES planetsim.c GL_utilities.c VectorUtils3.c loadobj.c LoadTGA.c MicroGlut.c  -lGL -lglut -lm

clean :
	rm planetsim
