#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

// функция для удаления перевода строки в конце строки
void trim_newline(char* str) {
	if (!str || !*str) return;

	char* end = str + strlen(str) - 1;

	if (*end == '\n') end[0] = '\0';
	else {
		char* p = str + strlen(str) - 1;
		while (p > str && (*p == '\n' || *p == '\r')) p--;
		*(p + 1) = '\0';
	}
}

int main() {
	system("chcp 65001 > nul");

	char path[512];
	

	printf("Введите путь к директории: ");
	fgets(path, 100, stdin);

	trim_newline(path);

	char command[1024];

	snprintf(command, sizeof(command), "git -C \"%s\" log --all --graph --oneline --decorate", path);

	FILE* fp = _popen(command, "r");
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