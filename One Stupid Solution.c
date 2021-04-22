#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Link_Node;
typedef struct Link_Node* PLink_Node;
struct Link_Node
{
    char info;
    int order;
    PLink_Node llink;
    PLink_Node rlink;
};
typedef struct Link_Node* Linklist;

Linklist Fun1 (char x, Linklist list, int order)
{
    if (list == NULL)
    {
        PLink_Node p;
        p = (PLink_Node)malloc(sizeof(struct Link_Node));
        p->info = x;
        p->order = order;
        list = p;
        p->llink = NULL;
        p->rlink = NULL;
    }
    else
    {
        PLink_Node q;
        q = list;
        while(1)
        {
            if (x > q->info && q->rlink != NULL)
            {
                if (x > q->rlink->info)
                {
                    q = q->rlink;
                }
                else//插入
                {
                    PLink_Node p;
                    p = (PLink_Node)malloc(sizeof(struct Link_Node));
                    p->info = x;
                    p->order = order;
                    p->rlink = q->rlink;
                    q->rlink->llink = p;
                    p->llink = q;
                    q->rlink = p;
                    break;
                }
            }
            else if (x > q->info && q->rlink == NULL)//插入
            {
                PLink_Node p;
                p = (PLink_Node)malloc(sizeof(struct Link_Node));
                p->info = x;
                p->order = order;
                q->rlink = p;
                p->llink = q;
                p->rlink = NULL;
                break;
            }
            else if (x < q->info)//移动头部位置
            {
                PLink_Node p;
                p = (PLink_Node)malloc(sizeof(struct Link_Node));
                p->info = x;
                p->order = order;
                q->llink = p;
                p->rlink = q;
                p->llink = NULL;
                list = p;
                break;
            }
        }
    }
    return list;    
}

struct TreeNode;
typedef struct TreeNode* PTreeNode;
struct TreeNode
{
    char info;
    PTreeNode llink;
    PTreeNode rlink;
};
typedef struct TreeNode* BinTree;
void preorder (PTreeNode t)
{
    if(t == NULL) return;
    printf ("%c", t->info);
    preorder (t->llink);
    preorder (t->rlink);
}
BinTree Create (void)
{
    BinTree btree;
    btree = NULL;
    return btree;
}
BinTree FindAndInsert (char x, BinTree btree, char target, int direction)//1代表左，2代表右
{
    PTreeNode p;
    p = (PTreeNode)malloc(sizeof(struct TreeNode));
    p->info = x;
    if (target == '@')//表示二叉树为空
    {
        btree = p;//会跑到这里来，但是不会插入新元素？
        p->llink = NULL;
        p->rlink = NULL;
    }
    else
    {
        PTreeNode q;
        q = btree;
        while (1)
        {
            if (target > q->info)
            {
                q = q->rlink;
            }
            else if (target < q->info)
            {
                q = q->llink;
            }
            else
            {
                break;
            }
        }
        if (direction == 1)
        {
            q->llink = p;
            p->llink = NULL;
            p->rlink = NULL;
        }
        else if (direction == 2)
        {
            q->rlink = p;
            p->llink = NULL;
            p->rlink = NULL;
        }
    }
    return btree;
}
void Fun2 (Linklist llist, char Start, int l, int r, BinTree btree, int max)//main里面找到开始第一个开始的
{
    PLink_Node start;
    start = llist;
    while (start->info != Start)
    {
        start = start->rlink;
    }
    //printf ("start->info...%c\n", start->info);
    PLink_Node q;
    int i;
    if (l == 0 && r == 0)
    {
        return;
    }
    else if (l != 0 && r == 0)
    {
        int r1 = -1,l1;
        PLink_Node lStart;
        lStart = start->llink;
        q = start;
        for (i=0;i<l;i++)
        {
            q = q->llink;
            if (q->order > lStart->order)
            {
                lStart = q;
            }
        }
        q = start;
        while (q != lStart)
        {
            q = q->llink;
            r1++;
        }
        l1 = l-r1-1;
        
        btree = FindAndInsert(lStart->info, btree, start->info, 1);
        
        Fun2 (llist, lStart->info, l1, r1, btree, max);
    }
    else if (l == 0 && r != 0)
    {
        int l2 = -1, r2;
        PLink_Node rStart;
        rStart = start->rlink;
        q = start;
        for (i=0;i<r;i++)
        {
            q = q->rlink;
            if (q->order > rStart->order)
            {
                rStart = q;
            }
        }
        q = start;
        while (q != rStart)
        {
            q = q->rlink;
            l2++;
        }
        r2 = r-l2-1;
        
        btree = FindAndInsert(rStart->info, btree, start->info, 2);
        
        Fun2 (llist, rStart->info, l2, r2, btree, max);
    }
    else if ( l != 0 && r != 0)
    {
        int r1 = -1,l1;
        PLink_Node lStart;
        lStart = start->llink;
        q = start;
        for (i=0;i<l;i++)
        {
            q = q->llink;
            if (q->order > lStart->order)
            {
                lStart = q;
            }
        }
        q = start;
        while (q != lStart)
        {
            q = q->llink;
            r1++;
        }
        l1 = l-r1-1;
        
        btree = FindAndInsert(lStart->info, btree, start->info, 1);
        //printf ("btree->llink->info...%c", btree->llink->info);
        //preorder(btree);
        //printf ("\n");
        Fun2 (llist, lStart->info, l1, r1, btree, max);
        
        int l2 = -1, r2;
        PLink_Node rStart;
        rStart = start->rlink;
        q = start;
        for (i=0;i<r;i++)
        {
            q = q->rlink;
            if (q->order > rStart->order)
            {
                rStart = q;
            }
        }
        q = start;
        while (q != rStart)
        {
            q = q->rlink;
            l2++;
        }
        r2 = r-l2-1;
        
        btree= FindAndInsert(rStart->info, btree, start->info, 2);
        //preorder (btree);
        //printf ("\n");
        Fun2 (llist, rStart->info, l2, r2, btree, max);
    }
}

