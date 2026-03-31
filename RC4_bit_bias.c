#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void rc4_crypt(unsigned char *key, int keylen,
               unsigned char *data, int datalen,
               unsigned char *output)
{
    unsigned char S[256];
    int i, j = 0;

    // KSA
    for (i = 0; i < 256; i++)
        S[i] = i;

    for (i = 0; i < 256; i++)
    {
        j = (j + S[i] + key[i % keylen]) % 256;
        unsigned char tmp = S[i];
        S[i] = S[j];
        S[j] = tmp;
    }

    // PRGA
    i = 0;
    j = 0;

    for (int k = 0; k < datalen; k++)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;

        unsigned char tmp = S[i];
        S[i] = S[j];
        S[j] = tmp;

        unsigned char keystream = S[(S[i] + S[j]) % 256];
        output[k] = data[k] ^ keystream;
    }
}

int main()
{
    srand(time(NULL));

    int trials = 100000;
    int count_zero = 0;

    for (int t = 0; t < trials; t++)
    {
        // случаен ключ (5 байта)
        unsigned char key[5];
        for (int i = 0; i < 5; i++)
            key[i] = rand() % 256;

        // вход = нули
        unsigned char data[2] = {0, 0};
        unsigned char output[2];

        rc4_crypt(key, 5, data, 2, output);

        // проверяваме 2-рия байт
        if (output[1] == 0x00)
            count_zero++;
    }

    double probability = (double)count_zero / trials;

    printf("Zero count: %d\n", count_zero);
    printf("Probability: %f\n", probability);

    return 0;
}
