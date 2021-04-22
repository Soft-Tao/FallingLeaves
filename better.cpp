#include<iostream>
#include<cstring>
#include<string>
#include<iomanip>
#include<algorithm>
#include<queue>
using namespace std;

struct Node
{
 char info;
 Node* llink, *rlink;
};

void InsertNum(char num,Node* p)
{
 if (num < p->info)
 {
  if(p->llink!=NULL)
   InsertNum(num, p->llink);
  else
  {
   p->llink = new Node;
   p->llink->info = num;
   p->llink->llink = NULL;
   p->llink->rlink = NULL;
  }
 }
 else if(num>p->info)
 {
  if(p->rlink!=NULL)
   InsertNum(num, p->rlink);
  else
  {
   p->rlink = new Node;
   p->rlink->info = num;
   p->rlink->llink = NULL;
   p->rlink->rlink = NULL;
  }
 }
}

void visit(Node* p)
{
 cout << p->info;
 if (p->llink != NULL)
  visit(p->llink);
 if (p->rlink != NULL)
  visit(p->rlink);
}

int main()
{
 while (1)
 {
  char abc[8][20];
  int i = 0, j = 0,NumOfLine=0;
  int flag = 1;
  while (cin >> abc[i])
  {
   if (abc[i][0] == '*')
    break;
   if (abc[i][0] == '$')
   {
    flag = 0;
    break;
   }
   i++;
  }
  Node* p = new Node;
  i--;
  if (i >=0)
  {
   p->info = abc[i][0];
   p->llink = NULL;
   p->rlink = NULL;
  }
  while (i--)
  {
   for (j = 0; abc[i][j] != '\0'; j++)
   {
    InsertNum(abc[i][j], p);
   }
  }
  visit(p);
  if (!flag)
   break;
  cout << endl;
 }
 return 0;
}
