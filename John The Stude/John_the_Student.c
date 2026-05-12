#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>

#define MAX_LINE 1024

// remove newline
void remove_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// ================= DICTIONARY ATTACK =================
char* dictionary_attack(char *hash, FILE *dict) {

    static char password[256];

    rewind(dict);

    while(fgets(password, sizeof(password), dict)) {

        remove_newline(password);

        // crypt(password, hash)
        // uses salt from hash automatically
        char *generated = crypt(password, hash);

        if(strcmp(generated, hash) == 0) {
            return password;
        }
    }

    return NULL;
}

// ================= PIN BRUTE FORCE =================
char* brute_force_pin(char *hash) {

    static char pin[5];

    for(int i = 0; i <= 9999; i++) {

        sprintf(pin, "%04d", i);

        char *generated = crypt(pin, hash);

        if(strcmp(generated, hash) == 0) {
            return pin;
        }
    }

    return NULL;
}

int main(int argc, char *argv[]) {

    if(argc != 3) {
        printf("Usage:\n");
        printf("./my_john shadow.txt dictionary.txt\n");
        return 1;
    }

    FILE *shadow = fopen(argv[1], "r");
    FILE *dict = fopen(argv[2], "r");

    if(shadow == NULL || dict == NULL) {
        printf("File error\n");
        return 1;
    }

    char line[MAX_LINE];

    printf("\n--- Results ---\n\n");

    // read shadow line by line
    while(fgets(line, sizeof(line), shadow)) {

        remove_newline(line);

        // username:hash:...
        char *username = strtok(line, ":");
        char *hash = strtok(NULL, ":");

        if(username == NULL || hash == NULL)
            continue;

        // skip invalid hashes
        if(strcmp(hash, "x") == 0 ||
           strcmp(hash, "*") == 0 ||
           strcmp(hash, "!") == 0)
        {
            continue;
        }

        // ===== dictionary attack =====
        char *found = dictionary_attack(hash, dict);

        if(found != NULL) {

            printf("%s : %s (dictionary)\n",
                   username,
                   found);

            continue;
        }

        // ===== brute force pin =====
        found = brute_force_pin(hash);

        if(found != NULL) {

            printf("%s : %s (brute-force)\n",
                   username,
                   found);

            continue;
        }

        // ===== not cracked =====
        printf("%s : [NOT CRACKED]\n", username);
    }

    fclose(shadow);
    fclose(dict);

    return 0;
}
