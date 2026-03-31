#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rc4_crypt(unsigned char *key, int keylen,
               unsigned char *data, int datalen,
               unsigned char *output)
{
    unsigned char S[256];
    int i, j = 0;
    for (i = 0; i < 256; i++)
        S[i] = i;

    for (i = 0; i < 256; i++)
    {
        j = (j + S[i] + key[i % keylen]) % 256;
        unsigned char tmp = S[i];
        S[i] = S[j];
        S[j] = tmp;
    }
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

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s input_file output_file key\n", argv[0]);
        return 1;
    }

    char *input_name = argv[1];
    char *output_name = argv[2];
    char *key = argv[3];

    FILE *in = fopen(input_name, "rb");   // бинарно четене
    if (in == NULL)
    {
        printf("Cannot open input file\n");
        return 1;
    }

    FILE *out = fopen(output_name, "wb"); // бинарно писане
    if (out == NULL)
    {
        printf("Cannot open output file\n");
        fclose(in);
        return 1;
    }
    fseek(in, 0, SEEK_END);
    int size = ftell(in);
    rewind(in);
    unsigned char *data = malloc(size);
    fread(data, 1, size, in);

    unsigned char *result = malloc(size);
    rc4_crypt((unsigned char *)key, strlen(key), data, size, result);
  
    fwrite(result, 1, size, out);

    free(data);
    free(result);

    fclose(in);
    fclose(out);

    printf("Done!\n");
    return 0;
}
