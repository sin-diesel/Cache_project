#include "Artem.h"


/*struct hash_item
{
	char flag;
	struct node_t *list_elem;
};

struct hash_table
{
	struct hash_item* table;
	int size;
};*/

// return hash of the page
int hash_func (int page, int size) {
	return page % size;
}

// create hash table according to list
struct hash_table hesh_init (struct list_t list) {
	struct hash_table s;
	s.table = (struct hash_item*) calloc (list.size, sizeof(struct hash_item));
	assert (s.table != NULL);

	s.size = list.size;
	for (int i = 0; i < s.size; ++i)
		s.table[i].list_elem = list.front_elem[i];

	return s;
}

// check if the page in hash table (ret 1 if yes, 0 - vice verse)
char hash_check_elem (int page, struct hash_table s) {
	int hash_page = hash_func (page, s.size);
	return (s.table[hash_page].flag == 1) ? 1 : 0;
}

// add this page in hash table
void hash_add_elem (int page, struct hash_table s) {
	
	if (hash_check_elem (page, s) == 1)
		return;

	int hash_page = hash_func (page, s.size);

	s.table[hash_page].flag = 1;
}

// delete this page from hash table
void hash_delete_elem (int page, struct hash_table table) {
	if (hash_check_elem (page, s) == 0)
		return;
	
	int hash_page = hash_func (page, s.size);

	s.table[hash_page].flag = 0;
}

// free hash table
void hash_free (struct hash_table s) {
	free(s.table);
	s.size = 0;
}