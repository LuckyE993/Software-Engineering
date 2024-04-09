#include "gtest/gtest.h"
#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;

// 最大子数组和
int maxSubArraySum(const vector<int>& nums) {
    if (nums.empty()) {
        return 0; // 如果数组为空，返回0
    }

    int maxSoFar = nums[0]; // 到目前为止的最大子数组和 
    int currentMax = nums[0]; // 当前位置的最大子数组和

    for (int i = 1; i < nums.size(); ++i) {
        currentMax = max(nums[i], currentMax + nums[i]);
        maxSoFar = max(maxSoFar, currentMax);
    }

    return maxSoFar > 0 ? maxSoFar : 0;
}

// 单元测试
// 处理 maxSubArraySum 函数中空数组的测试用例。
TEST(MaxSubArraySumTest, HandlesEmptyArray) {
    cout << "Testing with an empty array." << endl;
    std::vector<int> nums = {};
    EXPECT_EQ(maxSubArraySum(nums), 0);
}
// 处理所有负数的测试用例。
TEST(MaxSubArraySumTest, HandlesAllNegativeNumbers) {
    cout << "Testing with all negative numbers." << endl;
    std::vector<int> nums = { -1, -2, -3, -4 };
    EXPECT_EQ(maxSubArraySum(nums), 0);
}
// 处理混合正负数的测试用例。
TEST(MaxSubArraySumTest, HandlesMixedPositiveAndNegativeNumbers) {
    cout << "Testing with mixed positive and negative numbers." << endl;
    std::vector<int> nums = { -2, 11, -4, 13, -5, -2 };
    EXPECT_EQ(maxSubArraySum(nums), 20);
}
// 处理所有正数的测试用例。
TEST(MaxSubArraySumTest, HandlesAllPositiveNumbers) {
    cout << "Testing with all positive numbers." << endl;
    std::vector<int> nums = { 1, 2, 3, 4 };
    EXPECT_EQ(maxSubArraySum(nums), 10);
}
// 处理单个元素的测试用例。
TEST(MaxSubArraySumTest, HandlesSingleElementArray) {
    cout << "Testing with a single element array." << endl;
    std::vector<int> nums = { -5 };
    EXPECT_EQ(maxSubArraySum(nums), 0);

    cout << "Testing with a single positive element array." << endl;
    nums = { 5 };
    EXPECT_EQ(maxSubArraySum(nums), 5);
}
// 处理单个零元素的测试用例。
TEST(MaxSubArraySumTest, HandlesSingleZeroElementArray) {
    cout << "Testing with a single zero element array." << endl;
    std::vector<int> nums = { 0 };
    EXPECT_EQ(maxSubArraySum(nums), 0);
}
// 处理所有零元素的测试用例。
TEST(MaxSubArraySumTest, HandlesAllZerosArray) {
    cout << "Testing with an array of all zeros." << endl;
    std::vector<int> nums = { 0, 0, 0, 0 };
    EXPECT_EQ(maxSubArraySum(nums), 0);
}


//Google Test主程序
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
