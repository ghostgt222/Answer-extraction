#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
int main() {
	printf("*****************����ȡ��****************\n");
	printf("���ߣ�gt\n");
	int count;
	char answer[100];			//���б�
	char* mark1 = "class=\"singleAnswer";	//��־�ַ���
	char* mark2 = "<label>";				//��־�ַ���
	char temp1[20] = { 0 };		//�Ƿ���class="singleAnswer"
	char temp2[8] = { 0 };		//�Ƿ���<label>
	FILE* fp;
	fp = fopen("��ҳԴ����.txt", "rb");
	if (fp == NULL) {
		printf("��ҳԴ����.txt�޷���\n");
		getchar();
		return 0;
	}
	for (int j = 0; j < 100; j++) {
		//�ظ�ѭ��ֱ����ȡclass="singleAnswer"
		while (1) {
			for (int i = 0; i < 19; i++) {
				temp1[i] = fgetc(fp);
			}
			fseek(fp, -18, SEEK_CUR);   //�˻�18���ַ�ǰ
			//�Ƚ��ַ���
			int result = strcmp(temp1, mark1);
			if (result == 0) {
				//Ϊ�˸����ҵ�<label>
				fseek(fp, -150, SEEK_CUR);
				count = 0;
				//�ظ�ѭ������ֱ����ȡ<label>
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
							count += 1;		//��¼�ļ�ָ���ƶ����ַ���
						}
						else {
							fseek(fp, -9, SEEK_CUR);
							count += 2;		//��¼�ļ�ָ���ƶ����ַ���
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
	//�����
	for (int i = 1; i <= 100; i++) {

		printf("%2d: %c\t", i, answer[i - 1]);
		if (i % 5 == 0) {
			printf("\n");

		}
	}
	printf("*****************����ȡ���****************\n");
	getchar();
	return 0;

}