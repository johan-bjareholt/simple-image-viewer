#include <stdlib.h>
#include <string.h>

#include "filenamenode.h"

struct FilenameNode* newFilenameNode(char* filename, struct FilenameNode* next, struct FilenameNode* prev) {

    struct FilenameNode* ptr = (struct FilenameNode*)malloc(sizeof(struct FilenameNode));

    ptr->filename = malloc(strlen(filename)+1);
    strcpy(ptr->filename, filename);

    ptr->next = next;
    ptr->prev = prev;

    return ptr;
}

void deleteFilenameNode(struct FilenameNode* nodeptr){
    nodeptr->prev->next = nodeptr->next;
    nodeptr->next->prev = nodeptr->prev;
    free((char*)nodeptr->filename);
}

void deleteAllFilenameNodes(struct FilenameNode* startnode){
    struct FilenameNode* node = startnode->next;
    struct FilenameNode* prev;
    free((char*)startnode->filename);
    while (node != startnode){
        prev = node;
        node = node->next;
        free((char*)prev->filename);
    }
}

void loadFilenames(int argc, char** argv){
    struct FilenameNode* firstPicture = newFilenameNode(argv[1], NULL, NULL);
    firstPicture->next = firstPicture;
    firstPicture->prev = firstPicture;

    struct FilenameNode* previousPicture = firstPicture;
    for (int i=2; i<argc; i++){
        struct FilenameNode* picture = newFilenameNode(argv[i], firstPicture, previousPicture);
        firstPicture->prev = picture;
        previousPicture->next = picture;
        previousPicture = picture;
    }

    selectedPicture = firstPicture;
}
