#include "LRU_hash.h"
#include "List.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


struct array {
	int *arr;
	int size;
};

struct array arr_generator () {
	struct array res;
	
	res.size = abs (rand()) % 100000 + 1;
	res.arr = (int*) calloc (res.size, sizeof (int));
	assert (res.arr);

	for (int i = 0; i < res.size; ++i)
		res.arr[i] = rand () % 1000000;

	return res;
}


void test (struct array a, int capacity) {
	int *arr = a.arr;
	int size = a.size;

	struct hash_table* s = hash_init (capacity);
	struct node_t* node = (struct node_t*) calloc (1, sizeof (struct node_t));

	int i = 0;

	for (i = 0; i < size; ++i)
		hash_add_elem (arr[i], s, node);

	for (i = 0; i < size; ++i)
		assert (hash_check_elem (arr[i], *s) == 1 && "add");

	for (i = 0; i < size; ++i) {
		assert (hash_page_position (arr[i], s) == node && "page ptr");
	}

	for (i = 0; i < size; ++i)
		hash_delete_elem (arr[i], s);

	for (i = 0; i < size; ++i)
		assert (hash_check_elem (arr[i], *s) == 0 && "delete");

	hash_free (s);
	printf ("freed\n");
	free (node);
}

void hand_tests () {
	int a1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int a2[1] = {1};
	int a3[5] = {0};
	int a4[9] = {1, 3, 5, 7, 9, 2, 4, 6, 11};
	struct array arr1 = {a1, 10};
	struct array arr2 = {a2, 1};
	struct array arr3 = {a3, 5};
	struct array arr4 = {a4, 9};

	test (arr1, 10);
	test (arr2, 2);
	test (arr3, 1);
	test (arr4, 2);
}


void rand_tests (int n) {
	for (int i = 0; i < n; ++i)
		test (arr_generator(), (rand() % 1000 + 1));
}

int main () {

	srand (time(NULL));

	hand_tests ();
	rand_tests (100);

	return 0;
}