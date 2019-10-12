#include<stdio.h>
#include <ctype.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include "invertedIndex.h"
#include "myBST.h"

//This function will create a new empty BST
InvertedIndexBST  CreateNewBst(char *word, char *filename) {
    return NewBSTNode(word,filename);
}

//This function will create a new node who contain a key word
InvertedIndexBST  NewBSTNode(char *word, char *filename) {
    InvertedIndexBST NewBST = malloc(sizeof(NewBST)+100);
    NewBST->word = malloc(sizeof(char)*100);
    word = normaliseWord(word);
    strcpy(NewBST->word,word);
    NewBST->fileList = newFilenode(word,filename);
    NewBST->left = NULL;
    NewBST->right = NULL;
    return NewBST;
}


//This function will insert the input node in appropriate place
InvertedIndexBST insertBSTNode(InvertedIndexBST input, InvertedIndexBST BST) {
    InvertedIndexBST curr = BST;
    InvertedIndexBST prev = BST;
    if(curr == NULL) {
        BST = input;
        return BST;
    }
    while(curr != NULL) {
        prev = curr;
        if(strcmp(input->word,curr->word) < 0) {
            curr = curr -> left;
            prev->left = (curr == NULL)? input : prev->left;
        } else if (strcmp(input->word,curr->word) == 0) {
            insertFilenode(curr, input);
            //free(input);
            return BST;
        } else {
            curr = curr -> right;
            prev->right = (curr == NULL)? input : prev->right;
        }
    }
    return BST;
}

//This function will count the number of word in files
double count_tf(char *word, char *filename) {
    double number = 0;
    double total = 0;
    FILE *f = fopen(filename,"r");
    char *temp = malloc(sizeof(char)*100);
    while(fscanf(f, "%s", temp) != EOF) {
        int same = 1;
        for(int i = 0; word[i] != '\0'; i++) {
            if(word[i] != temp[i] && word[i] != tolower(temp[i])){
                same = 0;
                break;
            }
        }
        number = (same == 1)?number+1:number;
        total++;
    }
    fclose(f);
    free(temp);
    double result = number/total;
    return result;
}
//This function will insert filelist into BST
FileList newFilenode(char *word, char *filename){
    FileList node = malloc(sizeof(FileList)+100);
    node->filename = malloc(sizeof(char)*100);
    strcpy(node->filename, filename);
    node->tf = count_tf(word,filename);
    node->next = NULL;
    return node;
}

//This function will show the filelist in a given BSTnode
void  showFileList(InvertedIndexBST root) {
    FileList head = root->fileList;
    
    for(FileList curr = head;curr != NULL;curr = curr->next)
        printf("%s ",curr->filename);
    return;
}
//This function will insert the Filenode from one BST node to other 
void insertFilenode(InvertedIndexBST desti, InvertedIndexBST from){
    FileList curr = desti->fileList;
    FileList new = from->fileList;
    FileList prev = NULL;
    //FileList next;

    char *inputname = new->filename;

    char *currname = curr->filename;

    while(curr != NULL) {
        //next = curr->next;
        currname = curr->filename;
        if(strcmp(inputname,currname)<0) {
            if(prev == NULL) {
                new->next = curr;
                desti->fileList = new;
            } else {
                prev->next = new;
                new->next = curr;
            }
            break;
        }
        
        if(strcmp(inputname,currname) == 0){
            break;
        }
        prev = curr;
        curr = curr->next;
        prev->next = (curr == NULL)? new:prev->next;
    }
    return;
}
double  count_idf(FileList head, double total_file) {
    double contain = 0;
    for(FileList temp = head; temp != NULL; temp=temp->next)contain++;
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
    return old;
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
    for(TfIdfList curr1 = node; curr1 != NULL; curr1 = curr1->next) {
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
            if(curr2 == NULL)break;
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
