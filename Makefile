compiler = gcc
file = main.c
file2 = bookFunc.c

all: $(file)
	$(compiler) ./$(file) ./$(file2) -std=c89 -Wall -o output && ./output
	

clean:
	rm output