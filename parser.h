#include <string.h>
#include "config.h"
#include "handler.h"
#include "util.h"
#include <stdio.h>

void parseSpace(char *input, char **parsed)
{
    char *token = strtok(input, " ");
    int i;
    for (i = 0; i < CONFIG.COMMAND_MAX_WORDS; i++)
    {
        if (token == NULL)
            break;
        parsed[i] = token;
        token = strtok(NULL, " ");
    }

    parsed[i] = NULL;
}

int processInput(char *input, char **parsed)
{

    // checks constraints
    if (strlen(input) > CONFIG.COMMAND_MAX_CHARS)
    {
        displayError("MaxLengthError", "length shouldn't exceed 80 characters !");
        return -1;
    }
    else if (getNumberOfWords(input) > CONFIG.COMMAND_MAX_WORDS)
    {
        displayError("MaxNumberOfWordsError", "The maximum number of words allowed in the command is 10 !");
        return -1;
    }

    parseSpace(input, parsed);

    if (handleBuiltinCommand(parsed))
        return 0;
    else
        return 1;
}