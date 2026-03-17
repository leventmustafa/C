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
    else if (islower(symbol))
    {
        return ((symbol - 'a' - key + 26) % 26) + 'a';
    }
    return symbol;
}

char* caesar_decrypt(char* cipher, int key)
{
    int length = strlen(cipher);
    char* plaintext = malloc(sizeof(char) * (length + 1));

    for (int i = 0; i < length; i++)
    {
        plaintext[i] = caesar_decrypt_char(cipher[i], key);
    }
    plaintext[length] = '\0';

    return plaintext;
}

int* count_letters(char* cipher)
{
    int* counts = malloc(sizeof(int) * LETTERS_COUNT);
    memset(counts, 0, sizeof(int) * LETTERS_COUNT);

    for (int i = 0; cipher[i] != '\0'; i++)
    {
        if (isalpha(cipher[i]))
        {
            int letter_index = toupper(cipher[i]) - 'A';
            counts[letter_index]++;
        }
    }
    return counts;
}

char get_most_common_letter(char* cipher)
{
    int* counts = count_letters(cipher);

    int maxIndex = 0;
    for (int i = 1; i < LETTERS_COUNT; i++)
    {
        if (counts[i] > counts[maxIndex])
        {
            maxIndex = i;
        }
    }

    char letter = maxIndex + 'A';
    free(counts);  

    return letter;
}

int get_key(char common_letter, char referent_letter)
{

    return (common_letter - referent_letter + 26) % 26;
}

void caesar_decrypt_analyze(char* cipher)
{
    
    char common_letter = get_most_common_letter(cipher);

    int keys[] = {
        get_key(common_letter, 'E'),
        get_key(common_letter, 'T'),
        get_key(common_letter, 'A'),
        get_key(common_letter, 'O')
    };

    char referents[] = {'E', 'T', 'A', 'O'};

    for (int i = 0; i < 4; i++)
    {
        char* plaintext = caesar_decrypt(cipher, keys[i]);
        printf("Assuming '%c': %s (key = %d)\n",
               referents[i], plaintext, keys[i]);
        free(plaintext);  
    }
}

int main()
{
    char cipher[MAXN];

    printf("Enter ciphered text:\n");
    fgets(cipher, MAXN, stdin);


    cipher[strcspn(cipher, "\n")] = '\0';

    caesar_decrypt_analyze(cipher);

    return EXIT_SUCCESS;
}