#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "symtab.h"

unsigned int hash_function(const char *str, unsigned htab_size) {
    unsigned int h = 0;
    const unsigned char *p;
    for(p = (const unsigned char *)str; *p != '\0'; p++)
        h = 65599*h + *p;
    return h % htab_size;
}

int st_init(symtab_t **table){
    *table = (symtab_t *) malloc(sizeof(symtab_elem_t)*TABLE_SIZE);

    if (table == NULL)
        return - 1;

    for (int i = 0; i < TABLE_SIZE; i++) {
        (*table)->elements[i] = NULL;
    }

    return 0;
}

symtab_elem_t *st_add(symtab_t *tabulka, char *token) {
    unsigned int klic = hash_function(token, TABLE_SIZE);

    symtab_elem_t *synon = (symtab_elem_t *) malloc(sizeof(symtab_elem_t));

    if (synon == NULL)
        return NULL;

    synon->id = token;

    if (tabulka->elements[klic] != NULL) {
        synon->nextElem = tabulka->elements[klic]->nextElem;
        tabulka->elements[klic]->nextElem = synon;
    }
    else {
        synon->nextElem = NULL;
        tabulka->elements[klic] = synon;
    }

    return synon;
}

symtab_elem_t *st_find (symtab_t *tabulka, char *token){
    unsigned int klic = hash_function(token, TABLE_SIZE);

    symtab_elem_t *ptr = tabulka->elements[klic];

    while (ptr != NULL) {
        if (strcmp(ptr->id, token) == 0)
            return ptr;

        ptr = ptr->nextElem;
    }

    return NULL;
}

void st_free(symtab_t *table) {
    symtab_elem_t *ptr;
    for (int i = 0; i <TABLE_SIZE; i++)
    {
        if (table->elements[i] != NULL) {
            while (table->elements[i]->nextElem != NULL) {
                ptr = table->elements[i]->nextElem;
                table->elements[i]->nextElem = table->elements[i]->nextElem->nextElem;
                free(ptr);
            }

            free(table->elements[i]);
        }
    }
    free(table);
}

void st_print_elem(symtab_elem_t *elem) {
    printf("%s\n", elem->id);
}

void st_print(symtab_t *table) {
    symtab_elem_t *ptr;

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table->elements[i] != NULL) {
            ptr = table->elements[i];

            while (ptr != NULL) {
                st_print_elem(ptr);

                ptr = ptr->nextElem;
            }
        }
    }
}
