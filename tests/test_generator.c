#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "test_generator.h"

void generate_nums(int cache_size, int npages, int max_page, FILE* stream) {

	srand(time(NULL));

	//fprintf(stdout, "%d", cache_size);
	fprintf(stream, "%d ", cache_size);
	fprintf(stream, "%d\n", npages);

	for (int i = 0; i < npages; ++i) {
		int num = rand() % max_page;
		assert(num >= 0);
		fprintf(stream, "%d ", num);
	}

}
