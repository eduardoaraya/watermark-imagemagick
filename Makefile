build:	
		g++ --std=c++17 -lstdc++fs \
		`Magick++-config --cxxflags --cppflags` -O2 -o ./bin/main main.cpp \
		`Magick++-config --ldflags --libs` 
	
run: 
		./bin/main