#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXN 1000

char* vigenere_encrypt(const char* plaintext, const char* key){
    int plainttext_len=strlen(plaintext);
    int key_len=strlen(key);
    int key_index=0;
    char* output = malloc(sizeof(char) * (plainttext_len + 1 ));
    for(int i = 0; i < plainttext_len; i++)
    {
        char symbol=plaintext[i];
        if(isalpha(symbol))
        {
            char key_symbol=toupper(key[key_index % key_len]);
            int shift = key_symbol - 'A';
            if(isupper(symbol))
            {
                output[i]=((symbol - 'A' + shift) % 26) + 'A';
            }
            else if(islower(symbol))
            {
                output[i]=((symbol - 'a' + shift) % 26) + 'a';
            }

            key_index++;
        }
        else
        {
            output[i] = plaintext[i];
        }
    }
    output[plainttext_len] = '\0';
    return output;
}

char* vigenere_decrypt(const char* cipher, const char* key){
    int cipher_len=strlen(cipher);
    int key_len=strlen(key);
    int key_index=0;
    char* output = malloc(sizeof(char) * (cipher_len + 1 ));
    for(int i = 0; i < cipher_len; i++)
    {
        char symbol=cipher[i];
        if(isalpha(symbol))
        {
            char key_symbol=toupper(key[key_index % key_len]);
            int shift = key_symbol - 'A';
            if(isupper(symbol))
            {
                output[i]=((symbol - 'A' - shift + 26) % 26) + 'A';
            }
            else if(islower(symbol))
            {
                output[i]=((symbol - 'a' - shift + 26) % 26) + 'a';
            }

            key_index++;
        }
        else
        {
            output[i] = cipher[i];
        }
    }
    output[cipher_len] = '\0';
    return output;
}

int main(){
    char plaintext[MAXN];
    scanf("%s", plaintext);

    char key[MAXN];
    scanf("%s", key);
    
    char*cipher=vigenere_encrypt(plaintext,key);
    printf("Encrypted: %s\n", cipher);

    char*decipher=vigenere_decrypt(cipher,key);
    printf("Decrypted: %s\n", decipher);
    return EXIT_SUCCESS;

}
