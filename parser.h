#ifndef PARSER_H
#define PARSER_H

struct meas
{
    char anchorname[8];
    double ddist;
};

struct anchor *read_map(char fileName[]);
void parse_data(char line[], struct meas measurement[], int numAnchor);
int sub_in_str(char str[], char sub[]);

int main();

#endif