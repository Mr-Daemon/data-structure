
/*
 * 输入：
   第一行包含两个数字，n，Q。表示数组中元素个数和查询个数。
   第二行包含n个数字，表示有序数组。接下来Q行每行一个整数q，表示询问元素。
   (n <= 1e6, q <= 1e5)
   输出：
   对于每个查询q，输出查询结果
 */
#include <stdio.h>

int main(int argc, char const *argv[]) {
    int n, Q;
    scanf("%d", &n);
    scanf("%d", &Q);
    int array[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d", array + i);
    }
    for (int i = 0; i < Q; ++i) {
        int query;
        scanf("%d", query);
        int low = 0, high = n;
        int mid = (low + high) / 2;
        while (low + 1 < high) {
            mid = (low + high) / 2;
            if (array[mid] > query) {
                high = mid;
            } else if (array[mid] < query) {
                low = mid + 1;
            } else {
                break;
            }
        }
        printf("%d\n", mid);
    }
    return 0;
}