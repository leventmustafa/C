#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char text[2000];

    printf("Enter cipher text:\n");
    fgets(text, sizeof(text), stdin);

    int len = strlen(text);

    // маха newline
    if (text[len - 1] == '\n')
        text[len - 1] = '\0';

    len = strlen(text);

    for (int i = 0; i < len - 2; i++)
    {
        // взимаме само букви
        if (!isalpha(text[i]) || !isalpha(text[i+1]) || !isalpha(text[i+2]))
            continue;

        for (int j = i + 1; j < len - 2; j++)
        {
            if (strncmp(&text[i], &text[j], 3) == 0)
            {
                printf("Found \"%.3s\": Pos %d & Pos %d -> Distance: %d\n",
                       &text[i], i, j, j - i);
            }
        }
    }

    return 0;
}kasiski_helper.c
