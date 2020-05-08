#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct node_t {
    struct node_t* next;
    struct node_t* prev;
    int hash;
    int page; // page number
};

struct hash_node_t
{
	struct node_t *list_node_t;
	struct hash_node_t *next, *prev;
	int page;
};

struct hash_table
{
	struct hash_node_t *table;
	int capacity;
};



struct list_t {
    struct node_t* front_elem;
    struct node_t* back_elem;
    struct hash_table* hashTable;
    int size;
};

struct cache_t { /* cache data structure */

	struct list_t main_mem; /* main memory list + hash */
	struct hash_table main_hash;
	unsigned main_mem_size;

	unsigned elements_ctr; /* elements counter */
};






/////////////////HAAAAAAAAAAAAAAAAAAAAAAASH

// return hash of the page
int hash_func (int page, struct hash_table s);

// Create hash_node with these arguments
struct hash_node_t* hash_create_node (int page, struct node_t *list_node_t, struct hash_node_t *prev);

//find this page in the branch
struct hash_node_t* hash_find_page (int page, struct hash_table s);

// create hash table with size = capacity (capacity >> list_size)
struct hash_table* hash_init (int capacity); 

// check if the page in hash table (so that in cache too) (ret 1 if yes, 0 - vice verse)
char hash_check_elem (int page, struct hash_table s);

// add this page in hash table
void hash_add_elem (int page, struct hash_table* s, struct node_t* pNode);

// delete this page from hash table
void hash_delete_elem (int page, struct hash_table* s);

// free hash table
void hash_free (struct hash_table* s);

// free branch of hash
void hash_free_branch (struct hash_node_t* top);
 
//return position of current page in the list
struct node_t* hash_page_position (int page, struct hash_table *s);








//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// return hash of the page (hash < size of hash table)
int hash_func (int page, struct hash_table s) {
	int hash = (((page < 0) ? -page : page) % s.capacity) * 19 % s.capacity;
	return hash;
}

//Create hash_node
struct hash_node_t* hash_create_node (int page, struct node_t *list_node_t, struct hash_node_t *prev) {
	struct hash_node_t* node;
	node = (struct hash_node_t*) calloc (1, sizeof (struct hash_node_t));
	
	node->page = page;
	node->prev = prev;
	node->list_node_t = list_node_t;

	return node;
}

//find this page in the branch
struct hash_node_t* hash_find_page (int page, struct hash_table s) {
	int hash_page;
	struct hash_node_t *h_node;
	
	hash_page = hash_func (page, s);
	h_node = s.table + hash_page;
	
	while (h_node != NULL) {
		
		if (h_node->list_node_t != NULL && h_node->page == page)
			return h_node;

		h_node = h_node->next;
	}

	return NULL;
}

// create hash table with size=capacity (capacity >> list_size)
struct hash_table* hash_init (int capacity) {
	struct hash_table* s;
	s = (struct hash_table*) calloc (1, sizeof (struct hash_table));
	s->table = (struct hash_node_t*) calloc (capacity, sizeof(struct hash_node_t));
	assert (s->table != NULL);

	s->capacity = capacity;

	return s;
}

// check if the page in hash table (Cache) (ret 1 if yes, 0 - vice verse)
char hash_check_elem (int page, struct hash_table s) {
	struct hash_node_t *h_node;
	
	h_node = hash_find_page (page, s);
	
	return (h_node != NULL);
}

// add this page in hash table
void hash_add_elem (int page, struct hash_table* s, struct node_t* pNode) {
	
	struct hash_node_t* ptr;
	int hash_page;

	assert (pNode != NULL);
	if (hash_check_elem (page, *s) == 1)
		return;

	hash_page = hash_func (page, *s);
	ptr = s->table + hash_page;

	if (ptr->list_node_t == NULL) {
		ptr->list_node_t = pNode;
		ptr->page = page;
		return;
	}

	while (ptr->list_node_t != NULL && ptr->next != NULL)
		ptr = ptr->next;

	ptr->next = hash_create_node (page, pNode, ptr);
}


