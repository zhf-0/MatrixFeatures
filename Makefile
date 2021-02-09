CC=g++
CXXFLAGS= -std=c++11 -Wall -g
obj= features.o sparsemat.o 

main:main.cpp $(obj) 	
	$(CC) $(CXXFLAGS) $^ -o $@

test:test.cpp $(obj)
	$(CC) $(CXXFLAGS) $^ -o $@

$(obj):%.o:%.cpp 
	$(CC) $(CXXFLAGS) -c $^ -o $@



.PHONY:clean

clean:
	-rm main $(obj)
