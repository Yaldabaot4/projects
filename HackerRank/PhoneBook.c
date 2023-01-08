#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#pragma warning (disable : 4996)

typedef struct linked linked;
struct linked {
    int num;
    char* name;
    linked* next;
};

long long index_hash(char* name) {
    int hash_val = 0;
    int prime = 31;
    int power = 1;
    while (*name != '\0') {
        hash_val += ((*name - 'a' + 1) * power) % 10000;
        power = (power * prime) % 10000;
        name++;
    }
    return hash_val;
}

//int index_hash(char* name) {
//    int proto = 0;
//    while (*name != '\0') {
//        proto += *name;
//        name++;
//    }
//    return proto % 100000;
//}

void hash_insert(linked** hash, int index, char* name, int num) {
    if (hash[index] == NULL) {
        hash[index] = (linked*)malloc(sizeof(linked));
        hash[index]->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
        strcpy(hash[index]->name, name);
        hash[index]->num = num;
        hash[index]->next = NULL;
    }
    else {
        linked* parse = hash[index];
        while (parse->next != NULL) {
            parse = parse->next;
        }
        parse->next = (linked*)malloc(sizeof(linked));
        parse->next->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
        strcpy(parse->next->name, name);
        parse->next->num = num;
        parse->next->next = NULL;
    }
}

int main() {
    const int HASH_LEN = 100000;
    linked* hash[100000];
    for (long long i = 0; i < HASH_LEN; i++) {
        hash[i] = NULL;
    }

    int entries;
    scanf("%d", &entries);
    for (unsigned int i = 0; i < entries; i++) {
        char name[100];
        int num;
        scanf("%s %d", name, &num);
        hash_insert(hash, index_hash(name), name, num);
    }

    char query[100];
    char prev[100];
    int first_time = 0;
    while (scanf("%s", &query)) {

        if (first_time) {
            if (strcmp(prev, query) == 0) {
                break;
            }
        }
        strcpy(prev, query);
        first_time = 1;

        int look = index_hash(query);
        if (hash[look] == NULL) {
            printf("Not found\n");
        }
        else {
            linked* parse = hash[look];
            while (strcmp(parse->name, query) != 0) {
                parse = parse->next;
                if (parse == NULL) {
                    break;
                }
            }
            if (parse == NULL) {
                printf("Not found\n");
            }
            else {
                printf("%s=%d\n", parse->name, parse->num);
            }
        }
    }
    return 0;

}