#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef enum
{
    RB_BLACK = 0,
    RB_RED = 1,
} rb_color;

typedef struct Node
{
    int32_t data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    rb_color color;
} Node;

Node *root;
Node *NIL;

void insert(int32_t data);
void LeftRotate(Node *g);
void RightRotate(Node *g);
Node *GetUncle(Node *node);
void Balance_RB_Tree(Node *node);
void init_nil();
void printTree(Node *node, int indent);
void delete(int32_t data);
Node *get_brother(Node *node);
void db_balance(Node* node);

// 1️⃣ 每个节点要么是 红色，要么是 黑色
// 2️⃣ 根节点必须是黑色
// 3️⃣ 所有叶子节点（NULL节点）是黑色
// （注意：叶子节点指的是空节点，不是最后的数据节点）
// 4️⃣ 红色节点不能有红色子节点
int main()
{
    init_nil();
    root = NIL;
    return 0;
}

void insert(int32_t data)
{
    Node *temp1 = (Node *)malloc(sizeof(Node));
    temp1->left = NIL;
    temp1->right = NIL;
    temp1->parent = NIL;
    temp1->data = data;
    temp1->color = RB_RED;
    Node *temp = root;
    if (root == NIL)
    {
        root = temp1;
        root->color = RB_BLACK;
        return;
    }
    while (temp != NIL)
    {
        if (data < temp->data)
        {
            if (temp->left == NIL)
            {
                temp->left = temp1;
                temp1->parent = temp;
                break;
            }
            temp = temp->left;
        }
        else
        {
            if (temp->right == NIL)
            {
                temp->right = temp1;
                temp1->parent = temp;
                break;
            }
            temp = temp->right;
        }
    }
    Balance_RB_Tree(temp1);
}

Node *GetUncle(Node *node)
{
    Node *parent = node->parent;
    Node *grand = parent->parent;
    if (parent == grand->left)
    {
        return grand->right;
    }
    else
    {
        return grand->left;
    }
}

