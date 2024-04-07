//
// Created by LuckyE on 2024/4/7.
//

#include <cstdio>
#include <cstdlib>
#include <ctime>

// 生成并打印四则运算题目
void generate_questions(int grade, int num_questions) {
	srand(time(NULL));  // 初始化随机数生成器
	int n1, n2, operation;
	for (int i = 0; i < num_questions; i++) {
		if (grade == 1) { //一年级运算数为20以内，只生成加法或减法运算式，结果小于20
			n1 = rand() % 20;
			n2 = rand() % (20 - n1);  // 确保结果不超过20
			printf("%d + %d = \n", n1, n2);
		} else if (grade == 2) { //二年级运算数为50以内，生成加法和减法混合运算式，结果小于50
			n1 = rand() % 50;
			n2 = rand() % 50;
			operation = rand() % 2;  // 随机选择加法或减法
			if (operation == 0)
				printf("%d + %d = \n", n1, n2);
			else {
				if (n1 < n2) {  // 确保不出现负数结果
					int temp = n1;
					n1 = n2;
					n2 = temp;
				}
				printf("%d - %d = \n", n1, n2);
			}
		} else if (grade == 3) { //三年级运算数为1000以内，生成加法、减法和乘法混合运算式
			n1 = rand() % 1000;
			n2 = rand() % 1000;
			operation = rand() % 3;  // 随机选择加、减、乘法
			if (operation == 0)
				printf("%d + %d = \n", n1, n2);
			else if (operation == 1)
				printf("%d - %d = \n", n1, n2);
			else
				printf("%d * %d = \n", n1, n2);
		} else {
			// 四到六年级，生成更复杂且包含随机运算符的运算式
			const char *ops[] = {"+", "-", "*", "/"};
			int op1, op2, op3; // 用来存储随机选择的运算符索引


			int n1 = rand() % 100 + 1;
			int n2 = rand() % 100 + 1;
			int n3 = rand() % 100 + 1;
			int n4 = rand() % 100 + 1;

			// 随机选择运算符
			op1 = rand() % 4;
			op2 = rand() % 4;
			op3 = rand() % 4;

			int operation = rand() % 4; // 随机选择题目类型

			// 根据随机选择的运算符生成题目
			switch (operation) {
			case 0:
				printf("(%d %s %d) %s %d %s %d = \n", n1, ops[op1], n2, ops[op2], n3, ops[op3], n4);
				break;
			case 1:
				printf("%d %s (%d %s %d) %s %d = \n", n1, ops[op1], n2, ops[op2], n3, ops[op3], n4);
				break;
			case 2:
				printf("%d %s %d %s (%d %s %d) = \n", n1, ops[op1], n2, ops[op3], n3, ops[op2], n4);
				break;
			case 3:
				printf("(%d %s %d) %s (%d %s %d) = \n", n1, ops[op1], n2, ops[op2], n3, ops[op3], n4);
				break;

			}

		}
	}
}

int main() {
	int grade, num_questions;

	printf("请输入年级（1-6）和题目数量：\n");
	scanf("%d %d", &grade, &num_questions);
	printf("\n");
	// 根据输入的年级和题目数量生成题目
	generate_questions(grade, num_questions);

	return 0;
}
