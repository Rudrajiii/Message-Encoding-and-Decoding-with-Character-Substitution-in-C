#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to encode the message
char *tspeakEncode(char *inputText) {
    char *ledger[26] = {
        "6", "p", "&", "+", "=", "_", "-", ")", "(", "\"", "#", "@", "!", "~", "`", "*", "^", "%", "$", "/", "]", "[", "?", "<", ">", "::"
    };

    char *outputText = malloc(strlen(inputText) * sizeof(char));
    if (outputText == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; inputText[i] != '\0'; i++) {
        char c = tolower(inputText[i]);
        if (c >= 'a' && c <= 'z') {
            outputText[i] = *ledger[c - 'a'];
        } else {
            outputText[i] = c;
        }
    }
    outputText[strlen(inputText)] = '\0';
    return outputText;
}

// Function to decode the message
char *tspeakDecode(char *inputText) {
    char *ledger[26] = {
        "6", "p", "&", "+", "=", "_", "-", ")", "(", "\"", "#", "@", "!", "~", "`", "*", "^", "%", "$", "/", "]", "[", "?", "<", ">", "::"
    };

    char *outputText = malloc((strlen(inputText) + 1) * sizeof(char));
    if (outputText == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; inputText[i] != '\0'; i++) {
        char c = inputText[i];
        int found = 0;
        for (int j = 0; j < 26; j++) {
            if (c == *ledger[j]) {
                outputText[i] = 'a' + j;
                found = 1;
                break;
            }
        }
        if (!found) {
            outputText[i] = c;
        }
    }
    outputText[strlen(inputText)] = '\0';
    return outputText;
}

// Function to add message
char *addMessage() {
    char *messageSecret = malloc(100 * sizeof(char));
    if (messageSecret == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    printf("Enter the message: ");
    fgets(messageSecret, 100, stdin);
    // Remove newline character if present
    messageSecret[strcspn(messageSecret, "\n")] = '\0';
    return messageSecret;
}

int main() {
    char menu[] = "\n1. Enter Your Message\n2. Type \"Encode\" for Encoding\n3. Type \"Decode\" for Decoding\n4. Exit\nSELECT ANY CHOICE: ";
    char *messageSecret = NULL;
    char *encodedMessage = NULL;

    char user_input;
    while (1) {
        printf("%s", menu);
        scanf(" %c", &user_input);
        getchar();  // Consume newline character

        switch(user_input) {
            case '1':
                if (messageSecret != NULL) {
                    free(messageSecret);
                }
                messageSecret = addMessage();
                break;
            case '2':
                if (messageSecret != NULL) {
                    printf("Message Encoding...\n");
                    if (encodedMessage != NULL) {
                        free(encodedMessage);
                    }
                    encodedMessage = tspeakEncode(messageSecret);
                    printf("Message Encoded: %s\n", encodedMessage);
                } else {
                    printf("Please enter a message first.\n");
                }
                break;
            case '3':
                if (encodedMessage != NULL) {
                    printf("Message Decoding...\n");
                    char *decodedMessage = tspeakDecode(encodedMessage);
                    printf("Message Decoded: %s\n", decodedMessage);
                    free(decodedMessage);
                } else {
                    printf("Please encode a message first.\n");
                }
                break;
            case '4':
                printf("Exiting...\n");
                if (messageSecret != NULL) {
                    free(messageSecret);
                }
                if (encodedMessage != NULL) {
                    free(encodedMessage);
                }
                exit(0);
            default:
                printf("Invalid User Input\n");
        }
    }

    return 0;
}