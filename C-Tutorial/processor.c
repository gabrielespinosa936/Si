// Gabriel Espinosa
#include "processor.h"

MESSAGE messageCache[CACHE_SIZE];

static int numMessagesInCache = 0;
static int numMessages = 0;
static int numBatches = 0;
static int stats[4] = {0, 0, 0, 0};

void addMessageToCache(char *inputLine) {
    MESSAGE msg;
    inputLine[1] = 0;
    msg.type = atoi(inputLine);
    inputLine += 2;

    int offset;
    switch (msg.type) {
        case MSG_TYPE_1: {
            size_t length = strlen(inputLine);
            char *str = malloc((length + 1) * sizeof(char));
            strcpy(str, inputLine);
            msg.content.string = str;
            //msg.content.string = strdup(inputLine);
            stats[0]++;
            break;
        }
        case MSG_TYPE_2: {
            for (int i = 0; i < NUM_OF_INTEGERS; i++) {
                sscanf(inputLine, "%d%n,", &msg.content.integers[i], &offset);
                inputLine += offset + 1;
            }
            stats[1]++;
            break;
        }
        case MSG_TYPE_3: {
            for (int i = 0; i < NUM_OF_DOUBLES; i++) {
                sscanf(inputLine, "%lf%n", &msg.content.doubles[i], &offset);
                inputLine += offset + 1;
            }
            stats[2]++;
            break;
        }
        case MSG_TYPE_4: {
            for (int i = 0; i < NUM_OF_STRINGS; i++) {
                char buf[BUFFER_SIZE];
                sscanf(inputLine, "%[^ ]%n", buf, &offset);
                //if (strlen(buf) != LENGTH_OF_STRINGS) { /* error */ }
                strcpy(msg.content.words[i], buf);
                inputLine += offset + 1;
            }
            stats[3]++;
        }
    }
    //messageCache[numMessages] = msg;
    //numMessages++;
    messageCache[numMessagesInCache++] = msg;
    numMessages++;
    if (numMessagesInCache == CACHE_SIZE)
        messageDispatcher();
}

void messageDispatcher(void) {
    for (int m = 0; m < numMessagesInCache; m++) {
        processMessage(&messageCache[m]);
        if (messageCache[m].type == MSG_TYPE_1)
            free(messageCache[m].content.string);
    }
    numMessagesInCache = 0;
    numBatches++;
}

void processMessage(MESSAGE *message) {
    switch (message->type) {
        case MSG_TYPE_1:
            printf("TYPE 1: %s\n", message->content.string);
            break;
        case MSG_TYPE_2:
            printf("TYPE 2: ");
            for (int i = 0; i < NUM_OF_INTEGERS; ++i) {
                if (i < NUM_OF_INTEGERS - 1)
                    printf("%d,", message->content.integers[i]);
                else
                    printf("%d\n", message->content.integers[i]);
            }
            break;
        case MSG_TYPE_3:
            printf("TYPE 3: ");
            for (int i = 0; i < NUM_OF_DOUBLES; ++i) {
                if (i < NUM_OF_DOUBLES - 1)
                    printf("%.6lf/", message->content.doubles[i]);
                else
                    printf("%.6lf\n", message->content.doubles[i]);
            }
            break;
        case MSG_TYPE_4:
            printf("TYPE 4: ");
            for (int i = 0; i < NUM_OF_STRINGS; ++i) {
                if (i < NUM_OF_STRINGS - 1)
                    printf("%s ", message->content.words[i]);
                else
                    printf("%s\n", message->content.words[i]);
            }
    }
}

void printStatistics(void) {
    printf("Number of message batches: %d\n", numBatches);
    printf("Messages processed:\n");
    printf("Total: %d\n", numMessages);
    printf("Type 1: %d\n", stats[0]);
    printf("Type 2: %d\n", stats[1]);
    printf("Type 3: %d\n", stats[2]);
    printf("Type 4: %d\n", stats[3]);
}
