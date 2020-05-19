CXX = clang++
CXXFLAGS = -std=c++2a -Wall -Wextra -Wpedantic -pedantic-errors
LFLAGS = -lglfw -lGLEW -framework OpenGL
OBJS = main.o

%.o : %.c
	$(CXX) -MMD -c -o $@ $< $(CXXFLAGS) -include *.d

run : $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LFLAGS)

.PHONY : clean distclean

clean :
	$(RM) $(OBJS)

distclean : clean
	$(RM) run
