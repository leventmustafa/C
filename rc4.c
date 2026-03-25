#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void rc4_crypt(unsigned char *key, int keylen, unsigned char *data, int datalen, unsigned char *output) {
    unsigned char S[256];
    int i, j = 0;
    unsigned char temp;


    for (i = 0; i < 256; i++) S[i] = i;

  
    for (i = 0; i < 256; i++) {
        j=(j + S[i] +key[i % keylen]) % 256;
        int tmp=S[i];
        S[i]=S[j];
        S[j]=tmp;
    }

    // --- PRGA (Pseudo-Random Generation Algorithm) ---
    i = 0; j = 0;
    for (int k = 0; k < datalen; k++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        int tmp=S[i];
        S[i]=S[j];
        S[j]=tmp;
        char keystreamByte=S[(S[i] + S[j]) %256];
        output[k]=data[k]^keystreamByte;
    }
}


int main() {
    unsigned char key[] = "Key";
    unsigned char plaintext[] = "Wiki";
    int plaintext_len=strlen(plaintext);
    unsigned char ciphertext[10];

    printf("Plaintext: %s\n", plaintext);
    rc4_crypt(key, strlen((char*)key), plaintext, strlen((char*)plaintext), ciphertext);
    
    printf("Ciphertext (Hex): ");
    for(int i=0; i<plaintext_len; i++) printf("%02X ", ciphertext[i]);
    printf("\n");
    
    // Очакван изход: EB 9F 77 81
    return EXIT_SUCCESS;
}