#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char shadow_line[] = "bob:$6$xq7%3$03TJMkvoZmSoSVmWpDUuBvXNInUeIT3fLj6EvodCh1qFYjK9azoiyfxT4/gomNcpX.5Xfg08ZPU6U.xIHu8Pn.:19000:0:99999:7:::";
    
    char *username = NULL;
    char *hash = NULL;

    username = strtok(shadow_line, ":");
    
    hash = strtok(NULL, ":");

    if (username && hash) {
        printf("Target User: %s\n", username);
        printf("Target Hash: %s\n", hash);
    } else {
        printf("Parsing error!\n");
    }

    return EXIT_SUCCESS;
}
