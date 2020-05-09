#include <stdio.h>
#include <stdlib.h>
#include "include/LRU_hash.h"
#include "include/List.h"
#include "include/cache.h"


int main () {

	int main_size = 30;

	struct cache_t cache = cache_init(main_size);

	FILE* tests = fopen("tests.txt", "r");
    assert(tests);

    system("make -f Makefile_tests.txt all");
    system ("./tests");/* questionable */

	run_tests(&cache, tests);

	return 0;
}
