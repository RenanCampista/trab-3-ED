#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"
#include "vector.h"

struct Node{
    key_type key;
    data_type data;
    Node *left;
    Node *right;
};

struct BinaryTree{
    Node *root;
    int size;
};


Node* _node_construct(key_type key, data_type value, Node *left, Node *right){
    Node *node = (Node*) calloc(1, sizeof(Node));
    if (node == NULL)
        exit(printf("Error: node_construct: could not allocate memory.\n"));
    
    node->key = key;
    node->data = value;
    node->left = left;
    node->right = right;
    
    return node;
}

BinaryTree* binary_tree_construct(){
    BinaryTree *tree = (BinaryTree*) calloc(1, sizeof(BinaryTree));
    if (tree == NULL)
        exit(printf("Error: binary_tree_construct: could not allocate memory.\n"));
    
    tree->root = NULL;
    tree->size = 0;
    
    return tree;
}

void _destroy_recursive(Node *node, void (*free_data)(data_type)) {
    if (node == NULL)
        return;

    _destroy_recursive(node->left, free_data);
    _destroy_recursive(node->right, free_data);

    if (free_data != NULL)
        free_data(node->data);
    free(node);
}

void _destroy_recursive_node(Node *node) {
    if (node == NULL)
        return;
        
    _destroy_recursive_node(node->left);
    _destroy_recursive_node(node->right);

    free(node->key);
    free(node);

}


void binary_tree_destroy(BinaryTree *tree, void (*free_data)(data_type)){
    _destroy_recursive(tree->root, free_data);
    free(tree);
}

void binary_tree_destroy_nodes(BinaryTree *tree){
    _destroy_recursive_node(tree->root);
    tree->root = NULL;
    tree->size = 0;
}

Node *_add_recursive(Node *node, key_type key, data_type value) {
    if (node == NULL)
        return _node_construct(key, value, NULL, NULL);
    if (strcmp(key, node->key) < 0)
        node->left = _add_recursive(node->left, key, value);
    else
        node->right = _add_recursive(node->right, key, value);
    return node;
}

void binary_tree_add(BinaryTree *tree, key_type key, data_type value){
    tree->root = _add_recursive(tree->root, key, value);
    tree->size++;
}

Node *_search_recursive(Node *node, key_type key) {
    if (node == NULL)
        return NULL;
    if (strcmp(key, node->key) == 0)
        return node;
    if (strcmp(key, node->key) < 0)
        return _search_recursive(node->left, key);
    else
        return _search_recursive(node->right, key);
}

data_type binary_tree_search(BinaryTree *tree, key_type key){
    Node *node = _search_recursive(tree->root, key);
    return node != NULL ? node->data : NULL;
}

Node *_remove_recursive(Node *node, key_type key) {
    if (node == NULL)
        return NULL;
    if (strcmp(key, node->key) < 0)
        node->left = _remove_recursive(node->left, key);
    else if (strcmp(key, node->key) > 0)
        node->right = _remove_recursive(node->right, key);
    else {
        if (node->left == NULL && node->right == NULL) {
            free(node);
            return NULL;
        }
        else if (node->left == NULL || node->right == NULL) {
            Node *temp;
            if (node->left == NULL)
                temp = node->right;
            else
                temp = node->left;
            free(node);
            return temp;
        }
        else {
            Node *temp = node->right;
            while (temp->left != NULL)
                temp = temp->left;
            node->key = temp->key;
            node->data = temp->data;
            node->right = _remove_recursive(node->right, temp->key);
        }
    }
    return node;
}

void binary_tree_remove(BinaryTree *tree, key_type key){
    tree->root = _remove_recursive(tree->root, key);
    tree->size--;
}

int binary_tree_size(BinaryTree *tree){
    return tree->size;
}

data_type binary_tree_get(BinaryTree *tree, key_type key){
    Node *node = _search_recursive(tree->root, key);
    return node != NULL ? node->data : NULL;
}

int binary_tree_contains_key(BinaryTree *tree, key_type key){
    return _search_recursive(tree->root, key) != NULL;
}

void _fprint_all_data_recursive(Node *node, void (*fprint)(data_type, FILE *), FILE *file) {
    if (node == NULL)
        return;
    _fprint_all_data_recursive(node->left, fprint, file);
    fprint(node->data, file);
    _fprint_all_data_recursive(node->right, fprint, file);
}

void binary_tree_fprint_all_data(BinaryTree *tree, void (*fprint)(data_type, FILE *), FILE *file){
    _fprint_all_data_recursive(tree->root, fprint, file);
}

void in_order_traversal(Node *node, Vector *data) {
    if (node == NULL) {
        return;
    }

    in_order_traversal(node->left, data);
    vector_push_back(data, node->data);
    in_order_traversal(node->right, data);
}

Vector *binary_tree_all_data(BinaryTree *tree) {
    Vector *data = vector_construct();
    in_order_traversal(tree->root, data);
    return data;
}