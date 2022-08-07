#include <stdio.h>
#include <stdlib.h>

int universalMax(void* arr, int len, int size, int (*cmp)(const void* a,const void* b)) {
    int num = 0;
    for (int i = 0; i < len; arr += size) {
        if((*cmp)(arr, arr + size*(num - i)) > 0) {
            num = i;
        }
    }
    return num;
}
int cmp_int(const void* a, const void* b) {
    int* f = (int*)a;
    int* s = (int*)b;
    return *f - *s;
}
int cmp_chr(const void* a, const void* b) {
    char* f = (char*)a;
    char* s = (char*)b;
    return *f - *s;
}
int cmp_flt(const void* a, const void* b) {
    float* f = (float*)a;
    float* s = (float*)b;
    return *f - *s;
}
int main(){
    int* arr = malloc(10 * sizeof(int));
    for(int i = 0; i < 10; i++) {
        scanf("%d", &arr[i]);
    } 
    
    printf("%d", arr[0]);
    for(int i = 1; i < 10; i++) {
        printf("\n%d", arr[i]);
    }
    
    return 0;
}