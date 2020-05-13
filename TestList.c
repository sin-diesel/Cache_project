#include "TestList.h"

void Test_All_List(){

    Test_Push();

    Test_Exchange();

    Test_Move();

    Test_Send();

    fprintf(stderr, "Test List OK");
}

void Test_Push(){

    for (int j = 0; j < NUM_TESTS; j++) {
        //test Init
        struct hash_table *hashTable = hash_init(HASH_CAPACITY);
        struct list_t *list = Init_List(LIST_CAPACITY, hashTable);
        Assert_List(list);

        struct node_t *tmp = list->front_elem;
        for (int i = 0; i < Size_List(list); ++i) {
            tmp->page = i;
            tmp = tmp->next;
        }

        for (int i = 0; i < Size_List(list); ++i) {
            Push_Back(list, i);
            if (Front_Elem(list) != (i + 1) % Size_List(list)) {
                Print_List_Front(list);
                Print_List_Back(list);
                fprintf(stderr, "ERROR LIST: Push_Back: Front elem error - %d != %d", Front_Elem(list),
                        (i + 1) % Size_List(list));
                exit(1);
            }
            if (Back_Elem(list) != i) {
                Print_List_Front(list);
                Print_List_Back(list);
                fprintf(stderr, "ERROR LIST: Push_Back: Back elem error - %d != %d", Back_Elem(list), i);
                exit(2);
            }
        }
        Assert_List(list);

        for (int i = 0; i < Size_List(list); ++i) {
            Push_Front(list, Size_List(list) - i - 1);
            if (Front_Elem(list) != Size_List(list) - i - 1) {
                Print_List_Front(list);
                Print_List_Back(list);
                fprintf(stderr, "ERROR LIST: Push_Front: Front elem error - %d != %d", Front_Elem(list),
                        Size_List(list) - i - 1);
                exit(3);
            }
            if (Back_Elem(list) != (2 * Size_List(list) - i - 2) % Size_List(list)) {
                Print_List_Front(list);
                Print_List_Back(list);
                fprintf(stderr, "ERROR LIST: Push_Front: Back elem error -  %d != %d", Back_Elem(list),
                        Size_List(list) - i - 2);
                exit(4);
            }
        }
        Assert_List(list);
        Free_List(list);
    }
}


void Test_Exchange(){
    for (int j = 0; j < NUM_TESTS; ++j) {
        struct hash_table *hashTable = hash_init(HASH_CAPACITY);
        struct list_t *list1 = Init_List(LIST_CAPACITY, hashTable);
        Assert_List(list1);

        struct list_t *list2 = Init_List(LIST_CAPACITY / 2, hashTable);
        Assert_List(list2);
        assert(!Is_Empty(list2));

        struct node_t *tmp = list1->front_elem;
        for (int i = 0; i < Size_List(list1); ++i) {
            tmp->page = Size_List(list1) - i - 1;
            tmp = tmp->next;
        }

        for (int i = 0; i < Size_List(list2); ++i)
            Exchange_Elem(list1, list2, i);

        tmp = list2->front_elem;
        for (int i = 0; i < Size_List(list2); ++i) {
            if (tmp->page != Size_List(list2) - i - 1) {
                Print_List_Front(list1);
                Print_List_Front(list2);
                fprintf(stderr, "ERROR LIST: Exchange_Elem - %d != %d", tmp->page, i);
                exit(5);
            }
            tmp = tmp->next;
        }
        Assert_List(list1);
        Assert_List(list2);
    }
}

void Test_Move(){
    struct hash_table *hashTable = hash_init(HASH_CAPACITY);
    struct list_t *list = Init_List(LIST_CAPACITY, hashTable);
    Assert_List(list);

    for (int i = Size_List(list) - 1; i >= 0; --i) {
        Push_Front(list, i);
    }

    //test 1
    Move_Elem_Page(list, 0);
    Assert_List(list);
    if (Front_Elem(list) != 0)
    {
        Print_List_Front(list);
        fprintf(stderr, "ERROR LIST: Move_Elem_Page: test 1");
        exit(6);
    }

   //test 2
    Move_Elem_Page(list, Back_Elem(list));
    Assert_List(list);
    if (Front_Elem(list) != Size_List(list) - 1)
    {
        Print_List_Front(list);
        fprintf(stderr, "ERROR LIST: Move_Elem_Page: test 2");
        exit(6);
    }

    //test 3
    srand(time(NULL));
    for (int i = 0; i < NUM_TESTS; i++) {
        int rp = rand() % (LIST_CAPACITY - 1);
        Move_Elem_Page(list, rp);
        Assert_List(list);
        if (Front_Elem(list) != rp) {
            Print_List_Front(list);
            fprintf(stderr, "ERROR LIST: Move_Elem_Page: test 3");
            exit(6);
        }
    }
}

void Test_Send(){
    struct hash_table *hashTable = hash_init(HASH_CAPACITY);
    struct list_t *list1 = Init_List(LIST_CAPACITY, hashTable);
    Assert_List(list1);

    struct list_t *list2 = Init_List(LIST_CAPACITY, hashTable);
    Assert_List(list2);

    for (int i = Size_List(list1) - 1; i >= 0; --i) {
        Push_Front(list1, i);
    }
    Assert_List(list1);

    struct node_t* tmp = NULL;

    //test 1
    int page = Front_Elem(list1);
    Send_to_Main(list1, list2, page);
    Assert_List(list1);
    Assert_List(list2);
    if (Back_Elem(list1) != -1 && Front_Elem(list2) != page){
        fprintf(stderr, "ERROR LIST: Send_to_Main : test 1");
        exit(7);
    }
    tmp = list1->front_elem;
    for (int i = 1; i < Size_List(list1) - 2; ++i){
        if (tmp->page != i ){
            Print_List_Front(list1);
            printf("[%d]", i);
            fprintf(stderr, "ERROR LIST: Send_to_Main : test 1");
            exit(8);
        }
        tmp = tmp->next;
    }

    //test 2
    page = rand() % (Size_List(list1) - 2);
    Send_to_Main(list1, list2, page);
    Assert_List(list1);
    Assert_List(list2);
    if (Back_Elem(list1) != -1 && Front_Elem(list2) != page ){
        fprintf(stderr, "ERROR LIST: Send_to_Main : test 2");
        exit(7);
    }
}


