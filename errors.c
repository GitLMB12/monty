#include "monty.h"

void err(int error_code, ...)
{
	va_list args;

	va_start(args, error_code);
	switch (error_code)
	{
		case 1:
			fprintf(stderr, "USAGE: monty file\n");
			break;
		case 2:
			fprintf(stderr, "Error: Can't open file %s\n", va_arg(args, char *))
				break;
		case 3:
			fprintf(stderr, "L%d: unknown instruction %s\n", va_arg(args, int), va_arg(args, char *));
			break;
		case 4:
			fprintf(stderr, "Error: malloc failed\n");
			break;
		case 5:
			fprintf(stderr, "L%d: usage: push integer\n", va_arg(args, int));
			break;
		default:
			break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}
void more_err(int error_code, ...)
{
	va_list args;

	va_start(args, error_code);
	switch (error_code)
	{
		case 6:
			fprintf(stderr, "L%d: can't pint, stack empty\n", va_arg(args, int));
			break;
		case 7:
			fprintf(stderr, "L%d: can't pop an empty stack\n", va_arg(args, int));
			break;
		case 8:
			fprintf(stderr, "L%d: can't %s, stack too short\n", va_arg(args, int), va_arg(args, char *));
			break;
		case 9:
			fprintf(stderr, "L%d: division by zero\n", va_arg(args, int));
			break;
		default:
			break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}
void string_err(int error_code, ...)
{
	va_list args;

	va_start(args, error_code);

	int line_number = va_arg(args, int);

	switch (error_code)
	{
		case 10:
			fprintf(stderr, "L%d: can't pchar, value out of range\n", line_number);
			break;
		case 11:
			fprintf(stderr, "L%d: can't pchar, stack empty\n", line_number);
			break;
		default:
			break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}
