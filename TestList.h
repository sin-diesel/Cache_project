#pragma once

#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "List.h"
#include "LRU_hash.h"

enum {
    NUM_TESTS = 100,
    HASH_CAPACITY = 1000000,
    LIST_CAPACITY = 10
};

//test ALL
void Test_All_List();

//test func: Push_Back & Push_Front
void Test_Push();


//test func: Exchange_Elem
void Test_Exchange();

//test func: Move_Elem_Page
void Test_Move();

//test func: Send_to_Main
void Test_Send();


