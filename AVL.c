#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

typedef struct Node
{
    int32_t data;
    int32_t height;
    struct Node* left;
    struct Node* right;
} Node;

Node* root;
int32_t top = -1;
Node* stack[100];

void Push(Node* root);
void Pop();
Node* Top();
void Insert(int32_t data);
void Delete(Node* root, int32_t data);
void InOrder(Node* root);
int32_t BalanceFactor(Node* root);
int32_t SetHeight(Node* root);
int32_t Max(int32_t a, int32_t b);
Node* RightRotate(Node* imbalanced);
Node* LeftRotate(Node* imbalanced);
void CheckAVL(Node* root);
int32_t Height(Node* root);
void PrintTree(Node* root, int space);
void Balance();

int main() {
    int a[] = {50,30,70,20,40,60,80};

    for(int i=0;i<7;i++)
        Insert(a[i]);

    printf("Initial tree:\n");
    PrintTree(root, 0);

    printf("\nDelete 50\n");

    Delete(root, 50);
    CheckAVL(root);

    PrintTree(root, 0);
    return 0;
}

void Delete(Node* root1, int32_t data) {
    top = -1;
    if (root1 == NULL) {
        return;
    }
    else if (root1->data == data) {
        if (root1->right == NULL && root1->left == NULL) {
            free(root1);
            root = NULL;
            return;
        }
        else if (root1->right == NULL) {
            root = root1->left;
            free(root1);
            return;
        }
        else if (root1->left == NULL) {
            root = root1->right;
            free(root1);
            return;
        }
        //有两个字节点的话 相当于删除右子树中的最小值 所以会转到else部分
    }
    while (root1 != NULL && root1->data != data) {
        Push(root1);
        if (root1->data < data) {
            root1 = root1->right;
        }
        else if (root1->data > data) {
            root1 = root1->left;
        }
    }
    if (root1 == NULL) {
            printf("failed to delete!\n");
            return;
        }
    if (root1->left == NULL && root1->right == NULL) {
        if (Top()->left == root1) {
            Top()->left = NULL;
        }
        else {
            Top()->right = NULL;
        }
        free(root1);
    }
    else if (root1->left == NULL) {
        if (Top()->right == root1) {
            Top()->right = root1->right;
        }
        else if (Top()->left == root1) {
            Top()->left = root1->right;
        }
        free(root1);
    }
    else if (root1->right == NULL) {
        if (Top()->left == root1) {
            Top()->left = root1->left;
        }
        else if (Top()->right == root1) {
            Top()->right = root1->left;
        }
        free(root1);
    }
    else {
        Push(root1);
        Node* temp = root1->right;
        while (temp->left != NULL){
            Push(temp);
            temp = temp->left;
        }
        root1->data = temp->data;
        Node* right = temp->right;
        if (Top()->left == temp) {
            Top()->left = right;
        }
        else {
            Top()->right = right;
        }
        free(temp);
    }
    Balance();
}

void Insert(int32_t data) {
    top = -1;
    Node* temp1 = (Node*)malloc(sizeof(Node));
    temp1->data = data;
    temp1->height = 0;
    temp1->left = NULL;
    temp1->right = NULL;
    Node* temp = root;
    if (root == NULL) {
        root = temp1;
        return;
    }
    while (1) {
        if (data < temp->data) {
            Push(temp);
            if (temp->left == NULL) {
                temp->left = temp1;
                break;
            }
            temp = temp->left;
        }
        else if (data > temp->data) {
            Push(temp);
            if (temp->right == NULL) {
                temp->right = temp1;
                break;
            }
            temp = temp->right;
        }
    }
    Balance();
}

int32_t SetHeight(Node* root) {
    return Max(Height(root->left), Height(root->right)) + 1;
}

int32_t BalanceFactor(Node* root) {
    return Height(root->left) - Height(root->right);
}

int32_t Max(int32_t a, int32_t b) {
    return a >= b ? a : b;
}

