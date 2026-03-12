#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

#define MAX 20

typedef struct Node
{
    int32_t data;
    struct Node* left;
    struct Node* right;
} Node;


Node* queue[MAX];
int32_t front = -1;
int32_t rear = -1;
Node* root = NULL;

void Insert(int32_t data);
Node* InsertR(Node* root, int32_t data);
Node* Search(int32_t data);
bool SearchR(Node* root, int32_t data);
Node* Delete(Node* root, int32_t data);
int32_t Max(int32_t a, int32_t b);
int32_t FindHeight(Node* root);
Node* FindMin(Node* root);
Node* FindMax(Node* root);
void PreOrder(Node* root);
void InOrder(Node* root);
void PostOrder(Node* root);
void LevelOrder();
void Enqueue(Node* data);
void Dequeue();
Node* Front();
bool isFull();
bool isEmpty();
bool isBinarySearchTree(Node* root, int32_t min_value, int32_t max_value);
Node* GetSuccessor(Node* root, int32_t data);

int main() {
    Insert(9);
    Insert(2);
    Insert(3);
    Insert(8);
    Insert(16);
    Insert(4);
    Insert(12);
    Insert(7);
    root = Delete(root,4);
    Node* successor = GetSuccessor(root, 7);
    printf("%" PRId32 "\n", successor->data);
    bool check = isBinarySearchTree(root, INT32_MIN, INT32_MAX);
    if (check) {
        printf("this is binary search tree!\n");
    }
    else {
        printf("this is not binary search tree!\n");
    }
    InOrder(root);
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
        if (data <= temp->data) {
            if (temp->left == NULL) {
                temp->left = temp1;
                return;
            }
            temp = temp->left;
        }
        if (data > temp->data) {
            if (temp->right == NULL) {
                temp->right = temp1;
                return;
            }
            temp = temp->right;
        }
    }
}

Node* Search(int32_t data) {
    Node* temp = root;
    if (root == NULL) {
        printf("There are no elements!\n");
        return NULL;
    }
    while (temp != NULL) {
    if (data == temp->data) {
        printf("Have!\n");
        return temp;
    }
    else if (data < temp->data) {
        temp = temp->left;
    } 
    else {
        temp = temp->right;
    }
    }
    printf("Don't Have!\n");
    return NULL;
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

//左子树和右子树的最大高度加一就是这个根的高度
int32_t FindHeight(Node* root) {
    if (root == NULL) {
        return -1;
    }
    int32_t left_height = FindHeight(root->left);
    int32_t right_height = FindHeight(root->right);
    int32_t height = Max(left_height, right_height) + 1;
    return height;
}
Node* FindMin(Node* root) {
    if (root == NULL) {
        printf("There are no elements!\n");
        return NULL;
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}
Node* FindMax(Node* root) {
    if (root == NULL) {
        printf("There are no elements!\n");
        return NULL;
    }
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

int32_t Max(int32_t a, int32_t b) {
    return a >= b ? a : b;
}

//根左右
void PreOrder(Node* root) {
    if (root == NULL) {
        return;
    }
    printf("%" PRId32 "\n", root->data);
    PreOrder(root->left);
    PreOrder(root->right);
}
void InOrder(Node* root) {
    if (root == NULL) {
        return;
    }
    InOrder(root->left);
    printf("%" PRId32 "\n", root->data);
    InOrder(root->right);
}
void PostOrder(Node* root) {
    if (root == NULL) {
        return;
    }
    PostOrder(root->left);
    PostOrder(root->right);
    printf("%" PRId32 "\n", root->data);
}

void LevelOrder() {
    if (root == NULL) {
        return;
    }
    Enqueue(root);
    while (!isEmpty()) {
        Node* current = Front();
        if (current->left != NULL) {
            Enqueue(current->left);
        }
        if (current->right != NULL) {
            Enqueue(current->right);
        }
        printf("%" PRId32 "\n", current->data);
        Dequeue();
    }
}

void Enqueue(Node* data) {
    if (isEmpty()) {
        rear++;
        front++;
        queue[rear] = data;
        return;
    }
    if (isFull()) {
        printf("Queue is full\n");
        return;
    }
    rear++;
    rear = rear % MAX;
    queue[rear] = data;
}

void Dequeue() {
    if (isEmpty()) {
        printf("There are no elements!\n");
        return;
    }
    if (front == rear) {
        front = -1;
        rear = -1;
    }
    else {
        front++;
        front = front % MAX;
    }
}

bool isEmpty() {
    return front == -1;
}

bool isFull() {
    int32_t temp = (rear + 1) % MAX;
    if (temp == front) {
        return true;
    }
    return false;
}

Node* Front() {
    if (isEmpty()) {
        printf("Queue is empty!\n");
        return NULL;
    }
    return queue[front];
}

//min_value是负无穷 max_value是正无穷
bool isBinarySearchTree(Node* root, int32_t min_value, int32_t max_value) {
    if (root == NULL) {
        return true;
    }
    if (root->data > min_value && root->data < max_value
        && isBinarySearchTree(root->left, min_value, root->data) 
        && isBinarySearchTree(root->right, root->data, max_value)){
            return true;
        }
    else {
        return false;
    }
}

Node* Delete(Node* root, int32_t data) {
    if (root == NULL) {
        return NULL;
    }
    if (data < root->data) {
        root->left = Delete(root->left, data);
    }
    else if (data > root->data) {
        root->right = Delete(root->right, data);
    }
    //找到了
    else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        else if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        else {
            Node* temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            root->data = temp->data;
            root->right = Delete(root->right, temp->data);
            return root;
        }
    }
    return root;
}

Node* GetSuccessor(Node* root, int32_t data) {
    Node* current = Search(data);
    if (current == NULL) {
        return NULL;
    }
    if (current->right != NULL) {
        Node* successor = FindMin(current->right);
        return successor;
    }
    if (current->right == NULL) {
        Node* successor = NULL;
        while (root != current) {
            if (root->data > data) {
                successor = root;
                root = root->left;
            }
            else {
                root = root->right;
            }
        }
        return successor;
        }
        return NULL;
}