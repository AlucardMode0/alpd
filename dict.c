#include "dict.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Dictionary* dict_new() {
    Dictionary *dictionary = (Dictionary*)malloc(sizeof(Dictionary));
    assert(dictionary != NULL);
    dictionary->head = NULL;
    dictionary->tail = NULL;
    return dictionary;
}

void dict_add(Dictionary *dictionary, const char *key, int value) {
    int ok=1;
	int i =0;
	if(dict_has(dictionary, key))
		while(dictionary != NULL)
			{
			if(strcmp(dictionary->head->key, key) == 0)
			{for(i=0;i<dictionary->head->counter;++i)
						if (dictionary->head->value[i]==value)
						{ok=0;
						break;}
				if (ok==1)
				{dictionary->head->counter++;
				//printf("%s the supli\n ",key);
				//printf("%d\n",dictionary->head->counter);
				dictionary->head->value[dictionary->head->counter-1] = value;
				break;}
			}
			dictionary = dictionary->tail;
			}
	else{
		if (dictionary->head != NULL) {
			while(dictionary->tail != NULL) {
				dictionary = dictionary->tail;
			}
			Dictionary *next = dict_new();
			dictionary->tail = next;
			dictionary = dictionary->tail;
		}
		int key_length = strlen(key) + 1;
		dictionary->head = (KVPair*)malloc(sizeof(KVPair));
		assert(dictionary->head != NULL);
		dictionary->head->key = (char *)malloc(key_length * sizeof(char));
		dictionary->head->value = (int *)malloc(total * sizeof(int));
		assert(dictionary->head->key != NULL);
		strcpy(dictionary->head->key, key);
		//printf("%s normal key\n ",key);
		dictionary->head->counter=1;
		dictionary->head->value[0] = value;
	}
}

int dict_has(Dictionary *dictionary, const char *key) {
    if (dictionary->head == NULL)
        return 0;
    while(dictionary != NULL) {
        if(strcmp(dictionary->head->key, key) == 0)
            return 1;
        dictionary = dictionary->tail;
    }
    return 0;
}

/* int dict_get(Dictionary *dictionary, const char *key) {
    if (dictionary->head == NULL)
        return 0;
    while(dictionary != NULL) {
        if(strcmp(dictionary->head->key, key) == 0)
            return dictionary->head->value;
        dictionary = dictionary->tail;
    }
    return 0;
}
 */
 
void dict_print_key(Dictionary *dictionary, const char *key) 
{
	int i ;
    while(dictionary != NULL) {
        	if(strcmp(dictionary->head->key, key) == 0)
			{for(i=0;i<dictionary->head->counter;++i)
					printf("%d ",dictionary->head->value[i]);
				break;}
        dictionary = dictionary->tail;
    }
    
}

void dict_print(Dictionary *dictionary) 
{
	int i ;
    while(dictionary != NULL) {
		printf("%s:",dictionary->head->key);
			for(i=0;i<dictionary->head->counter;++i)
					printf("%d ",dictionary->head->value[i]);
		printf("\n");
        dictionary = dictionary->tail;
    }
    
}
void dict_remove(Dictionary *dictionary, const char *key) {
    if (dictionary->head == NULL)
        return;
    Dictionary *previous = NULL;
    while(dictionary != NULL) {
        if(strcmp(dictionary->head->key, key) == 0) {
            if(previous == NULL) {
                free(dictionary->head->key);
                dictionary->head->key = NULL;
                if (dictionary->tail != NULL) {
                    Dictionary *toremove = dictionary->tail;
                    dictionary->head->key = toremove->head->key;
                    dictionary->tail = toremove->tail;
                    free(toremove->head);
                    free(toremove);
                    return;
                }
            }
            else {
                previous->tail = dictionary->tail;
            }
            free(dictionary->head->key);
            free(dictionary->head);
            free(dictionary);
            return;
        }
        previous = dictionary;
        dictionary = dictionary->tail;
    }
}

void dict_free(Dictionary *dictionary) {
    if(dictionary == NULL)
        return;
    free(dictionary->head->key);
	free(dictionary->head->value);	
    free(dictionary->head);
    Dictionary *tail = dictionary->tail;
    free(dictionary);
    dict_free(tail);
}
