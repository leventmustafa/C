#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char caesar_encrypt_char(char c, int key)
{
    if (isupper(c))
    {
        return ((c - 'A' + key) % 26) + 'A';
    }
    else if (islower(c))
    {
        return ((c - 'a' + key) % 26) + 'a';
    }
    return c;
}

char caesar_decrypt_char(char c, int key)
{
    if (isupper(c))
    {
        return ((c - 'A' - key + 26) % 26) + 'A';
    }
    else if (islower(c))
    {
        return ((c - 'a' - key + 26) % 26) + 'a';
    }
    return c;
}

int read_key(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Cannot open key file\n");
        exit(1);
    }

    int key;
    if (fscanf(file, "%d", &key) != 1)
    {
        printf("Invalid key format\n");
        fclose(file);
        exit(1);
    }

    fclose(file);

    key = key % 26;
    if (key < 0)
        key += 26;

    return key;
}

void process_file(char *input_name, char *key_name, char *output_name, int encrypt)
{
    FILE *input = fopen(input_name, "r");
    if (input == NULL)
    {
        printf("Cannot open input file\n");
        exit(1);
    }

    FILE *output = fopen(output_name, "w");
    if (output == NULL)
    {
        printf("Cannot open output file\n");
        fclose(input);
        exit(1);
    }

    int key = read_key(key_name);

    int ch;
    while ((ch = fgetc(input)) != EOF)
    {
        char result;

        if (encrypt)
            result = caesar_encrypt_char(ch, key);
        else
            result = caesar_decrypt_char(ch, key);

        fputc(result, output);
    }

    fclose(input);
    fclose(output);
}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("Usage:\n");
        printf("  %s -e input.txt key.txt output.txt\n", argv[0]);
        printf("  %s -d input.txt key.txt output.txt\n", argv[0]);
        return 1;
    }

    char *mode = argv[1];
    char *input_file = argv[2];
    char *key_file = argv[3];
    char *output_file = argv[4];

    if (mode[0] == '-' && mode[1] == 'e')
    {
        process_file(input_file, key_file, output_file, 1);
        printf("Encryption complete -> %s\n", output_file);
    }
    else if (mode[0] == '-' && mode[1] == 'd')
    {
        process_file(input_file, key_file, output_file, 0);
        printf("Decryption complete -> %s\n", output_file);
    }
    else
    {
        printf("Invalid mode! Use -e or -d\n");
        return 1;
    }

    return 0;
}