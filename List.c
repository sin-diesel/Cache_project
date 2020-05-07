#include "List.h"

static struct node_t* Create_Node();

struct list_t* Init_List(int size, struct hash_table* hashTable)
{
    assert(hashTable);
    struct node_t* top = NULL;
    struct node_t* tmp = NULL;
    struct list_t* list = (struct list_t*)calloc(1, sizeof(struct list_t));
    assert(list);
    if (size == 0)
        return list;
    top = Create_Node();
    list->front_elem = top;
    list->size = size;
    tmp = top;
    for (int i = 1; i < size; ++i)
    {
        tmp->next = Create_Node();
        tmp->next->page = i;
        tmp->next->prev = tmp;
        tmp = tmp->next;
    }
    list->back_elem = tmp;
    list->hashTable = hashTable;
    assert(list->back_elem);
    return list;
}

struct node_t* Front_Elem(struct list_t* list)
{
    assert(list);
    return list->front_elem;
}

struct node_t* Back_Elem(struct list_t* list)
{
    assert(list);
    return list->back_elem;
}

char Is_Empty (struct list_t* list)
{
    assert(list);
    if (list->size == 0 && list->front_elem == NULL && list->back_elem == NULL)
        return 1;
    if (list->size == 0 && (list->front_elem != NULL || list->back_elem != NULL))
    {
        printf("ERROR : list size");
        exit(1);
    }
    return 0;
}

size_t Size_List (struct list_t* list)
{
    assert(list);
    return list->size;
}

void Push_Back(struct list_t* list, int page)
{
    if (Is_Empty(list))
    {
        printf("ERROR: list void");
        exit(2);
    }
    struct node_t* old_back = NULL;
    struct node_t* new_back = NULL;
    if (list->size == 1)
    {
        list->back_elem->page = page;
        return;
    }
    old_back = list->back_elem;
    new_back = list->front_elem;

    hash_delete_elem(new_back->page, list->hashTable);

    list->front_elem = list->front_elem->next;
    list->front_elem->prev = NULL;

    new_back->page = page;
    new_back->prev = old_back;
    new_back->next = NULL;

    old_back->next = new_back;
    list->back_elem = new_back;

    hash_add_elem(page, list->hashTable, list->back_elem);
}

void Push_Front(struct list_t* list, int page)
{
    Print_List_Back(list);
    if (Is_Empty(list))
    {
        printf("ERROR: list void");
        exit(3);
    }
    struct node_t* old_front = NULL;
    struct node_t* new_front = NULL;
    if (list->size == 1)
    {
        list->back_elem->page = page;
        return;
    }
    old_front = list->front_elem;
    new_front = list->back_elem;

    hash_delete_elem(new_front->page, list->hashTable);

    list->back_elem = list->back_elem->prev;
    list->back_elem->next = NULL;

    new_front->page = page;
    new_front->prev = NULL;
    new_front->next = old_front;

    old_front->prev = new_front;
    list->front_elem = new_front;

    hash_add_elem(page, list->hashTable, list->front_elem);
}

void Exchange_Elem(struct list_t* list1, struct list_t* list2, int page)
{
    int page_back = list1->back_elem->page;
    Push_Front(list1, page);
    Push_Front(list2, page_back);
}

void Move_Elem_Page(struct list_t* list, int page)
{
    assert(list);
    struct node_t* node = NULL;
    struct node_t* tmp = NULL;

    node = hash_page_position(page, list->hashTable);
    if(node == NULL)
        return;

    if (node == list->front_elem)
        return;

    if (node == list->back_elem)
    {
        tmp = node->prev;
        tmp->next = NULL;
        list->back_elem = tmp;
    } else
        {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
    node->next = list->front_elem;
    list->front_elem->prev = node;
    list->front_elem = node;
    node->prev = NULL;
}

void Free_List (struct list_t* list)
{
    struct node_t* top = list->front_elem;
    struct node_t* tmp = NULL;
    while (top != NULL)
    {
        tmp = top->next;
        free(top);
        top = tmp;
    }
    list->size = 0;
    free(list);
}

void Print_List_Front(struct list_t* list)
{
    if (list->size == 0)
        return;
    struct node_t* tmp = list->front_elem;
    while (tmp != NULL)
    {
        printf("[%d]->", tmp->page);
        tmp = tmp->next;
    }
    printf("\n");
}

void Print_List_Back(struct list_t* list)
{
    if (list->size == 0)
        return;
    struct node_t* tmp = list->back_elem;
    while (tmp != NULL)
    {
        printf("<-[%d]", tmp->page);
        tmp = tmp->prev;
    }
    printf("\n");
}

static struct node_t* Create_Node()
{
    struct node_t* node = (struct node_t*)calloc(1, sizeof(struct node_t));
    assert(node);
    return node;
}

/*
void Assert_List(struct list_t* list)
{
    Is_Empty(list);
    if(list->front_elem->prev == NULL)
    {
        fprintf(stderr, "ERROR: There is pointer to the parent of the front node");
        exit(3);
    }
    if(list->back_elem->next == NULL)
    {
        fprintf(stderr, "ERROR: There is pointer to the child of the back node");
        exit(3);
    }
    struct node_t* node = list->front_elem;
    while (node != NULL)
    {

    }
}
*/
