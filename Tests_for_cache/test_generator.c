#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "test_generator.h"

void generate_nums(int iterations, FILE* stream) {

	int const max_page_num = 10000;
	srand(time(NULL));

	for (int i = 0; i < iterations; ++i) {
		int num = rand() % max_page_num;
		assert(num > 0);
		fprintf(stream, "%d ", num);
	}

}