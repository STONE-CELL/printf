#include "main.h"
/**
 * print_unsigned - Entry point
 * @types:input
 * @buffer: input
 * @flags: input
 * @width: input
 * @precision: input
 * @size: input
 * Return: Always 0
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int o = BUFF_SIZE - 2;
	unsigned long int u = va_arg(types, unsigned long int);

	u = convert_size_unsgnd(u, size);

	if (u == 0)
		buffer[o--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (u > 0)
	{
		buffer[o--] = (u % 10) + '0';
		u /= 10;
	}

	o++;

	return (write_unsgnd(0, o, buffer, flags, width, precision, size));
}

/**
 * print_octal - Entry point
 * @types: input
 * @buffer: input
 * @flags: input
 * @width: input
 * @precision:input
 * @size:input
 * Return:Always 0
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int o = BUFF_SIZE - 2;
	unsigned long int u = va_arg(types, unsigned long int);
	unsigned long int init_num = u;

	UNUSED(width);

	u = convert_size_unsgnd(u, size);

	if (u == 0)
		buffer[o--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (u > 0)
	{
		buffer[o--] = (u % 8) + '0';
		u /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[o--] = '0';

	o++;

	return (write_unsgnd(0, o, buffer, flags, width, precision, size));
}


/**
 * print_hexadecimal - Entry point
 * @types: input
 * @buffer: input
 * @flags: input
 * @width: input
 * @precision: input
 * @size: input
 * Return:Always 0
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}


/**
 * print_hexa_upper - Entry point
 * @types: input
 * @buffer:input
 * @flags: input
 * @width: input
 * @precision: input
 * @size: input
 * Return:Always 0
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}


/**
 * print_hexa - Entry point
 * @types: input
 * @map_to: input
 * @buffer: input
 * @flags:input
 * @flag_ch:input
 * @width:input
 * @precision:input
 * @size:input
 * @size:input
 * Return: Always 0
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int o = BUFF_SIZE - 2;
	unsigned long int u = va_arg(types, unsigned long int);
	unsigned long int init_num = u;

	UNUSED(width);

	u = convert_size_unsgnd(u, size);

	if (u == 0)
		buffer[o--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (u > 0)
	{
		buffer[o--] = map_to[u % 16];
		u /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[o--] = flag_ch;
		buffer[o--] = '0';
	}

	o++;

	return (write_unsgnd(0, o, buffer, flags, width, precision, size));
}

