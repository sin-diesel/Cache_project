#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "LRU_hash.h"

enum {VOID = -1};

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

//access the first element
static inline int Front_Elem(struct list_t* list){return list->front_elem->page;}

//access the last element
static inline int Back_Elem(struct list_t* list){return list->back_elem->page;}

//returns the number of elements
static inline int Size_List (struct list_t* list){return list->size;};

//init list of the selected size
struct list_t* Init_List(int size, struct hash_table* hashTable);

//check whether the underlying container is empty
char Is_Empty (struct list_t* list);

//add elem in the end of the list, top of the list deleted
void Push_Back(struct list_t* list, int page);

//add elem in the top of the list, end of the list deleted
void Push_Front(struct list_t* list, int page);

//add elem in the top of the list1 an, end of the list moves to the top of the list2
void Exchange_Elem(struct list_t* list1, struct list_t* list2, int page);

//Move elem forward by page
//if page not found nothing happens
void Move_Elem_Page(struct list_t* list, int page);

//Send to main , delete in out
void Send_to_Main(struct list_t* out, struct list_t* main, int page);

//free list
void Free_List (struct list_t* list);

//print list from the front
void Print_List_Front(struct list_t* list);

//print list from the back
void Print_List_Back(struct list_t* list);

//Assert List
void Assert_List(struct list_t* list);

//Create node for list
struct node_t* Create_Node();

//Creating array from list
int* Create_ArrayByList(struct list_t* list);

//creates list from array
struct list_t* Create_ListByArray(int* arr, int len);

//Resize list
void Resize_List(struct list_t* list, int newsize);

//Fill list
void Fill_List(struct list_t* list ,int val);