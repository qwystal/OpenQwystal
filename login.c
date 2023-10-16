#include "include.h"

#define APIKEY_MAX_LENGTH 128

char *GetCredentials() { // TODO: make storing the apikey more secure
    char *apikey = (char *)malloc(APIKEY_MAX_LENGTH + 1);
    char *credentials = (char *)malloc(APIKEY_MAX_LENGTH + 7);
    if (apikey == NULL || credentials == NULL)
    {
        return NULL;
    }
    
    // look for existing login data as a file
    FILE *file = fopen("login", "r");
    if (file != NULL) {
        fgets(apikey, APIKEY_MAX_LENGTH, file);
        fclose(file);
        // remove trailing newline
        apikey[strcspn(apikey, "\n")] = 0;
        printf("Using existing login file.\n");
        return apikey;
    }

    printf("Enter your API key: ");
    fgets(apikey, APIKEY_MAX_LENGTH, stdin);

    // remove trailing newline
    apikey[strcspn(apikey, "\n")] = 0;

    // add username and apikey to apikey
    snprintf(credentials, APIKEY_MAX_LENGTH + 7, "apikey:%s", apikey);
    if (credentials == NULL) {
        printf("Not enough memory\n");
        exit(1);
    }
    return credentials;
}

char *GetAddress() {
    char *address = (char *)malloc(256);
    if (address == NULL) {
        return NULL;
    }
    // look for existing address data as a file
    FILE *file = fopen("address", "r");
    if (file != NULL) {
        fgets(address, 256, file);
        fclose(file);
        // remove trailing newline
        address[strcspn(address, "\n")] = 0;
        printf("Using existing address file.\n");
        return address;
    }
    
    printf("Enter the Webaddress of the project: ");
    fgets(address, 256, stdin);
    // If there is no http:// or https:// in the address, add https://
    if (strncmp(address, "https://", 8) != 0) {
        char *temp = (char *)malloc(256);
        if (temp == NULL) {
            return NULL;
        }
        snprintf(temp, 256, "https://%s", address);
        address = temp;
    }

     // remove trailing newline
    address[strcspn(address, "\n")] = 0;
    
    // remove everything after the third slash if there is no third slash add one at the end
    int slashCount = 0;
    
    for (int i = 0; i < strlen(address); i++) {
        if (address[i] == '/') {
            slashCount++;
        }
        
        if (slashCount == 3) {
            // Found the third slash, remove everything after it
            address[i + 1] = '\0';
            i = strlen(address);
        }
    }
    
    // If there are less than three slashes, add one at the end
    if (slashCount < 3) {
        strcat(address, "/");
    }

    // add page to address
    snprintf(address, 256, "%sapi/v3/", address);
    if (address == NULL) {
        printf("Not enough memory\n");
        exit(1);
    }
    return address;
}

char *AddAddress(const char *address, char *page) { // add something to the address. for example: the address is op.example.com and the page is users/me, the result will be op.example.com/users/me
    char *temp = (char *)malloc(2048);
    if (temp == NULL) {
        return NULL;
    }
    snprintf(temp, 2048, "%s%s", address, page);
    if (temp == NULL) {
        printf("Not enough memory\n");
        exit(1);
    }
    return temp;
}