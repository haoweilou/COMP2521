// crawl.c ... build a graph of part of the web
// Written by John Shepherd, September 2015
// Uses the cURL library and functions by Vincent Sanders
// <vince@kyllikki.org>

#include <ctype.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "graph.h"
#include "html.h"
#include "set.h"
#include "queue.h"
#include "url_file.h"

#define BUFSIZE 1024

static void setFirstURL (char *, char *);

int main (int argc, char **argv)
{
	URL_FILE *handle;
	char buffer[BUFSIZE];
	char baseURL[BUFSIZE];
	char firstURL[BUFSIZE];
	char *next;
	int maxURLs;

	if (argc > 2) {
		strcpy (baseURL, argv[1]);
		setFirstURL (baseURL, firstURL);
		maxURLs = atoi (argv[2]);
		if (maxURLs < 40)
			maxURLs = 40;
	} else {
		fprintf (stderr, "Usage: %s BaseURL MaxURLs\n", argv[0]);
		exit (1);
	}

	// You need to modify the code below to implement:
	//
	// add firstURL to the ToDo list
	Queue ToDo = newQueue();
	enterQueue(ToDo, firstURL);
	// initialise Graph to hold up to maxURLs
	Graph graph = newGraph((ulong)maxURLs);
	// initialise set of Seen URLs
	Set seen = newSet();
	insertInto(seen,firstURL);
	// while (ToDo list not empty and Graph not filled) {
	while (emptyQueue(ToDo) != 1 && nVertices(graph) < (size_t)maxURLs)
	{
		// curr is the front at queues
		next = leaveQueue(ToDo);
		if(strstr(next,"unsw")==NULL){
			free(next);
			continue;
		}
		//open the next url from ToDo list
		if (!(handle = url_fopen (next, "r"))) {
			fprintf (stderr, "Couldn't open %s\n", next);
			exit(1);
		}
		while (!url_feof (handle)) {
			//next is all characters in the handle html file, store in buffer
			url_fgets (buffer, sizeof (buffer), handle);
			//fputs(buffer,stdout);
			int pos = 0;
			char result[BUFSIZE];
			memset (result, 0, BUFSIZE);
			while ((pos = GetNextURL (buffer, next, result, pos)) > 0) {
	            //if (Graph not filled or both URLs in Graph)
				if(nVertices(graph) != (ulong)maxURLs || isConnected(graph,next,result) == 0){
					addEdge(graph,next,result);
					//printf("vertices is : %zu\n",nVertices(graph));
				}
                //if (this URL not Seen already)
				if(!(isElem(seen,result))) {
					insertInto(seen,result);
					enterQueue(ToDo, result);
				}
				printf ("Found: '%s'\n", result);
				memset (result, 0, BUFSIZE);
				//free(result);
			}
		}
		url_fclose (handle);
		sleep (1);
		free(next);
	}
	showGraph(graph,0);
	dropGraph(graph);
	dropSet(seen);
	dropQueue(ToDo);
	//    grab Next URL from ToDo list
	//    if (not allowed) continue
	//    foreach line in the opened URL {
	//       foreach URL on that line {
	//             add an edge from Next to this URL
	//          
	//             add it to the Seen set
	//             add it to the ToDo list
	//          }
	//       }
	//    }
	//    close the opened URL
	//    sleep(1)
	// }
	return 0;
}

// setFirstURL(Base,First)
// - sets a "normalised" version of Base as First
// - modifies Base to a "normalised" version of itself
static void setFirstURL (char *base, char *first)
{
	char *c;
	if ((c = strstr (base, "/index.html")) != NULL) {
		strcpy (first, base);
		*c = '\0';
	} else if (base[strlen (base) - 1] == '/') {
		strcpy (first, base);
		strcat (first, "index.html");
		base[strlen (base) - 1] = '\0';
	} else {
		strcpy (first, base);
		strcat (first, "/index.html");
	}
}
