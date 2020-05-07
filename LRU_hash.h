#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


struct node_t{
    struct node_t* next;
    struct node_t* prev;
    int hash;
    int page; // page number
};

struct hash_table
{
	struct node_t **table;
	int capacity;
};

// return hash of the page
int hash_func (int page, struct hash_table s);

// create hash table with size = capacity (capacity >> list_size)
struct hash_table* hash_init (int capacity); 

// check if the page in hash table (so that in cache too) (ret 1 if yes, 0 - vice verse)
char hash_check_elem (int page, struct hash_table s);

// add this page in hash table
void hash_add_elem (int page, struct hash_table* s, struct node_t* pNode);

// delete this page from hash table
void hash_delete_elem (int page, struct hash_table* s);

// free hash table
void hash_free (struct hash_table* s); 
 
//return position of current page in the list
struct node_t* hash_page_position (int page, struct hash_table s);