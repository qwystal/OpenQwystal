#include "include.h"

int SaveFile(char *filename, const char *data){
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        return 1;
    }
    fprintf(file, "%s", data);
    fclose(file);
    return 0;
}

int SecureSaveFile(char *filename, char *data){
    // encrypt data with AES, the key is the hardware ids and save it to the file

    


    return 0;
}