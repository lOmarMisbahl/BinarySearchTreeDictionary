#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct BSTNode {
    struct BSTNode* LEFT;
    struct BSTNode* RIGHT;
    char data[50];
} BSTNode;


BSTNode* newBSTNode(char  data[50]){
    BSTNode *Node = malloc(sizeof(BSTNode));
    strcpy(Node->data,data);
    Node->RIGHT=NULL;
    Node->LEFT=NULL;
    return Node;
}
int isEmpty(BSTNode* Root){
    return Root==NULL;
}

int Size(BSTNode* Root){
    return (Root==NULL) ? 0 : 1+Size(Root->LEFT)+Size(Root->RIGHT);
}

int Height(BSTNode* Root){
    return (Root==NULL) ? -1 : 1+MaxInt(Height(Root->LEFT),Height(Root->RIGHT));
}

int MaxInt (int a, int b){
    if(a>b)
        return a;
    else return b;
}

int isLeaf(BSTNode* Node){
return Node->LEFT==NULL && Node->RIGHT==NULL;
}

char* min(BSTNode* Root){
BSTNode* P = Root;
while(P->LEFT != NULL)
    P = P->LEFT;
return P->data;
}

char* Max(BSTNode* Root){
return (Root->RIGHT == NULL) ? Root->data : Max(Root->RIGHT);
}


char* Successor(BSTNode* Node , char data[]){
    if (Node == NULL)
        return data;
    else if (strcmp(data,Node->data) > 0)
        return Successor(Node->RIGHT, data);
    else if (strcmp(data,Node->data) == 0)
        return (Node->RIGHT == NULL) ? data : Successor(Node->RIGHT, data);
    else {
            char* temp = malloc(50*sizeof(char));
         strcpy(temp,Successor(Node->LEFT,data));
    return (strcmp(temp,data) == 0) ? Node->data : temp;
    }
}

char* Predecessor(BSTNode* Node , char data[]){
    if (Node == NULL)
        return data;
    else if (strcmp(data,Node->data) < 0)
        return Predecessor(Node->LEFT, data);
    else if (strcmp(data,Node->data) == 0)
        return (Node->LEFT == NULL) ? data : Predecessor(Node->LEFT, data);
    else {
            char* temp = malloc(50*sizeof(char));
         strcpy(temp,Predecessor(Node->RIGHT,data));
    return (strcmp(temp,data) == 0) ? Node->data : temp;
    }
}


int search(BSTNode* Node,BSTNode* Root,char data[]){

        if(strcmp(data, Node->data) == 0){
            printf("%s - Correct\n",data);
            return 1;
        }else if (strcmp(data, Node->data) < 0){
          if (Node->LEFT == NULL){
              printf("%s - %s, %s, %s\n",data,Node->data,Successor(Root,Node->data),Predecessor(Root,Node->data));
              return 0;
            }
            search(Node->LEFT,Root,data);
         }else if (strcmp(data, Node->data) > 0){
           if (Node->RIGHT == NULL){
               printf("%s - %s, %s, %s\n",data,Node->data,Successor(Root,Node->data),Predecessor(Root,Node->data));
               return 0;
             }
            search(Node->RIGHT,Root,data);
          }
    }

void destroy(BSTNode* Root){
if(Root != NULL){
    destroy(Root->LEFT);
    destroy(Root->RIGHT);
    free(Root);
}
}

BSTNode* insert(BSTNode * tree, char val[50])
{

    if(tree == NULL)
    {
        tree = newBSTNode(val);

    }

    if(strcmp(val,tree->data) < 0)
    {
        tree->LEFT = insert(tree->LEFT, val);
    }
    else if(strcmp(val,tree->data) > 0)
    {
        tree->RIGHT = insert(tree->RIGHT, val);
    }
    return tree;
}




int main()
{
    BSTNode *Root = NULL;
    char data[50];
    FILE *fp;
    fp = fopen ("Search.txt","r");
    if(!fp){
     printf("Error opening file\n" );
   }
    fscanf(fp,"%s",data);
    Root = insert(Root,data);
    while(!feof(fp)){
    fscanf(fp,"%s",data);
    insert(Root,data);
    }

    char str[80];
    const char s[2] = " ";
    char *token;
    int i = 0;

    printf("Enter The Sentence You Want To Check : ");
    scanf("%[^\n]s ",str);
   token = strtok(str, s);
   while( token != NULL ) {
   search(Root,Root,token);
    token = strtok(NULL, s);
   }

   return 0;
}
