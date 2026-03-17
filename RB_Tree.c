#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef enum {
    RB_BLACK = 0,
    RB_RED = 1,
} rb_color;

typedef struct Node {
    int32_t data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    rb_color color;
} Node;

Node* root;
Node* NIL;

void insert(int32_t data);
void LeftRotate(Node* g);
void RightRotate(Node* g);
Node* GetUncle(Node* node);
void Balance_RB_Tree(Node* node);
void init_nil();
void printTree(Node* node, int indent);


//1️⃣ 每个节点要么是 红色，要么是 黑色
//2️⃣ 根节点必须是黑色
//3️⃣ 所有叶子节点（NULL节点）是黑色
//（注意：叶子节点指的是空节点，不是最后的数据节点）
//4️⃣ 红色节点不能有红色子节点
int main() {
    init_nil();
    root = NIL;
    int32_t vals[] = {10, 20, 30, 15, 25, 5, 1};
    int n = sizeof(vals) / sizeof(vals[0]);

    printf("--- 开始插入数据 ---\n");
    for (int i = 0; i < n; i++) {
        printf("插入: %d\n", vals[i]);
        insert(vals[i]);
    }

    printf("\n--- 最终红黑树结构 (旋转90度) ---\n");
    printTree(root, 0);

    return 0;
}

void insert(int32_t data) {
    Node* temp1 = (Node*)malloc(sizeof(Node));
    temp1->left = NIL;
    temp1->right = NIL;
    temp1->parent = NIL;
    temp1->data = data;
    temp1->color = RB_RED;
    Node* temp = root;
    if (root == NIL) {
        root = temp1;
        root->color = RB_BLACK;
        return;
    }
    while(temp != NIL) {
        if (data < temp->data) {
            if (temp->left == NIL) {
                temp->left = temp1;
                temp1->parent = temp;
                break;
            }
            temp = temp->left;
        }
        else {
            if (temp->right == NIL) {
                temp->right = temp1;
                temp1->parent = temp;
                break;
            }
            temp = temp->right;
    }
}
    Balance_RB_Tree(temp1);
}

Node* GetUncle(Node* node) {
    Node* parent = node->parent;
    Node* grand = parent->parent;
    if (parent == grand->left) {
        return grand->right;
    }
    else {
        return grand->left;
    }
}


void Balance_RB_Tree(Node* node) {
    if (node == root) {
        node->color = RB_BLACK;
        return;
    }
    Node* g = node->parent->parent;
    Node* p = node->parent;
    if (p->color == RB_BLACK) {
        return;
    }
    else {
        if (GetUncle(node)->color == RB_RED) {
        g->color = RB_RED;
        p->color = RB_BLACK;
        GetUncle(node)->color = RB_BLACK;
        Balance_RB_Tree(g);
    } else {
        //L
        if (g->left == p) {
            //LR
            if (p->right == node) { //LR->LL
                LeftRotate(p);
                node = p;
                p = node->parent;
            }
            //LL
            g->color = RB_RED;
            p->color = RB_BLACK;
            RightRotate(g);
        }
        else {
            if (p->left == node) {
                RightRotate(p);
                node = p;
                p = node->parent;
            }
            g->color = RB_RED;
            p->color = RB_BLACK;
            LeftRotate(g);
        }
    }
}
}

void LeftRotate(Node* g) {
    Node* p = g->right;
    g->right = p->left;
    if (p->left != NIL) {
        p->left->parent = g;
    }

    p->parent = g->parent;
    if (g->parent == NIL) {
        root = p;
    }
    else if (g->parent->left == g) {
        g->parent->left = p;
    }
    else {
        g->parent->right = p;
        }
    g->parent = p;
    p->left = g;
}
void RightRotate(Node* g) {
    Node* p = g->left;
    g->left = p->right;
    if (p->right != NIL) {
        p->right->parent = g;
    }
    p->parent = g->parent;
    if (g->parent == NIL) {
        root = p;
    }
    else if (g->parent->left == g) {
        g->parent->left = p;
    }
    else {
        g->parent->right = p;
    }
    g->parent = p;
    p->right = g;
}

void init_nil() {
    NIL = (Node*)malloc(sizeof(Node));
    NIL->color = RB_BLACK;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NIL;
    NIL->data = 0;
}

void printTree(Node* node, int indent) {
    if (node == NIL) return;

    printTree(node->right, indent + 8); // 先打印右子树

    for (int i = 0; i < indent; i++) printf(" ");
    printf("%" PRId32 "(%s)\n", node->data, node->color == RB_RED ? "RED" : "BLK");

    printTree(node->left, indent + 8); // 后打印左子树
}