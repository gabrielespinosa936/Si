//Gabriel Espinosa
#include "processor.h"

int main(void)
{
    char inputBuffer[BUFFER_SIZE];

    while (true) {
        // get a line of input from he user
        scanf(" %[^\n]", inputBuffer);

        if (strncmp(inputBuffer, SENTINEL, SENTINEL_LEN) == 0)
            // stop when "END" is read in
            break;
        // add the message to the cache
        addMessageToCache(inputBuffer);
    }
    messageDispatcher();
    printStatistics();
    return 0;
}
