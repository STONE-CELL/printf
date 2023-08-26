#include "main.h"
#include <stddef.h>

/**
 * get_flags - Entry point
 * @format: input
 * @i: input
 * Return: Always 0
 */
int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int k, h;
	int f = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (h = *i + 1; format[h] != '\0'; h++)
	{
		for (k = 0; FLAGS_CH[k] != '\0'; k++)
			if (format[h] == FLAGS_CH[k])
			{
				f  |= FLAGS_ARR[k];
				break;
			}

		if (FLAGS_CH[k] == 0)
			break;
	}

	*i = h - 1;

	return (f);
}

