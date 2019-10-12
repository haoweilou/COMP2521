#include "invertedIndex.h"
//This function will create a new empty BST node
InvertedIndexBST  NewBSTNode(char *word, char *filename);
//insertBSTNode function insert a new nood 'input' in to a tree
InvertedIndexBST  insertBSTNode(InvertedIndexBST input, InvertedIndexBST root);
//This function will rotate the tree left
InvertedIndexBST Rotateleft(InvertedIndexBST root);
//This function will rotate the tree right
InvertedIndexBST Rotateright(InvertedIndexBST root);
//This function will calculate the depth of tree
int BSTdepth(InvertedIndexBST root);
//This function will count the tf value of a word in a file
double count_tf(char *word, char *filename);
//This function will count the idf value
double  count_idf(FileList head, double total_file);
//Create a new Tf node
TfIdfList NewTfnode(char *filename, double tfidf);
//insert Tf node into appropriate place
TfIdfList TfIdfListInsert(TfIdfList old, TfIdfList new);
//find the BST node who has same word
InvertedIndexBST searchTree(char *word, InvertedIndexBST tree);
//merge two tf list together
TfIdfList mergeTwoTfIdfList(TfIdfList desti, TfIdfList from);
//free tflist
void freeTfIdfList(TfIdfList desti);
//delete duplicate nodes who has same filename and add their tfidf_sum together
void deleteDuplicateNodes(TfIdfList node);
//sort the tfidf list again
TfIdfList reorderTfIdfList(TfIdfList node);
//create a new filelistnode
FileList    newFilenode(char *word, char *filename);
//insert filenode into appropriate place
void    insertFilenode(InvertedIndexBST head, InvertedIndexBST input);
