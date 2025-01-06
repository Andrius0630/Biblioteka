compiler = gcc
file = main.c
file2 = bookFunc.c
file3 = ui.c
file4 = ascii.c

all: $(file)
	$(compiler) ./$(file) ./$(file2) ./$(file3) ./$(file4) -std=c89 -lm -Wall -o output && ./output
	

clean:
	rm output