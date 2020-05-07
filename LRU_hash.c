#include "LRU_hash.h"


/*struct hash_table
{
	struct node_t **table;
	int capacity;
};
*/

// return hash of the page (hash < size of hash table)
int hash_func (int page, struct hash_table s) {
	int hash = ((page < 0) ? -page : page) % s.capacity;
	return hash;
}

// create hash table according to list
struct hash_table* hash_init (int capacity) {
	struct hash_table* s;
	s = (struct hash_table*) calloc (1, sizeof (struct hash_table));
	s->table = (struct node_t**) calloc (capacity, sizeof(struct node_t*));
	assert (s->table != NULL);

	s->capacity = capacity;

	return s;
}

// check if the page in hash table (Cache) (ret 1 if yes, 0 - vice verse)
char hash_check_elem (int page, struct hash_table s) {
	int hash_page = hash_func (page, s.capacity);
	return (s.table[hash_page] != NULL);
}

// add this page in hash table
void hash_add_elem (int page, struct hash_table* s, struct node_t* pNode) {
	
	assert (pNode != NULL);
	if (hash_check_elem (page, *s) == 1)
		return;

	int hash_page = hash_func (page, s->capacity);

	s->table[hash_page] = pNode;
}

// delete this page from hash table
void hash_delete_elem (int page, struct hash_table* s) {
	if (hash_check_elem (page, *s) == 0)
		return;
	
	int hash_page = hash_func (page, s->capacity);

	s->table[hash_page] = NULL;
}

// free hash table
void hash_free (struct hash_table* s) {
	free(s->table);
	s->capacity = 0;
	free (s);
} 
 
