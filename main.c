#include <stdio.h>
#include <stdlib.h>
#include "LRU_hash.h"
#include "List.h"
#include "cache.h"

#define LRU /* which version to use */


int main () {

	#ifdef LRU

	cache_test(100, 5, 200, 5); /* main_size min_page max_page step */
	system("make -f Makefile_cache.txt clean");
	//system("make -f Makefile_tests.txt сlean");

	#endif

	#ifdef TWOQ

	cache2q_test(100, 25, 50, 5, 200, 5) /* main_size in_size out_size min_size max_size step */

	int cache_size = 5;
	int out_size = 3;
	int in_size = 2;
	int main_size = cache_size;

	struct cache2q_t cache2q = cache2q_init(main_size, in_size, out_size);

	FILE* tests = fopen("tests2.txt", "r");
    assert(tests);

    system("make -f Makefile_tests.txt all");
    system ("./tests");/* questionable */

	run_tests_2q(&cache2q, tests);
	#endif

	return 0;
}