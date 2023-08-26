#include "main.h"
#include <stddef.h>

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Entry point
 * @format: input
 * Return: Always 0
 */
int _printf(const char *format, ...)
{
	int p, t = 0, c = 0;
int f, w, r, z, buff_ind = 0;
	va_list l;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(l, format);

	for (p = 0; format && format[p] != '\0'; p++)
	{
		if (format[p] != '%')
		{
			buffer[buff_ind++] = format[p];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[p], 1);*/
			c++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			f = get_flags(format, &p);
			w = get_width(format, &p, l);
		       r  = get_precision(format, &p, l);
			z = get_size(format, &p);
			++p;
			t = handle_print(format, &p, l, buffer,
				f, w, r, z);
			if (t == -1)
				return (-1);
			c += t;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(l);

	return (c);
}

/**
 * print_buffer - Entry point
 * @buffer: input
 * @buff_ind:input
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}

