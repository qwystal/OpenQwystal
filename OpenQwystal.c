/*
gcc .\OpenQwystal.c -o .\OpenQwystal.exe -lcurl -Wall
*/

#include "include.h"
#include "get_request.c"
#include "login.c"
#include "savefile.c"
#include "signalhandler.c"

int main(int argc, char **argv) {
    signal(SIGINT, sigHandler);

    const char *address = GetAddress();
    const char *credentials = GetCredentials();
    char **displayedPath;
    char path[256] = "$ ";
    char *command;
    char *arguments;

    SaveFile("login", credentials);
    SaveFile("address", address);

    cJSON *json = GetRequest(AddAddress(address, "users/me"), credentials);
    SaveFile("user.me.json", cJSON_Print(json)); // TODO: create folder structure for saves
    const cJSON *userName = cJSON_GetObjectItemCaseSensitive(json, "name");

    cJSON_Delete(json);

    json = GetRequest(AddAddress(address, ""), credentials);
    cJSON *openProject = cJSON_GetObjectItemCaseSensitive(json, "instanceName");
    const char *instanceName = openProject->valuestring;
    printf("You are using %s\n", instanceName);
    displayedPath[0] = (char*) userName;
    displayedPath[1] = ":~";

    // TODO: build a path structure
    while (1) {
        printf("%s", displayedPath);
        fgets(arguments, 256, stdin);
        arguments[strcspn(arguments, "\n")] = 0;
        command = strtok(arguments, " ");
        
    }
    
    
    getchar();

    return 0;
}