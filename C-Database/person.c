// Gabriel Espinosa
#include "person.h"

LIST *head = NULL, *tail = NULL;

void inputPersonalData(PERSON *person) {
    // TODO Implement the function

    scanf(" %s %d %f %d/%d/%d",
            person->name,
            &(person->age),
            &(person->height),
            &(person->bday.month),
            &(person->bday.day),
            &(person->bday.year));
}
void addPersonalDataToDatabase(PERSON *person)
{
    // TODO Implement the function

    add(&head, &tail, person);

}

void displayDatabase()
{
    // TODO Implement the function
    LIST *node = head;
    while(node != NULL)
    {
        displayPerson((PERSON *)node->data);
        printf("\n");
        node = node->next;
    }
}

void displayPerson(PERSON *person)
{
    // TODO Implement the function
    printf("%s ",person->name);
    printf("%d ",person->age);
    printf("%.1f ",person->height);
    printf(" %d/%2d/%4d", person->bday.month, person->bday.day, person->bday.year);

}

PERSON *findPersonInDatabase(char *name)
{
    // TODO Implement the function
//    if(head == NULL)
//        return NULL;
    LIST *node = head;
    while(node!=NULL)
    {
        PERSON *candidate = node->data;
        // Made a new person called candidate and set to node data
        // then using strcmp to see if the candidate data is the
        // same as the data we're looking for.
        if(0 == strcmp(candidate->name, name))
            return candidate;
        node = node->next; // since I am using a while loop I need to update the node by
        // setting the node we're using to the next node
    }
    return NULL; // if not found
}

void removePersonFromDatabase(char *name)
{
    // TODO Implement the function

    // Don't check if list is empty because find person in database does for me
    PERSON *person = findPersonInDatabase(name);
    if(person != NULL)
    {
        delete(&head, &tail, person);
    }
}

void clearDatabase()
{
    // TODO Implement the function
    
    // clearIteratively(&head, &tail);
    clearRecursively(&head, &tail);
}
