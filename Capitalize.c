#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum options options;
enum options {
    CHANGE_ALL,
    MAKE_ALL_LOWERCASE,
    MAKE_ALL_UPPERCASE,
    LEAVE_FIRST_UPPERCASE
};

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

int check_option(char letter, unsigned int count, options option)
{
    if (option == CHANGE_ALL) {
        return 1;
    }
    else if (option == MAKE_ALL_LOWERCASE) {
        return (letter >= 'A' && letter <= 'Z');
    }
    else if (option == MAKE_ALL_UPPERCASE) {
        return (letter >= 'a' && letter <= 'z');
    }
    else {
        return (letter >= 'A' && letter <= 'Z') && 
            (count || (letter >= 'a' && letter <= 'z'));
    }
}

char* capitalize(char* instring, options option)
{
    unsigned int in_len = length(instring);
    char* res = (char*)malloc(in_len * sizeof(char));
    if (res == NULL) {
        fprintf(stderr, "capitalize: not enough memory\n");
        exit(1);
    }
    unsigned int i = 0;
    while (instring[i] != '\n') {
        if (check_option(instring[i], i, option)) {
            res[i] = change_capitalization(instring[i]);
        }
        else {
            res[i] = instring[i];
        }
        i++;
    }
    res[i] = 0;
    return res;
}

void gettext(char* input_string)
{
    printf("Enter your text below:\n");
    fgets(input_string, 100, stdin);
    fflush(stdin);
}

void getoption(options* input_option)
{
    printf("Select one of the options:\n"
            "type 0 to reverse capitalization of every letter\n"
            "type 1 to change all upper case letters to lower case\n"
            "type 2 to change all lower case letters to upper case\n"
            "type 3 to leave the first letter upper cased and change"
            " the rest to lower case\n");
    fscanf(stdin, "%d", input_option);
    fflush(stdin);
}

int main(int argc, char* argv[])
{
    int stayloop = 1;
    char input_string[100];
    char choice = 'f';
    options input_option;
    while (stayloop) {
        gettext(input_string);
        if (choice == 'f') {
            getoption(&input_option);
        }
        char* changed = capitalize(input_string, input_option);
        printf("%s", changed);
        free(changed);
        printf("\nType q to quit the program or c to continue:\n");
        fgets(&choice, 1, stdin); //fix: buffer stores 2 \n from somewhere and I need to fix that
        fflush(stdin);
        if (choice == 'q') {
            stayloop = 0;
        }
    }
    return 0;
}
