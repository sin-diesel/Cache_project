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

struct cache2q_t cache2q_init(int main_size, int in_size, int out_size) {

	assert(main_size >= 0);
	assert(in_size >= 0);
	assert(out_size >= 0);

	struct cache2q_t* cache = (struct cache2q_t*) calloc(1, sizeof(struct cache2q_t));
	assert(cache);

	int hash_main_capacity = main_size * 100; // needs testing
	int hash_in_capacity = in_size * 100;
	int hash_out_capacity = out_size * 100;

	cache->main_mem.hash = *(hash_init(hash_main_capacity));
	assert(&(cache->main_mem.hash));
	cache->main_mem.pages = *(Init_List(main_size, &(cache->main_mem.hash)));
	assert(&(cache->main_mem.hash));

	cache->in_mem.hash = *(hash_init(hash_in_capacity));
	assert(&(cache->in_mem.hash));
	cache->in_mem.pages = *(Init_List(in_size, &(cache->in_mem.hash)));
	assert(&(cache->in_mem.hash));

	cache->out_mem.hash = *(hash_init(hash_out_capacity));
	assert(&(cache->out_mem.hash));
	cache->out_mem.pages = *(Init_List(main_size, &(cache->out_mem.hash)));
	assert(&(cache->out_mem.hash));

	cache->main_mem_size = main_size;
	cache->in_mem_size = in_size;
	cache->out_mem_size = out_size;

	cache->main_elem_ctr = 0;
	cache->in_elem_ctr = 0;
	cache->out_elem_ctr = 0;

	return *cache;
}

void cache2q_delete(struct cache2q_t* cache) {

	assert(cache);

	struct list_t* main_pages = &(cache->main_mem.pages);
	struct hash_table* main_hash = &(cache->main_mem.hash);

	struct list_t* in_pages = &(cache->in_mem.pages);
	struct hash_table* in_hash = &(cache->in_mem.hash);

	struct list_t* out_pages = &(cache->out_mem.pages);
	struct hash_table* out_hash = &(cache->out_mem.hash);

	hash_free(main_hash);
	Free_List(main_pages);

	hash_free(in_hash);
	Free_List(in_pages);

	hash_free(out_hash);
	Free_List(out_pages);

	free(cache);
}

int handle_page(struct cache_t* cache, int page) {

	char result = 0;

	struct list_t* main_pages = &(cache->main_mem.pages);


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

int handle_page_2q(struct cache2q_t* cache, int page) {

	char result_main = 0;
	//char result_in = 0;
	char result_out = 0;

	struct list_t* main_pages = &(cache->main_mem.pages);
	struct list_t* in_pages = &(cache->in_mem.pages);
	struct list_t* out_pages = &(cache->out_mem.pages);


	result_main = hash_check_elem(page, cache->main_mem.hash);
	//int page_hash = hash_func(page, 10000000);

	if (result_main == 0) { // not in the main memory

		result_out = hash_check_elem(page, cache->out_mem.hash);
		if (result_out == 1) {
			Push_Front(main_pages, page);
		} else {
			Exchange_Elem(in_pages, out_pages, page);
		}	

	} else {
		Move_Elem_Page(main_pages, page);
	}


	return result_main; // fix due to result having unclear interpretation
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

 void run_tests_2q(struct cache2q_t* cache, FILE* data_source) { /* with stdout for now */

	assert(cache);
	assert(data_source);

	int page = 0;
	int hits = 0;
	int misses = 0;
	int res = 0;

	while (fscanf(data_source, "%d ", &page) == 1) {
		res = handle_page_2q(cache, page);
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











