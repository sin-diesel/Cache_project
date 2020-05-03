#include <stdlib.h>

struct cache_t { /* cache data structure */

	struct list_t main_mem; /* main memory list + hash */
	struct hash_t main_hash;
	unsigned main_mem_size;

	unsigned elements_ctr;
}

struct cache_t* cache_init(int main_size);

void handle_page(struct cache_t* cache, int page); /* page handler */

void cache_delete();

void insert_page_pos(struct cache_t* cache, int pos); /* takes position for insertion */

void delete_page_pos(struct cache_t* cache, int pos);

void move_page(struct cache_t* cache, int from, int to);
