#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define MAX_LINE 1024

// ================= SHA256 =================
void sha256(const char *input, char *output_hex) {

    EVP_MD_CTX *ctx;

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    ctx = EVP_MD_CTX_new();

    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);

    EVP_DigestUpdate(ctx, input, strlen(input));

    EVP_DigestFinal_ex(ctx, hash, &hash_len);

    EVP_MD_CTX_free(ctx);

    // convert to hex
    for(int i = 0; i < hash_len; i++) {
        sprintf(output_hex + (i * 2), "%02x", hash[i]);
    }

    output_hex[64] = '\0';
}

// ================= GENERATE SALT =================
void generate_salt(char *salt_hex) {

    unsigned char salt[4];

    // random 4 bytes
    RAND_bytes(salt, sizeof(salt));

    // convert to hex
    for(int i = 0; i < 4; i++) {
        sprintf(salt_hex + (i * 2), "%02x", salt[i]);
    }

    salt_hex[8] = '\0';
}

// ================= REGISTER =================
void register_user() {

    char username[100];
    char password[100];

    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    // generate salt
    char salt[9];

    generate_salt(salt);

    // salt + password
    char combined[256];

    sprintf(combined, "%s%s", salt, password);

    // hash
    char hash[65];

    sha256(combined, hash);

    // save
    FILE *db = fopen("users.db", "a");

    fprintf(db,
            "%s:%s:%s\n",
            username,
            salt,
            hash);

    fclose(db);

    printf("User registered.\n");
}

// ================= LOGIN =================
void login_user() {

    char username[100];
    char password[100];

    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    FILE *db = fopen("users.db", "r");

    if(db == NULL) {
        printf("Database not found\n");
        return;
    }

    char line[MAX_LINE];

    while(fgets(line, sizeof(line), db)) {

        line[strcspn(line, "\n")] = '\0';

        char *file_user = strtok(line, ":");
        char *salt = strtok(NULL, ":");
        char *stored_hash = strtok(NULL, ":");

        if(file_user == NULL ||
           salt == NULL ||
           stored_hash == NULL)
        {
            continue;
        }

        // user found
        if(strcmp(username, file_user) == 0) {

            // salt + input password
            char combined[256];

            sprintf(combined,
                    "%s%s",
                    salt,
                    password);

            // calculate hash
            char check_hash[65];

            sha256(combined, check_hash);

            // compare
            if(strcmp(check_hash, stored_hash) == 0) {
                printf("Login successful\n");
            }
            else {
                printf("Wrong password\n");
            }

            fclose(db);
            return;
        }
    }

    printf("User not found\n");

    fclose(db);
}

// ================= MAIN =================
int main() {

    int choice;

    printf("1. Register\n");
    printf("2. Login\n");

    scanf("%d", &choice);

    if(choice == 1) {
        register_user();
    }
    else if(choice == 2) {
        login_user();
    }
    else {
        printf("Invalid choice\n");
    }

    return 0;
}Simple Shadow File
