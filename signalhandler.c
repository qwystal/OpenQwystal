#include "include.h"

const char exitMessage[] = "Use 'exit' if you want to exit.\n";
const char unknownMessage[] = "Unknown signal.\n";

void sigHandler(int sig_num)
{
    switch (sig_num)
    {
    case SIGINT:
        write(STDOUT_FILENO, exitMessage, sizeof(exitMessage) - 1);
        signal(SIGINT, sigHandler);
        break;

    case SIGTERM:
        write(STDOUT_FILENO, exitMessage, sizeof(exitMessage) - 1);
        signal(SIGTERM, sigHandler);
        break;
    
    default:
        write(STDOUT_FILENO, unknownMessage, sizeof(unknownMessage) - 1);
        break;
    }
}
