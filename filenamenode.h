#ifndef FILENAMENODE_H
#define FILENAMENODE_H

struct FilenameNode {
    char* filename;
    struct FilenameNode* next;
    struct FilenameNode* prev;
};

struct FilenameNode* newFilenameNode(char* filename, struct FilenameNode* next, struct FilenameNode* prev);
void deleteFilenameNode(struct FilenameNode* nodeptr);
void deleteAllFilenameNodes(struct FilenameNode* startnode);
void loadFilenames(int, char**);

extern struct FilenameNode* selectedPicture;

#endif
