#include <stdio.h>
#include <string.h>
#include <crypt.h>
#include <stdlib.h>

void crack_pin(const char *target_hash) {
    char guess[5]; // 4 digits + '\0'
    
    printf("--- Begin PIN Brute-Force ---\n");
    
    for (int i = 0; i <= 9999; i++) {
        // 1. Format the number as 4-digits string (ex. 0042)
        sprintf(guess, "%04d", i);
        
        // 2. Hash the guess
        char *computed_hash = crypt(guess, target_hash);
        
        // 3. Compare the hashes
        if (strcmp(computed_hash, target_hash) == 0) {
            printf("[SUCCESS] The password is: %s\n", guess);
            return;
        }
    }
    printf("[FAIL] The password is not 4-digit PIN.\n");
}

int main() {
    char shadow_line[] = "bob:$6$xq7%3$03TJMkvoZmSoSVmWpDUuBvXNInUeIT3fLj6EvodCh1qFYjK9azoiyfxT4/gomNcpX.5Xfg08ZPU6U.xIHu8Pn.:19000:0:99999:7:::";
    
    char *username = NULL;
    char *hash = NULL;

    username = strtok(shadow_line, ":");
    
    hash = strtok(NULL, ":");

    if (username && hash) {
        printf("Target User: %s\n", username);
        printf("Target Hash: %s\n", hash);

        crack_pin(hash);
    } else {
        printf("Parsing error!\n");
    }

    return EXIT_SUCCESS;
}
