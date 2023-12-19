#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "forward_list.h"

struct Pair {
    data_type key;
    data_type val;
};

struct HashTable {
    ForwardList **buckets;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int table_size;
    int n_elements;
};


Pair *_hash_pair_construct(data_type key, data_type val) {
    Pair *pair = (Pair *)calloc(1, sizeof(Pair));
    if (pair == NULL)
        exit(printf("Error: _hash_pair_construct: could not allocate memory.\n\n"));
    pair->key = key;
    pair->val = val;
    return pair;
}

void _hash_pair_destroy(Pair *pair, void (*free_data)(data_type)) {
   // free(pair->key);
    if (free_data != NULL)
        free_data(pair->val);
    free(pair);
}

void _hash_pair_destroy_node(Pair *pair) {
    free(pair->val);
    free(pair);
}


data_type _hash_pair_get_item(Pair *item) {
    return item != NULL ? item->val : NULL;
}

HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn) {
    HashTable *ht = (HashTable *)calloc(1, sizeof(HashTable));
    if (ht == NULL)
        exit(printf("Error: hash_table_construct: could not allocate memory.\n\n"));

    ht->table_size = table_size;
    ht->hash_fn = hash_fn;
    ht->cmp_fn = cmp_fn;
    ht->buckets = (ForwardList **)calloc(table_size, sizeof(ForwardList *));
    ht->n_elements = 0;
    
    if (ht->buckets == NULL)
        exit(printf("Error: hash_table_construct: could not allocate memory.\n\n"));

    return ht;
}

void hash_table_destroy_buckets(HashTable *h) {
    for (int i = 0; i < h->table_size; i++) {
        if (h->buckets[i] != NULL) {
            forward_list_destroy(h->buckets[i], (data_type)_hash_pair_destroy);
        }
    }
    free(h->buckets);
    free(h);
}

void hash_table_destroy(HashTable *h, void (*free_data)(data_type)) {
    for (int i = 0; i < h->table_size; i++) {
        if (h->buckets[i] != NULL) {
            ForwardListIterator *it = forward_list_iterator_init(h->buckets[i]);
            while (forward_list_iterator_has_next(it)) {
                Pair *pair = (Pair *)forward_list_iterator_get_data(it);
                _hash_pair_destroy(pair, free_data);
                forward_list_iterator_next(it);
            }
            forward_list_iterator_destroy(it);
            forward_list_destroy(h->buckets[i], NULL);
        }
    }
    free(h->buckets);
    free(h);
}

int hash_table_size(HashTable *h) {
    return h->n_elements;
}

int hash_table_get_table_size(HashTable *h) {
    return h->table_size;
}

void hash_table_insert(HashTable *h, data_type key, data_type val) {  
    int hash = h->hash_fn(h, key);
    if (hash < 0 || hash >= h->table_size) 
        exit(printf("Error: hash_table_insert: hash function returned invalid value. (%d)\n\n", hash));

    if (h->buckets[hash] == NULL) 
        h->buckets[hash] = forward_list_construct();
    
    Pair *pair = _hash_pair_construct(key, val);
    forward_list_push_front(h->buckets[hash], pair);
    h->n_elements++;
}

int hash_table_contains_key(HashTable *h, data_type key) {
    int hash = h->hash_fn(h, key);
    
    if (hash < 0 || hash >= h->table_size) 
        exit(printf("Error: hash_table_contains_key: hash function returned invalid value. (%d)\n\n", hash));
    if (h->buckets[hash] == NULL) 
        return 0;
    return forward_list_get(h->buckets[hash], key, h->cmp_fn) != NULL;
}

Pair *hash_table_get(HashTable *h, data_type key) {
    int hash = h->hash_fn(h, key);
    if (hash < 0 || hash >= h->table_size) 
        exit(printf("Error: hash_table_get: hash function returned invalid value. (%d)\n\n", hash));

    if (h->buckets[hash] == NULL) 
        return NULL;

    return (Pair *)forward_list_get(h->buckets[hash], key, h->cmp_fn);
}

void hash_table_fprint_all_data(HashTable *h, void (*fprint_fn)(data_type, FILE *), FILE *file) {
    for (int i = 0; i < h->table_size; i++) {
        if (h->buckets[i] != NULL) {
            ForwardListIterator *it = forward_list_iterator_init(h->buckets[i]);
            while (forward_list_iterator_has_next(it)) {
                Pair *pair = (Pair *)forward_list_iterator_get_data(it);
                fprint_fn(pair->val, file);
                forward_list_iterator_next(it);
            }
            forward_list_iterator_destroy(it);
        }

    }
}

void push_pairs(ForwardList *bucket, Vector *pairs) {
    ForwardListIterator *it = forward_list_iterator_init(bucket);
    while (forward_list_iterator_has_next(it)) {
        Pair *pair = forward_list_iterator_get_data(it);
        vector_push_back(pairs, pair);
        forward_list_iterator_next(it);
    }

    forward_list_iterator_destroy(it);
}

Vector *hash_table_all_pairs(HashTable *h) {
    Vector *pairs = vector_construct();
    for (int i = 0; i < h->table_size; i++) {
        ForwardList *bucket = h->buckets[i];
        if (bucket != NULL) {
            push_pairs(bucket, pairs);
        }
    }

    return pairs;
}
