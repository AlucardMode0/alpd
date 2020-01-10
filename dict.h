#ifndef _DICT_
#define _DICT_
#include <ctype.h>
extern int total;
typedef struct {
    char *key;
    int value;
} KVPair;

typedef struct Dictionary_t {
    KVPair *head;
    struct Dictionary_t *tail;
} Dictionary;

Dictionary* dict_new();
void dict_add(Dictionary *dictionary,  char *key);
int dict_has(Dictionary *dictionary, const char *key);
int dict_get(Dictionary *dictionary, const char *key);
void dict_remove(Dictionary *dictionary, const char *key);
void dict_free(Dictionary *dictionary);
void dict_print_key(Dictionary *dictionary, const char *key);
void dict_print(Dictionary *dictionary) ;
void dict_to_dirs(Dictionary *dictionary,char *file) ;
#endif
