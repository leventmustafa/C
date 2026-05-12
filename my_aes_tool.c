#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

void handleErrors() {
    printf("OpenSSL error\n");
    exit(1);
}

int encrypt(unsigned char *plaintext,
            int plaintext_len,
            unsigned char *key,
            unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;

    int len;
    int ciphertext_len;

    ctx = EVP_CIPHER_CTX_new();

    EVP_EncryptInit_ex(
        ctx,
        EVP_aes_128_ecb(),
        NULL,
        key,
        NULL);

    EVP_EncryptUpdate(
        ctx,
        ciphertext,
        &len,
        plaintext,
        plaintext_len);

    ciphertext_len = len;

    EVP_EncryptFinal_ex(
        ctx,
        ciphertext + len,
        &len);

    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int decrypt(unsigned char *ciphertext,
            int ciphertext_len,
            unsigned char *key,
            unsigned char *plaintext)
{
    EVP_CIPHER_CTX *ctx;

    int len;
    int plaintext_len;

    ctx = EVP_CIPHER_CTX_new();

    EVP_DecryptInit_ex(
        ctx,
        EVP_aes_128_ecb(),
        NULL,
        key,
        NULL);

    EVP_DecryptUpdate(
        ctx,
        plaintext,
        &len,
        ciphertext,
        ciphertext_len);

    plaintext_len = len;

    EVP_DecryptFinal_ex(
        ctx,
        plaintext + len,
        &len);

    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}

int main(int argc, char *argv[]) {

    if(argc != 5) {
        printf("Usage:\n");
        printf("./my_aes_tool [enc|dec] input output key\n");
        return 1;
    }

    char *mode = argv[1];
    char *input_file = argv[2];
    char *output_file = argv[3];
    unsigned char *key = (unsigned char *)argv[4];

    FILE *in = fopen(input_file, "rb");
    FILE *out = fopen(output_file, "wb");

    if(in == NULL || out == NULL) {
        printf("File error\n");
        return 1;
    }

    // file size
    fseek(in, 0, SEEK_END);
    int filesize = ftell(in);
    rewind(in);

    // read file
    unsigned char *buffer = malloc(filesize);
    fread(buffer, 1, filesize, in);

    unsigned char output[filesize + 32];

    int output_len;

    if(strcmp(mode, "enc") == 0) {

        output_len = encrypt(
                        buffer,
                        filesize,
                        key,
                        output);

    }
    else if(strcmp(mode, "dec") == 0) {

        output_len = decrypt(
                        buffer,
                        filesize,
                        key,
                        output);
    }
    else {
        printf("Invalid mode\n");
        return 1;
    }

    fwrite(output, 1, output_len, out);

    free(buffer);

    fclose(in);
    fclose(out);

    printf("Done\n");

    return 0;
}
