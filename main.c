#include <stdio.h>
#include <stdlib.h>
#include "LRU_hash.h"
#include "List.h"
#include "cache.h"

#define TWOQ


int main () {

	#ifdef LRU

	int main_size = 30;

	struct cache_t cache = cache_init(main_size);

	FILE* tests = fopen("tests.txt", "r");
    assert(tests);

    system("make -f Makefile_tests.txt all");
    system ("./tests");/* questionable */

	run_tests(&cache, tests);

	#endif

	int main_size = 4;
	int in_size = 2;
	int out_size = 3;

	struct cache2q_t cache2q = cache2q_init(main_size, in_size, out_size);

	FILE* tests = fopen("tests.txt", "r");
    assert(tests);

    system("make -f Makefile_tests.txt all");
    system ("./tests");/* questionable */

	//run_tests_2q(&cache2q, tests);

	return 0;
}