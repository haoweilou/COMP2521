
/* countEven.c 
   Written by Ashesh Mahidadia, October 2017
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "BSTree.h"

/* 
    You will submit only this one file.

    Implement the function "countEven" below. Read the exam paper for 
    detailed specification and description of your task.  

    - You can add helper functions in this file, if required.  

    - DO NOT modify code in the file BSTree.h . 
    - DO NOT add "main" function in this file. 
*/


int countEven(BSTree t){
 	int count = 0;
	if(t == NULL) return 0;
	if(t->left == NULL && t->right == NULL) return 0;
	else if (t->left == NULL || t->right == NULL) count++;
	count += countEven(t->left);
	count += countEven(t->right);
	

	// Implement this function, 
	// also change the return value below!
	return count;
    

}



