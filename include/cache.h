#include <stdlib.h>
#include "LRU_hash.h"
#include "List.h"

struct memory_t { /* main memory list + hash */
	struct list_t pages;
	struct hash_table hash;
};

struct cache_t { /* cache data structure */

	struct memory_t main_mem;
	unsigned main_mem_size;

	unsigned elements_ctr; /* elements counter */
};

struct cache_t cache_init(int main_size); /* initilizes cache */

int handle_page(struct cache_t* cache, int page); /* page handler, returns -1 if miss and page hash if hit*/

void cache_delete(struct cache_t* cache); /* deletes cache */

void run_tests(struct cache_t* cache, FILE* data_source); /* test program */
