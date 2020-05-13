#include "../include/TestList.h"

void Test_All_List(){

    Test_Init();

    Test_Push();

    Test_Exchange();

    Test_Move();

    Test_Send();

    fprintf(stderr, "Test List OK");
}

void Test_Init(){
    srand(time(NULL));
    struct hash_table* hashTable = hash_init(100 );
    struct list_t* list = Init_List(rand() % 10, hashTable);
    Assert_List(list);
    struct node_t* node = list->front_elem;
    for (int i = 0; i < Size_List(list); ++i){
        if (node->page != VOID){
            fprintf(stderr, "ERROR LIST: Init_List , Size = %d", Size_List(list));
            exit(1);
        }
        node = node->next;
    }
}

void Test_Push(){
    //Test 1
    int test1[10] = {1, 2, 3, 4, 5 ,6 ,7, 8, 9, 10};
    int test1_new[10] = {228, 1, 2, 3, 4, 5 ,6 ,7, 8, 9};
    struct list_t* list1 = Create_ListByArray(test1, 10);
    Assert_List(list1);
    Push_Front(list1, 228);
    int* b1 = Create_ArrayByList(list1);
    if (!Comp_Array(b1, test1_new, 10, Size_List(list1))){
        fprintf(stderr, "ERROR: Push_Front: Test 1");
        exit(1);
    }
    //hash_free(list1->hashTable);
    Free_List(list1);
    free(b1);

    //Test 2
    int test2[0] = {};
    int test2_new[1] = {228};
    struct list_t* list2 = Create_ListByArray(list2, 0);
    Resize_List(list2, 1);
    Assert_List(list2);
    Push_Front(list2, 228);
    int* b2 = Create_ArrayByList(list2);
    if (!Comp_Array(b2, test2_new, 1, Size_List(list2))){
        fprintf(stderr, "ERROR: Push_Front: Test 2");
        exit(1);
    }
    //hash_free(list2->hashTable);
    Free_List(list2);
    free(b2);

    //Test 3
    int test3[10] = {1, 2, 3, 4, 5 ,6 ,7, 8, 9, 10};
    int test3_new[10] = {2, 3, 4, 5 ,6 ,7, 8, 9, 10, 228};
    struct list_t* list3 = Create_ListByArray(test3, 10);
    Assert_List(list3);
    Push_Back(list3, 228);
    int* b3 = Create_ArrayByList(list3);
    if (!Comp_Array(b3, test3_new, 10, Size_List(list3))){
        fprintf(stderr, "ERROR: Push_Back: Test 3");
        exit(1);
    }
    //hash_free(list1->hashTable);
    Free_List(list3);
    free(b3);

    //Test 4
    int test4[0] = {};
    int test4_new[1] = {228};
    struct list_t* list4 = Create_ListByArray(list4, 0);
    Resize_List(list4, 1);
    Assert_List(list4);
    Push_Front(list4, 228);
    int* b4 = Create_ArrayByList(list4);
    if (!Comp_Array(b4, test4_new, 1, Size_List(list4))){
        fprintf(stderr, "ERROR: Push_Front: Test 4");
        exit(1);
    }
    //hash_free(list2->hashTable);
    Free_List(list4);
    free(b4);
}


void Test_Exchange(){
    //Test 1
    int test11[10] = {1, 2, 3, 4, 5 ,6 ,7, 8, 9, 10};
    struct list_t* list11 = Create_ListByArray(test11, 10);
    Assert_List(list11);
    int test12[10] = {11, 12, 13, 14, 15};
    struct list_t* list12 = Create_ListByArray(test12, 5);
    Assert_List(list12);
    int test11_new[10] = {228, 1, 2, 3, 4, 5 ,6 ,7, 8, 9};
    int test12_new[10] = {10, 11, 12, 13, 14};
    Exchange_Elem(list11, list12, 228);
    int* arr11 = Create_ArrayByList(list11);
    int* arr12 = Create_ArrayByList(list12);
    if (!Comp_Array(arr11, test11_new, 10, Size_List(list11)) ||
        !Comp_Array(arr12, test12_new, 5, Size_List(list12))){
        fprintf(stderr, "ERROR: Exchange: Test 1");
        exit(1);
    }
    //hash_free(list11->hashTable);
    Free_List(list11);
    //hash_free(list12->hashTable);
    Free_List(list12);
    free(arr11);
    free(arr12);
}