//return position of current page in the list
struct node_t* hash_page_position (int page, struct hash_table *s) {
	
	struct hash_node_t* h_node;

	h_node = hash_find_page (page, *s);

	return (h_node != NULL) ? h_node->list_node_t : NULL;
}

// delete this page from hash table
void hash_delete_elem (int page, struct hash_table* s) {
	struct hash_node_t* h_node;

	if (hash_check_elem (page, *s) == 0)
		return;
	
	h_node = hash_find_page (page, *s);
	
	if (h_node->prev == NULL) {
		if (h_node->next == NULL) {
			h_node->page = 0;
			h_node->list_node_t = NULL;
			return;
		}
		
		*h_node = *(h_node->next);
		h_node->prev = NULL;
		free(h_node->next->prev);
		h_node->next->prev = h_node;
		return;
	}

	h_node->prev->next = h_node->next;
	
	if (h_node->next != NULL)
		h_node->next->prev = h_node->prev;

	free (h_node);
}

//free branch of hash
void hash_free_branch (struct hash_node_t* top) {
	if (top == NULL)
		return;

	if (top->next == NULL){
		free (top);
		return;
	}

	hash_free_branch (top->next);
}

// free hash table
void hash_free (struct hash_table* s) {
	int i;
	
	for (i = 0; i < s->capacity; ++i)
		hash_free_branch (s->table[i].next);

	free(s->table);
	s->capacity = 0;
	free (s);
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!








///////////////LIIIIIIIIIIIIIIIIIIIIIIIIIIIST

//init list of the selected size
struct list_t* Init_List(int size, struct hash_table* hashTable);

//access the first element
struct node_t* Front_Elem(struct list_t* list);

//access the last element
struct node_t* Back_Elem(struct list_t* list);

//check whether the underlying container is empty
char Is_Empty (struct list_t* list);

//returns the number of elements
size_t Size_List (struct list_t* list);

//add elem in the top of the list, end of the list deleted
void Push_Front(struct list_t* list, int page);

//add elem in the top of the list1 an, end of the list moves to the top of the list2
void Exchange_Elem(struct list_t* list1, struct list_t* list2, int page);

//Move elem forward by page
//if page not found nothing happens
void Move_Elem_Page(struct list_t* list, int page);

//free list
void Free_List (struct list_t* list);








//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
static struct node_t* Create_Node();

struct list_t* Init_List(int size, struct hash_table* hashTable)
{
    
    struct node_t* top = NULL;
    struct node_t* tmp = NULL;
    struct list_t* list;
    int i;

    list = (struct list_t*)calloc(1, sizeof(struct list_t));
    
    assert(hashTable);
    assert(list);

    if (size == 0)
        return list;

    top = Create_Node();

    list->front_elem = top;
    list->size = size;
    tmp = top;

    for (i = 1; i < size; ++i)
    {
        tmp->next = Create_Node();
        tmp->next->prev = tmp;
        tmp = tmp->next;
    }

    list->back_elem = tmp;
    list->hashTable = hashTable;

    assert(list->back_elem);

    return list;
}

struct node_t* Front_Elem(struct list_t* list)
{
    assert(list);
    return list->front_elem;
}

struct node_t* Back_Elem(struct list_t* list)
{
    assert(list);
    return list->back_elem;
}

char Is_Empty (struct list_t* list)
{
    assert(list);
    
    if (list->size == 0 && list->front_elem == NULL && list->back_elem == NULL)
        return 1;
    
    if (list->size == 0 && (list->front_elem != NULL || list->back_elem != NULL))
    {
        printf("ERROR : list size");
        exit(1);
    }
    
    return 0;
}

size_t Size_List (struct list_t* list)
{
    assert(list);
    return list->size;
}


void Push_Front(struct list_t* list, int page)
{
    struct node_t* old_front = NULL;
    struct node_t* new_front = NULL;

    //Print_List_Back(list);
    
    if (Is_Empty(list))
    {
        printf("ERROR: list void");
        exit(3);
    }
    
    if (list->size == 1)
    {
        list->back_elem->page = page;
        return;
    }
    
    old_front = list->front_elem;
    new_front = list->back_elem;

    hash_delete_elem(new_front->page, list->hashTable);

    list->back_elem = list->back_elem->prev;
    list->back_elem->next = NULL;

    new_front->page = page;
    new_front->prev = NULL;
    new_front->next = old_front;

    old_front->prev = new_front;
    list->front_elem = new_front;

    hash_add_elem(page, list->hashTable, list->front_elem);
}

void Exchange_Elem(struct list_t* list1, struct list_t* list2, int page)
{
    int page_back = list1->back_elem->page;
    Push_Front(list1, page);
    Push_Front(list2, page_back);
}

void Move_Elem_Page(struct list_t* list, int page)
{
    struct node_t* node = NULL;
    struct node_t* tmp = NULL;

    assert(list);

    node = hash_page_position(page, list->hashTable);

    if(node == NULL)
        return;

    if (node == list->front_elem)
        return;

    if (node == list->back_elem)
    {
        tmp = node->prev;
        tmp->next = NULL;
        list->back_elem = tmp;
    }
    else
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    node->next = list->front_elem;
    list->front_elem->prev = node;
    list->front_elem = node;
    node->prev = NULL;
}

void Free_List (struct list_t* list)
{
    struct node_t* top = list->front_elem;
    struct node_t* tmp = NULL;
    
    while (top != NULL)
    {
        tmp = top->next;
        free(top);
        top = tmp;
    }
    
    list->size = 0;
    free(list);
}


static struct node_t* Create_Node()
{
    struct node_t* node;
    node = (struct node_t*) calloc (1, sizeof (struct node_t));
    assert(node);
    return node;
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!






///////////////CAAAAAAAAAAAAAAAAAACHE

struct cache_t* cache_init(int main_size); /* initilizes cache */

int handle_page(struct cache_t* cache, int page); /* page handler, returns -1 if miss and page hash if hit*/

void cache_delete(struct cache_t* cache); /* deletes cache */

void run_tests(struct cache_t* cache, int* arr, int arr_size); /* test program */






//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
struct cache_t* cache_init(int main_size) {

	int capacity;
	struct cache_t* cache;

	assert(main_size >= 0);

	capacity = 10 * main_size;

	cache = (struct cache_t*) calloc(1, sizeof(struct cache_t));
	assert(cache);

	cache->main_hash = *(hash_init(capacity));
	assert(&(cache->main_hash));

	cache->main_mem = *(Init_List(main_size, &(cache->main_hash)));
	assert(&(cache->main_mem));

	cache->main_mem_size = main_size;

	cache->elements_ctr = 0;

	return cache;
}

int handle_page(struct cache_t* cache, int page) {
	int res;
	
	if ((res = hash_check_elem (page, cache->main_hash)) == 0)
		Push_Front (&cache->main_mem, page);
	else
		Move_Elem_Page (&cache->main_mem, page);

	return res;
}


void cache_delete(struct cache_t* cache) {

	struct list_t* main_mem = &(cache->main_mem);
	struct hash_table* main_hash = &(cache->main_hash);

	assert(cache);

	hash_free(main_hash);
	Free_List(main_mem);

	free(cache);
}

void run_tests(struct cache_t* cache, int *arr, int arr_size) {
	int hits = 0;
	int n = 0;

	for (n = 0; n < arr_size; ++n)
		hits += handle_page(cache, arr[n]);

	printf("%d\n", hits);
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!





int main () {

	int main_size, i, arr_size, *arr;

	struct cache_t* cache;

	scanf ("%d %d", &main_size, &arr_size);

	arr = (int*) calloc (arr_size, sizeof (int));

	for (i = 0; i < arr_size; ++i)
		scanf ("%d", &arr[i]);

	cache = cache_init(main_size);

	run_tests(cache, arr, arr_size);

	//cache_delete (cache);

	return 0;
}