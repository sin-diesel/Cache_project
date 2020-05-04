#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


struct hash_table
{
	struct node_t **table;
	int capacity;
};

// return hash of the page
int hash_func (int page, int mod);

// create hash table according to list
struct hash_table* hesh_init (int capacity);

// check if the page in hash table (ret 1 if yes, 0 - vice verse)
char hash_check_elem (int page, struct hash_table s);

// add this page in hash table
void hash_add_elem (int page, struct hash_table* s, struct node_t* pNode);

// delete this page from hash table
void hash_delete_elem (int page, struct hash_table* s);

// free hash table
void hash_free (struct hash_table* s); 
 
