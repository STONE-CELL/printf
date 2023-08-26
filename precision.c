#include "main.h"
#include <stddef.h>

/**
 * get_precision - Entry point
 * @format: input
 * @i:input
 * @list: input.
 *
 * Return: Always 0 .
 */
int get_precision(const char *format, int *i, va_list list)
{
	int h = *i + 1;
	int p = -1;

	if (format[h] != '.')
		return (p);

	p = 0;

	for (h += 1; format[h] != '\0'; h++)
	{
		if (is_digit(format[h]))
		{
			p *= 10;
			p += format[h] - '0';
		}
		else if (format[h] == '*')
		{
			h++;
			p = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = h - 1;

	return ();
}


