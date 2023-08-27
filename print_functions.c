#include "main.h"
#include <stddef.h>

/**
 * print_char - Entry point
 * @types: input
 * @buffer:input
 * @flags: input
 * @width: input
 * @precision: input
 * @size: input
 * Return: Always 0
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char b = va_arg(types, int);

	return (handle_write_char(b, buffer, flags, width, precision, size));
}

/**
 * print_string - Entry point
 * @types: input
 * @buffer: input
 * @flags: input
 * @width: input
 * @precision:input
 * @size: input
 * Return: Always 0
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int l = 0, o;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[l] != '\0')
		l++;

	if (precision >= 0 && precision < l)
		l = precision;

	if (width > l)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], l);
			for (o = width - l; o > 0; o--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (o = width - l; o > 0; o--)
				write(1, " ", 1);
			write(1, &str[0], l);
			return (width);
		}
	}

	return (write(1, str, l));
}

/**
 * print_percent - Entry point
 * @types: input
 * @buffer:input
 * @flags:input
 * @width:input.
 * @precision: input
 * @size:input
 * Return: Always 0
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}


/**
 * print_int - Entry point
 * @types: input
 * @buffer:input
 * @flags: input
 * @width: input
 * @precision: input
 * @size: input
 * Return: Always 0
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	int s = 0;
	long int t = va_arg(types, long int);
	unsigned long int u;

	t = convert_size_number(t, size);

	if (t == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	u = (unsigned long int)t;

	if (t < 0)
	{
		u = (unsigned long int)((-1) * t);
		s = 1;
	}

	while (u > 0)
	{
		buffer[j--] = (u % 10) + '0';
		u /= 10;
	}

	j++;

	return (write_number(s, j, buffer, flags, width, precision, size));
}


/**
 * print_binary - Entry point
 * @types: input
 * @buffer: input
 * @flags: input
 * @width: input
 * @precision: input
 * @size:input
 * Return: Always 0
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int t, p, y, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	t = va_arg(types, unsigned int);
	p = 2147483648; /* (2 ^ 31) */
	a[0] = t / p;
	for (y = 1; y < 32; y++)
	{
		p /= 2;
		a[y] = (t / p) % 2;
	}
	for (y = 0, sum = 0, count = 0; y < 32; y++)
	{
		sum += a[y];
		if (sum || y == 31)
		{
			char z = '0' + a[y];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

