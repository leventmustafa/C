#include <stdio.h>
#include <ctype.h>

void print_histogram(const char *text)
{
    int counts[26] = {0};
    int total_letters = 0;

    // 1. Преброяване
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            int index = toupper(text[i]) - 'A';
            counts[index]++;
            total_letters++;
        }
    }

    // 2. Визуализация
    printf("\n--- FREQUENCY HISTOGRAM ---\n");

    for (int i = 0; i < 26; i++)
    {
        if (counts[i] > 0)
        {
            printf("%c (%3d): ", 'A' + i, counts[i]);

            for (int j = 0; j < counts[i]; j++)
            {
                printf("*");
            }

            printf("\n");
        }
    }

    printf("\nTotal letters: %d\n", total_letters);
}

int main()
{
    char text[1000];

    printf("Enter text:\n");
    fgets(text, sizeof(text), stdin);

    print_histogram(text);

    return 0;
}frequency_analysis_caesar.c
