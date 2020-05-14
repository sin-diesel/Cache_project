#include "../include/LRU_hash.h"
#include "../include/List.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void test () {
	struct hash_table* s = hash_init (10);
	struct node_t* node = (struct node_t*) calloc (1, sizeof (struct node_t));
	int i = 0;
	
	for (i = 0; i < 20; ++i)
		hash_add_elem (i, s, node);

	for (i = 0; i < 20; ++i)
		assert (hash_check_elem (i, *s) == 1 && "add");

	for (i = 0; i < 20; ++i)
		assert (hash_page_position (i, s) == node && "page ptr");

	for (i = 0; i < 20; ++i)
		hash_delete_elem (i, s);

	for (i = 0; i < 20; ++i)
		assert (hash_check_elem (i, *s) == 0 && "delete");

	hash_free (s);
	free (node);
}

int main () {
	test();

	return 0;
}