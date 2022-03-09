#include "holberton.h"
/* true false */
#include <stdbool.h>
/* fprintf */
#include <stdio.h>


/*
 * Special project requirements:
 * - You are not allowed to use loops of any kind.
 * - ltrace allowed functions: write, printf, putchar, puts
 * - static variables are not allowed
 */
/*
 * Currently failing only these three tests in testWild:
 *  - Expected 1 for base:'a*abab' pattern:'a*b'
 *  - Expected 1 for base:'ab' pattern:'*?'
 *  - Expected 1 for base:'abc' pattern:'*?'
 */
/**
 * globMatch - recursive helper to _wildcmp, checks substrings in base and
 *   pattern to see if the local base substring is a valid match to the local
 *   pattern substring following the current wildcard, or if the current
 *   wildcard should continue to skip ahead in the base string
 *
 * @base: current position in base string for comparison
 * @pattern: current postion in pattern string to compare to - can contain the
 *   special character `*`, which can represent any string (including an empty
 *   string)
 * @tested_indices: count of how many positions in the base and pattern
 *   substrings have been evaluated, modified by reference
 *
 * Return: 1 if glob matches base after current wildcard, 0 if not or failure
 */
int globMatch(char *base, char *pattern, int *tested_indices)
{
	if (!base || !pattern || !tested_indices)
		return (0);

	(*tested_indices)++;

	/*
	 * If glob is at end of pattern or is bounded by another wildcard,
	 * then it counts as a match beyond the current wildcard.
	 */
	if (*base == *pattern)
	{
		if (*(pattern + 1) == '\0' || *(pattern + 1) == '*')
			return (1);

		return (globMatch(base + 1, pattern + 1, tested_indices));
	}

	return (0);
}


/**
 * _wildcmp - recursive helper to wildcmp, compares two strings using
 *   UNIX-like asterisk wildcard syntax
 *
 * @base: current position in base string for comparison
 * @pattern: current postion in pattern string to compare to - can contain the
 *   special character `*`, which can represent any string (including an empty
 *   string)
 * @wildcard: flag to indicate if last character read in pattern was a '*'
 *
 * Return: 1 if the strings can be considered identical, 0 if not or failure
 */
int _wildcmp(char *base, char *pattern, bool wildcard)
{
	int offset = 0;

	if (!base || !pattern)
		return (0);

	if (*pattern == '*')
		return (_wildcmp(base, pattern + 1, true));

	if (*pattern == '?')
	{
		if (*base == '\0')
			return (0);

		return (_wildcmp(base + 1, pattern + 1, false));
	}

	if (wildcard)
	{
		if (*base == '\0')
			return (*pattern == '\0');

		if (*base == *pattern && globMatch(base, pattern, &offset))
			return (_wildcmp(base + offset,
					 pattern + offset, false));

		return (_wildcmp(base + 1, pattern, true));
	}

	if (*base == *pattern)
	{
		if (*base == '\0')
			return (1);

		return (_wildcmp(base + 1, pattern + 1, false));
	}

	return (0);
}


/**
 * wildcmp - compares two strings using UNIX-like asterisk wildcard syntax
 *
 * @s1: base string for comparison
 * @s2: pattern string to compare to - can contain the special character `*`,
 *   which can represent any string (including an empty string)
 *
 * Return: 1 if the strings can be considered identical, 0 if not or failure
 */
int wildcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
	{
		fprintf(stderr, "wildcmp: NULL parameter(s)\n");
		return (0);
	}

	return (_wildcmp(s1, s2, false));
}
