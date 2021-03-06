﻿#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_INT 65536

char cur_download[MAX_INT];
int j = 0;
char input_[MAX_INT];

int duxiu_checker() {
	char error_ch, cur_ch;
	FILE *error, *cur;
	sprintf(cur_download,"ren temp %d.png", j);
	system("hexdump temp > tmp.he");
	if (((error = fopen("duxiu_error", "r")) == 0) || ((cur = fopen("tmp.he", "r")) == 0)) {
		printf("文件不存在，请检查目录内有没有duxiu_error，按任意键退出");
		system("pause>nul");
		exit(1);
	}

	do{
		error_ch = fgetc(error);
		cur_ch = fgetc(cur);
		if (error_ch != cur_ch)
		{
			_fcloseall();
			j++;
			return 1;
		}
	} while (error_ch != EOF || cur_ch != EOF);
	_fcloseall();
	system("del temp");
	system("del tmp.he");
	return 0;
}


void duxiu_downloader(const char *extension) {
	char ext_num[MAX_INT];
	char cmd[MAX_INT];
	int i = 0;

	while (1) {
		i++;
		sprintf(ext_num, extension, i);
		sprintf(cmd, "wget %s/%s?zoom=2 -O temp -q", input_, ext_num);
		printf("正在下载第%i页\n", j);
		system(cmd);
		int result_checker = duxiu_checker(j);
		if (result_checker == 1) {
			system(cur_download);
			system("del tmp.he");
		}
		else if (result_checker == 0) {
			break;
		}
	}
}

int main() {
	char _input[MAX_INT];
	int com_check = 0;

	printf("=============================================================\n");
	printf("读秀包库全文下载工具 By:Karo\n");
	printf("使用方法：在浏览器中进入图书的“包库全文阅读”界面，\n");
	printf("在任意一页右键选择复制图片地址后粘贴到此处。\n");
	printf("=============================================================\n");
	printf("如果遇到不能粘贴的情况，鼠标右键单击窗口标题栏，\n");
	printf("在出现的右键菜单栏中打开“属性-选项-快速编辑模式”即可。\n");
	printf("=============================================================\n");
	printf("图片地址示例：\n");
	printf("http://img.sslibrary.com/n/6c948d9f365db88af9ed63e585cf4588MC\n");
	printf("218837224705/img1/AFC7D110F568FE3D41FEFFF926C65C56956A47BF00C\n");
	printf("7FC87CD8BF06ACB87EE458E9B8577B0679B1238FC5C76850E04871F80BC0B\n");
	printf("2FB95E72B33A519C42C04F4F2752DC52A146FFC206132ACC74EB2C6DD2955\n");
	printf("8BBE8DD70E67620C48ACBE9741DAD0FC459033F1B25C99473785230F3F33C\n");
	printf("8B/nf1/qw/10471452/F7286C5FA69C4D5FA3BE934F81F8F882/bok001?zoom=0");
	printf("\n=============================================================\n");
	printf("请输入图片地址：");

	check:
	scanf("%s", _input);
	printf("正在检查图片地址ַ\n");
	for (int i = strlen(_input)-1; i >= 0; i--) {
		if (_input[i] == '/') {
			com_check = 1;
			strncpy(input_,_input,i);
		}
	}
	if (com_check == 0) {
		printf("请输入正确的图片地址，或重新复制后尝试：");
		goto check;
	}

	duxiu_downloader("bok%03d"); // 书名
	duxiu_downloader("cov%03d"); // 封面
	duxiu_downloader("leg%03d"); // 出版信息
	duxiu_downloader("fow%03d"); // 前言
	duxiu_downloader("!%05d"); // 目录
	duxiu_downloader("%06d"); // 正文
	printf("\n===========================================================\n");
	printf("下载完成！");
	system("del temp > nul");
	system("del tmp.he > nul");
	system("pause");
	return 0;
}