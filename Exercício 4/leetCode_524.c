#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isSubsequence(char *word, char *s) {
    int i = 0;
    int j = 0;
    
    while (word[i] != '\0' && s[j] != '\0') {
        if (word[i] == s[j]) {
            i++;
        }
        j++;
    }
    return word[i] == '\0';
}

char * findLongestWord(char * s, char ** dictionary, int dictionarySize) {
    char *res = "";
    
    for (int i = 0; i < dictionarySize; i++) {
        char *word = dictionary[i];
        int lenWord = strlen(word);
        int lenRes = strlen(res);
        
        if (lenWord > lenRes || (lenWord == lenRes && strcmp(word, res) < 0)) {
            if (isSubsequence(word, s)) {
                res = word;
            }
        }
    }
    
    return res;
}

int main() {
    char *s1 = "abpcplea";
    char *dict1[] = {"ale", "apple", "monkey", "plea"};
    int size1 = 4;
    printf("Teste 1: %s\n", findLongestWord(s1, dict1, size1));

    char *s2 = "abpcplea";
    char *dict2[] = {"a", "b", "c"};
    int size2 = 3;
    printf("Teste 2: %s\n", findLongestWord(s2, dict2, size2));

    char *s3 = "abpcplea";
    char *dict3[] = {"apple", "apply", "abe"};
    int size3 = 3;
    printf("Teste 3: %s\n", findLongestWord(s3, dict3, size3));

    return 0;
}