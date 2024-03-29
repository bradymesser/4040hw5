DIR = src/
PROJECT = warper
FILTER = Filter
IMAGE = Image
RGBTOHSV = rgbToHsv
GLOBALS = Globals
OBJECTS = ${PROJECT}.o matrix.o ${FILTER}.o ${IMAGE}.o ${RGBTOHSV}.o

default:
	g++ -Wall -c -g ${DIR}*.cpp
	g++ -Wall -g -o ${PROJECT} ${OBJECTS} -L /usr/lib64/ -lglut -lGL -lGLU -lOpenImageIO -lm

clean:
	rm -f core.* *.o *~ ${PROJECT} .nfs*

run:
	-make clean
	-make default
	-./${PROJECT} images/waves.png

r:
	-make clean
	-make default
	./${PROJECT} images/durer_rhino.png
