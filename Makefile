all: clean assign3

assign3:
	g++ -g -Wall main.cpp -o assign3
clean:
	rm -rf assign3