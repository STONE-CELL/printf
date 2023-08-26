#include "main.h"

/**
 * get_size - Entry point
 * @format:input
 * @i:input
 *
 * Return:Always 0
 */
int get_size(const char *format, int *i)
{
	int o = *i + 1;
	int s = 0;

	if (format[o] == 'l')
		s = S_LONG;
	else if (format[o] == 'h')
		s = S_SHORT;

	if (s == 0)
		*i = o - 1;
	else
		*i = o;

	return (s);
}

