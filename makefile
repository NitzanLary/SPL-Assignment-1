all: cTrace

cTrace: bin/Graph.o bin/Tree.o bin/Session.o bin/Agent.o bin/main.o
	@echo 'linking'
	g++ -o bin/cTrace bin/Graph.o bin/Tree.o bin/Session.o bin/Agent.o bin/main.o

bin/Graph.o: src/Graph.cpp
		g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Graph.o src/Graph.cpp
		
bin/Tree.o: src/Tree.cpp
		g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Tree.o src/Tree.cpp
		
bin/Session.o: src/Session.cpp
		g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Session.o src/Session.cpp

bin/Agent.o: src/Agent.cpp
		g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Agent.o src/Agent.cpp
		
bin/main.o: src/main.cpp
		g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp

clean:
	@echo 'cleaning'
	rm -f bin/*
