#include <stdio.h>
#include <stdlib.h>


#define ARR_LENGTH 1000

int read_file(char c[],int lineNr);

int main(){
    char c[ARR_LENGTH];
    int lineNr = 0;
    read_file(c, lineNr);
    printf("Data from the file:\n%s", c);
    return 0;
}


int read_file(char c[],int lineNr)
{
    
    FILE *fptr;
    if ((fptr = fopen("tagdata.json", "r")) == NULL)
    {
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);         
    }
    // reads text until newline 
    fscanf(fptr,"%[^\n]", c);
    printf("Data from the file:\n%s", c);
    fclose(fptr);
    
    return 0;
}