void Balance_RB_Tree(Node *node)
{
    if (node == root)
    {
        node->color = RB_BLACK;
        return;
    }
    Node *g = node->parent->parent;
    Node *p = node->parent;
    if (p->color == RB_BLACK)
    {
        return;
    }
    else
    {
        if (GetUncle(node)->color == RB_RED)
        {
            g->color = RB_RED;
            p->color = RB_BLACK;
            GetUncle(node)->color = RB_BLACK;
            Balance_RB_Tree(g);
        }
        else
        {
            // L
            if (g->left == p)
            {
                // LR
                if (p->right == node)
                { // LR->LL
                    LeftRotate(p);
                    node = p;
                    p = node->parent;
                }
                // LL
                g->color = RB_RED;
                p->color = RB_BLACK;
                RightRotate(g);
            }
            else
            {
                if (p->left == node)
                {
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

void LeftRotate(Node *g)
{
    Node *p = g->right;
    g->right = p->left;
    if (p->left != NIL)
    {
        p->left->parent = g;
    }

    p->parent = g->parent;
    if (g->parent == NIL)
    {
        root = p;
    }
    else if (g->parent->left == g)
    {
        g->parent->left = p;
    }
    else
    {
        g->parent->right = p;
    }
    g->parent = p;
    p->left = g;
}
void RightRotate(Node *g)
{
    Node *p = g->left;
    g->left = p->right;
    if (p->right != NIL)
    {
        p->right->parent = g;
    }
    p->parent = g->parent;
    if (g->parent == NIL)
    {
        root = p;
    }
    else if (g->parent->left == g)
    {
        g->parent->left = p;
    }
    else
    {
        g->parent->right = p;
    }
    g->parent = p;
    p->right = g;
}

void init_nil()
{
    NIL = (Node *)malloc(sizeof(Node));
    NIL->color = RB_BLACK;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NIL;
    NIL->data = 0;
}

void printTree(Node *node, int indent)
{
    if (node == NIL)
        return;

    printTree(node->right, indent + 8); // 先打印右子树

    for (int i = 0; i < indent; i++)
        printf(" ");
    printf("%" PRId32 "(%s)\n", node->data, node->color == RB_RED ? "RED" : "BLK");

    printTree(node->left, indent + 8); // 后打印左子树
}

void delete(int32_t data)
{
    Node *node = root;
    if (node == NIL) // 树为空
    {
        printf("There are no elements!\n");
        return;
    }
    else // 树不为空
    {
        while (node != NIL) // 查找要删的节点
        {
            if (data < node->data)
            {
                node = node->left;
            }
            else if (data > node->data)
            {
                node = node->right;
            }
            else 
            {
                break;
            }
        }
        if (node == NIL) // 这颗树里没有要删的节点
        {
            printf("don't have this element!");
            return;
        }
        // 有要删除的节点
        if (node == root && node->left == NIL && node->right == NIL) //这个节点是没有左右子树的根节点
        {
            root = NIL;
            free(node);
            return;
        }
        if (node->left != NIL && node->right != NIL)   //有左右子树
        {
            Node* temp = node->right;
            while (temp->left != NIL) {     //寻找右子树中最小的节点即知道左子树为空位置
                temp = temp->left;
            }
            node->data = temp->data;
            node = temp;
        }
        if (node->left == NIL && node->right != NIL) // 只有右子树
        {
            node->right->color = RB_BLACK;
            if (node == root) {
                root = node->right;
                root->parent = NIL;
                free(node);
                return;
            }
            else if (node->parent->left == node)
            {
                node->parent->left = node->right;
                node->right->parent = node->parent;
                free(node);
                return;
            }
            else
            {
                node->parent->right = node->right;
                node->right->parent = node->parent;
                free(node);
                return;
            }
        }
        else if (node->right == NIL && node->left != NIL) // 只有左子树
        {
            node->left->color = RB_BLACK;
            if (node == root) {
                root = node->left;
                root->parent = NIL;
                free(node);
                return;
            }
            else if (node->parent->right == node)
            {
                node->parent->right = node->left;
                node->left->parent = node->parent;
                free(node);
                return;
            }
            else
            {
                node->parent->left = node->left;
                node->left->parent = node->parent;
                free(node);
                return;
            }
        }
        else if (node->left == NIL && node->right == NIL) // 要删除的节点没有左右子树
        {
            if (node->color == RB_RED) // 要删除的节点是红色
            {
                if (node->parent->left == node)
                {
                    node->parent->left = NIL;
                }
                else
                {
                    node->parent->right = NIL;
                }
                free(node);
                return;
            }
            else    //要删除的节点是黑色
            {
                Node* db = node;    //double black
                db_balance(db);
                if (node->parent->left == node)
                {
                    node->parent->left = NIL;
                }
                else 
                {
                    node->parent->right = NIL;
                }
                free(node);
                return;
            }
        }
    }
}
Node *get_brother(Node *node)
{
    return node->parent->left == node ? node->parent->right : node->parent->left;
}

void db_balance(Node *node)
{
    if (node == root)
    {
        node->color = RB_BLACK;
        return;
    }
    Node *bro = get_brother(node);
    Node *p = node->parent;
    if (p->left == bro)     //L
    {
        if (bro->color == RB_BLACK)     //兄弟节点是黑色
        {
            Node *s1 = bro->left;
            Node *s2 = bro->right;
            if (s1->color == RB_RED)    //LL
            {
                s1->color = bro->color;
                bro->color = p->color;
                p->color = RB_BLACK;
                RightRotate(p);
                return;
            }
            else if (s1->color == RB_BLACK && s2->color == RB_RED)      //LR
            {
                s2->color = p->color;
                p->color = RB_BLACK;
                LeftRotate(bro);
                RightRotate(p);
                return;
            }
            else if (s1->color == RB_BLACK && s2->color == RB_BLACK)      //兄弟的孩子都是黑色
            {
                bro->color = RB_RED;
                if (p == root) {    //如果父亲节点是根节点
                    p->color = RB_BLACK;
                    return;
                }
                else if (p->color == RB_BLACK)   //父节点是黑色
                {
                    db_balance(p);
                }
                else        //父节点是红色
                {
                    p->color = RB_BLACK;
                    return;
                }
            }
        }
        else    //兄弟是红色
        {
            bro->color = RB_BLACK;
            p->color = RB_RED;
            RightRotate(p);
            db_balance(node);
        }
    }
    else    //R
    {
        if (bro->color == RB_BLACK)
        {
            Node *s1 = bro->left;
            Node *s2 = bro->right;
            if (s2->color == RB_RED)
            {
                s2->color = bro->color;
                bro->color = p->color;
                p->color = RB_BLACK;
                LeftRotate(p);
                return;
            }
            else if (s2->color == RB_BLACK && s1->color == RB_RED)
            {
                s1->color = p->color;
                p->color = RB_BLACK;
                RightRotate(bro);
                LeftRotate(p);
                return;
            }
            else if (s2->color == RB_BLACK && s1->color == RB_BLACK)
            {
                bro->color = RB_RED;
                if (p->color == RB_BLACK)
                {
                    db_balance(p);
                }
                else
                {
                    p->color = RB_BLACK;
                    return;
                }
            }
        }
        else    //兄弟是红色
        {
            bro->color = RB_BLACK;
            p->color = RB_RED;
            LeftRotate(p);
            db_balance(node);
        }
    }
}