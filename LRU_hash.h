#pragma once

#include "List.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/**
 * An element of hash table.
 */
struct hash_node_t
{
	struct node_t *list_node_t;       /**< a pointer to an element of the list. */
	struct hash_node_t *next, *prev;  /**< pointers to the previous and next elements of the hash table. */
	int page;                         /**< the page, located in current element of hash table. */
};


/**
 * Hash table with its capacity.
 */
struct hash_table
{
	struct hash_node_t *table;       /**< array of hash nodes. */
	int capacity;                    /**< max number of elements with different hashs. */
};



/**
 * Calculating the hash of the page according to hash table.
 * @param page the page, which hash we need to know.
 * @param s a  struct of hash table, where this page probably will be inserted.
 * @return the hash of the page.
 */
int hash_func (int page, struct hash_table s);

/**
 * Creating the element of the hash table with repeating hash.
 * @param page the page to be inserted in hash table.
 * @param list_node_t a pointer to the element of list, where this page is located.
 * @param prev a pointer to the previous element of hash table.
 * @return a pointer to the new hash table element.
 */
struct hash_node_t* hash_create_node (int page, struct node_t *list_node_t, struct hash_node_t *prev);

/**
 * Finding out if the page in hash table.
 * @param page a page which we want to find.
 * @param s a struct of hash table where we searching.
 * @return a pointer to the element of hash table if this page is founded or NULL pointer if it is not.
 */
struct hash_node_t* hash_find_page (int page, struct hash_table s);

/**
 * Creating a hash table.
 * @param capacity the number of unique hashs.
 * @return a pointer to the  struct of hash table.
 */
struct hash_table* hash_init (int capacity); 

/**
 * Checking if the page in hash table (and in cache too)
 * @param page a page which we are searching.
 * @param s a struct of hash table, where we are searching.
 * @return 1 if the page is in hash table or 0 if it is not
 */
char hash_check_elem (int page, struct hash_table s);

/**
 * Adding the page in hash table.
 * @param page a page we want to add.
 * @param s a pointer to the struct of hash table, in which we want to add.
 * @param pNode a pointer to the element of list, where this page is located.
 */
void hash_add_elem (int page, struct hash_table *s, struct node_t *pNode);

/**
 * Deleting the page from hash table.
 * @param page a page we want to delete.
 * @param s a pointer to the struct of hash table, from wich we want to delete.
 */
void hash_delete_elem (int page, struct hash_table *s);

/**
 * Deleting the struct of hash table.
 */
void hash_free (struct hash_table *s);

/**
 * Deleting all elements with the same hash, beginnig from the top.
 */
void hash_free_branch (struct hash_node_t *top);
 
/**
 * Searching the pointer to the list's element with this page.
 * @param page a page which pointer we want to find.
 * @param s a pointer to the struct of hash table, where we are searching.
 * @return a pointer to the list's element if this page is in hash table or NULL pointer if it is not.
 */
struct node_t* hash_page_position (int page, struct hash_table *s);