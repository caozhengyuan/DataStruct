#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

typedef struct Node
{
    int32_t data;
    struct Node* left;
    struct Node* right;
} Node;

Node* root = NULL;

void Insert(int32_t data);
Node* InsertR(Node* root, int32_t data);
void Search(int32_t data);
bool SearchR(Node* root, int32_t data);
void Delete(int32_t data);

int main() {
    Insert(1);
    Insert(2);
    Insert(3);
    Search(2);
    return 0;
}

void Insert(int32_t data) {
    Node* temp1 = (Node*)malloc(sizeof(Node));
    temp1->data = data;
    temp1->left = NULL;
    temp1->right = NULL;
    Node* temp = root;
    if (root == NULL) {
        root = temp1;
        return;
    }
    while (1) {
    if (data <= temp->data && temp->left != NULL) {
        temp = temp->left;
    }
    if (data <= temp->data && temp->left == NULL) {
        temp->left = temp1;
        return;
    }
    if (data > temp->data && temp->right != NULL) {
        temp = temp->right;
    }
    if (data > temp->data && temp->right == NULL) {
        temp->right = temp1;
        return;
    }
    }
}

void Search(int32_t data) {
    Node* temp = root;
    if (root == NULL) {
        printf("There are no elements!\n");
        return;
    }
    while (temp != NULL) {
    if (data == temp->data) {
        printf("Have!\n");
        return;
    }
    else if (data < temp->data) {
        temp = temp->left;
    } 
    else {
        temp = temp->right;
    }
    }
    printf("Don't Have!\n");
}

Node* InsertR(Node* root, int32_t data) {
    if (root == NULL) {
        Node* temp = (Node*)malloc(sizeof(Node));
        temp->data = data;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    }
    if (data <= root->data) {
        root->left = InsertR(root->left, data);
    }
    else {
        root->right = InsertR(root->right, data);
    }
    return root;
}

bool SearchR(Node* root, int32_t data) {
    if (root == NULL) {
        return false;
    }
    if (data == root->data) {
        return true;
    }
    if (data < root->data) {
        return SearchR(root->left, data);
    }
    else {
        return SearchR(root->right, data);
    }
}
void Delete(int32_t data) {
}