Node* RightRotate(Node* imbalanced) {
    Node* imbalancedLR = imbalanced->left->right;
    Node* imbalancedL = imbalanced->left;
    imbalancedL->right = imbalanced;
    imbalanced->left = imbalancedLR;
    imbalanced->height = SetHeight(imbalanced);
    imbalancedL->height = SetHeight(imbalancedL);
    return imbalancedL;
}

Node* LeftRotate(Node* imbalanced) {
    Node* imbalancedRL = imbalanced->right->left;
    Node* imbalancedR = imbalanced->right;
    imbalancedR->left = imbalanced;
    imbalanced->right = imbalancedRL;
    imbalanced->height = SetHeight(imbalanced);
    imbalancedR->height = SetHeight(imbalancedR);
    return imbalancedR;
}

void Push(Node* root) {
    top++;
    stack[top] = root;
}

void Pop() {
    if (top == -1) {
        printf("Error");
        return;
    }
    top--;
}

Node* Top() {
    return stack[top];
}

void InOrder(Node* root) {
    if (root == NULL) {
        return;
    }
    InOrder(root->left);
    printf("%" PRId32 "\n", root->data);
    InOrder(root->right);
}

void CheckAVL(Node* root)
{
    if(root == NULL) return;

    int bf = BalanceFactor(root);

    if(bf > 1 || bf < -1)
    {
        printf("AVL violated at %" PRId32 "\n", root->data);
    }

    CheckAVL(root->left);
    CheckAVL(root->right);
}

int32_t Height(Node* root) {
    if (root == NULL) {
        return -1;
    }
    return root->height;
}

// 这里的 space 是缩进量，通常初始调用传入 0 AI写的
void PrintTree(Node* root, int space) {
    // 基础情况：空节点
    if (root == NULL) return;

    // 每次增加缩进距离
    space += 10;

    // 先处理右子树（打印在上方）
    PrintTree(root->right, space);

    // 打印当前节点
    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    // 打印数据和该节点的高度(H)
    printf("%" PRId32 "(H:%" PRId32 ")\n", root->data, root->height);

    // 再处理左子树（打印在下方）
    PrintTree(root->left, space);
}

void Balance() {
    while (top != -1) {
        Top()->height = SetHeight(Top());
        //LL 右旋
        if (BalanceFactor(Top()) == 2 && BalanceFactor(Top()->left) >= 0) {
            Node* imbalanced = Top();
            Pop();
            if (top == -1) {
                root = RightRotate(imbalanced);
            }
            else if (Top()->right == imbalanced) {
                Top()->right = RightRotate(imbalanced);
            }
            else {
                Top()->left = RightRotate(imbalanced);
            }
        }
        //LR 左旋左子节点右旋
        else if (BalanceFactor(Top()) == 2 && BalanceFactor(Top()->left) == -1) {
            Node* imbalanced = Top();
            Pop();
            imbalanced->left = LeftRotate(imbalanced->left);
            if (top == -1) {
                root = RightRotate(imbalanced);
            }
            else if (Top()->right == imbalanced) {
                Top()->right = RightRotate(imbalanced);
            }
            else {
                Top()->left = RightRotate(imbalanced);
            }
        }
        //RR 左旋
        else if (BalanceFactor(Top()) == -2 && BalanceFactor(Top()->right) <= 0) {
            Node* imbalanced = Top();
            Pop();
            if (top == -1) {
                root = LeftRotate(imbalanced);
            }
            else if (Top()->right == imbalanced) {
                Top()->right = LeftRotate(imbalanced);
            }
            else {
                Top()->left = LeftRotate(imbalanced);
            }
        }
        //RL
        else if (BalanceFactor(Top()) == -2 && BalanceFactor(Top()->right) == 1) {
            Node* imbalanced = Top();
            Pop();
            imbalanced->right = RightRotate(imbalanced->right);
            if (top == -1) {
                root = LeftRotate(imbalanced);
            }
            else if (Top()->right == imbalanced) {
                Top()->right = LeftRotate(imbalanced);
            }
            else {
                Top()->left = LeftRotate(imbalanced);
            }
        }
        //无失衡
        else {
            Pop();
        }
    }
}