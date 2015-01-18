#include <string.h>
#include <stdint.h>
#include <stddef.h>

void *memset(void *dst, int32_t x, size_t n)
{
	char *d = dst;

	while (n--)
	{
		*d++ = x;
	}

	return d;
}

void *memcpy(void *dst, void *src, size_t n)
{
	char *d = dst;
	char *s = src;

	while (n--)
	{
		*d++ = *s++;
	}

	return d;
}

void *memmove(void *dst, void *src, size_t len)
{
	char *d = dst;
	char *s = src;

	if (s > d)
	{
		return memcpy(d, s, len);
	}

	s += len;
	d += len;

	while (len--)
	{
		*--d = *--s;
	}

	return d;
}

int memcmp(void *ptr1, void *ptr2, size_t n)
{
	char *p1 = ptr1;
	char *p2 = ptr2;

	while (n--)
	{
		if (*p1 < *p2)
		{
			return -1;
		}
		else if (*p1 > *p2)
		{
			return +1;
		}

		p1++;
		p2++;
	}

	return 0;
}

int strcmp(char *str1, char *str2)
{
	for (int i = 0; str1[i] != '\0'; i++)
	{
		if (str1[i] < str2[i])
		{
			return -1;
		}
		else if (str1[i] > str2[i])
		{
			return +1;
		}
	}

	return 0;
}
