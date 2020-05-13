#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "test_generator.h"

int main() {
	
	int cache_size = 100;
	int max_pages = 10000;
	int npages = 100000;
	FILE* out_file = fopen("tests.txt", "w");
	assert(out_file);
	generate_nums(cache_size, npages, max_pages, out_file);
	fclose(out_file);
	
	return 0;
}
