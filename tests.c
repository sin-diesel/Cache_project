#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "test_generator.h"

int main() {

	int iterations = 10000;
	FILE* out_file = fopen("tests.txt", "w");
	assert(out_file);
	generate_nums(iterations, out_file);
	
	return 0;
}
