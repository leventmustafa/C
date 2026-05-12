#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>

void print_hash(const char *filename, const EVP_MD *md_type) {

    FILE *file = fopen(filename, "rb");

    if(file == NULL) {
        printf("Cannot open %s\n", filename);
        return;
    }

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();

    EVP_DigestInit_ex(ctx, md_type, NULL);

    unsigned char buffer[1024];
    size_t bytesRead;

    while((bytesRead = fread(buffer, 1, 1024, file)) > 0) {
        EVP_DigestUpdate(ctx, buffer, bytesRead);
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    EVP_DigestFinal_ex(ctx, hash, &hash_len);

    for(int i = 0; i < hash_len; i++) {
        printf("%02x", hash[i]);
    }

    printf("\n");

    EVP_MD_CTX_free(ctx);

    fclose(file);
}

int main() {

    printf("MD5 file1:\n");
    print_hash("file1.pdf", EVP_md5());

    printf("MD5 file2:\n");
    print_hash("file2.pdf", EVP_md5());

    printf("\nSHA256 file1:\n");
    print_hash("file1.pdf", EVP_sha256());

    printf("SHA256 file2:\n");
    print_hash("file2.pdf", EVP_sha256());

    return 0;
}
