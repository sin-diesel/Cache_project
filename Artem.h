#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


struct hash_item
{
	char flag;
	struct node_t *list_elem;
};

struct hash_table
{
	struct hash_item* table;
	int size;
};

// return hash of the page
int hash_func (int page, int size);

// create hash table according to list
struct hash_table hesh_init (struct list_t list);

// check if the page in hash table (ret 1 if yes, 0 - vice verse)
char hash_check_elem (int page, struct hash_table s);

// add this page in hash table
void hash_add_elem (int page, struct hash_table s);

// delete this page from hash table
void hash_delete_elem (int page, struct hash_table s);

// free hash table
void hash_free (struct hash_table s);