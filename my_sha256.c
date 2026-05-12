#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>

#define BUFFER_SIZE 1024

void handleErrors() {
    printf("OpenSSL error\n");
    exit(1);
}

int main(int argc, char *argv[]) {

    if(argc != 2) {
        printf("Usage: ./my_sha256 file\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");

    if(file == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    EVP_MD_CTX *ctx;

    ctx = EVP_MD_CTX_new();

    if(ctx == NULL)
        handleErrors();

    // initialize SHA256
    if(1 != EVP_DigestInit_ex(
                ctx,
                EVP_sha256(),
                NULL))
    {
        handleErrors();
    }

    unsigned char buffer[BUFFER_SIZE];

    size_t bytesRead;

    // read file in chunks
    while((bytesRead = fread(
                buffer,
                1,
                BUFFER_SIZE,
                file)) > 0)
    {
        // update hash
        if(1 != EVP_DigestUpdate(
                    ctx,
                    buffer,
                    bytesRead))
        {
            handleErrors();
        }
    }

    unsigned char hash[EVP_MAX_MD_SIZE];

    unsigned int hash_len;

    // finalize hash
    if(1 != EVP_DigestFinal_ex(
                ctx,
                hash,
                &hash_len))
    {
        handleErrors();
    }

    EVP_MD_CTX_free(ctx);

    fclose(file);

    // print hash
    for(int i = 0; i < hash_len; i++) {
        printf("%02x", hash[i]);
    }

    printf("\n");

    return 0;
}
