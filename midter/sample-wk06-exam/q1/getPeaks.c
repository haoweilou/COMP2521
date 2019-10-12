// getPeaks.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/* 
    You will submit only this one file.

    Implement the function "getPeaks" below. Read the exam paper for 
    detailed specification and description of your task.  

    - DO NOT modify code in the file DLList.h . 
    - You can add helper functions in this file.  
    - DO NOT add "main" function in this file. 
    
*/

DLList getPeaks(DLList L){

	DLList peaksL = newDLList();
    for(DLListNodeP curr = L->first; curr != NULL;curr = curr->next) {
        if(curr == L->first)
            continue;
        if(curr == L->last)
            continue;
        if(curr->value > curr->next->value && curr->value > curr->prev->value) {
            DLListNodeP new = newDLListNode(curr->value);
            if(peaksL->first == NULL) {
                peaksL->first = new;
                peaksL->curr = new; 
                peaksL->last = new;
            } else {
                peaksL->last->next = new;
                new->prev = peaksL->last;
                peaksL->last = new;
            }
            peaksL->nitems = peaksL->nitems + 1;
        }
    }
    
	return peaksL;

}