void Write (PLink_Node list)
{
    PLink_Node p;
    p = list;
    while (p->rlink != NULL)
    {
        printf ("%c %d\n", p->info, p->order);
        p = p->rlink;
    }
    printf ("%c %d\n", p->info, p->order);
}
int main (void)
{
    /*char str[26];
    int ord = 0,len,i;
    Linklist list;
    BinTree btree;
    btree = Create();
    list = NULL;
    scanf ("%s", str);
    while (strcmp (str,"*") != 0)
    {
        ord++;
        len = strlen (str);
        for (i=0;i<len;i++)
        {
            list = Fun1 (str[i], list, ord);
        }
        scanf ("%s", str);
    }
    //Write (list);
    PLink_Node p,pre;
    int l=0,r=0;
    p = list;
    //printf ("p->info...%c\n",p->info);
    //printf ("ord...%d\n", ord);
    while(p->order != ord)
    {
        p = p->rlink;
        l++;
    }
    //printf ("p->info...%c\n", p->info);
    pre = p;
    while(p->rlink != NULL)
    {
        p = p->rlink;
        r++;
    }
    btree = (BinTree)malloc(sizeof(struct TreeNode));
    btree->info = pre->info;
    btree->llink = NULL;
    btree->rlink = NULL;
    //preorder (btree);
    //printf ("l...%d r...%d\n", l, r);
    Fun2 (list, pre->info, l, r, btree, ord);//这里还是越界了啊啊啊啊啊
    preorder (btree);
    printf ("\n");*/
    char str[26];
    scanf ("%s", str);
    while (1)
    {
        int ord = 0,len,i;
        Linklist list;
        BinTree btree;
        btree = Create ();
        list = NULL;
    
        while (strcmp (str,"*") != 0 && strcmp (str,"$") !=0 )
        {
            ord ++;
            len = strlen(str);
            for (i=0;i<len;i++)
            {
                list = Fun1(str[i], list, ord);
            }
            scanf ("%s", str);
        }
        PLink_Node p,pre;
        int l=0,r=0;
        p = list;
        while(p->order != ord)
        {
            p = p->rlink;
            l++;
        }
        pre = p;
        while (p->rlink != NULL)
        {
            p = p->rlink;
            r++;
        }
        btree = (BinTree)malloc(sizeof(struct TreeNode));
        btree->info = pre->info;
        btree->llink = NULL;
        btree->rlink = NULL;
        Fun2 (list, pre->info, l ,r, btree, ord);
        preorder (btree);
        printf ("\n");
        if (strcmp (str, "*") == 0)
        {
            scanf ("%s", str);
        }
        else if (strcmp(str, "$") == 0)
        {
            break;
        }
    }
    return 0;
}
