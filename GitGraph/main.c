#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int main() {
	system("chcp 65001 > nul");
	FILE* fp = _popen("git branch", "r");
	if (fp == NULL)
	{
		perror("Ошибка");
		return 1;
	}

	char buffer[128];
	printf("Локальные ветки в репозитории:\n");

	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		printf("%s", buffer);
	}

	_pclose(fp);
	return 0;
}