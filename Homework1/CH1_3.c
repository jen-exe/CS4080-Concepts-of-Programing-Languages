#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* text;
    struct Node* next;
    struct Node* prev;
} Node;

Node* find(Node* l, const char* w) {
    while (l && strcmp(l->text, w)) l = l->next;
    return l;
}

void insert(Node** l, Node* a, const char* w) {
    Node* n = malloc(sizeof(Node));
    n->text = strdup(w);
    if(!n->text){
        free(n);
        return;
    }

    if (!a) {
        n->next = *l; n->prev = NULL;
        if (*l) (*l)->prev = n;
        *l = n;
    } else {
        n->next = a->next; n->prev = a;
        if (a->next) a->next->prev = n;
        a->next = n;
    }
}

void delete(Node** l, Node* x) {
    if (!x) return;
    if (x == *l) *l = x->next;
    if (x->prev) x->prev->next = x->next;
    if (x->next) x->next->prev = x->prev;
    if(x->text) free(x->text);
    free(x);
}

void dump(Node* l) {
    while (l) { printf("%s ", l->text); l = l->next; }
    printf("\n");
}

int main() {
    Node* list = NULL;

    insert(&list, NULL, "four");
    insert(&list, NULL, "one");
    insert(&list, find(list,"one"), "two");
    insert(&list, find(list,"two"), "three");

    dump(list);

    delete(&list, find(list,"three"));
    delete(&list, find(list,"one"));

    dump(list);

    
}
