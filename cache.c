#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cache.h"
#include "List.h"
#include "LRU_hash.h"
#include <assert.h>

#define DEBUG


struct cache_t* cache_init(int main_size) {

	assert(main_size >= 0);
	int hash_factor = 100; /* choosing hash size for cache */

	struct cache_t* cache = (struct cache_t*) calloc(1, sizeof(struct cache_t));
	assert(cache);

	int hash_capacity = main_size * hash_factor; 
	cache->main_mem.hash = *(hash_init(hash_capacity));
	assert(&(cache->main_mem.hash));

	cache->main_mem.pages = *(Init_List(main_size, &(cache->main_mem.hash)));
	assert(&(cache->main_mem.hash));

	cache->main_mem_size = main_size;

	cache->elements_ctr = 0;

	return cache;
}

struct cache2q_t* cache2q_init(int main_size, int in_size, int out_size) {

	assert(main_size >= 0);
	assert(in_size >= 0);
	assert(out_size >= 0);

	struct cache2q_t* cache = (struct cache2q_t*) calloc(1, sizeof(struct cache2q_t));
	assert(cache);

	int hash_factor = 100;

	int hash_main_capacity = main_size * hash_factor; // needs testing
	int hash_in_capacity = in_size * hash_factor;
	int hash_out_capacity = out_size * hash_factor;

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
	cache->cache_size = main_size;

	cache->main_elem_ctr = 0;
	cache->in_elem_ctr = 0;
	cache->out_elem_ctr = 0;

	return cache;
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
	if (result != 0) {
		cache->elements_ctr++;
		Move_Elem_Page(main_pages, page);
	} else {
		Push_Front(main_pages, page);
	}


	return result;
}

int handle_page_2q(struct cache2q_t* cache, int page) {

	char result_main = 0;
	char result_in = 0;
	char result_out = 0;

	struct list_t* main_pages = &(cache->main_mem.pages);
	struct list_t* in_pages = &(cache->in_mem.pages);
	struct list_t* out_pages = &(cache->out_mem.pages);

 	#ifdef DEBUG
	result_main = hash_check_elem(page, cache->main_mem.hash);
	fprintf(stderr, "Current page: %d\n", page);
	fprintf(stderr, "Current cache state: \n");
	fprintf(stderr, "Main: ");
	Print_List_Front(main_pages);
	fprintf(stderr, "In: ");
	Print_List_Front(in_pages);
	fprintf(stderr, "Out: ");
	Print_List_Front(out_pages);
	fprintf(stderr, "\n");
	#endif

	if (result_main == 0) { // not in the main memory

		result_out = hash_check_elem(page, cache->out_mem.hash);
		result_in = hash_check_elem(page, cache->in_mem.hash);

		if (result_out == 1) {
			Send_to_Main(out_pages, main_pages, page);
		} else if (result_in == 1) {
			Move_Elem_Page(in_pages, page);
		} else {
			Exchange_Elem(in_pages, out_pages, page);
		}
	} else {
		Move_Elem_Page(main_pages, page);
	}
	#ifdef DEBUG
	fprintf(stderr, "Cache state after handling page: \n");
	fprintf(stderr, "Main: ");
	Print_List_Front(main_pages);
	fprintf(stderr, "In: ");
	Print_List_Front(in_pages);
	fprintf(stderr, "Out: ");
	Print_List_Front(out_pages);
	(result_main == 1) ? fprintf(stderr, "hit \n") : fprintf(stderr, "miss \n");
	fprintf(stderr, "\n\n\n");
	#endif


	return result_main; // fix due to result having unclear interpretation
}

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
	FILE* results = fopen("results.txt", "a+"); /* file for representing results */
	assert(results);

	while (fscanf(data_source, "%d ", &page) == 1) {
		res = handle_page(cache, page);
		if (res != 0) {
			++hits;
		} else {
			++misses;
		}
	}

	double hit_rate = 100 * 1.0 * hits / (hits + misses);

	fprintf(stdout, "LRU: Hits: %d\n Misses: %d\n Hit rate: %.2f %%\n", hits, misses, hit_rate);
	fprintf(results, "%u %f\n", cache->main_mem_size, hit_rate); /* for LRU */
}

 void run_tests_2q(struct cache2q_t* cache, FILE* data_source) { /* with stdout for now */

	assert(cache);
	assert(data_source);

	int page = 0;
	int hits = 0;
	int misses = 0;
	int res = 0;

	FILE* results = fopen("results.txt", "a+"); /* file for representing results */
	assert(results);

	while (fscanf(data_source, "%d ", &page) == 1) {
		res = handle_page_2q(cache, page);
		if (res != 0) {
			++hits;
		} else {
			++misses;
		}
	}

	double hit_rate = 100 * 1.0 * hits / (hits + misses);

	fprintf(stdout, "2Q: Hits: %d\n Misses: %d\n Hit rate: %.2f %%\n", hits, misses, hit_rate);
	fprintf(results, "%u %f\n", cache->cache_size, hit_rate); /* for 2Q */
}



void cache_test(int min_size, int max_size, int step) {


    for (int size = min_size; size < max_size; size += step) {
    	struct cache_t* cache = cache_init(size);

    	system("make -f Makefile_tests.txt all");
   		system ("./tests");/* questionable */
   		FILE* tests = fopen("tests.txt", "r");
   	    assert(tests);

    	run_tests(cache, tests);

    	//cache_delete(cache);
	}

}


void cache_2q_test(int min_size, int max_size, int step) {

	#ifndef DEBUG

    for (int size = min_size; size < max_size; size += step) {
    	struct cache2q_t* cache = cache2q_init(size, size * 0.25, size * 0.5);

    	system("make -f Makefile_tests.txt all");
   		system ("./tests");/* questionable */
   		FILE* tests = fopen("tests.txt", "r");
   	    assert(tests);

    	run_tests_2q(cache, tests);

    	//cache_delete(cache);
	}
	#else 

	FILE* tests = fopen("tests2.txt", "r"); /* additional tests*/
	assert(tests);

	struct cache2q_t* cache = cache2q_init(3, 2, 3);
	run_tests_2q(cache, tests);

	#endif
}








