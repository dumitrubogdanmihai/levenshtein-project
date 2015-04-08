#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct list_node {
    struct list_node *next;
    struct list_node *prev;
    char *word;
} ListNode;

typedef struct list {
    struct list_node *head;
} List;

ListNode* listSearch(List *l,char *k);
void listInsert(List *l, ListNode *x);
void listRemove(List *l, ListNode *x);
void printList(List l);

#endif // LIST_H_INCLUDED
