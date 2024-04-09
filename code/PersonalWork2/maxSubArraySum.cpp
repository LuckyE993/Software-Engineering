#include <stdio.h>
#include <stdlib.h>

// 函数用于计算最大连续子数组和
int maxSubArraySum(int nums[], int n) {
    if (n == 0) return 0; // 如果数组长度为0，返回0

    int maxSoFar = nums[0]; // 到目前为止的最大子数组和
    int currentMax = nums[0]; // 当前位置的最大子数组和

    // 从数组的第二个元素开始遍历
    for (int i = 1; i < n; ++i) {
        currentMax = (nums[i] > currentMax + nums[i]) ? nums[i] : currentMax + nums[i];
        maxSoFar = (maxSoFar > currentMax) ? maxSoFar : currentMax;
    }

    // 如果最大子数组和小于0，则按题目要求返回0
    return maxSoFar > 0 ? maxSoFar : 0;
}

int main() {
    int n; // 数组的长度
    printf("请输入数组的长度: ");
    scanf("%d", &n); // 读取数组的长度

    int* nums = (int*)malloc(n * sizeof(int)); // 动态分配数组

    if (nums == NULL) {
        printf("内存分配失败\n");
        return 1; // 如果内存分配失败，退出程序
    }

    printf("请输入数组元素: ");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &nums[i]); // 逐个读取数组元素
    }

    // 计算并输出最大连续子数组和
    printf("最大连续子数组和为: %d\n", maxSubArraySum(nums, n));

    free(nums); // 释放动态分配的内存

    getchar();
    getchar();
    return 0;
}
