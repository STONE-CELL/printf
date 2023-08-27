#include "main.h"
#include <stddef.h>


/**
 * print_pointer - Entry point
 * @types: input
 * @buffer:input
 * @flags: input
 * @width:input
 * @precision: input
 * @size: input
 * Return: Alwyas 0
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = 0, p = ' ';
	int d = BUFF_SIZE - 2, l = 2, t = 1;
	unsigned long u;
	char m[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	u = (unsigned long)addrs;

	while (u > 0)
	{
		buffer[d--] = m[u % 16];
		u /= 16;
		l++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		p = '0';
	if (flags & F_PLUS)
		c = '+', l++;
	else if (flags & F_SPACE)
		c = ' ', l++;

	d++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, d, l,
		width, flags, p, c, t));
}


/**
 * print_non_printable - Entry point
 * @types: input
 * @buffer: input
 * @flags: input
 * @width: input
 * @precision: input
 * @size: input
 * Return: Always 0
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int o = 0, f = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[o] != '\0')
	{
		if (is_printable(str[o]))
			buffer[o + f] = str[o];
		else
			f += append_hexa_code(str[o], buffer, o + f);

		o++;
	}

	buffer[o + f] = '\0';

	return (write(1, buffer, o + f));
}

/**
 * print_reverse - Entry point
 * @types:input
 * @buffer: input
 * @flags: input
 * @width: input
 * @precision:input
 * @size: input
 * Return:Always 0
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int o, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (o = 0; str[o]; o++)
		;

	for (o = o - 1; o >= 0; o--)
	{
		char z = str[o];

		write(1, &z, 1);
		count++;
	}
	return (count);
}

/**
 * print_rot13string - Entry point
 * @types: input
 * @buffer:input
 * @flags: input
 * @width:input
 * @precision:input
 * @size:input
 * Return: Always 0
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char r;
	char *str;
	unsigned int o, k;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (o = 0; str[o]; o++)
	{
		for (k = 0; in[k]; k++)
		{
			if (in[k] == str[o])
			{
				r = out[k];
				write(1, &r, 1);
				count++;
				break;
			}
		}
		if (!in[k])
		{
			r = str[o];
			write(1, &r, 1);
			count++;
		}
	}
	return (count);
}

