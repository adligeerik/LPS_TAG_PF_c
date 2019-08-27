#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "particle_filter.h"
#include "parser.h"


/**
 * Reads a file that contains the map of the system and returns it as a anchor struct array
 */
struct anchor *
read_map(char fileName[])
{
    // Array with all anchors (TODO dynamic lenght of array)
    static struct anchor anchorMap[4];

    // Read file and puts the data in buffer
    char *buffer = 0;
    long length;
    FILE *f = fopen(fileName, "rb");

    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer)
        {
            fread(buffer, 1, length, f);
        }
        fclose(f);
    }

    
    //printf("%s\n",buffer);

    // Parse the json string
    if (buffer)
    {   
        int anchorNum = -1;
        int openBrackets = 0;
        int quotMark = 0;
        char *name;
        name = malloc(20);
        for (int i = 0; i < length; i++)
        {   
            // New object starts
            if (buffer[i] == (int)'{')
            {
                openBrackets++;
                i++;
            }
            // End of object
            if (buffer[i] == (int)'}')
            {
                openBrackets--;
                i++;
            }
            // Key in object starts/stop
            if (buffer[i] == (int)'"')
            {
                quotMark++;
                quotMark = quotMark % 2;
                i++;
            }
            // When a new key
            if (quotMark)
            {
                int j = 0;
                while (quotMark)
                {

                    name[j] = buffer[i];
                    i++;
                    j++;
                    if (buffer[i] == (int)'"')
                    {
                        quotMark++;
                        quotMark = quotMark % 2;
                        name[j] = 0;
                    }
                }
                // New anchor
                if(openBrackets == 1){
                    anchorNum++;
                    strcpy( anchorMap[anchorNum].anchorname, name);
                }
                // Parse content of anchor, coordinates and if ref anchor
                char strVal[30] = {0};       
                char xstr[] = "x";
                char ystr[] = "y";
                char zstr[] = "z";
                char refAncstr[] = "ref_anchor";
                // x coordinate
                
                if (!strcmp(name,xstr)){
                    i++;
                    i++;
                    int j = 0;
                    while(!(buffer[i] == (int)','||buffer[i] == (int)'\n')){
                        strVal[j] = buffer[i];
                        i++;
                        j++;
                    }
                    anchorMap[anchorNum].x = atof(strVal);
                }
                // y coordinate
                if (!strcmp(name,ystr)){
                    i++;
                    i++;
                    int j = 0;
                    while(!(buffer[i] == (int)','||buffer[i] == (int)'\n')){
                        strVal[j] = buffer[i];
                        i++;
                        j++;
                    }   
                    anchorMap[anchorNum].y = atof(strVal);
                }
                // z coordinate
                if (!strcmp(name,zstr)){
                    i++;
                    i++;
                    int j = 0;
                    while(!(buffer[i] == (int)','||buffer[i] == (int)'\n')){
                        strVal[j] = buffer[i];
                        i++;
                        j++;
                    }   
                    anchorMap[anchorNum].z = atof(strVal);
                }
                // ref anchor val
                if (!strcmp(name,refAncstr)){
                    i++;
                    i++;
                    int j = 0;
                    while(!(buffer[i] == (int)','||buffer[i] == (int)'\n')){
                        strVal[j] = buffer[i];
                        i++;
                        j++;
                    }
                    anchorMap[anchorNum].ref_anchor = (int)strVal[1]-48;
                }
            }
        }
    }
    return anchorMap;
}


/**
 * Calculates the occurance of a substring in a string
 */
int 
sub_in_str(char str[], char sub[]){
    int l1, l2, count, count1, i, j;

    l1 = strlen(str);
    l2 = strlen(sub);
 
    for (i = 0; i < l1;)
    {
        j = 0;
        count = 0;
        while ((str[i] == sub[j]))
        {
            count++;
            i++;
            j++;
        }
        if (count == l2)
        {
            count1++;                                   
            count = 0;
        }
        else
            i++;
    }
    return count1;
}

/**
 * Parse line from tag and put in a struct list with anchor name and ddist
 */
void
parse_data(char line[], struct meas measurement[], int numAnchor){
    int anchorIndex = 0;

    char addr[] = "addr";
    char ddist[] = "ddist";
    char tqf[] = "tqf";
    char rssi[] = "rssi";

    int lineLen = strlen(line);
    int addrLen = strlen(addr);
    int ddistLen = strlen(ddist);
    
    int addrindx = 0, ddistindx = 0;
    //printf("%s\n",line);
    for (int i = 0; i < lineLen;i++)
    {
        while (line[i] == addr[addrindx]){
            addrindx++;
            i++;
            // Found an addr
            if (addrindx == addrLen){
                char name[8];
                memset(name,0,strlen(name));
                i = i + 3; // to skip ":"
                int v = 0;
                // Extract the name of the anchor
                while (line[i] != (int)'"'){
                    name[v] = line[i];
                    i++;
                    v++;
                }
                strcpy( measurement[anchorIndex].anchorname, name);
                
                //printf("name :%s\n",name);
                
                while (line[i] != (int)'}'){
                    i++;
                    while (line[i] == ddist[ddistindx]){
                        ddistindx++;
                        i++;
                        // Found a ddist
                        while(ddistindx == ddistLen){
                            char data[8];
                            memset(data,0,strlen(data));
                            i = i + 3; // to skip ":"
                            v = 0;
                            // Extract the ddist of the anchor
                            while (line[i] != (int)'"'){
                                data[v] = line[i];
                                i++;
                                v++;
                            }
                            measurement[anchorIndex].ddist = atof(data);
                            //printf("ddist :%f\n",measurement[anchorIndex].ddist);
                            ddistindx = 0;
                            break;
                        }
                    }
                }        
                anchorIndex++;
            }
        }
        addrindx = 0;
    }
}