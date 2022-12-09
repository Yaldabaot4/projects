#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned int length(char* string) 
{
    unsigned int len = 0;
    while (string[len++] != '\n');
    return len;
}

char change_capitalization(char letter)
{
    char difference = 'a' - 'A';

    if (letter >= 'A' && letter <= 'Z') {
        return letter + difference;
    }
    else if (letter >= 'a' && letter <= 'z') {
        return letter - difference;
    }
    else {
        return letter;
    }
}

char* capitalize(char* instring)
{
    unsigned int in_len = length(instring);
    char* res = (char*)malloc(in_len * sizeof(char));
    if (res == NULL) {
        fprintf(stderr, "capitalize: not enough memory\n");
        exit(1);
    }
    unsigned int i = 0;
    while (instring[i] != '\n') {
        res[i] = change_capitalization(instring[i]);
        i++;
    }
    res[i] = 0;
    return res;
}

int main(int argc, char* argv[])
{
    int stayloop = 1;
    while (stayloop) {
        printf("Enter your text below:\n");
        char user_input[100];
        fgets(user_input, 100, stdin);
        char* changed = capitalize(user_input);
        printf("%s", changed);

        stayloop = 0;
        free(changed);
    }
    return 0;
}
