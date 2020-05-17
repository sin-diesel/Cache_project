#include <stdio.h>
#include <stdlib.h>
#include "include/LRU_hash.h"
#include "include/List.h"
#include "include/cache.h"


#define TWOQ /* which version to use */


int main () {

	#ifdef LRU

	cache_test();
	//system("make -f Makefile_cache.txt clean");
	//system("make -f Makefile_tests.txt сlean");

	#endif

	#ifdef TWOQ

	cache_2q_test();

	#endif

	return 0;
}