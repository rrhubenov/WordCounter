#include <iostream>

const char STOP_SIGN = '#';


int findStopSign(char* arg) {
    for(unsigned i = 0; i < strlen(arg); i++) {
        if(arg[i] == STOP_SIGN) return i;
    }
    return -1;
}

bool hashInsert(char* word, char wordsArray[1024][64], unsigned& wordsArraySize, unsigned* wordsCountArray) {
    for(unsigned i = 0; i < wordsArraySize; i++) {
        if(strcmp(wordsArray[i], word) == 0) {
            wordsCountArray[i]++;
            return false;
        }
    }
    strcpy(wordsArray[wordsArraySize], word);
    wordsCountArray[wordsArraySize] = 1;
    wordsArraySize++;

    return true;
}

void swapWordsCountArray(unsigned* wordsCountArray, unsigned position1, unsigned position2) {
    unsigned temp = wordsCountArray[position1];
    wordsCountArray[position1] = wordsCountArray[position2];
    wordsCountArray[position2] = temp;
}


void swapWordsArray(char wordsArray[1024][64], unsigned position1, unsigned position2) {
    char temp[64] = "";
    strcpy(temp, wordsArray[position1]);
    strcpy(wordsArray[position1], wordsArray[position2]);
    strcpy(wordsArray[position2], temp);
}

bool compareWords(char* word1, char* word2) {
    unsigned shortestWordLength = 0;

    if(strlen(word1) > strlen(word2)) {
        shortestWordLength = strlen(word2);
    }
    else {
        shortestWordLength = strlen(word1);
    }

    for(unsigned i = 0; i < shortestWordLength; i++) {
        if(word1[i] > word2[i]) return true;
        else if(word1[i] < word2[i]) return false;
    }

    return false;
}

void insertionSortLex(char wordsArray[1024][64], const unsigned& wordsArraySize, unsigned* wordsCountArray) {
    for(unsigned i = 0; i < wordsArraySize; i++) {
        unsigned j = i;
        while(j > 0 && compareWords(wordsArray[j-1], wordsArray[j])) {
            swapWordsCountArray(wordsCountArray, j, j-1);
            swapWordsArray(wordsArray, j, j-1);
            j--;
        }
    }

}

void insertionSortRep(char wordsArray[1024][64], const unsigned& wordsArraySize, unsigned* wordsCountArray) {
    for(unsigned i = 0; i < wordsArraySize; i++) {
        unsigned j = i;
        while(j > 0 && (wordsCountArray[j-1] < wordsCountArray[j])) {
            swapWordsCountArray(wordsCountArray, j, j-1);
            swapWordsArray(wordsArray, j, j-1);
            j--;
        }
    }
}

void normalizeWord(char* word) {
    unsigned i = 0;
    while(*(word+i) != '\0') {
        if(*(word+i) >= 'A' && *(word+i) <= 'Z') {
            *(word+i) = *(word+i) + 32;
        }
        i++;
    }
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

    unsigned allWordsCount = 0;
    unsigned distinctWordsCount = 0;

    while(pch != NULL) {
        allWordsCount++;

        normalizeWord(pch);
        if(hashInsert(pch, wordsArray, wordsArraySize, wordsCountArray)) {
            distinctWordsCount++;
        }

        pch = strtok(NULL, " .,\n");
    }

    insertionSortLex(wordsArray, wordsArraySize, wordsCountArray);
    insertionSortRep(wordsArray, wordsArraySize, wordsCountArray);

    std::cout << "All words" << " - " << allWordsCount << "\n";
    std::cout << "Distinct words" << " - " << distinctWordsCount << "\n";

    for(unsigned i = 0; i < wordsArraySize; i++) {
        std::cout << wordsArray[i] << " - " << wordsCountArray[i] << "\n";
    }

    return 0;
}
