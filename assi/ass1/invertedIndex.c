#include<stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "invertedIndex.h"
#include "myBST.h"
#include <assert.h>


#define MAX 100
//double num_of_file = 0;
char * normaliseWord(char *str);
InvertedIndexBST generateInvertedIndex(char *collectionFilename);
void printInvertedIndex(InvertedIndexBST tree);
TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord , int D);
TfIdfList retrieve(InvertedIndexBST tree, char *searchWords[], int D);


/* int main(void) {
    //InvertedIndexBST tree = generateInvertedIndex("collection.txt");
    //printInvertedIndex(tree);
    //char *words[] = {"nasa", "sun","and","love",NULL};
    //TfIdfList new = retrieve(tree,words, 7);
    //showTFIdfList(new);
    //return 0;
}*/

char * normaliseWord(char *str) {
    //start stand for how many leading spaces str have
    int start = 0;
    for(int i = 0; str[i] == ' '; i++)
        start++;
    //printf("start is %d\n",start);
    for(int i = 0; str[i] != '\0'; i++)
        str[i] = str[i+start];
    //remove trailing columns
    int length = strlen(str);
    for(int i = length - 1; str[i] == ' '; i--)
        str[i] = '\0';
    //remove ',' ';' '.' '?' in last
    int j = strlen(str) - 1;
    if(str[j] == ',' || str[j] == ';' || str[j] == '.' || str[j] == '?')
        str[j] = '\0';
    //convert to lower case
    for(int i = 0; str[i] != '\0'; i++) 
        str[i] = tolower(str[i]);
    return str;
}

InvertedIndexBST generateInvertedIndex(char *collectionFilename) {
    FILE *f = fopen(collectionFilename,"r");
    char *unsorted = malloc(sizeof(char)*100);
    char *word = malloc(sizeof(char)*100);
    int times = 0;
    InvertedIndexBST BST = NULL;
    while(fscanf(f,"%s",unsorted) != EOF){
        FILE *fi = fopen(unsorted, "r");
        while(fscanf(fi,"%s",word) != EOF){
            if(times == 0) {
                BST = CreateNewBst(word, unsorted);
                times++;
            } else {
                InvertedIndexBST new = NewBSTNode(word, unsorted);
                BST = insertBSTNode(new, BST);   
            }
        }
        fclose(fi);
    }
    //printInvertedIndex(BST);
    fclose(f);
    
    return BST;
}

void printInvertedIndex(InvertedIndexBST tree) {
    if (tree != NULL) {   
       printInvertedIndex(tree->left);
       printf("%s ",tree->word);
       showFileList(tree);
       printf("\n");
       printInvertedIndex(tree->right);
    }
    return;
}

TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord , int D) {
    //find the node who contains the word
    InvertedIndexBST temp = searchTree(searchWord, tree);
    if(temp == NULL) return NULL;
    TfIdfList list = CreateNewTfIdf();
    FileList curr = temp->fileList;
    //printf("%s\n",temp->word);
    double tf = 0;
    double idf = count_idf(curr, D);
    //printf("idf for %s is %f\n",searchWord,idf);
    double tfidf = 0;
    while(curr != NULL) {
        //printf("%s->",curr->filename);
        //printf("%s->",curr->filename);
        tf = curr->tf;
        //printf("tf fof %s is %f\n", curr->filename, curr->tf);
        tfidf = tf*idf;
        //printf("tfidf fof %s is %f\n", curr->filename, tfidf);
        TfIdfList newnode = NewTfnode(curr->filename,tfidf);
        list = TfIdfListInsert(list, newnode);
        curr = curr->next;
    }
    //printf("\n");
    return list; 
}

TfIdfList retrieve(InvertedIndexBST tree, char *searchWords[], int D) {
    TfIdfList list = NULL;
    for(int i = 0; searchWords[i] != NULL; i++) {
        TfIdfList new = calculateTfIdf(tree, searchWords[i] , D);
        if(list == NULL)
            list = new;
        else
            list = mergeTwoTfIdfList(list, new);
        printf("%s\n",searchWords[i]);
        showTFIdfList(list);
        printf("\n\n");
    }
    deleteDuplicateNodes(list);
    list = reorderTfIdfList(list);
    //printf("\n\n");
    return list;
}

