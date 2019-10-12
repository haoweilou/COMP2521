// Ass1 ... COMP2521 

#ifndef _INVERTEDINDEX_GUARD
#define _INVERTEDINDEX_GUARD


struct FileListNode {
    char *filename;
	double tf;    // relative tf
	struct FileListNode *next;
};
typedef struct FileListNode *FileList;

struct InvertedIndexNode {

	char  *word;  // key

	struct FileListNode  *fileList;

	struct InvertedIndexNode  *left;
	struct InvertedIndexNode  *right;

};
typedef struct InvertedIndexNode *InvertedIndexBST;

struct TfIdfNode {
    char *filename;
	double tfidf_sum;    // tfidf sum value
	struct TfIdfNode *next;
};
typedef struct TfIdfNode *TfIdfList;



// Functions for Part-1
char * normaliseWord(char *str);
InvertedIndexBST generateInvertedIndex(char *collectionFilename);
void printInvertedIndex(InvertedIndexBST tree); 

// Functions for Part-2
TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord , int D);
TfIdfList retrieve(InvertedIndexBST tree, char* searchWords[] , int D);

#endif


