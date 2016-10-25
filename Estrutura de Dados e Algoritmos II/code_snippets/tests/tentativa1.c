#include <stdio.h>
#include <stdlib.h>
#include <string.h>

main()
{
	char ch [256];
	int freq[256];
	int i;
	
	for (i = 0; i < 256; i++) {
	    freq[i] = 0;
	}
	ler_ficheiro( freq, ch);	

}
freqs_listas(char caracter, int *freq, char *ch)
{
	freq[caracter] += 1;

}
ler_ficheiro(int *freq, char *ch)
{

	FILE* ficheiro;
	char caracter;
	size_t len= 0;
	ssize_t read;
	int i;

	ficheiro = fopen("input.txt", "r");
	if (ficheiro == NULL){
		printf("\n ficheiro não encontrado! \n");
	} else {
		while ((caracter = fgetc(ficheiro)) != EOF){
            freqs_listas(caracter, freq, ch);
        }
        
        fclose(ficheiro);
    }
    
    for (i = 0; i < 256; i++) {
        if (freq[i]) {
            printf("char: %c -- freq: %d\n", (char) i, freq[i]);
        }
    }
	
	

}

