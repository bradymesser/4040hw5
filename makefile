PROJECT = warper
FILTER = Filter
IMAGE = Image
RGBTOHSV = rgbToHsv
GLOBALS = Globals

default:
	g++ -c -g *.cpp
	g++ -g -o ${PROJECT} ${PROJECT}.o ${FILTER}.o ${IMAGE}.o ${RGBTOHSV}.o ${GLOBALS}.o -L /usr/lib64/ -lglut -lGL -lGLU -lOpenImageIO -lm
clean:
	rm -f core.* *.o *~ ${PROJECT}

run:
	-make clean
	-make default
	./convolve filters/cross.filt images/checkers.png

square:
	-make clean
	-make default
	./convolve filters/pulse.filt images/square.png
