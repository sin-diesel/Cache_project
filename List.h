#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "LRU_hash.h"

struct node_t{
    struct node_t* next;
    struct node_t* prev;
    int page;
};

struct list_t{
    struct node_t* front_elem;
    struct node_t* back_elem;
    struct hash_table* hashTable;
    int size;
};

//init list of the selected size
struct list_t* Init_List(int size, struct hash_table* hashTable);

//access the first element
struct node_t* Front_Elem(struct list_t* list);

//access the last element
struct node_t* Back_Elem(struct list_t* list);

//check whether the underlying container is empty
char Is_Empty (struct list_t* list);

//returns the number of elements
size_t Size_List (struct list_t* list);

//add elem in the end of the list, top of the list deleted
void Push_Back(struct list_t* list, int page);

//add elem in the top of the list, end of the list deleted
void Push_Front(struct list_t* list, int page);

//add elem in the top of the list1 an, end of the list moves to the top of the list2
void Exchange_Elem(struct list_t* list1, struct list_t* list2, int page);

//Move elem forward by page
//if page not found nothing happens
void Move_Elem_Page(struct list_t* list, int page);

//free list
void Free_List (struct list_t* list);

//print list from the front
void Print_List_Front(struct list_t* list);

//print list from the back
void Print_List_Back(struct list_t* list);

//Assert List
//void Assert_List(struct list_t* list);