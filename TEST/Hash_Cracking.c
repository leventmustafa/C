#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

void sha256(const char *input, char *output_hex) {

    EVP_MD_CTX *ctx;
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(ctx, input, strlen(input));
    EVP_DigestFinal_ex(ctx, hash, &hash_len);
    EVP_MD_CTX_free(ctx);
    // hash to hex
    for(int i = 0; i < hash_len; i++) {
        sprintf(output_hex + (i * 2), "%02x", hash[i]);
    }
    
    output_hex[64] = '\0';
}

int main() {
    char target_hash[] =
    "ef797c8118f02dfb649607dd5d3f8c7623048c9c063d532cc95c5ed7a898a64f";
    char salt[] = "2026-";
    char pin[5];
    //0000-9999
    for(int i = 0; i <= 9999; i++) {
        sprintf(pin, "%04d", i);
        char combined[100];
        sprintf(combined, "%s%s", salt, pin);
        char hash_hex[65];
        sha256(combined, hash_hex)
        if(strcmp(hash_hex, target_hash) == 0) {
            printf("PIN FOUND: %s\n", pin);
            return 0;
        }
    }

    printf("PIN not found\n");
    return 0;
}Hash Cracking
