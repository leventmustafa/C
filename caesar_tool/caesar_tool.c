#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define KEY_FILE "key.txt"
#define INPUT_FILE "plaintext.txt"
#define ENC_FILE "encrypted.txt"
#define DEC_FILE "decrypted.txt"

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

int read_key()
{
    FILE *kf = fopen(KEY_FILE, "r");
    if (!kf)
    {
        perror("Error opening key.txt");
        exit(EXIT_FAILURE);
    }

    int key;
    if (fscanf(kf, "%d", &key) != 1)
    {
        printf("Invalid key format!\n");
        fclose(kf);
        exit(EXIT_FAILURE);
    }

    fclose(kf);

    // normalize key (0–25)
    key = key % 26;
    if (key < 0) key += 26;

    return key;
}

void process_file(int mode) // 1 = encrypt, 0 = decrypt
{
    FILE *in = fopen(INPUT_FILE, "r");
    if (!in)
    {
        perror("Error opening plaintext.txt");
        exit(EXIT_FAILURE);
    }

    FILE *out;
    if (mode)
        out = fopen(ENC_FILE, "w");
    else
        out = fopen(DEC_FILE, "w");

    if (!out)
    {
        perror("Error opening output file");
        fclose(in);
        exit(EXIT_FAILURE);
    }

    int key = read_key();

    int ch;
    while ((ch = fgetc(in)) != EOF)
    {
        char result;
        if (mode)
            result = caesar_encrypt_char((char)ch, key);
        else
            result = caesar_decrypt_char((char)ch, key);

        fputc(result, out);
    }

    fclose(in);
    fclose(out);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s -e (encrypt) | -d (decrypt)\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '-' && argv[1][1] == 'e')
    {
        process_file(1);
        printf("Encryption complete -> encrypted.txt\n");
    }
    else if (argv[1][0] == '-' && argv[1][1] == 'd')
    {
        process_file(0);
        printf("Decryption complete -> decrypted.txt\n");
    }
    else
    {
        printf("Invalid option! Use -e or -d\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
