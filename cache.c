#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cache.h"
#include "List.h"
#include "LRU_hash.h"
#include <assert.h>


struct cache_t cache_init(int main_size) {

	assert(main_size >= 0);

	struct cache_t* cache = (struct cache_t*) calloc(1, sizeof(struct cache_t));
	assert(cache);

	cache->main_hash = *(hash_init(main_size));
	assert(&(cache->main_hash));

	cache->main_mem = *(Init_List(main_size, &(cache->main_hash)));
	assert(&(cache->main_mem));

	cache->main_mem_size = main_size;

	cache->elements_ctr = 0;

	return *cache;
}

int handle_page(struct cache_t* cache, int page) {

	char result = 0;

	fprintf(stderr, "Okay in: %d %s\n", __LINE__, __func__);

	struct list_t* main_mem = &(cache->main_mem);
	struct hash_table* main_hash = &(cache->main_hash);

	fprintf(stderr, "Okay in: %d %s\n", __LINE__, __func__);

	result = Hash_with_Page(main_mem, page);
	int page_hash = hash_func(page, 10000000);

	fprintf(stderr, "Okay in: %d %s\n", __LINE__, __func__);

	if (result != NAN) {
		Push_Front(main_mem, page, page_hash);
		fprintf(stderr, "Okay hit in: %d %s\n", __LINE__, __func__);	
		cache->elements_ctr++;
	} else {
		fprintf(stderr, "Okay miss in: %d %s\n", __LINE__, __func__);
		Move_Elem_Hash(main_mem, page_hash);
	}

	return result;
}

void cache_delete(struct cache_t* cache) {

	assert(cache);

	struct list_t* main_mem = &(cache->main_mem);
	struct hash_table* main_hash = &(cache->main_hash);

	Free_List(main_mem);
	hash_free(main_hash);

	free(cache);
}

void run_tests(struct cache_t* cache, FILE* data_source) { /* with stdout for now */

	assert(cache);
	assert(data_source);

	int page = 0;
	int hits = 0;
	int misses = 0;
	int res = 0;

	while (fscanf(data_source, "%d ", &page) == 1) {
		res = handle_page(cache, page);
		if (res == 1) {
			++hits;
		} else {
			++misses;
		}
	}

	fprintf(stdout, "Hits: %d\n Misses: %d\n", hits, misses);
 }












