#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char decrypt_char(char c, char key_char)
{
    if (isupper(c))
    {
        int c_val = c - 'A';
        int k_val = toupper(key_char) - 'A';
        return ((c_val - k_val + 26) % 26) + 'A';
    }
    else if (islower(c))
    {
        int c_val = c - 'a';
        int k_val = tolower(key_char) - 'a';
        return ((c_val - k_val + 26) % 26) + 'a';
    }
    return c;
}

void read_key(char *key)
{
    FILE *file = fopen("key.txt", "r");
    if (file == NULL)
    {
        printf("Cannot open key.txt\n");
        exit(1);
    }

    fgets(key, 1000, file);
    key[strcspn(key, "\n")] = '\0'; // маха newline

    fclose(file);
}

void decrypt_file()
{
    FILE *in = fopen("encrypted.txt", "r");
    if (in == NULL)
    {
        printf("Cannot open encrypted.txt\n");
        exit(1);
    }

    FILE *out = fopen("decrypted.txt", "w");
    if (out == NULL)
    {
        printf("Cannot open decrypted.txt\n");
        fclose(in);
        exit(1);
    }

    char key[1000];
    read_key(key);

    int key_len = strlen(key);
    int key_index = 0;

    int ch;
    while ((ch = fgetc(in)) != EOF)
    {
        if (isalpha(ch))
        {
            char decrypted = decrypt_char(ch, key[key_index % key_len]);
            fputc(decrypted, out);
            key_index++;
        }
        else
        {
            fputc(ch, out); // запазва символи
        }
    }

    fclose(in);
    fclose(out);
}

int main()
{
    decrypt_file();
    printf("Decryption complete -> decrypted.txt\n");
    return 0;
}