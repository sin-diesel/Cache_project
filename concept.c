#include <stdio.h>



struct cache_t { //conceptual representation of our cache

	int main_size
	int in_size;
	int out_size

	int* main_head; // main memory
	int* main_tail;
	int* in_head // in memory
	int* in_tail // out memory
}

int main () {

	//TODO

	//1) agree upon the representation of cache
	//2) write basic functions to operate with cache
	//2.5) write basic LRU algorithm
	//3) implement functions for 2q algorithm
	//4) assemble all functions into working condition
	//5) write tests for generating random data to put through 
	// the algorithm
	//6) display the tests on line chart and compare with basic LRU
	//7) write a proper documentation for each function and program in general

	struct cache_t cache;
// basic functions
	cache_init(&cache, main_size, in_size, out_size);

	insert_element_pos(&cache, after_position)

	insert_element_val(&cache, value)

	delete_element_pos(&cache, position)

	delete_element_val(&cache, value)

	delete_cache(&cache);

//LRU

	run_lru(&cache, FILE* stream)


	run_lru(struct cache* cache, FILE* stream) {

		while (fscanf(stream) == 1) {
			place_data();
			tell_miss_or_hit();
		}

	}

	//2Q

	run_2q(&cache, FILE* stream)


	run_2q(struct cache* cache, FILE* stream) {

		while (fscanf(stream) == 1) {
			place_data_2q();
			tell_miss_or_hit();
		}

	}
	//tests

	//use external program to check for mistakes
	//then use text file created by program to acquire data







	return 0;
}