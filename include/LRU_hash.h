#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "List.h"

struct hash_node_t
{
	struct node_t *list_node_t;
	struct hash_node_t *next, *prev;
	int page;
};

struct hash_table
{
	struct hash_node_t *table;
	int capacity;
};



// return hash of the page
int hash_func (int page, struct hash_table s);

// Create hash_node with these arguments
struct hash_node_t* hash_create_node (int page, struct node_t *list_node_t, struct hash_node_t *prev);

//find this page in the branch
struct hash_node_t* hash_find_page (int page, struct hash_table s);

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

// free branch of hash
void hash_free_branch (struct hash_node_t* top);
 
//return position of current page in the list
struct node_t* hash_page_position (int page, struct hash_table *s);