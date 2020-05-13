#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "../include/cache.h"
#include "../include/List.h"
#include "../include/LRU_hash.h"
#include <assert.h>

//#define DEBUG


/// Initializes LRU cache with given size
/// @param [main_size] main_size - cache size
/// @returns pointer to cache

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


/// Initializes 2Q cache with main memory size, in memory size and out memory size
/// @param [main_size] main_size - main_memory size
/// @param [in_size] in_size - in_memory size
/// @param [out_size] out_size - out_memory size
/// @returns pointer to cache 2Q


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

/// Deletes 2Q cache (with all hashtables and lists inside)
/// @param [struct cache2_t* cache] cache - pointer to cache
/// @note Will not work properly if hash or list delete functions fail

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

/// Anylizes whether page is in cache or not
/// @param [struct cache_t* cache] cache - pointer to cache
/// @param [page] page - page number
/// @returns 1 if hit, 0 if miss

int handle_page(struct cache_t* cache, int page) {

	char result = 0;

	struct list_t* main_pages = &(cache->main_mem.pages);


	result = hash_check_elem(page, cache->main_mem.hash);

	#ifdef DEBUG
	fprintf(stderr, "Current page: %d\n", page);
	fprintf(stderr, "Current cache state: \n");
	fprintf(stderr, "Main: ");
	Print_List_Front(main_pages);
	fprintf(stderr, "\n");
	#endif

	if (result != 0) {
		cache->elements_ctr++;
		Move_Elem_Page(main_pages, page);
	} else {
		Push_Front(main_pages, page);
	}

	#ifdef DEBUG
	fprintf(stderr, "Cache state after handling page: \n");
	fprintf(stderr, "Main: ");
	(result == 1) ? fprintf(stderr, "hit \n") : fprintf(stderr, "miss \n");
	fprintf(stderr, "\n\n\n");
	#endif


	return result;
}

/// Anylizes whether page is in 2Q cache or not
/// @param [struct cache_t* cache] cache - pointer to cache
/// @param [page] page - page number
/// @returns 1 if hit, 0 if miss

int handle_page_2q(struct cache2q_t* cache, int page) {

	char result_main = 0;
	char result_in = 0;
	char result_out = 0;

	struct list_t* main_pages = &(cache->main_mem.pages);
	struct list_t* in_pages = &(cache->in_mem.pages);
	struct list_t* out_pages = &(cache->out_mem.pages);

	int result = 0;


	result_main = hash_check_elem(page, cache->main_mem.hash);
	#ifdef DEBUG
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
			result = 1;
			Move_Elem_Page(in_pages, page);
		} else {
			Exchange_Elem(in_pages, out_pages, page);
		}
	} else {
		result = 1;
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



	return result; // return either main_result of in_results since accesing page either in main or in memory is a hit
}

/// Deletes LRU cache (with all hashtables and lists inside)
/// @param [struct cache_t* cache] cache - pointer to cache
/// @note Will not work properly if hash or list delete functions fail

void cache_delete(struct cache_t* cache) {

	assert(cache);

	struct list_t* main_pages = &(cache->main_mem.pages);
	struct hash_table* main_hash = &(cache->main_mem.hash);


	hash_free(main_hash);
	Free_List(main_pages);

	free(cache);
}


/// Uses tests file to run tests for LRU cache, prints result in stdout
/// @param [struct cache_t* cache] cache - pointer to cache
/// @param [FILE* data_source] data_source - test file
/// @param [int npages] npages- pages size

void run_tests(struct cache_t* cache, FILE* data_source, int npages) { /* with stdout for now */

	assert(cache);
	assert(data_source);

	int page = 0;
	int hits = 0;
	int misses = 0;
	int res = 0;
	//FILE* results = fopen("results.txt", "a+"); /* file for representing results */
	//assert(results);

	for (int i = 0; i < npages; ++i) {

		int res_scanf = 0;
		res_scanf = fscanf(data_source, "%d ", &page);
		assert(res_scanf == 1);

		res = handle_page(cache, page);
		if (res != 0) {
			++hits;
		} else {
			++misses;
		}
	}

	double hit_rate = 100 * 1.0 * hits / (hits + misses);

	fprintf(stdout, "LRU: Hits: %d\n Misses: %d\n Hit rate: %.2f %%\n", hits, misses, hit_rate);
//	fprintf(results, "%u %f\n", cache->main_mem_size, hit_rate); /* for LRU */
//	fclose(results);
}

/// Uses tests file to run tests for 2Q cache, prints result in stdout
/// @param [struct cache_t* cache] cache - pointer to cache
/// @param [FILE* data_source] data_source - test file
/// @param [int npages] npages- pages size

 void run_tests_2q(struct cache2q_t* cache, FILE* data_source, int npages) { /* with stdout for now */

	assert(cache);
	assert(data_source);

	int page = 0;
	int hits = 0;
	int misses = 0;
	int res = 0;

	//FILE* results = fopen("results.txt", "a+"); /* file for representing results */
	//assert(results);

	for (int i = 0; i < npages; ++i) {

		int res_scanf = 0;
		res_scanf = fscanf(data_source, "%d ", &page);
		assert(res_scanf == 1);

		res = handle_page_2q(cache, page);
		if (res != 0) {
			++hits;
		} else {
			++misses;
		}
	}

	double hit_rate = 100 * 1.0 * hits / (hits + misses);

	fprintf(stdout, "2Q: Hits: %d\n Misses: %d\n Hit rate: %.2f %%\n", hits, misses, hit_rate);
	//fprintf(results, "%u %f\n", cache->cache_size, hit_rate); /* for 2Q */
	//fclose(results);
}

/// Test LRU cache, read cache size and npages from tests.txt

void cache_test() {

	int cache_size = 0;
	int npages = 0;

   #ifndef DEBUG

	system("make -f Makefile_tests.txt all");
   	system ("./tests"); /* questionable */
   	FILE* tests = fopen("../tests.txt", "r");
   	assert(tests);

    fscanf(tests, "%d %d", &cache_size, &npages);
    assert(cache_size >= 0);
    assert(npages >= 0);

    struct cache_t* cache = cache_init(cache_size);
    assert(cache);

    run_tests(cache, tests, npages);

	//cache_delete(cache);

	#else 

	FILE* tests = fopen("../tests2.txt", "r"); /* additional tests*/
	assert(tests);

	struct cache_t* cache = cache_init(3);
	run_tests(cache, tests);
	#endif
}

/// Test 2Q cache, read cache size and npages from tests.txt

void cache_2q_test() {

	int cache_size = 0;
	int out_size = 0;
	int in_size = 0;
	int npages = 0;

	#ifndef DEBUG

    system("make -f Makefile_tests.txt all");
   	system ("./tests"); /* questionable */
   	FILE* tests = fopen(".//tests.txt", "r");
   	assert(tests);

    fscanf(tests, "%d %d", &cache_size, &npages);
    assert(cache_size >= 0);
    assert(npages >= 0);

    out_size = 0.5 * npages;
    in_size = 0.25 * cache_size;

    struct cache2q_t* cache = cache2q_init(cache_size, in_size, out_size);
    assert(cache);

    run_tests_2q(cache, tests, npages);
    //cache2q_delete(cache);

	#else 

	FILE* tests = fopen("../tests2.txt", "r"); /* additional tests*/
	assert(tests);

	struct cache2q_t* cache = cache2q_init(3, 2, 3);
	run_tests_2q(cache, tests);

	#endif
}








