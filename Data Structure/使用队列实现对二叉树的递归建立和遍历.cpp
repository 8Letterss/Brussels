#include <stdio.h>
#include <stdlib.h>

typedef char DataType;
typedef struct BTreeNode
{
    DataType data;
    struct BTreeNode *leftchild;
    struct BTreeNode *rightchild;
}BinTreeNode;
typedef BinTreeNode *BinTree;

typedef BinTreeNode *DataTypeQueue;
struct Node
{
    DataTypeQueue data;
    struct Node    *next;
};
typedef struct Node *PNode;
struct Queue
{
    PNode        f;
    PNode        r;
};
typedef struct Queue *LinkQueue;

LinkQueue  SetNullQueue_Link()
{
    LinkQueue lqueue;
    lqueue = (LinkQueue)malloc(sizeof(struct Queue));
    if (lqueue != NULL)
    {
        lqueue->f = NULL;
        lqueue->r = NULL;
    }
    else
        printf("Alloc failure! \n");
    return  lqueue;
}

int IsNullQueue_Link(LinkQueue lqueue) 
{
    return (lqueue->f == NULL);
}

void EnQueue_link(LinkQueue lqueue, DataTypeQueue x) 
{
    PNode  p;
    p = (PNode)malloc(sizeof(struct Node));
    if (p == NULL)
        printf("Alloc failure!");
    else{
        p->data = x;
        p->next = NULL;
        if (lqueue->f == NULL)
        {
            lqueue->f = p;
            lqueue->r = p;
        }
        else
        {
            lqueue->r->next = p;
            lqueue->r = p;
        }
    }
}
void DeQueue_link(LinkQueue lqueue) 
{
    struct Node  * p;
    if (lqueue->f == NULL)
        printf("It is empty queue!\n ");
    else
    {
        p = lqueue->f;
        lqueue->f = lqueue->f->next;
        free(p);
    }
}
DataTypeQueue  FrontQueue_link(LinkQueue lqueue) 
{
    if (lqueue->f == NULL)
    {
        printf("It is empty queue!\n");
        return 0;
    }
    else
        return (lqueue->f->data);
}

BinTree CreateBinTree_NRecursion()
{
    LinkQueue queue = SetNullQueue_Link();
    BinTreeNode *s, *p, *bt;
    char ch; int count = -1;
    ch = getchar();
    bt = NULL;
    while (ch != '#'){
        s = NULL;
        if (ch != '@'){
            s = (BinTreeNode *)malloc(sizeof(BinTreeNode));
            s->data = ch; s->leftchild = s->rightchild = NULL;
        }
        EnQueue_link(queue,s);
        count++;
        if (count == 0)
            bt=s;
        else
        {
            p = FrontQueue_link(queue);
            if (s != NULL && p != NULL)
                if (count % 2 == 1)
                    p->leftchild=s;
                else p->rightchild=s;
            if (count % 2 == 0)
                DeQueue_link(queue);
        }
        ch = getchar();
    }
    return bt;
}

void LevelOrder(BinTree bt)
{
    BinTree p;
    LinkQueue queue = SetNullQueue_Link();
    if (bt == NULL) return;
    p = bt;
    EnQueue_link(queue,bt);
    while (!IsNullQueue_Link(queue))
    {
        p = FrontQueue_link(queue);
        DeQueue_link(queue);
        printf("%c ", p->data);
        if (p->leftchild != NULL)
            EnQueue_link(queue, p->leftchild);
        if (p->rightchild != NULL)
            EnQueue_link(queue, p->rightchild);
    }
}

int main()
{
    BinTreeNode *bt;
    bt = CreateBinTree_NRecursion();
    LevelOrder(bt);
    return 0;
}
