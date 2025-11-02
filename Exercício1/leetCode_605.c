#include <stdio.h>
#include <stdbool.h> 


bool canPlaceFlowers(int* flowerbed, int flowerbedSize, int n) {
    
    int count = 0;

    for (int i = 0; i < flowerbedSize; i++) {
        
        if (flowerbed[i] == 0) {
            
            bool emptyLeft = (i == 0) || (flowerbed[i - 1] == 0);
            
            bool emptyRight = (i == flowerbedSize - 1) || (flowerbed[i + 1] == 0);
            
            if (emptyLeft && emptyRight) {
                flowerbed[i] = 1; 
                count++;
            }
        }
    }
    
    return count >= n;
}


int main() {
    
    int flowerbed1[] = {1, 0, 0, 0, 1};
    int size1 = 5;
    int n1 = 1;
    
    bool result1 = canPlaceFlowers(flowerbed1, size1, n1);
    
    printf("Exemplo 1: %s\n", result1 ? "true" : "false"); 

    
    int flowerbed2[] = {1, 0, 0, 0, 1};
    int size2 = 5;
    int n2 = 2;
    
    bool result2 = canPlaceFlowers(flowerbed2, size2, n2);
    
    printf("Exemplo 2: %s\n", result2 ? "true" : "false"); 

    
    int flowerbed3[] = {0, 0, 1, 0, 0};
    int size3 = 5;
    int n3 = 2;

    bool result3 = canPlaceFlowers(flowerbed3, size3, n3);

    printf("Exemplo 3: %s\n", result3 ? "true" : "false"); 


    return 0; 
}