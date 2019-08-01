#include <stdio.h>
#include <stdlib.h>

int read_file(char c[]);

int main(){
    char c[1000];
    read_file(c);
    printf("Data from the file:\n%s", c);
    return 0;
}


int read_file(char c[])
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
