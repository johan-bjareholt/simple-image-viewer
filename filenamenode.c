#include <stdlib.h>
#include <string.h>

#include "filenamenode.h"

struct FilenameNode* newFilenameNode(char* filename, struct FilenameNode* next, struct FilenameNode* prev) {
    // Try to allocate vector structure.

    struct FilenameNode* ptr = (struct FilenameNode*)malloc(sizeof(struct FilenameNode));

    ptr->filename = malloc(strlen(filename)+1);
    strcpy(ptr->filename, filename);

    ptr->next = next;
    ptr->prev = prev;

    return ptr;
}

void deleteFilenameNode(struct FilenameNode* nodeptr){
    free((char*)nodeptr->filename);
}

void deleteAllFilenameNodes(struct FilenameNode* startnode){
    struct FilenameNode* node = startnode->next;
    struct FilenameNode* prev;
    deleteFilenameNode(startnode);
    while (node != startnode){
        prev = node;
        node = node->next;
        deleteFilenameNode(prev);
    }
}
