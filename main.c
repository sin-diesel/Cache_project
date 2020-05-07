#include <stdio.h>
#include <stdlib.h>
#include "LRU_hash.h"
#include "List.h"
#include "cache.h"


int main () {

	int main_size = 2;

	struct cache_t cache = cache_init(main_size);
	//fprintf(stderr, "Okay in: %d %s\n", __LINE__, __func__);

	FILE* tests = fopen("tests.txt", "r");
    assert(tests);

	run_tests(&cache, tests);

	return 0;
}