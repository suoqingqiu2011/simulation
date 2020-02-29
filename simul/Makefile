all: genere

run: all
	./genere

genere: genere.c
	gcc -Wall genere.c -lm -o genere

plot: all
	./genere > result
	Rscript essai.R
	eog hist.jpg
	eog courbe.jpg


clean:	
	rm genere
