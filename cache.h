#include <stdlib.h>

struct cache_t { /* cache data structure */

	struct list_t main_mem; /* main memory list + hash */
	struct hash_t main_hash;
	unsigned main_mem_size;

	unsigned elements_ctr; /* elements counter */
}

struct cache_t cache_init(int main_size); /* initilizes cache */

void handle_page(struct cache_t* cache, int page); /* page handler */

void cache_delete(struct cache_t* cache); /* deletes cache */
