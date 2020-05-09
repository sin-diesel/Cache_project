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

	int hash_capacity = main_size * 100000; // needs testing
	cache->main_mem.hash = *(hash_init(hash_capacity));
	assert(&(cache->main_mem.hash));

	cache->main_mem.pages = *(Init_List(main_size, &(cache->main_mem.hash)));
	assert(&(cache->main_mem.hash));

	cache->main_mem_size = main_size;

	cache->elements_ctr = 0;

	return *cache;
}

int handle_page(struct cache_t* cache, int page) {

	char result = 0;

	struct list_t* main_pages = &(cache->main_mem.pages);
	struct hash_table* main_hash = &(cache->main_mem.hash);


	result = hash_check_elem(page, cache->main_mem.hash);
	//int page_hash = hash_func(page, 10000000);

	if (result != 0) {
		fprintf(stderr, "\tOkay hit with page %d before swap in: %d %s\n", page, __LINE__, __func__);	
		cache->elements_ctr++;
		Print_List_Front(main_pages);
		Move_Elem_Page(main_pages, page);
		fprintf(stderr, "\tOkay hit with page %d after swap in: %d %s\n", page, __LINE__, __func__);	
		Print_List_Front(main_pages);
	} else {
		fprintf(stderr, "Okay miss with page before push %d in: %d %s\n", page, __LINE__, __func__);
		Print_List_Front(main_pages);
		Push_Front(main_pages, page);
		fprintf(stderr, "Okay miss with page after push %d in: %d %s\n", page, __LINE__, __func__);
		Print_List_Front(main_pages);
	}


	return result;
}

/*
int handle_page(struct cache_t* cache, int page) {
	int res;
	if ((res = hash_check_elem (page, cache->main_hash)) == 0)
		push_front (page, cache->main_mem);

	return res;
}

*/

void cache_delete(struct cache_t* cache) {

	assert(cache);

	struct list_t* main_pages = &(cache->main_mem.pages);
	struct hash_table* main_hash = &(cache->main_mem.hash);


	hash_free(main_hash);
	Free_List(main_pages);

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
		if (res != 0) {
			++hits;
		} else {
			++misses;
		}
	}

	fprintf(stdout, "Hits: %d\n Misses: %d\n", hits, misses);
 }

/*

void run_tests(struct cache_t* cache, FILE* data_source) {
	int hits = 0;
	int n = 0;
	
	while (fscanf(data_source, "%d ", &page) == 1) {
		hits += handle_page(cache, page) == 1;
		n++;
	}

	fprintf(stdout, "Hits: %d\n Misses: %d\n", hits, n - hits);
}

*/











