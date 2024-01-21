#include "monty.h"
bus_t bus = {NULL, NULL, NULL, 0};
/**
 * custom_getline - Custom implementation of getline
 * @lineptr: Pointer to the buffer
 * @n: Pointer to the size of the buffer
 * @stream: File stream to read from
 * Return: Number of characters read, or -1 if there are no more lines
 */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t i;
	int c;

	if (*lineptr == NULL)
	{
		*n = 128;
		*lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
	}
	i = 0;
	while ((c = fgetc(stream)) != EOF && c != '\n')
	{
		if (i >= *n - 1)
		{
			*n *= 2;
			*lineptr = (char *)realloc(*lineptr, *n);
			if (*lineptr == NULL)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}
		(*lineptr)[i++] = (char)c;
	}
	if (i == 0 && c == EOF)
	{
		return (-1);
	}
	(*lineptr)[i] = '\0';
	return (i);
}
/**
 * main - Monty code interpreter
 * @argc: Number of arguments
 * @argv: Monty file location
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	char *content;
	FILE *file;
	size_t size = 0;
	ssize_t read_line = 1;
	stack_t *stack = NULL;
	unsigned int counter = 0;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	bus.file = file;
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while (read_line > 0)
	{
		content = NULL;
		read_line = custom_getline(&content, &size, file);
		bus.content = content;
		counter++;
		if (read_line > 0)
		{
			execute(content, &stack, counter, file);
		}
		free(content);
	}
	free_stack(stack);
	fclose(file);
	return (0);
}