void Test_Move(){
    //Test 1
    int test1[10] = {1, 2, 3, 4, 5 ,6 ,7, 8, 9, 10};
    struct list_t* list1 = Create_ListByArray(test1, 10);
    Assert_List(list1);
    int test1_new[10] = {10, 1, 2, 3, 4, 5 ,6 ,7, 8, 9};
    Move_Elem_Page(list1, 10);
    int* arr1 = Create_ArrayByList(list1);
    if (!Comp_Array(arr1, test1_new, 10, Size_List(list1))){
        fprintf(stderr, "ERROR: Move: Test 1");
        exit(1);
    }
    //hash_free(list1->hashTable);
    Free_List(list1);
    free(arr1);

    //Test 2
    int test2[10] = {1, 2, 3, 4, 5 ,6 ,7, 8, 9, 10};
    struct list_t* list2 = Create_ListByArray(test2, 10);
    Assert_List(list2);
    int test2_new[10] = {5, 1, 2, 3, 4, 6 ,7, 8, 9, 10};
    Move_Elem_Page(list2, 5);
    int* arr2 = Create_ArrayByList(list2);
    if (!Comp_Array(arr2, test2_new, 10, Size_List(list2))){
        fprintf(stderr, "ERROR: Move: Test 2");
        exit(1);
    }
    //hash_free(list1->hashTable);
    Free_List(list2);
    free(arr2);

    //Test 3
    int test3[1] = {1};
    struct list_t* list3 = Create_ListByArray(test3, 1);
    Assert_List(list3);
    Move_Elem_Page(list3, 5);
    int* arr3 = Create_ArrayByList(list3);
    if (!Comp_Array(arr3, test3, 1, Size_List(list3))){
        fprintf(stderr, "ERROR: Move: Test 3");
        exit(1);
    }
    //hash_free(list1->hashTable);
    Free_List(list3);
    free(arr3);
}

void Test_Send(){
    //Test 1
    int test11[10] = {1, 2, 3, 4, 5 ,6 ,7, 8, 9, 10};
    struct list_t* list11 = Create_ListByArray(test11, 10);
    Assert_List(list11);
    int test12[10] = {11, 12, 13, 14, 15};
    struct list_t* list12 = Create_ListByArray(test12, 5);
    Assert_List(list12);
    int test11_new[10] = {1, 2, 4, 5 ,6 ,7, 8, 9, 10, VOID};
    int test12_new[10] = {3, 11, 12, 13, 14};
    Send_to_Main(list11, list12, 3);
    int* arr11 = Create_ArrayByList(list11);
    int* arr12 = Create_ArrayByList(list12);
    if (!Comp_Array(arr11, test11_new, 10, Size_List(list11)) ||
        !Comp_Array(arr12, test12_new, 5, Size_List(list12))){
        fprintf(stderr, "ERROR: Send: Test 1");
        exit(1);
    }
    //hash_free(list11->hashTable);
    Free_List(list11);
    //hash_free(list12->hashTable);
    Free_List(list12);
    free(arr11);
    free(arr12);
}

char Comp_Array(int* arr1, int* arr2, int len1, int len2){
    if (len1 != len2)
        return 0;
    int len = len1;
    for (int i = 0; i < len; ++i){
        if (arr1[i] != arr2[i]) {
            printf("%d != %d", arr1[i], arr2[i]);
            return 0;
        }
    }
    return 1;
}

void Print_Array(int* arr, int len){
    printf("[");
    for(int i = 0; i < len; ++i){
        if (i != len - 1)
            printf(" %d,", arr[i]);
        else
            printf(" %d ]\n", arr[i]);
    }
}


