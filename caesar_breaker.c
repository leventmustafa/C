#include <stdio.h>
#include <ctype.h>

char caesar_decrypt_char(char c, int key)
{
    if (isupper(c))
    {
        return ((c - 'A' - key + 26) % 26) + 'A';
    }
    return c;
}

void caesar_decrypt(char *cipher, int key, char *result)
{
    int i = 0;

    while (cipher[i] != '\0')
    {
        result[i] = caesar_decrypt_char(cipher[i], key);
        i++;
    }

    result[i] = '\0';
}

int main()
{
    char cipher[] = "WKLV LV D VHFUHW PHVVDJH";
    char result[1000];

    for (int key = 1; key <= 25; key++)
    {
        caesar_decrypt(cipher, key, result);
        printf("Key %2d: %s\n", key, result);
    }

    return 0;
}
