#include "invertedIndex.h"
//This function will create a new empty BST
InvertedIndexBST  CreateNewBst();
InvertedIndexBST  NewBSTNode(char *word, char *filename);
InvertedIndexBST  insertBSTNode(InvertedIndexBST input, InvertedIndexBST first);
double count_tf(char *word, char *filename);

double  count_idf(FileList head, double total_file);
TfIdfList CreateNewTfIdf(void);
TfIdfList NewTfnode(char *filename, double tfidf);
TfIdfList TfIdfListInsert(TfIdfList old, TfIdfList new);
InvertedIndexBST searchTree(char *word, InvertedIndexBST tree);
void showTFIdfList(TfIdfList list);
TfIdfList mergeTwoTfIdfList(TfIdfList desti, TfIdfList from);
void freeTfIdfList(TfIdfList desti);
void deleteDuplicateNodes(TfIdfList node);
TfIdfList reorderTfIdfList(TfIdfList node);

FileList    newFilenode(char *word, char *filename);
void    insertFilenode(InvertedIndexBST head, InvertedIndexBST input);
void  showFileList(InvertedIndexBST root);
