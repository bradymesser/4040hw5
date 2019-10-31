PROJECT = warper
FILTER = Filter
IMAGE = Image
RGBTOHSV = rgbToHsv
GLOBALS = Globals
OBJECTS = ${PROJECT}.o matrix.o ${FILTER}.o ${IMAGE}.o ${RGBTOHSV}.o ${GLOBALS}.o

default:
	g++ -c -g *.cpp
	g++ -g -o ${PROJECT} ${OBJECTS} -L /usr/lib64/ -lglut -lGL -lGLU -lOpenImageIO -lm
	
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


# CC      = g++
# C       = cpp
#
# CFLAGS  = -g
#
# ifeq ("$(shell uname)", "Darwin")
#   LDFLAGS     = -framework Foundation -framework GLUT -framework OpenGL -lOpenImageIO -lm
# else
#   ifeq ("$(shell uname)", "Linux")
#     LDFLAGS   = -L /usr/lib64/ -lglut -lGL -lGLU -lOpenImageIO -lm
#   endif
# endif
#
# PROJECT		= warper
#
# OBJECTS = ${PROJECT}.o matrix.o
#
# ${PROJECT}:	${PROJECT}.o matrix.o
# 	${CC} ${CFLAGS} ${LFLAGS} -o ${PROJECT} ${OBJECTS} ${LDFLAGS}
#
# %.o: %.cpp
# 	${CC} -c ${CFLAGS} *.${C}
#
# clean:
# 	rm -f core.* *.o *~ ${PROJECT}
