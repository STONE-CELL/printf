#include "main.h"
#include <stddef.h>

/**
 * get_width - Entry point
 * @format: input.
 * @i: input
 * @list: input
 *
 * Return: Always 0.
 */
int get_width(const char *format, int *i, va_list list)
{
	int h;
	int w = 0;

	for (h = *i + 1; format[h] != '\0'; h)
	{
		if (is_digit(format[h]))
		{
			w *= 10;
			w += format[h] - '0';
		}
		else if (format[h] == '*')
		{
			h++;
			w = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = h - 1;

	return (w);
}

