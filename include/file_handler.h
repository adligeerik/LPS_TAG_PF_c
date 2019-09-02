
#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#define COORD_STRING_LEN 50

void write_file(struct particle *particles, char *fileName);
void write_file_anchor(struct anchor *anchors, char *fileName, int numAnchors);

#endif