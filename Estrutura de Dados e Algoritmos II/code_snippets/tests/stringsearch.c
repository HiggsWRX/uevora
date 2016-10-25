#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define d 256
const unsigned long Q = 101;
// 4294967291

int naive_search(char *T, char *P, int n)
{
    char *t;
    int N = strlen(T);
    int M = strlen(P);
    static int index = 0;
    if (n == 1) {
        index = 0;
    }

    for (t = T + (n ? 0 : index + 1); t < T + N - M; ++t) {
        char *tt = t, *p = P;

        while (*p && *p == *tt) {
            ++tt, ++p;
        }
        if (*p == '\0') {
            index = t - T;
            return index;
        }
    }

    return -1;
}

void rabin_karp_search(char pat[], char txt[])
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;
 
    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M-1; i++) {
        h = (h*d)%Q;
    }
 
    // Calculate the hash value of pattern and first
    // window of text
    for (i = 0; i < M; i++)
    {
        p = (d*p + pat[i])%Q;
        t = (d*t + txt[i])%Q;
    }
 
    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++)
    {
 
        // Check the hash values of current window of text
        // and pattern. If the hash values match then only
        // check for characters on by one
        if ( p == t )
        {
            /* Check for characters one by one */
            for (j = 0; j < M; j++)
            {
                if (txt[i+j] != pat[j])
                    break;
            }
 
            // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
            if (j == M)
                printf("Pattern found at index %d \n", i);
        }
 
        // Calculate hash value for next window of text: Remove
        // leading digit, add trailing digit
        if ( i < N-M )
        {
            t = (d*(t - txt[i]*h) + txt[i+M])%Q;
 
            // We might get negative value of t, converting it
            // to positive
            if (t < 0)
            t = (t + Q);
        }
    }
}

int main()
{
    FILE *input;
    char *line = NULL;
    char pat[32];
    size_t len = 0;
    ssize_t read;
    int pos;
    int num = 1;

    printf("Pattern to match?\n");
    scanf("%s", pat);
    input = fopen("strings.txt", "r");
    while (read = getline(&line, &len, input) != -1) {
        /*int x = 1;
        while ((pos = naive_search(line, pat, x)) != -1) {
            x = 0;
            printf("Pattern %s ocorreu na posicao %d na linha %d.\n", pat, pos + 1, num);
        }
        num++;*/
        rabin_karp_search(pat, line);
    }

    free(line);
    fclose(input);

    return 0;
}