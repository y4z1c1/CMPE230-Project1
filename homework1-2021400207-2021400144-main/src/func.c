#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// boolean to check if the input is exit
int ifExit = 1;

// location struct that has name, subjects array and integer that how many subjects are in the location
struct Location
{
    char name[1025];
    char *subjects[1000];
    int subjectCount; // how many subjects are in the location
};

// subject struct that has name, items and number of items array, integer that how many items subject have and location pointer
struct Subject
{
    char name[1025];
    struct Location *location;
    char *items[1000];        // stores items which subject has
    int numbersOfItems[1000]; // stores the number of items in accord with the index
    int totalItems;
};

struct Location locations[1000]; // stores locations mentioned
static int totalLocations = 0;   // total locations that appeared
struct Subject subjects[1000];   // stores subjects mentioned
static int totalSubjects = 0;    // total number of subjects

// checks if the given string is valid according to rules
int isValidString(const char *str)
{
    if (strcmp(str, "buy") == 0)
    {
        return 0;
    }
    else if (strcmp(str, "go") == 0)
    {
        return 0;
    }
    else if (strcmp(str, "sell") == 0)
    {
        return 0;
    }
    else if (strcmp(str, "has") == 0)
    {
        return 0;
    }
    else if (strcmp(str, "more") == 0)
    {
        return 0;
    }
    else if (strcmp(str, "less") == 0)
    {
        return 0;
    }
    else if (strcmp(str, "than") == 0)
    {
        return 0;
    }
    else if (strcmp(str, "at") == 0)
    {
        return 0;
    }
    else if (strcmp(str, "total") == 0)
    {
        return 0;
    }
    else if (strcmp(str, "where") == 0)
    {
        return 0;
    }
    else if (strcmp(str, "who") == 0)
    {
        return 0;
    }
    else if (strcmp(str, "NOWHERE") == 0)
    {
        return 0;
    }
    else if (strcmp(str, "NOTHING") == 0)
    {
        return 0;
    }
    else if (strcmp(str, "NOBODY") == 0)
    {
        return 0;
    }

    while (*str != '\0')
    {
        if (!((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z') || (*str == '_')))
        {
            return 0;
        }
        str++;
    }

    return 1;
}

// Check if the character is a word boundary (space, end of string, punctuation, etc.)
int isWordBoundary(char c)
{
    return isspace(c) || ispunct(c) || c == '\0';
}

// checks if the given input contains the word which is the parameter
int containsWord(const char *input, const char *word)
{
    const char *pos = input;
    size_t wordLength = strlen(word);

    while ((pos = strstr(pos, word)) != NULL)
    {
        // Check if the word is at the beginning of the input string or if there is a word boundary before it
        int isAtStart = (pos == input) || isWordBoundary(*(pos - 1));

        // Check if the word is at the end of the input string or if there is a word boundary after it
        int isAtEnd = isWordBoundary(*(pos + wordLength));

        if (isAtStart && isAtEnd)
        {
            return 1; // Word found
        }

        // Move past the current position to continue searching
        pos += wordLength;
    }

    return 0; // Word not found
}

// check if given string is integer
int isInteger(const char *str)
{
    // Check for an empty string
    if (*str == '\0')
    {
        return 0;
    }

    // Check each character to ensure it's a digit
    while (*str != '\0')
    {
        if (*str < '0' || *str > '9')
        {
            return 0; // Found a non-digit character
        }
        str++;
    }

    return 1; // Only digits (possibly with a leading sign) were found
}

// check if the string is a name of subject who is mentioned before
int inSubjects(const char *str)
{
    for (int i = 0; i < totalSubjects; i++)
    {
        if (strcmp(subjects[i].name, str) == 0)
        {
            return 1;
        }
    }
    return 0;
}

// check if the string is a name of location that is mentioned before
int inLocations(const char *str)
{
    for (int i = 0; i < totalLocations; i++)
    {
        if (strcmp(locations[i].name, str) == 0)
        {
            return 1;
        }
    }
    return 0;
}

// prints all subjects in a given location
void whoAt(char *location)
{
    for (int i = 0; i < totalLocations; i++)
    {
        // search for the location in locations array
        if (strcmp(locations[i].name, location) == 0)
        {
            // Check if no one is at the location
            if (locations[i].subjectCount == 0)
            {
                printf("NOBODY\n");
                return;
            }

            printf("%s", locations[i].subjects[0]);
            for (int j = 1; j < locations[i].subjectCount; j++)
            {
                printf(" and %s", locations[i].subjects[j]);
            }
            printf("\n");
            return;
        }
    }
}

// check if the subject is at the desired location
int checkAt(char tempString[1025])
{
    char destination[1025];
    char *token;
    char second[1025];
    char *token2;
    strcpy(second, tempString);
    token = strtok(tempString, " ");

    while (strcmp(token, "at") != 0)
    {
        token = strtok(NULL, " ");
    }
    token = strtok(NULL, " ");
    token2 = strtok(second, " ");

    while (strcmp(token2, "at") != 0)
    {
        for (int i = 0; i < totalSubjects; i++)
        {

            if (strcmp(subjects[i].name, token2) == 0)
            {

                if (subjects[i].location == NULL)
                {
                    return 0;
                }

                if (strcmp(subjects[i].location->name, token) != 0)
                {
                    return 0;
                }
            }
        }

        token2 = strtok(NULL, " ");
        if (token2 == NULL)
        {
            break;
        }

        if (strcmp(token2, "and"))
        {
            token2 = strtok(NULL, " ");
        }
    }
    return 1;
}

// check if the seller subject is able to sell items to the buyer(s)
int checkHasLessorEqualTo(char *tempString)
{
    char *people[1000];
    int totalPerson = 0;
    char *token;
    char *items[1000];
    int totalItems = 0;
    char str[1025];

    int contains = 0;
    token = strtok(tempString, " ");
    people[totalPerson++] = strdup(token);

    token = strtok(NULL, " ");
    while (strcmp(token, "has"))
    {
        token = strtok(NULL, " ");
        token = strtok(NULL, " ");
        people[totalPerson++] = strdup(token);
    }

    token = strtok(NULL, " ");
    token = strtok(NULL, " ");
    token = strtok(NULL, " ");

    strcpy(str, token);
    token = strtok(NULL, " ");
    strcat(str, " ");
    while (token != NULL)
    {
        strcat(str, token);
        items[totalItems++] = strdup(str);
        strcpy(str, "");
        token = strtok(NULL, " ");

        if (token && strcmp(token, "and") == 0)
        {
            token = strtok(NULL, " ");
            strcat(str, token);
            strcat(str, " ");
            token = strtok(NULL, " ");
        }
    }

    for (int i = 0; i < totalPerson; i++)
    {

        for (int j = 0; j < totalSubjects; j++)
        {
            if (strcmp(subjects[j].name, people[i]) == 0)
            {
                for (int k = 0; k < totalItems; k++)
                {

                    contains = 0;

                    int quantity;

                    token = strtok(items[k], " ");

                    quantity = atoi(token);
                    token = strtok(NULL, " ");

                    int index = 0;

                    while (index != subjects[j].totalItems)
                    {

                        if (strcmp(subjects[j].items[index], token) == 0)
                        {
                            contains = 1;

                            if (subjects[j].numbersOfItems[index] < quantity)
                            {

                                return 1;
                            }

                            break;
                        }

                        index++;
                    }
                    if (!contains && quantity > 0)
                        return 1;
                }
            }
        }
    }
    return 0;
}

// check if subject has, has more than or has less than given items
int checkHas(char *tempString)
{
    char *people[1000];
    int totalPerson = 0;
    char *token;
    char *items[1000];
    int totalItems = 0;
    char str[1025];

    int contains = 0;
    token = strtok(tempString, " ");
    people[totalPerson++] = strdup(token);

    token = strtok(NULL, " ");
    while (strcmp(token, "has"))
    {
        token = strtok(NULL, " ");
        token = strtok(NULL, " ");
        people[totalPerson++] = strdup(token);
    }

    token = strtok(NULL, " ");

    // check if subject has more than given items
    if (strcmp(token, "more") == 0)
    {
        token = strtok(NULL, " ");
        token = strtok(NULL, " ");

        strcpy(str, token);
        token = strtok(NULL, " ");
        strcat(str, " ");
        while (token != NULL)
        {
            strcat(str, token);
            items[totalItems++] = strdup(str);
            strcpy(str, "");
            token = strtok(NULL, " ");

            if (token && strcmp(token, "and") == 0)
            {
                token = strtok(NULL, " ");
                strcat(str, token);
                strcat(str, " ");
                token = strtok(NULL, " ");
            }
        }

        for (int i = 0; i < totalPerson; i++)
        {

            for (int j = 0; j < totalSubjects; j++)
            {
                if (strcmp(subjects[j].name, people[i]) == 0)
                {
                    for (int k = 0; k < totalItems; k++)
                    {

                        contains = 0;

                        int quantity;
                        token = strtok(items[k], " ");

                        quantity = atoi(token);
                        token = strtok(NULL, " ");

                        int index = 0;

                        while (index != subjects[j].totalItems)
                        {

                            if (strcmp(subjects[j].items[index], token) == 0)
                            {
                                contains = 1;

                                if (subjects[j].numbersOfItems[index] <= quantity)
                                {

                                    return 0;
                                }

                                break;
                            }

                            index++;
                        }

                        if (!contains)
                        {

                            return 0;
                        }
                    }
                }
            }
        }
    }

    // check if subject has less than given items
    else if (strcmp(token, "less") == 0)
    {
        token = strtok(NULL, " ");
        token = strtok(NULL, " ");

        strcpy(str, token);
        token = strtok(NULL, " ");
        strcat(str, " ");
        while (token != NULL)
        {
            strcat(str, token);
            items[totalItems++] = strdup(str);
            strcpy(str, "");
            token = strtok(NULL, " ");

            if (token && strcmp(token, "and") == 0)
            {
                token = strtok(NULL, " ");
                strcat(str, token);
                strcat(str, " ");
                token = strtok(NULL, " ");
            }
        }

        for (int i = 0; i < totalPerson; i++)
        {

            for (int j = 0; j < totalSubjects; j++)
            {
                if (strcmp(subjects[j].name, people[i]) == 0)
                {
                    for (int k = 0; k < totalItems; k++)
                    {

                        contains = 0;

                        int quantity;
                        token = strtok(items[k], " ");

                        quantity = atoi(token);
                        token = strtok(NULL, " ");

                        int index = 0;

                        while (index != subjects[j].totalItems)
                        {

                            if (strcmp(subjects[j].items[index], token) == 0)
                            {
                                contains = 1;

                                if (subjects[j].numbersOfItems[index] >= quantity)
                                {
                                    return 0;
                                }

                                break;
                            }

                            index++;
                        }

                        if (!contains && quantity == 0)
                        {
                            return 0;
                        }
                    }
                }
            }
        }
    }

    // check if subject has exactly the number of given items
    else
    {
        strcpy(str, token);
        token = strtok(NULL, " ");
        strcat(str, " ");
        while (token != NULL)
        {
            strcat(str, token);
            items[totalItems++] = strdup(str);
            strcpy(str, "");
            token = strtok(NULL, " ");

            if (token && strcmp(token, "and") == 0)
            {
                token = strtok(NULL, " ");
                strcat(str, token);
                strcat(str, " ");
                token = strtok(NULL, " ");
            }
        }

        for (int i = 0; i < totalPerson; i++)
        {

            for (int j = 0; j < totalSubjects; j++)
            {
                if (strcmp(subjects[j].name, people[i]) == 0)
                {
                    for (int k = 0; k < totalItems; k++)
                    {

                        contains = 0;

                        int quantity;
                        token = strtok(items[k], " ");

                        quantity = atoi(token);
                        token = strtok(NULL, " ");

                        int index = 0;

                        while (index != subjects[j].totalItems)
                        {

                            if (strcmp(subjects[j].items[index], token) == 0)
                            {
                                contains = 1;

                                if (subjects[j].numbersOfItems[index] != quantity)
                                {
                                    return 0;
                                }

                                break;
                            }

                            index++;
                        }

                        if (!contains && quantity != 0)
                        {
                            return 0;
                        }
                    }
                }
            }
        }
    }

    return 1;
}

// check if the conditional sentence is a "has" conditional sentence or an "at" conditional sentence
int checkGeneral(char *tempString)
{
    if (strstr(tempString, " has"))
    {
        return checkHas(tempString);
    }
    else
    {
        return checkAt(tempString);
    }
}

// make the subject go to the desired location
void executeGoTo(char sentence[1025])
{
    char *token;
    token = strtok(sentence, " ");

    char *subjectsGo[1000];
    int totalSubjectsGo = 0;

    struct Location *location;
    struct Location *oldLocation;

    while (strcmp(token, "go"))
    {

        if (strcmp(token, "and"))
        {
            subjectsGo[totalSubjectsGo] = strdup(token);
            totalSubjectsGo++;
        }
        token = strtok(NULL, " ");
    }

    token = strtok(NULL, " ");
    token = strtok(NULL, " ");

    for (int k = 0; k < totalLocations; k++)
    {
        if (strcmp(token, locations[k].name) == 0)
        {
            location = &locations[k];
        }
    }

    for (int i = 0; i < totalSubjectsGo; i++)
    {
        for (int j = 0; j < totalSubjects; j++)
        {
            if (strcmp(subjectsGo[i], subjects[j].name) == 0)
            {

                if (subjects[j].location)
                {

                    oldLocation = subjects[j].location;

                    for (int l = 0; l < oldLocation->subjectCount; l++)
                    {
                        if (strcmp(oldLocation->subjects[l], subjects[j].name) == 0)
                        {

                            for (int i = l; i < oldLocation->subjectCount - 1; i++)
                            {
                                oldLocation->subjects[i] = oldLocation->subjects[i + 1];
                            }

                            oldLocation->subjectCount--;
                        }
                    }
                }

                subjects[j].location = location;

                location->subjects[location->subjectCount] = strdup(subjects[j].name);
                location->subjectCount++;
            }
        }
    }
}

// subject(s) buy item(s) from an infinite source
void executeBuy(char sentence[1025])
{
    char *token;
    token = strtok(sentence, " ");

    char *subjectsBuy[1000];
    int totalSubjectsBuy = 0;

    while (strcmp(token, "buy"))
    {

        if (strcmp(token, "and"))
        {
            subjectsBuy[totalSubjectsBuy] = strdup(token);
            totalSubjectsBuy++;
        }
        token = strtok(NULL, " ");
    }

    token = strtok(NULL, " ");

    int quantity = atoi(token);

    token = strtok(NULL, " ");

    int contains = 0;

    for (int i = 0; i < totalSubjectsBuy; i++)
    {
        for (int j = 0; j < totalSubjects; j++)
        {
            if (strcmp(subjects[j].name, subjectsBuy[i]) == 0)
            {
                for (int k = 0; k < subjects[j].totalItems; k++)
                {
                    if (strcmp(subjects[j].items[k], token) == 0)
                    {
                        contains = 1;
                        subjects[j].numbersOfItems[k] += quantity;
                        break;
                    }
                }

                if (!contains && quantity > 0)
                {
                    subjects[j].items[subjects[j].totalItems] = strdup(token);
                    subjects[j].numbersOfItems[subjects[j].totalItems] = quantity;
                    subjects[j].totalItems++;
                }
            }
        }
    }

    token = strtok(NULL, " ");

    while (token && strcmp(token, "and") == 0)
    {
        token = strtok(NULL, " ");

        int quantity = atoi(token);

        token = strtok(NULL, " ");

        int contains = 0;

        for (int i = 0; i < totalSubjectsBuy; i++)
        {
            for (int j = 0; j < totalSubjects; j++)
            {
                if (strcmp(subjects[j].name, subjectsBuy[i]) == 0)
                {
                    for (int k = 0; k < subjects[j].totalItems; k++)
                    {
                        if (strcmp(subjects[j].items[k], token) == 0)
                        {
                            contains = 1;
                            subjects[j].numbersOfItems[k] += quantity;
                            break;
                        }
                    }

                    if (!contains && quantity > 0)
                    {
                        subjects[j].items[subjects[j].totalItems] = strdup(token);
                        subjects[j].numbersOfItems[subjects[j].totalItems] = quantity;
                        subjects[j].totalItems++;
                    }
                }
            }
        }
        token = strtok(NULL, " ");
    }
}

// subject(s) buy item(s) from the seller if seller is capable of selling it/them
void executeBuyFrom(char sentence[1025])
{
    char sentence2[1025];
    char sentence3[1025];
    char *token;
    char *token2;
    char *token3;

    int multiplier = 1;

    strcpy(sentence2, sentence);
    strcpy(sentence3, sentence);

    char *subjectsBuy[1000];
    int totalSubjectsBuy = 0;

    char tempString[1025];

    token2 = strtok(sentence, " ");

    while (strcmp(token2, "from") != 0)
    {
        if (strcmp(token2, "and") == 0)
        {
            token2 = strtok(NULL, " ");
            if (!isInteger(token2))
                multiplier++;
        }
        else
        {
            token2 = strtok(NULL, " ");
        }
    }

    token2 = strtok(NULL, " ");

    strcpy(tempString, token2);
    strcat(tempString, " has less than ");

    token3 = strtok(sentence2, " ");
    while (strcmp(token3, "buy"))
    {
        token3 = strtok(NULL, " ");
    }

    token3 = strtok(NULL, " ");

    while (strcmp(token3, "from"))
    {
        if (isInteger(token3))
        {
            int quantity = atoi(token3);
            int final_quantity = multiplier * quantity;
            char str[1025];
            sprintf(str, "%d", final_quantity);
            strcat(tempString, str);
        }
        else
        {
            strcat(tempString, token3);
        }

        strcat(tempString, " ");

        token3 = strtok(NULL, " ");
    }

    if (checkHasLessorEqualTo(tempString))
    {
        return;
    }

    token = strtok(sentence3, " ");

    while (strcmp(token, "buy"))
    {

        if (strcmp(token, "and"))
        {
            subjectsBuy[totalSubjectsBuy] = strdup(token);
            totalSubjectsBuy++;
        }
        token = strtok(NULL, " ");
    }

    token = strtok(NULL, " ");

    int quantity = atoi(token);

    token = strtok(NULL, " ");

    for (int j = 0; j < totalSubjects; j++)
    {
        if (strcmp(subjects[j].name, token2) == 0)
        {
            for (int k = 0; k < subjects[j].totalItems; k++)
            {
                if (strcmp(subjects[j].items[k], token) == 0)
                {
                    subjects[j].numbersOfItems[k] -= multiplier * quantity;
                    if (subjects[j].numbersOfItems[k] == 0)
                    {
                        for (int i = k; i < subjects[j].totalItems - 1; i++)
                        {
                            subjects[j].items[i] = subjects[j].items[i + 1];
                            subjects[j].numbersOfItems[i] = subjects[j].numbersOfItems[i + 1];
                        }

                        subjects[j].totalItems--;
                    }
                    break;
                }
            }
        }
    }

    int contains = 0;

    for (int i = 0; i < totalSubjectsBuy; i++)
    {
        for (int j = 0; j < totalSubjects; j++)
        {
            if (strcmp(subjects[j].name, subjectsBuy[i]) == 0)
            {
                for (int k = 0; k < subjects[j].totalItems; k++)
                {
                    if (strcmp(subjects[j].items[k], token) == 0)
                    {
                        contains = 1;
                        subjects[j].numbersOfItems[k] += quantity;
                        break;
                    }
                }

                if (!contains && quantity > 0)
                {
                    subjects[j].items[subjects[j].totalItems] = strdup(token);
                    subjects[j].numbersOfItems[subjects[j].totalItems] = quantity;
                    subjects[j].totalItems++;
                }
            }
        }
    }

    token = strtok(NULL, " ");

    while (token && strcmp(token, "and") == 0)
    {
        token = strtok(NULL, " ");

        int quantity = atoi(token);

        token = strtok(NULL, " ");

        for (int j = 0; j < totalSubjects; j++)
        {
            if (strcmp(subjects[j].name, token2) == 0)
            {
                for (int k = 0; k < subjects[j].totalItems; k++)
                {
                    if (strcmp(subjects[j].items[k], token) == 0)
                    {
                        subjects[j].numbersOfItems[k] -= multiplier * quantity;
                        if (subjects[j].numbersOfItems[k] == 0)
                        {
                            for (int i = k; i < subjects[j].totalItems - 1; i++)
                            {
                                subjects[j].items[i] = subjects[j].items[i + 1];
                                subjects[j].numbersOfItems[i] = subjects[j].numbersOfItems[i + 1];
                            }

                            subjects[j].totalItems--;
                        }
                        break;
                    }
                }
            }
        }

        int contains = 0;

        for (int i = 0; i < totalSubjectsBuy; i++)
        {
            for (int j = 0; j < totalSubjects; j++)
            {
                if (strcmp(subjects[j].name, subjectsBuy[i]) == 0)
                {
                    for (int k = 0; k < subjects[j].totalItems; k++)
                    {
                        if (strcmp(subjects[j].items[k], token) == 0)
                        {
                            contains = 1;
                            subjects[j].numbersOfItems[k] += quantity;
                            break;
                        }
                    }

                    if (!contains && quantity > 0)
                    {
                        subjects[j].items[subjects[j].totalItems] = strdup(token);
                        subjects[j].numbersOfItems[subjects[j].totalItems] = quantity;
                        subjects[j].totalItems++;
                    }
                }
            }
        }
        token = strtok(NULL, " ");
    }
}

// subject(s) sell item(s) to the infinite source
int executeSell(char sentence[1025])

{
    char *token;
    char sentence2[1025];
    char sentence3[1025];
    char *token2;
    char *token3;

    strcpy(sentence2, sentence);
    strcpy(sentence3, sentence);
    char *subjectsSell[1000];
    int totalSubjectsSell = 0;

    char tempString[1025];

    token2 = strtok(sentence, " ");
    strcpy(tempString, "");

    while (strcmp(token2, "sell") != 0)
    {
        strcat(tempString, token2);
        strcat(tempString, " ");
        token2 = strtok(NULL, " ");
    }

    strcat(tempString, "has less than ");

    token3 = strtok(sentence2, " ");
    while (strcmp(token3, "sell"))
    {
        token3 = strtok(NULL, " ");
    }

    token3 = strtok(NULL, " ");

    while (token3 != NULL)
    {

        strcat(tempString, token3);

        strcat(tempString, " ");

        token3 = strtok(NULL, " ");
    }

    if (checkHasLessorEqualTo(tempString))
    {
        return 0;
    }

    token = strtok(sentence3, " ");

    while (strcmp(token, "sell"))
    {

        if (strcmp(token, "and"))
        {
            subjectsSell[totalSubjectsSell] = strdup(token);
            totalSubjectsSell++;
        }
        token = strtok(NULL, " ");
    }

    token = strtok(NULL, " ");

    int quantity = atoi(token);

    token = strtok(NULL, " ");

    int contains = 0;

    for (int i = 0; i < totalSubjectsSell; i++)
    {
        for (int j = 0; j < totalSubjects; j++)
        {
            if (strcmp(subjects[j].name, subjectsSell[i]) == 0)
            {
                for (int k = 0; k < subjects[j].totalItems; k++)
                {
                    if (strcmp(subjects[j].items[k], token) == 0)
                    {
                        contains = 1;
                        subjects[j].numbersOfItems[k] -= quantity;
                        if (subjects[j].numbersOfItems[k] == 0)
                        {
                            for (int i = k; i < subjects[j].totalItems - 1; i++)
                            {
                                subjects[j].items[i] = subjects[j].items[i + 1];
                                subjects[j].numbersOfItems[i] = subjects[j].numbersOfItems[i + 1];
                            }

                            subjects[j].totalItems--;
                        }
                        break;
                    }
                }

                if (!contains && quantity > 0)
                {

                    return 0;
                }
            }
        }
    }

    token = strtok(NULL, " ");

    while (token && strcmp(token, "and") == 0)
    {
        token = strtok(NULL, " ");

        int quantity = atoi(token);

        token = strtok(NULL, " ");

        int contains = 0;

        for (int i = 0; i < totalSubjectsSell; i++)
        {
            for (int j = 0; j < totalSubjects; j++)
            {
                if (strcmp(subjects[j].name, subjectsSell[i]) == 0)
                {
                    for (int k = 0; k < subjects[j].totalItems; k++)
                    {
                        if (strcmp(subjects[j].items[k], token) == 0)
                        {
                            contains = 1;
                            subjects[j].numbersOfItems[k] -= quantity;
                            if (subjects[j].numbersOfItems[k] == 0)
                            {
                                for (int i = k; i < subjects[j].totalItems - 1; i++)
                                {
                                    subjects[j].items[i] = subjects[j].items[i + 1];
                                    subjects[j].numbersOfItems[i] = subjects[j].numbersOfItems[i + 1];
                                }

                                subjects[j].totalItems--;
                            }
                            break;
                        }
                    }

                    if (!contains && quantity > 0)
                    {
                        return 0;
                    }
                }
            }
        }
        token = strtok(NULL, " ");
    }
    return 1;
}

// if it is possible, seller sell item(s) to the buyer(s)
void executeSellTo(char sentence[1025])
{
    char *token;
    char *token2;
    int multiplier = 1;
    char tempString[1025];
    char tempString2[1025];
    char sentence2[1025];
    strcpy(sentence2, sentence);
    token = strtok(sentence, " ");
    strcpy(tempString, "");
    while (strcmp(token, "to") != 0)
    {
        strcat(tempString, token);
        strcat(tempString, " ");
        if (strcmp(token, "and") == 0)
        {
            token = strtok(NULL, " ");
            if (!isInteger(token))
                multiplier++;
        }
        else
        {
            token = strtok(NULL, " ");
        }
    }
    token = strtok(NULL, " ");
    strcpy(tempString2, token);
    if (executeSell(tempString))
    {

        strcat(tempString2, " buy ");
        token2 = strtok(sentence2, " ");
        while (strcmp(token2, "sell") != 0)
        {
            token2 = strtok(NULL, " ");
        }
        token2 = strtok(NULL, " ");
        while (strcmp(token2, "to") != 0)
        {
            if (isInteger(token2))
            {
                int quantity = atoi(token2);
                int final_quantity = multiplier * quantity;
                char str[1025];
                sprintf(str, "%d", final_quantity);
                strcat(tempString2, str);
            }
            else
            {
                strcat(tempString2, token2);
            }
            strcat(tempString2, " ");
            token2 = strtok(NULL, " ");
        }
        executeBuy(tempString2);
    }
}

// check which action is going to be executed
void executeGeneral(char str[1025])
{
    // check if the action is "go to"
    if (strstr(str, "go to"))
    {
        executeGoTo(str);
    }
    // check if the action is "buy"
    else if (strstr(str, " buy"))
    {
        // check if the action is "buy from"
        if (strstr(str, " from"))
        {
            executeBuyFrom(str);
        }
        else
        {

            executeBuy(str);
        }
    }
    // check if the action is "sell"
    else if (strstr(str, " sell"))
    {
        // check if the action is "sell to"
        if (strstr(str, " to"))
        {
            executeSellTo(str);
        }
        else
        {
            executeSell(str);
        }
    }
}

// prints the location of the desired subject
void executeWhere(char sentence[1025])
{
    char *token;
    token = strtok(sentence, " ");
    for (int i = 0; i < totalSubjects; i++)
    {
        if (strcmp(subjects[i].name, token) == 0)
        {
            // check if the subject is at somewhere
            if (subjects[i].location)
            {
                printf("%s\n", subjects[i].location->name);
                return;
            }
            else
                printf("NOWHERE\n");
            return;
        }
    }
}

// prints what and how many items the subject have
void executeTotal(char sentence[1025])
{
    char *token;
    token = strtok(sentence, " ");
    for (int i = 0; i < totalSubjects; i++)
    {
        if (strcmp(subjects[i].name, token) == 0)
        {
            if (subjects[i].totalItems == 0)
            {
                printf("NOTHING");
            }
            for (int k = 0; k < subjects[i].totalItems; k++)
            {
                printf("%d ", subjects[i].numbersOfItems[k]);
                printf("%s", subjects[i].items[k]);
                if (k != subjects[i].totalItems - 1)
                {
                    printf(" and ");
                }
            }
            printf("\n");
        }
    }
}

// prints the total number of the item that subject(s) have
void executeTotalItem(char sentence[1025])
{
    char *token;
    char *token2;
    int total = 0;
    char sentence2[1025];
    strcpy(sentence2, sentence);
    token = strtok(sentence, " ");
    while (strcmp(token, "total"))
    {
        token = strtok(NULL, " ");
    }
    token = strtok(NULL, " ");
    token2 = strtok(sentence2, " ");
    while (strcmp(token2, "total"))
    {
        if (strcmp(token2, "and") != 0)
        {
            for (int i = 0; i < totalSubjects; i++)
            {
                if (strcmp(subjects[i].name, token2) == 0)
                {
                    for (int k = 0; k < subjects[i].totalItems; k++)
                    {
                        if (strcmp(subjects[i].items[k], token) == 0)
                        {
                            total += subjects[i].numbersOfItems[k];
                        }
                    }
                }
            }
        }
        token2 = strtok(NULL, " ");
    }
    printf("%d\n", total);
}

// check when the conditional sentences begin and when they end
// if conditions are true, then make the executions if possible
void scanArrays(char *clauses[], char *clauseTypes[], int clauseNum)
{
    printf("OK\n");
    fflush(stdout);
    int lastSentence = -1;
    int firstCond = 0;
    int lastCond = 0;
    int current = 0;
    int condValid = 1;

    while (lastSentence < clauseNum)
    {

        condValid = 1;

        while (strcmp(clauseTypes[current], "condition"))
        {
            current++;

            if (current == clauseNum)
            {
                break;
            }
        }

        firstCond = current;

        if (current != clauseNum)
        {
            while (strcmp(clauseTypes[current], "action"))
            {

                current++;

                if (current == clauseNum)
                {
                    break;
                }
            }
        }

        lastCond = current;

        for (int i = firstCond; i < lastCond; i++)
        {
            // contidion check function
            if (checkGeneral(clauses[i]) == 0)
            {
                condValid = 0;
                break;
            }
        }

        if (condValid)
        {
            if (lastSentence == -1)
            {
                lastSentence = 0;
            }

            for (int i = lastSentence; i < firstCond; i++)
            {
                // execute function
                executeGeneral(clauses[i]);
            }
        }

        lastSentence = lastCond;
    }
}

// check if the input is valid
// classify the clauses into two groups that are condition and actions if the input is valid
void checkType(char line[1025])
{
    int first = 1;
    int ifCond = 0;
    char *clauses[200];     // stores clauses for using after validation check
    char *clauseTypes[200]; // stores clause types to check if the input is valid or not
    int clauseNumbers = 0;
    char *token;
    token = strtok(line, " ");

    if (strcmp("exit", token) == 0)
    {
        ifExit = 0;
        return;
    }

    char temp_string[1025];
    strcpy(temp_string, "");

    if (strcmp("who", token) == 0) // check the validity of "who at ... ?"
    {

        token = strtok(NULL, " ");

        if (strcmp("at", token) == 0)
        {

            token = strtok(NULL, " ");

            if (isValidString(token))
            {
                if (inSubjects(token))
                {
                    printf("INVALID\n");
                    return;
                }
                if (inLocations(token) == 0)
                {
                    struct Location loca;
                    strcpy(loca.name, token);
                    loca.subjectCount = 0;
                    locations[totalLocations++] = loca;
                }
            }
            else
            {
                printf("INVALID\n");
                return;
            }

            char cur_location[1025];
            strcpy(cur_location, token);

            token = strtok(NULL, " ");

            if (token && strcmp(token, "?") == 0)
            {
                token = strtok(NULL, " ");

                if (token)
                {
                    printf("INVALID\n");
                    return;
                }

                whoAt(cur_location);
                return;
            }
            else
            {
                printf("INVALID\n");
                return;
            }
        }
    }

    while (token != NULL) // check the validity of all words one by one
    {

        if (strcmp(temp_string, "") == 0 && strcmp(token, "and") == 0)
        {

            first = 1;
            token = strtok(NULL, " ");
            if (strcmp(token, "and") == 0 || clauseNumbers == 0) // if a sentence starts with "and", print invalid
            {
                printf("INVALID\n");
                return;
            }
            continue;
        }
        if (first) // check if the first word is a valid subject or "if"
        {
            if (isValidString(token))
            {
                if (inLocations(token))
                {
                    printf("INVALID\n");
                    return;
                }
                if (inSubjects(token) == 0)
                {
                    struct Subject person;
                    strcpy(person.name, token);
                    person.location = NULL;
                    person.totalItems = 0;
                    subjects[totalSubjects++] = person;
                }
            }
            else if ((strcmp(token, "if") == 0 && clauseNumbers > 0))
            {
                ifCond = 1;
                token = strtok(NULL, " ");
            }

            else
            {
                printf("INVALID\n");
                return;
            }
        }

        strcat(temp_string, token);
        strcat(temp_string, " ");
        if (strcmp(token, "go") == 0) // check if "go to" sentence is valid
        {
            ifCond = 0;
            token = strtok(NULL, " ");
            if (strcmp(token, "to") == 0)
            {
                strcat(temp_string, token);
                strcat(temp_string, " ");
                token = strtok(NULL, " ");
                if (isValidString(token))
                {
                    if (inSubjects(token) || strcmp(token, "NOWHERE") == 0)
                    {
                        printf("INVALID\n");
                        return;
                    }
                    if (inLocations(token) == 0)
                    {
                        struct Location loca;
                        strcpy(loca.name, token);
                        loca.subjectCount = 0;
                        locations[totalLocations++] = loca;
                    }

                    // add the valid sentence to clause and clauseTypes arrays
                    strcat(temp_string, token);
                    clauses[clauseNumbers] = strdup(temp_string);
                    clauseTypes[clauseNumbers++] = "action";
                    strcpy(temp_string, "");
                    token = strtok(NULL, " ");
                }

                else
                {
                    printf("INVALID\n");
                    return;
                }
            }
            else
            {
                printf("INVALID\n");
                return;
            }
        }
        else if (strcmp(token, "buy") == 0) // check if "buy" sentence is valid
        {
            ifCond = 0;
            token = strtok(NULL, " ");
            if (token && isInteger(token))
            {
                strcat(temp_string, token);
                strcat(temp_string, " ");
                token = strtok(NULL, " ");
                if (!token || inSubjects(token) || inLocations(token) || !isValidString(token))
                {
                    printf("INVALID\n");
                    return;
                }
                else
                {
                    strcat(temp_string, token);
                    strcat(temp_string, " ");
                }
                token = strtok(NULL, " ");
            }
            else
            {
                printf("INVALID\n");
                return;
            }

            while (token && strcmp(token, "and") == 0) // check for other items
            {
                token = strtok(NULL, " ");

                if (token && isInteger(token))
                {
                    strcat(temp_string, "and ");
                    strcat(temp_string, token);
                    strcat(temp_string, " ");
                    token = strtok(NULL, " ");

                    char temp_string2[1025];
                    strcpy(temp_string2, temp_string);

                    if (containsWord(temp_string2, token))
                    {
                        printf("INVALID\n");
                        return;
                    }

                    if (!token || inSubjects(token) || inLocations(token) || !isValidString(token))
                    {
                        printf("INVALID\n");
                        return;
                    }
                    else
                    {
                        strcat(temp_string, token);
                        strcat(temp_string, " ");
                    }
                    token = strtok(NULL, " ");
                }
                else
                {
                    first = 1;
                    break;
                }
            }

            if (token && strcmp(token, "from") == 0) // check if "buy from" sentence is valid
            {
                strcat(temp_string, token);
                strcat(temp_string, " ");
                token = strtok(NULL, " ");
                if (!token || strstr(temp_string, token))
                {
                    printf("INVALID\n");
                    return;
                }
                else
                {
                    if (!token || inLocations(token) || !isValidString(token))
                    {
                        printf("INVALID\n");
                        return;
                    }
                    if (token && !inSubjects(token))
                    {
                        struct Subject person;
                        strcpy(person.name, token);
                        person.location = NULL;
                        person.totalItems = 0;
                        subjects[totalSubjects++] = person;
                    }
                    // add the valid sentence to clause and clauseTypes arrays
                    strcat(temp_string, token);
                    clauses[clauseNumbers] = strdup(temp_string);
                    clauseTypes[clauseNumbers++] = "action";
                    strcpy(temp_string, "");
                    token = strtok(NULL, " ");
                }
            }
            else
            {
                // add the valid sentence to clause and clauseTypes arrays
                clauses[clauseNumbers] = strdup(temp_string);
                clauseTypes[clauseNumbers++] = "action";
                strcpy(temp_string, "");
            }
        }

        else if (strcmp(token, "sell") == 0) // check if "sell" sentence is valid
        {
            ifCond = 0;
            token = strtok(NULL, " ");
            if (token && isInteger(token)) 
            {
                strcat(temp_string, token);
                strcat(temp_string, " ");
                token = strtok(NULL, " ");
                if (!token || inSubjects(token) || inLocations(token) || !isValidString(token)) 
                {
                    printf("INVALID\n");
                    return;
                }
                else
                {
                    strcat(temp_string, token);
                    strcat(temp_string, " ");
                }
                token = strtok(NULL, " ");
            }
            else
            {
                printf("INVALID\n");
                return;
            }

            while (token && strcmp(token, "and") == 0) 
            {
                token = strtok(NULL, " ");

                if (token && isInteger(token)) 
                {
                    strcat(temp_string, "and ");
                    strcat(temp_string, token);
                    strcat(temp_string, " ");
                    token = strtok(NULL, " ");

                    if (containsWord(temp_string, token))
                    {
                        printf("INVALID\n");
                        return;
                    }
                    if (!token || inSubjects(token) || inLocations(token) || !isValidString(token)) 
                    {
                        printf("INVALID\n");
                        return;
                    }
                    else
                    {
                        strcat(temp_string, token);
                        strcat(temp_string, " ");
                    }
                    token = strtok(NULL, " ");
                }
                else
                {
                    first = 1;
                    break;
                }
            }

            if (token && strcmp(token, "to") == 0) // check if "sell to" sentence is valid
            {
                strcat(temp_string, token);
                strcat(temp_string, " ");
                token = strtok(NULL, " ");
                if (!token || strstr(temp_string, token)) 
                {
                    printf("INVALID\n");
                    return;
                }
                else
                {
                    if (!token || inLocations(token) || !isValidString(token)) 
                    {
                        printf("INVALID\n");
                        return;
                    }
                    if (token && !inSubjects(token))
                    {
                        struct Subject person;
                        strcpy(person.name, token);
                        person.location = NULL;
                        person.totalItems = 0;
                        subjects[totalSubjects++] = person;
                    }
                    // add the valid sentence to clause and clauseTypes arrays
                    strcat(temp_string, token);
                    clauses[clauseNumbers] = strdup(temp_string);
                    clauseTypes[clauseNumbers++] = "action";
                    strcpy(temp_string, "");
                    token = strtok(NULL, " ");
                }
            }
            else
            {
                // add the valid sentence to clause and clauseTypes arrays
                clauses[clauseNumbers] = strdup(temp_string);
                clauseTypes[clauseNumbers++] = "action";
                strcpy(temp_string, "");
            }
        }

        else if (first) // if token is the first word of the sentence, pass it
        {
            token = strtok(NULL, " ");
            first = 0;
        }

        else if (strcmp(token, "and") == 0) // check the validity of the next sentence after the word "and"
        {
            token = strtok(NULL, " ");

            char temp_string2[1025];
            strcpy(temp_string2, temp_string);

            if (containsWord(temp_string2, token))
            {
                printf("INVALID\n");
                return;
            }

            if (isValidString(token))
            {
                if (inSubjects(token) == 0)
                {
                    struct Subject person;
                    strcpy(person.name, token);
                    person.location = NULL;
                    person.totalItems = 0;
                    subjects[totalSubjects++] = person;
                }
                strcat(temp_string, token);
                strcat(temp_string, " ");
                token = strtok(NULL, " ");
            }
            else
            {
                printf("INVALID\n");
                return;
            }
        }

        else if (strcmp(token, "if") == 0) // check the validity of the use of "if"
        {
            strcpy(temp_string, "");
            token = strtok(NULL, " ");
            first = 1;
            ifCond = 1;
            if (!token)
            {
                strcpy(temp_string, "INVALID");
            }
        }

        else if (strcmp(token, "at") == 0) // check the validity of "at"
        {

            if (clauseNumbers == 0 || ifCond == 0)
            {
                printf("INVALID\n");
                return;
            }

            token = strtok(NULL, " ");

            if (isValidString(token))
            {
                if (inSubjects(token))
                {
                    printf("INVALID\n");
                    return;
                }
                if (inLocations(token) == 0)
                {
                    struct Location loca;
                    strcpy(loca.name, token);
                    loca.subjectCount = 0;
                    locations[totalLocations++] = loca;
                }

                strcat(temp_string, token);
                clauses[clauseNumbers] = strdup(temp_string);
                clauseTypes[clauseNumbers++] = "condition";
                strcpy(temp_string, "");
                token = strtok(NULL, " ");
            }

            else
            {
                printf("INVALID\n");
                return;
            }
        }

        else if (strcmp(token, "has") == 0) // check the validity of "has"
        {
            if (clauseNumbers == 0 || ifCond == 0)
            {
                printf("INVALID\n");
                return;
            }

            token = strtok(NULL, " ");

            if (strcmp(token, "more") == 0 || strcmp(token, "less") == 0) // check the validity of "has more than" or "has less than"
            {
                strcat(temp_string, token);
                strcat(temp_string, " ");
                token = strtok(NULL, " ");
                if (strcmp(token, "than") != 0)
                {
                    printf("INVALID\n");
                    return;
                }
                strcat(temp_string, token);
                strcat(temp_string, " ");
                token = strtok(NULL, " ");
            }

            if (token && isInteger(token)) 
            {
                strcat(temp_string, token);
                strcat(temp_string, " ");
                token = strtok(NULL, " ");
                if (!token || inSubjects(token) || inLocations(token) || !isValidString(token)) 
                {
                    printf("INVALID\n");
                    return;
                }
                else
                {

                    strcat(temp_string, token);
                    strcat(temp_string, " ");
                }
                token = strtok(NULL, " ");
            }
            else
            {
                printf("INVALID\n");
                return;
            }

            while (token && strcmp(token, "and") == 0) // check for the next items
            {
                token = strtok(NULL, " ");

                if (token && isInteger(token))
                {
                    strcat(temp_string, "and ");
                    strcat(temp_string, token);
                    strcat(temp_string, " ");
                    token = strtok(NULL, " ");

                    if (containsWord(temp_string, token))
                    {
                        printf("INVALID\n");
                        return;
                    }

                    if (!token || inSubjects(token) || inLocations(token) || !isValidString(token)) 
                    {
                        printf("INVALID\n");
                        return;
                    }
                    else
                    {
                        strcat(temp_string, token);
                        strcat(temp_string, " ");
                    }
                    token = strtok(NULL, " ");
                }
                else
                {
                    first = 1;
                    break;
                }
            }

            clauses[clauseNumbers] = strdup(temp_string);
            clauseTypes[clauseNumbers++] = "condition";
            strcpy(temp_string, "");
        }
        else if (token && strcmp(token, "total") == 0 && clauseNumbers == 0) // check the validity of "total"
        {
            token = strtok(NULL, " ");

            if (token && strcmp(token, "?") == 0)
            {
                token = strtok(NULL, " ");

                if (token)
                {
                    printf("INVALID\n");
                    return;
                }
                // call the executeTotal function for the valid "total ?" question sentence
                executeTotal(temp_string);
                return;
            }
            else
            {

                if (!token || inSubjects(token) || inLocations(token) || !isValidString(token)) 
                {
                    printf("INVALID\n");
                    return;
                }
                else
                {
                    strcat(temp_string, token);

                    token = strtok(NULL, " ");

                    if (token && strcmp(token, "?") == 0)
                    {
                        token = strtok(NULL, " ");

                        if (token)
                        {
                            printf("INVALID\n");
                            return;
                        }

                        // call the executeTotalItem function for the valid "total item ?" question sentence
                        executeTotalItem(temp_string);
                        return;
                    }
                    else
                    {
                        printf("INVALID\n");
                        return;
                    }
                }
            }
        }

        else if (strcmp(token, "where") == 0 && clauseNumbers == 0 && !strstr(temp_string, " and")) // check the validity of "where"
        {
            token = strtok(NULL, " ");

            if (token && strcmp(token, "?") == 0)
            {
                token = strtok(NULL, " ");

                if (token)
                {
                    printf("INVALID\n");
                    return;
                }
                // call the executeWhere function for the valid "where subject ?" question sentence
                executeWhere(temp_string);
                return;
            }
            else
            {
                printf("INVALID\n");
                return;
            }
        }

        else
        {
            printf("INVALID\n");
            return;
        }
    }

    if (strcmp(temp_string, "") != 0) // print invalid for the case when temp_string is not empty
    {
        printf("INVALID\n");
        return;
    }

    scanArrays(clauses, clauseTypes, clauseNumbers); // call scanArrays function for valid sentences
}
