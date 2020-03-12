all: clean gameoflife

gameoflife:
	g++ -g -Wall *.cpp -o gameoflife
clean:
	rm -rf gameoflife