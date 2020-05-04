#include <stdio.h>
#include <stdlib.h>
#include "Artem.h"
#include "List.h"
#include "cache.h"


int main () {

	int main_size = 10;

	struct cache_t cache = cache_init(main_size);
	cache_delete(&cache);

	return 0;
}