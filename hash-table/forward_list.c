#include <stdio.h>
#include <stdlib.h>
#include "forward_list.h"

struct Node {
    data_type data;
    Node *next;
};

struct ForwardList {
    Node *head;
    int size;
};

Node *node_construct(data_type value, Node *next) {
    Node *n = (Node *) calloc(1, sizeof(Node));
    if (n == NULL) 
        exit(printf("Error: node_construct: could not allocate memory.\n\n"));

    n->data = value;
    n->next = next;
    return n;
}

void node_destroy(Node *n, void (*destroy_fn)(data_type)) {
    if (n != NULL) {
        if (destroy_fn != NULL)
            destroy_fn(n->data);
        free(n);
    }
}

ForwardList *forward_list_construct() {
    ForwardList *l = (ForwardList *) calloc(1, sizeof(ForwardList));
    if (l == NULL)
        exit(printf("Error: forward_list_construct: could not allocate memory.\n\n"));

    return l;
}

void forward_list_destroy(ForwardList *l, void (*destroy_fn)(data_type)) {
    Node *n = l->head;
    Node *aux;

    while(n != NULL) {
        aux = n->next;
        node_destroy(n, destroy_fn);
        n = aux;
    }
    free(l);
}

void forward_list_destroy_node(ForwardList *l) {
    Node *n = l->head;
    Node *aux;

    while(n != NULL) {
        aux = n->next;
        free(n);
        n = aux;
    }

    free(l);
}

int forward_list_size(ForwardList *l) {
    return l->size;
}

void forward_list_push_front(ForwardList *l, data_type data) {
    Node *n = node_construct(data, l->head);
    l->head = n;
    l->size++;
}

void forward_list_remove(ForwardList *l, data_type value, void (*destroy_fn)(data_type)) {
    Node *n = l->head;
    Node *aux;

    if (n == NULL)
        return;

    if (n->data == value) {
        l->head = n->next;
        if (destroy_fn != NULL)
            node_destroy(n, destroy_fn);
        else
            free(n);
        l->size--;
        return;
    }

    while(n->next != NULL) {
        if (n->next->data == value) {
            aux = n->next;
            n->next = aux->next;
            if (destroy_fn != NULL)
                node_destroy(aux, destroy_fn);
            else
                free(aux);
            l->size--;
            return;
        }
        n = n->next;
    }
}

// void forward_list_fprint(ForwardList *l, void (*fprint_fn)(data_type, FILE *), FILE *file) {

//     Node *n = l->head;

//     while(n != NULL) {
//         fprint_fn(n->data, file);
//         n = n->next;
//     }
// }

void forward_list_fprint_reverse(Node *n, void (*fprint_fn)(data_type, FILE *), FILE *file) {
    if (n != NULL) {
        forward_list_fprint_reverse(n->next, fprint_fn, file);
        fprint_fn(n->data, file);
    }
}

void forward_list_fprint(ForwardList *l, void (*fprint_fn)(data_type, FILE *), FILE *file) {
    forward_list_fprint_reverse(l->head, fprint_fn, file);
}

data_type forward_list_pop_front(ForwardList *l, void (*destroy_fn)(data_type)) {
    Node *n = l->head;
    data_type data_removed = n->data;
    l->head = n->next;
    node_destroy(n, destroy_fn);
    l->size--;
    return data_removed;
}

void forward_list_sort(ForwardList *l, int (*cmp_fn)(data_type, data_type)) {
    Node *n = l->head;
    Node *aux;
    data_type data;

    while(n != NULL) {
        aux = n->next;
        while(aux != NULL) {
            if (cmp_fn(n->data, aux->data) < 0) {
                data = n->data;
                n->data = aux->data;
                aux->data = data;
            }
            aux = aux->next;
        }
        n = n->next;
    }
}

data_type forward_list_get(ForwardList *l, data_type data, int (*cmp_fn)(data_type, data_type)) {
    Node *n = l->head;

    while(n != NULL) {
        if (cmp_fn(n->data, data) == 1)
            return n->data;
        n = n->next;
    }
    return NULL;
}

data_type forward_list_get_head_data(ForwardList *l) {
    return l->head->data;
}


struct ForwardListIterator{
    Node *current;
};

// Inicializa o iterador
ForwardListIterator *forward_list_iterator_init(ForwardList *l) {
    ForwardListIterator *iterator = (ForwardListIterator *) calloc(1, sizeof(ForwardListIterator));
    if (iterator == NULL)
        exit(printf("Error: forward_list_iterator_init: could not allocate memory.\n\n"));
    iterator->current = l->head;
    return iterator;
}

void forward_list_iterator_destroy(ForwardListIterator *iterator) {
    free(iterator);
}

int forward_list_iterator_has_next(ForwardListIterator *iterator) {
    return iterator->current != NULL;
}

data_type forward_list_iterator_get_data(ForwardListIterator *iterator) {
    return iterator->current->data;
}

void forward_list_iterator_next(ForwardListIterator *iterator) {
    iterator->current = iterator->current->next;
}