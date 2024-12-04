compiler = gcc
file = main.c
file2 = bookFunc.c
file3 = ui.c

all: $(file)
	$(compiler) ./$(file) ./$(file2) ./$(file3) -std=c89 -Wall -o output && ./output
	

clean:
	rm output