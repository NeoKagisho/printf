#include "main.h"
#include <stdarg.h>
#include <unistd.h>

/**
 * _printf - Produces output according to a format.
 * @format: The format string.
 * @...: Variable number of arguments.
 *
 * Return: The number of characters printed (excluding the null byte).
 */
int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    int precision = -1; // Initialize precision to -1 (undefined)

    va_start(args, format);

    while (*format)
    {
        if (*format == '%' && *(format + 1))
        {
            if (*(format + 1) == '.')
            {
                // Handle precision
                precision = 0;
                format += 2;
                while (*format >= '0' && *format <= '9')
                {
                    precision = precision * 10 + (*format - '0');
                    format++;
                }
            }

            switch (*(format + 1))
            {
            case 'c':
                count += write(1, &va_arg(args, int), 1);
                break;
            case 's':
                {
                    char *str = va_arg(args, char *);
                    if (precision >= 0)
                    {
                        while (*str && precision-- > 0)
                        {
                            count += write(1, str++, 1);
                        }
                    }
                    else
                    {
                        count += write(1, str, _strlen(str));
                    }
                }
                break;
            case '%':
                count += write(1, "%", 1);
                break;
            default:
                count += write(1, "%", 1);
                count += write(1, &(*(format + 1)), 1);
            }
            precision = -1; // Reset precision to -1 after use
            format += 2;
        }
        else
        {
            count += write(1, format, 1);
            format++;
        }
    }

    va_end(args);
    return count;
}

/**
 * _strlen - Computes the length of a string.
 * @str: The string.
 *
 * Return: The length of the string.
 */
int _strlen(const char *str)
{
    int len = 0;
    while (*str)
    {
        len++;
        str++;
    }
    return len;
}
