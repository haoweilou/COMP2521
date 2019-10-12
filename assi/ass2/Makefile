CC = gcc

.PHONY: all
all: pagerank searchPagerank scaledFootrule

pagerank:	pagerank.o graph.o
pagerank.o:		pagerank.c graph.c
graph.o: graph.c

searchPagerank: searchPagerank.o
searchPagerank.o: searchPagerank.h searchPagerank.c

scaledFootrule: scaledFootrule.o
scaledFootrule.o: scaledFootrule.h scaledFootrule.c