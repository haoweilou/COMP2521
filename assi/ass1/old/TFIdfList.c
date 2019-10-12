#include<stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "invertedIndex.h"
#include "BSTree.h"
#include "FileList.h"
#include "TFIdfList.h"

double  count_idf(FileList head, double total_file) {
    double contain = 0;
    for(FileList temp = head; temp != NULL; temp=temp->next)
        contain++;
    //printf("total %f files\n",total_file);
    //printf("contain %f files\n",contain);
    return log(total_file/contain)/log(10);
}

TfIdfList CreateNewTfIdf(void) {
    return NULL;
}

TfIdfList NewTfnode(char *filename, double tfidf){
    TfIdfList new = malloc(sizeof(TfIdfList)+100);
    new->filename = malloc(100);
    strcpy(new->filename, filename);
    new->tfidf_sum = tfidf;
    new->next = NULL;
    return new;
}

TfIdfList TfIdfListInsert(TfIdfList old, TfIdfList new) {
    TfIdfList curr = old;
    if(old == NULL) {
        old = new;
        return old;
    }
    TfIdfList prev = NULL;
    while(curr!=NULL) {
        if(new->tfidf_sum > curr->tfidf_sum) {
            if(prev == NULL) {
                new->next = old;
                old = new;
                return old;
            }
            prev->next = new;
            new->next = curr;
            return old;
        }else if(new->tfidf_sum == curr->tfidf_sum) {
            if(strcmp(new->filename, curr->filename) < 0){
                if(prev == NULL) {
                    new->next = old;
                    old = new;
                    return old;   
                }
                prev->next = new;
                new->next = curr;
                return old;
            } else if (strcmp(new->filename, curr->filename) == 0) {
                curr->tfidf_sum += new->tfidf_sum;
                return old;
            }
        }
        prev = curr;
        if(prev->next == NULL) {
            prev->next = new;
            new->next = NULL;
            return old;
        }
        curr = curr->next;
    }
    //printf("old is %s, whith %f\n",old->filename,old->tfidf_sum );
    //printf("new is %s, whith %f\n",new->filename,new->tfidf_sum );
    return 0;
}
InvertedIndexBST searchTree(char *word, InvertedIndexBST tree) {
    InvertedIndexBST temp = tree;
    while(temp != NULL && strcmp(word, temp->word) != 0) {
        if(strcmp(word, temp->word) > 0) {
            temp = temp->right;
            continue;
        }
        if(strcmp(word, temp->word) < 0) {
            temp = temp->left;
            continue;
        }
    }
    //printf("The temp word is [%s]\n",temp->word);
    return temp;
}
void showTFIdfList(TfIdfList list) {
    for(TfIdfList curr = list; curr != NULL; curr = curr->next){
        printf("[%s], tfidf_sum is: %.5lf\n",curr->filename, curr->tfidf_sum);
    }
}

TfIdfList mergeTwoTfIdfList(TfIdfList desti, TfIdfList from) {
    TfIdfList prev = NULL;
    for(TfIdfList temp = desti; temp != NULL;) {
        prev = temp;
        temp = temp->next;
    }
    prev->next = from;
    return desti;
}
void freeTfIdfList(TfIdfList desti) {
    TfIdfList prev = NULL;
    for(TfIdfList temp = desti; temp != NULL; temp = temp->next) {
        free(prev);
        prev = temp;
    }
    free(prev);
}
void deleteDuplicateNodes(TfIdfList node) {
    TfIdfList curr1 = node;
    for(; curr1 != NULL; curr1 = curr1->next) {
        TfIdfList prev2 = curr1;
        TfIdfList curr2 = curr1;
        TfIdfList next2 = curr2;
        while(curr2 != NULL) {
            if(strcmp(curr1->filename, curr2->filename) == 0){
                if(curr1 != curr2){
                    curr1->tfidf_sum += curr2->tfidf_sum;
                    prev2->next = next2;
                    free(curr2);
                    curr2 = next2;
                    if(curr2 != NULL)next2 = curr2->next;
                    continue;  
                }
            }
            prev2 = curr2;
            curr2 = curr2->next;
            if(curr2 == NULL)
                break;
            next2 = curr2->next;
        }
        
    }
}
TfIdfList reorderTfIdfList(TfIdfList node) {
    TfIdfList new = NULL;
    for(TfIdfList curr = node; curr != NULL; curr = curr->next) {
        TfIdfList newnode = NewTfnode(curr->filename,curr->tfidf_sum);
        new = TfIdfListInsert(new, newnode);
    }
    return new;
}
