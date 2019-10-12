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


/*int main(void) {
    InvertedIndexBST tree = generateInvertedIndex("collection.txt");
    //printf("%s\n",tree->word);
    //int d = BSTdepth(tree);
    printInvertedIndex(tree);
    char *words[] = {"moon",NULL};
    TfIdfList new = retrieve(tree,words, 7);
    //showTFIdfList(new);
    return 0;
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
    char *filename = malloc(sizeof(char)*100);
    char *word = malloc(sizeof(char)*100);
    InvertedIndexBST BST = NULL;
    while(fscanf(f,"%s",filename) != EOF){
        FILE *fi = fopen(filename, "r");
        while(fscanf(fi,"%s",word) != EOF){
            InvertedIndexBST new = NewBSTNode(word, filename);
            if(BST == NULL) BST = new;
            else BST = insertBSTNode(new, BST);
        }
        fclose(fi);
    }
    fclose(f);
    
    return BST;
}

void printInvertedIndex(InvertedIndexBST tree) {
    if (tree == NULL) return;
    printInvertedIndex(tree->left);
    FILE *output = fopen("invertedIndex.txt","a");
    fprintf(output,"%s ",tree->word);
    for (FileList temp = tree->fileList; temp != NULL; temp = temp->next)
            fprintf(output,"%s ", temp->filename);
    fprintf(output,"\n");
    fclose(output);
    printInvertedIndex(tree->right);
}

TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord , int D) {
    //find the node who contains the word
    InvertedIndexBST temp = searchTree(searchWord, tree);
    if(temp == NULL) return NULL;
    TfIdfList list = NULL;
    for(FileList curr = temp->fileList; curr != NULL; curr = curr->next) {
        double tfidf = curr->tf * count_idf(temp->fileList, D);
        TfIdfList newnode = NewTfnode(curr->filename,tfidf);
        list = TfIdfListInsert(list, newnode);
    }
    return list; 
}

TfIdfList retrieve(InvertedIndexBST tree, char *searchWords[], int D) {
    TfIdfList list = NULL;
    for(int i = 0; searchWords[i] != NULL; i++) {
        TfIdfList new = calculateTfIdf(tree, searchWords[i] , D);
        if(list == NULL)list = new;
        else list = mergeTwoTfIdfList(list, new);
    }
    deleteDuplicateNodes(list);
    list = reorderTfIdfList(list);
    return list;
}

