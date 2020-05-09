#include <stdio.h>
#include <stdlib.h>
#include "LRU_hash.h"
#include "List.h"
#include "cache.h"

#define TWOQ


int main () {

	#ifdef LRU

	int main_size = 100;

	struct cache_t cache = cache_init(main_size);

	FILE* tests = fopen("tests.txt", "r");
    assert(tests);

    system("make -f Makefile_tests.txt all");
    system ("./tests");/* questionable */

	run_tests(&cache, tests);

	#endif

	#ifdef TWOQ

	int cache_size = 100;
	int out_size = cache_size * 0.5;
	int in_size = cache_size * 0.25;
	int main_size = cache_size - in_size - out_size;

	struct cache2q_t cache2q = cache2q_init(main_size, in_size, out_size);

	FILE* tests = fopen("tests.txt", "r");
    assert(tests);

    system("make -f Makefile_tests.txt all");
    system ("./tests");/* questionable */

	run_tests_2q(&cache2q, tests);
	#endif

	return 0;
}