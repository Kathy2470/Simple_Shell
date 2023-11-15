#include "shell.h"

/**
 * allocate_memory - Allocates memory for the words.
 * @numwords: Number of words to be allocated.
 * @str: The input string.
 * @i: The current position in the string.
 * @d: The delimiter string.
 * @s: The array to store the words.
 *
 * Return: 1 on success, 0 on failure.
 */
static int allocate_memory(int numwords, char *str, int i, char *d, char ***s)
{
	int j, k, m;

	for (j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;

		(*s)[j] = malloc((k + 1) * sizeof(char));
		if (!(*s)[j])
		{
			for (k = 0; k < j; k++)
				free((*s)[k]);
			free(*s);
			return (0);
		}

		for (m = 0; m < k; m++)
			(*s)[j][m] = str[i++];
		(*s)[j][m] = '\0';
	}
	(*s)[j] = NULL;
	return (1);
}

/**
 * strtow - Splits a string into words. Repeat delimiters are ignored.
 * @str: The input string.
 * @d: The delimiter string.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **strtow(char *str, char *d)
{
	int i, numwords = 0;
	char **s;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (!d)
		d = " ";

	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);

	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

	if (!allocate_memory(numwords, str, 0, d, &s))
		return (NULL);

	return (s);
}

/**
 * allocate_memory2 - Allocates memory for the words (alternative function).
 * @numwords: Number of words to be allocated.
 * @str: The input string.
 * @i: The current position in the string.
 * @d: The delimiter character.
 * @s: The array to store the words.
 *
 * Return: 1 on success, 0 on failure.
 */
static int allocate_memory2(int numwords, char *str, int i, char d, char ***s)
{
	int j, k, m;

	for (j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;

		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;

		(*s)[j] = malloc((k + 1) * sizeof(char));
		if (!(*s)[j])
		{
			for (k = 0; k < j; k++)
				free((*s)[k]);
			free(*s);
			return (0);
		}

		for (m = 0; m < k; m++)
			(*s)[j][m] = str[i++];
		(*s)[j][m] = '\0';
	}
	(*s)[j] = NULL;
	return (1);
}

/**
 * strtow2 - Splits a string into words.
 * @str: The input string.
 * @d: The delimiter character.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **strtow2(char *str, char d)
{
	int i, numwords = 0;
	char **s;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
			(str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;

	if (numwords == 0)
		return (NULL);

	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

	if (!allocate_memory2(numwords, str, 0, d, &s))
		return (NULL);

	return (s);
}

