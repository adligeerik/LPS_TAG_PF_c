#include <stdio.h>
#include <stdlib.h>

char *read_file();

int main(){
    char *line;
    line = read_file();
    printf("Data from the file:\n%s", line);
    return 0;
}


char *read_file()
{
    static char c[1000];
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
    
    return c;
}
