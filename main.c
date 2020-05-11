#include <stdio.h>
#include <stdlib.h>
#include "LRU_hash.h"
#include "List.h"
#include "cache.h"

#define TWOQ /* which version to use */


int main () {

	#ifdef LRU

	cache_test(5, 200, 5); /* min_page max_page step */
	system("make -f Makefile_cache.txt clean");
	//system("make -f Makefile_tests.txt сlean");

	#endif

	#ifdef TWOQ

	cache_2q_test(5, 200, 5); /* min_size max_size step */

	#endif

	return 0;
}