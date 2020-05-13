#pragma once

#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "List.h"
#include "LRU_hash.h"

//test ALL
void Test_All_List();

//test func: List_Init
void Test_Init();

//test func: Push_Back & Push_Front
void Test_Push();

//test func: Exchange_Elem
void Test_Exchange();

//test func: Move_Elem_Page
void Test_Move();

//test func: Send_to_Main
void Test_Send();

char Comp_Array(int* arr1, int* arr2, int len1, int len2);

void Print_Array(int* arr, int len);


