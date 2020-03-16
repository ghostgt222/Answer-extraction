#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
int main() {
	printf("*****************答案提取器****************\n");
	printf("作者：gt\n");
	int count;
	char answer[100];			//答案列表
	char* mark1 = "class=\"singleAnswer";	//标志字符串
	char* mark2 = "<label>";				//标志字符串
	char temp1[20] = { 0 };		//是否是class="singleAnswer"
	char temp2[8] = { 0 };		//是否是<label>
	FILE* fp;
	fp = fopen("网页源代码.txt", "rb");
	if (fp == NULL) {
		printf("网页源代码.txt无法打开\n");
		getchar();
		return 0;
	}
	for (int j = 0; j < 100; j++) {
		//重复循环直至获取class="singleAnswer"
		while (1) {
			for (int i = 0; i < 19; i++) {
				temp1[i] = fgetc(fp);
			}
			fseek(fp, -18, SEEK_CUR);   //退回18个字符前
			//比较字符串
			int result = strcmp(temp1, mark1);
			if (result == 0) {
				//为了更快找到<label>
				fseek(fp, -150, SEEK_CUR);
				count = 0;
				//重复循环回退直至获取<label>
				while (1) {
					for (int k = 0; k < 7; k++) {
						temp2[k] = fgetc(fp);
					}
					result = strcmp(temp2, mark2);
					if (result == 0) {
						answer[j] = fgetc(fp);
						break;
					}
					else {
						if (temp2[0] == 'l') {
							fseek(fp, -8, SEEK_CUR);
							count += 1;		//记录文件指针移动的字符数
						}
						else {
							fseek(fp, -9, SEEK_CUR);
							count += 2;		//记录文件指针移动的字符数
						}

					}
				}
			}
			if (!result) {
				fseek(fp, 150 + count, SEEK_CUR);
				break;
			}
		}
	}
	//输出答案
	for (int i = 1; i <= 100; i++) {

		printf("%2d: %c\t", i, answer[i - 1]);
		if (i % 5 == 0) {
			printf("\n");

		}
	}
	printf("*****************答案提取完成****************\n");
	getchar();
	return 0;

}