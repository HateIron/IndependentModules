CXX = gcc
LD  = g++

CXXFLAGS = -g
#CXXFLAGS= -g -DMyMacro

LDFLAGS  = -o
OBJ_DIR  = ./libs
ModuleDir=./Debug

INCS     =-I./include
LIBS     = 
#LIBS    = -lwinsock32

vpath  %.c   ./source
vpath  %.cpp ./source

EXE_NAME = ut
###################################################
SRC  = $(notdir $(wildcard ./source/*.c))
SRCC = $(notdir $(wildcard ./source/*.cpp))

OBJS = $(SRC:%.c=$(ModuleDir)/%.o) $(SRCC:%.cpp=$(ModuleDir)/%.o) 
#OBJS= $(patsubst %.c,$(ModuleDir)/%.o, $(SRC)) \
#	   $(patsubst %.cpp,$(ModuleDir)/%.o, $(SRCC))

${EXE_NAME} : ${OBJS}
	ar rcso ${OBJ_DIR}/frame.a ${OBJS}
	rm ${ModuleDir} -rf

# compile windows dll
#${LD} ${CXXFLAGS} ${LDFLAGS} ${ModuleDir}/frame.dll ${OBJS} -W1, --output-def,${ModuleDir}/frame.def,--output-implib,${ModuleDir}/frame.a
#${LD} ${CXXFLAGS} ${LDFLAGS} frame.dll ${OBJS} -w1, --output-def, frame.def,--output-implib,frame.a
#gcc -g shared -o foo.dll foo.c print.c -w1,--output-def, print.def,--output-implib, foo.a
#${LD} ${LDFLAGS} $@ ${OBJS} ${LIBS}

depend_dir :
	mkdir -p ${ModuleDir}
	mkdir -p ${OBJ_DIR}

$(ModuleDir)/%.o : %.cpp | depend_dir
	${LD} -c ${CXXFLAGS} ${INCS} $< -o $@

$(ModuleDir)/%.o : %.c | depend_dir
	${CXX} ${CXXFLAGS} ${INCS} $< -o $@
	
.PHONY : clean
clean:
	@rm log result -rf
	@rm {EXE_NAME} -rf
	@rm ${ModuleDir} -rf
check:
	@./${EXE_NAME}
	












