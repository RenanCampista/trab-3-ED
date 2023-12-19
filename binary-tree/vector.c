
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

static const int VECTOR_INIT_SIZE = 10;
static const int VECTOR_GROWTH_RATE = 2;

struct Vector {
    data_type *data;
    int size;
    int allocated;
};

Vector *vector_construct() {
    Vector *v = (Vector *)calloc(1, sizeof(Vector));
    if (v == NULL)
        exit(printf("Error: vector_construct: could not allocate memory.\n"));
        
    v->allocated = VECTOR_INIT_SIZE;
    v->size = 0;
    v->data = (data_type *)calloc(VECTOR_INIT_SIZE, sizeof(data_type));

    return v;
}

int vector_size(Vector *v) {
    return v->size;
}

data_type vector_get(Vector *v, int i) {
    if (i >= vector_size(v) || i < 0)
        exit(printf("Error: vector_get: invalid index %d for vector with size %d.\n", i, vector_size(v)));
    return v->data[i];
}

void vector_set(Vector *v, int i, data_type val) {
    if (i >= vector_size(v))
        exit(printf("Error: vector_set: invalid index %d for vector with size %d.\n", i, vector_size(v)));
    v->data[i] = val;
}

void vector_push_back(Vector *v, data_type val) {
    if (v->size >= v->allocated) {
        v->allocated *= VECTOR_GROWTH_RATE;
        v->data = (data_type *)realloc(v->data, v->allocated * sizeof(data_type));
    }

    v->data[v->size] = val;
    v->size++;
}

data_type vector_remove(Vector *v, int i) {
    if (i >= v->size || i < 0)
        exit(printf("Error: vector_remove: invalid index %d for vector with size %d.\n", i, v->size));

    data_type val = v->data[i];

    for (int j = i; j < v->size - 1; j++)
        v->data[j] = v->data[j + 1];

    v->size--;
    return val;
}

data_type vector_pop_front(Vector *v) {
    return vector_remove(v, 0);
}

data_type vector_pop_back(Vector *v) {
    return vector_remove(v, v->size - 1);
}

void vector_insert(Vector *v, int i, data_type val) {
    if (i < 0 || i > v->size)
        exit(printf("Error: vector_insert: invalid index %d for vector with size %d.\n", i, v->size));
    
    if (v->size == v->allocated) {
        v->allocated *= 2;
        v->data = (data_type *)realloc(v->data, v->allocated * sizeof(data_type));
    }

    for (int j = v->size; j > i; j--)
        v->data[j] = v->data[j - 1];

    v->data[i] = val;
    v->size++;
}

void vector_swap(Vector *v, int i, int j) {
    if (i < 0 || i >= v->size || j < 0 || j >= v->size)
        exit(printf("Error: vector_swap: invalid indices %d and %d for vector with size %d.\n", i, j, v->size));

    data_type temp = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = temp;
}

void vector_sort(Vector *v) {
    for (int i = 0; i < v->size - 1; i++) {
        int n_trocas = 0;
        for (int j = 0; j < v->size - i - 1; j++) {
            if (v->data[j] > v->data[j + 1]) {
                vector_swap(v, j, j + 1);
                n_trocas++;
            }
        }
        if (n_trocas == 0)
            break;
    }
}

int vector_binary_search(Vector *v, data_type val) {
    int left = 0;
    int right = v->size - 1;

    while (left <= right){
        int mid = left + (right - left) / 2;

        if (v->data[mid] == val)
            return mid;
        else if (v->data[mid] < val)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

void vector_reverse(Vector *v) {
    for (int i = 0; i < v->size / 2; i++)
        vector_swap(v, i, v->size - i - 1);
}

Vector *vector_copy(Vector *v) {
    Vector *copy = (Vector *)malloc(sizeof(Vector));

    copy->data = (data_type *)malloc(v->allocated * sizeof(data_type));
    copy->size = v->size;
    copy->allocated = v->allocated;

    memcpy(copy->data, v->data, v->size * sizeof(data_type));

    return copy;
}

int vector_find(Vector *v, data_type val, int (*cmp)(data_type, data_type)) {
    int i = 0;
    while (i < vector_size(v))
    {
        if (!cmp(vector_get(v, i), val))
            return i;
        i++;
    }

    return -1;
}

Vector *vector_unique(Vector *v, int (*cmp)(data_type, data_type)) {
    Vector *output = vector_construct();

    for (int i = 0; i < vector_size(v); i++)
        if (vector_find(output, vector_get(v, i), cmp) == -1)
            vector_push_back(output, v->data[i]);

    return output;
}

void vector_destroy(Vector *v) {
    free(v->data);
    free(v);
}

void vector_clear(Vector *v) {
    v->size = 0;
}