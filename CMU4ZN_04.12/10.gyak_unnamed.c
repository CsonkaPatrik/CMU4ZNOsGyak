#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	int fd1[2];
	int fd2[2];

	char fixed_str[] = " a neptun kodom";
	char input_str[6];
	pid_t p;

	if (pipe(fd1) == -1) {
		fprintf(stderr, "Nem sikerult csovezetek");
		return 1;
	}
	if (pipe(fd2) == -1) {
		fprintf(stderr, "nem sikerult csovezetek");
		return 1;
	}

	scanf("%s", input_str);
	p = fork();

	if (p < 0) {
		fprintf(stderr, "nem sikerult csovezetek");
		return 1;
	}

	else if (p > 0) {
		char concat_str[6];

		close(fd1[0]);

		write(fd1[1], input_str, strlen(input_str) + 1);
		close(fd1[1]);

		wait(NULL);

		close(fd2[1]);

		read(fd2[0], concat_str, 6);
		printf("Vegso sztring: %s\n", concat_str);
		close(fd2[0]);
	}

	else {
		close(fd1[1]);

		char concat_str[6];
		read(fd1[0], concat_str, 6);

		int k = strlen(concat_str);
		int i;
		for (i = 0; i < strlen(fixed_str); i++)
			concat_str[k++] = fixed_str[i];

		concat_str[k] = '\0';

		close(fd1[0]);
		close(fd2[0]);

		write(fd2[1], concat_str, strlen(concat_str) + 1);
		close(fd2[1]);

		exit(0);
	}
}
