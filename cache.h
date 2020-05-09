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

struct cache2q_t {

	struct memory_t main_mem;
	unsigned main_mem_size;
	unsigned main_elem_ctr;

	struct memory_t in_mem;
	unsigned in_mem_size;
	unsigned in_elem_ctr;

	struct memory_t out_mem;
	unsigned out_mem_size;
	unsigned out_elem_ctr;

	unsigned main_size;
	unsigned in_size;
	unsigned out_size;
};

struct cache2q_t cache2q_init(int main_size, int in_size, int out_size); /* initialize 2qCache */

struct cache_t cache_init(int main_size); /* initilizes cache */

int handle_page(struct cache_t* cache, int page); /* page handler, returns -1 if miss and page hash if hit*/

int handle_page_2q(struct cache2q_t* cache, int page); /* page handler, returns -1 if miss and page hash if hit*/

void cache_delete(struct cache_t* cache); /* deletes cache */

void run_tests(struct cache_t* cache, FILE* data_source); /* test program */

void run_tests_2q(struct cache2q_t* cache, FILE* data_source); /* test 2q algorithm */
