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

	int rounds = 4;
	int step = npages / rounds;

	for (int j = 0; j < rounds; ++j) {

		int epsilon = 0.2 * max_page / (rounds - j); /* setting acceptable deviations from average page */
		int upper = max_page / (rounds - j) + epsilon; /* the average max_page increases with rounds */
		int lower = max_page / (rounds - j) - epsilon;

		for (int i = 0; i < step; ++i) { /* First n/rounds times the page size we generate nums
										in the neighbourhood of max_page / rounds, then in the neighbourhood of max_page / 2 for
										next n/rounds pages and so on */
			int num = rand() % ((upper - lower + 1)) + lower;

			assert(num >= 0);
			fprintf(stream, "%d ", num);
		}
	}

}
