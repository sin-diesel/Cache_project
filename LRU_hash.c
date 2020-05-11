#include "LRU_hash.h"


/*

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

*/



// return hash of the page (hash < size of hash table)
int hash_func (int page, struct hash_table s) {
	int hash = ((page < 0) ? -page : page) % s.capacity;
	return hash;
}

//Create hash_node
struct hash_node_t* hash_create_node (int page, struct node_t *list_node_t, struct hash_node_t *prev) {
	struct hash_node_t* node;
	node = (struct hash_node_t*) calloc (1, sizeof (struct hash_node_t));
	
	node->page = page;
	node->prev = prev;
	node->list_node_t = list_node_t;

	return node;
}

//find this page in the branch
struct hash_node_t* hash_find_page (int page, struct hash_table s) {
	int hash_page;
	struct hash_node_t *h_node;
	
	hash_page = hash_func (page, s);
	h_node = s.table + hash_page;
	
	while (h_node != NULL) {
		
		if (h_node->list_node_t != NULL && h_node->page == page)
			return h_node;

		h_node = h_node->next;
	}

	return NULL;
}

// create hash table with size=capacity (capacity >> list_size)
struct hash_table* hash_init (int capacity) {
	struct hash_table* s;
	s = (struct hash_table*) calloc (1, sizeof (struct hash_table));
	s->table = (struct hash_node_t*) calloc (capacity, sizeof(struct hash_node_t));
	assert (s->table != NULL);

	s->capacity = capacity;

	return s;
}

// check if the page in hash table (Cache) (ret 1 if yes, 0 - vice verse)
char hash_check_elem (int page, struct hash_table s) {
	struct hash_node_t *h_node;
	
	h_node = hash_find_page (page, s);
	
	return (h_node != NULL);
}

// add this page in hash table
void hash_add_elem (int page, struct hash_table* s, struct node_t* pNode) {
	
	struct hash_node_t* ptr;
	int hash_page;

	assert (pNode != NULL);
	if (hash_check_elem (page, *s) == 1)
		return;

	hash_page = hash_func (page, *s);
	ptr = s->table + hash_page;

	if (ptr->list_node_t == NULL) {
		ptr->list_node_t = pNode;
		ptr->page = page;
		return;
	}

	while (ptr->list_node_t != NULL && ptr->next != NULL)
		ptr = ptr->next;

	ptr->next = hash_create_node (page, pNode, ptr);
}


//return position of current page in the list
struct node_t* hash_page_position (int page, struct hash_table *s) {
	
	struct hash_node_t* h_node;

	h_node = hash_find_page (page, *s);

	return (h_node != NULL) ? h_node->list_node_t : NULL;
}

// delete this page from hash table
void hash_delete_elem (int page, struct hash_table* s) {
	struct hash_node_t* h_node;
	struct hash_node_t* h_node_next;

	if (hash_check_elem (page, *s) == 0)
		return;
	
	h_node = hash_find_page (page, *s);
	
	if (h_node->prev == NULL) {
		if (h_node->next == NULL) {
			h_node->page = 0;
			h_node->list_node_t = NULL;
			return;
		}
		
		h_node_next = h_node->next;
		*h_node = *(h_node->next);
		h_node->prev = NULL;
		
		free(h_node_next);
		
		if (h_node->next != NULL)
			h_node->next->prev = h_node;
		
		return;
	}

	h_node->prev->next = h_node->next;
	
	if (h_node->next != NULL)
		h_node->next->prev = h_node->prev;

	free (h_node);
}

//free branch of hash
void hash_free_branch (struct hash_node_t* top) {
	if (top == NULL)
		return;

	hash_free_branch (top->next);
	free(top);
}

// free hash table
void hash_free (struct hash_table* s) {
	int i;
	
	for (i = 0; i < s->capacity; ++i)
		hash_free_branch (s->table[i].next);

	free(s->table);
	s->capacity = 0;
	free (s);
} 
 
