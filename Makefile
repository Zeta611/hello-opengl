CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -pedantic-errors
OBJS = main.o
LDLIBS = -lglfw -lGLEW

.PHONY : all clean distclean

all : run

run : $(OBJS)
	$(CXX) -o run $(OBJS) $(LDLIBS)

main.o : main.cpp

clean :
	$(RM) $(OBJS)

distclean : clean
	$(RM) run
