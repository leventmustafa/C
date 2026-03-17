#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXN 1000
#define LETTERS_COUNT 26

char caesar_decrypt_char(char symbol, int key)
{
    if (isupper(symbol))
    {
        return ((symbol - 'A' - key + 26) % 26) + 'A';
    }
    else if(islower(symbol))
    {
        return ((symbol - 'a' - key + 26) % 26) + 'a';
    }
    return symbol;
}

char* caesar_decrypt(char* cipher, int key)
{
    int length = strlen(cipher);
    char* plaintext = malloc(sizeof(char) * (length + 1));
    int index = 0;
    while (cipher[index] != '\0')
    {
        plaintext[index] = caesar_decrypt_char(cipher[index], key);
        index++;
    }
    plaintext[index] = '\0';
    return plaintext;
}

void caesar_bruteforce(char* cipher)
{
    printf("--- BRUTE FORCE REPORT ---\n");
    for(int key = 0; key < LETTERS_COUNT; key++)
    {
        char* plaintext = caesar_decrypt(cipher, key);
        printf("%s (key = %d)\n", plaintext, key);
        free(plaintext);
    }
}

int main()
{
    char cipher[MAXN];
    //TODO: read cipher from file
    printf("Enter ciphered text:\n");
    scanf("%s", cipher);
    caesar_bruteforce(cipher);

    return EXIT_SUCCESS;
}