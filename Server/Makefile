CXX = gcc
LIBS = -lpthread -lboost_system -lboost_thread -lboost_chrono
OPTS = -lstdc++ -std=c++17
DEBUG = -ggdb -O0

Main: Session.o Server.o Main.o
	$(CXX) -o Main Main.o Server.o Session.o ../ThreadManager/ThreadManager.o $(OPTS) $(LIBS) $(ggdb)

Main.o:
	$(CXX) -c Main.cpp

Server.o:
	$(CXX) -c Server.cpp

Session.o:
	$(CXX) -c Session.cpp

all: Main

clean:
	rm -rf *.o