#include <iostream>

const char STOP_SIGN = '#';


int findStopSign(char* arg) {
    for(unsigned i = 0; i < strlen(arg); i++) {
        if(arg[i] == STOP_SIGN) return i;
    }
    return -1;
}

void hashInsert(char* word, char wordsArray[1024][64], unsigned& wordsArraySize, unsigned* wordsCountArray) {
    for(unsigned i = 0; i < wordsArraySize; i++) {
        if(strcmp(wordsArray[i], word) == 0) {
            wordsCountArray[i]++;
            return;
        }
    }
    strcpy(wordsArray[wordsArraySize], word);
    wordsCountArray[wordsArraySize] = 1;
    wordsArraySize++;
}

int main() {
    char input[1024] = "";

    int stopSignLocation = -1;

    do {
        char line[1024];
        std::cin.getline(line, 1024);

        stopSignLocation = findStopSign(line);

        if(stopSignLocation != -1) {
             line[stopSignLocation] = '\0';
        }

        std::strcat(input, line);
        std::strcat(input, "\n");
    } while(stopSignLocation == -1);

    char wordsArray[1024][64];
    unsigned wordsArraySize = 0;

    unsigned wordsCountArray[1024];

    char* pch = strtok(input, " ,\n");

    while(pch != NULL) {
        hashInsert(pch, wordsArray, wordsArraySize, wordsCountArray);
        pch = strtok(NULL, " ,\n");
    }

    for(unsigned i = 0; i < wordsArraySize; i++) {
        std::cout << wordsArray[i] << " - " << wordsCountArray[i] << "\n";
    }

    return 0;
}
