# https://en.sfml-dev.org/forums/index.php?topic=9037.0

LIBS := -lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS := -O2 -std=c++14
CXX := g++

APPNAME := boids
FILES := main.o boid.o flock.o drawable.o

all: clean theapp

%.o: %.cpp
	@echo "** Building $@"
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(LIBS)

theapp: $(FILES)
	@echo "** Building the app"
	$(CXX) -o $(APPNAME) $(FILES) $(CXXFLAGS) $(LIBS)
	@echo
	@echo " --> success <--"

clean:
	@echo "** Removing object files and executable..."
	rm -f $(APPNAME) *.o
