#include<stdio.h>
#include <ctype.h>
#include<stdlib.h>
#include<string.h>

#include "FileList.h"
#include "BSTree.h"
#include "invertedIndex.h"
//This function will insert filelist into BST
FileList newFilenode(char *word, char *filename){
    FileList node = malloc(sizeof(FileList)+100);
    node->filename = malloc(sizeof(char)*100);
    strcpy(node->filename, filename);
    node->tf = count_tf(word,filename);
    //printf("%s in %s tf is %.2f\n",word, filename,node->tf);
    node->next = NULL;
    return node;
}

//This function will show the filelist in a given BSTnode
void  showFileList(InvertedIndexBST root) {
    FileList head = root->fileList;
    FileList curr = head;
    while(curr != NULL) {
        printf("%s ",curr->filename);
        curr = curr->next;
    }
    return;
}
//This function will insert the Filenode from one BST node to other 
void insertFilenode(InvertedIndexBST desti, InvertedIndexBST from){
    FileList curr = desti->fileList;
    FileList new = from->fileList;
    FileList prev = NULL;
    FileList next = desti->fileList->next;
    char *inputname = new->filename;
    char *currname = curr->filename;
    
    while(curr != NULL) {
        next = curr->next;
        currname = curr->filename;
        if(strcmp(inputname,currname)<0) {
            if(prev == NULL) {
                desti->fileList = new;
                new->next = curr;
            } else {
                prev->next = new;
                new->next = next;
            }
            break;
        }else if(strcmp(inputname,currname) == 0){
            break;
        }
          
        prev = curr;
        curr = curr->next;
        
        prev->next = (curr == NULL)? new:prev->next;
    }
    return;
}
