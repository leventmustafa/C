#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* vigenere_decrypt(const char *cipher, const char *key)
{
    int key_len = strlen(key);
    int key_index = 0;
    int cipher_len = strlen(cipher);

    char* plaintext = malloc(sizeof(char) * (cipher_len + 1));

    for (int i = 0; cipher[i] != '\0'; i++)
    {
        char symbol = cipher[i];

        if (isalpha(symbol))
        {
            char k_char = toupper(key[key_index % key_len]);
            int shift = k_char - 'A';

            if (islower(symbol))
                plaintext[i] = ((symbol - 'a' - shift + 26) % 26) + 'a';
            else
                plaintext[i] = ((symbol - 'A' - shift + 26) % 26) + 'A';

            key_index++;
        }
        else
        {
            plaintext[i] = symbol;
        }
    }

    plaintext[cipher_len] = '\0';
    return plaintext;
}

int main()
{
    FILE *input = fopen("encrypted.txt", "r");
    if (input == NULL)
    {
        printf("Cannot open encrypted.txt\n");
        return 1;
    }

    FILE *key_file = fopen("key.txt", "r");
    if (key_file == NULL)
    {
        printf("Cannot open key.txt\n");
        fclose(input);
        return 1;
    }

    FILE *output = fopen("decrypted.txt", "w");
    if (output == NULL)
    {
        printf("Cannot open decrypted.txt\n");
        fclose(input);
        fclose(key_file);
        return 1;
    }

    char cipher[1024];
    char key[1024];

    fgets(cipher, sizeof(cipher), input);
    fgets(key, sizeof(key), key_file);

    // махаме newline
    cipher[strcspn(cipher, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';

    char* plaintext = vigenere_decrypt(cipher, key);

    fprintf(output, "%s", plaintext);

    free(plaintext);

    fclose(input);
    fclose(key_file);
    fclose(output);

    printf("Decryption complete -> decrypted.txt\n");

    return 0;
}
