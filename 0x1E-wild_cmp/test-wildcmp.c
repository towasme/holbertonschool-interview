#include "holberton.h"
#include <stdio.h>
#include <stdbool.h>

/* adapted from http://developforperformance.com/MatchingWildcards_AnImprovedAlgorithmForBigData.html */

/*
#define COMPARE_PERFORMANCE  1
*/
#define COMPARE_WILD         1
#define COMPARE_TAME         1
#define COMPARE_EMPTY        1


bool test(char *base, char *pattern, bool expected_result)
{
	if (expected_result != (bool)wildcmp(base, pattern))
	{
		printf("Expected %i for base:'%s' pattern:'%s'\n", expected_result ? 1 : 0, base, pattern);
	        return (false);
	}

	return (true);
}

int testWild(void)
{
	int  nReps;
	bool all_passed = true;

#ifdef COMPARE_PERFORMANCE
	/* Can choose as many repetitions as you're expecting in the real world. */
	nReps = 1000000;
#else
	nReps = 1;
#endif

	while (nReps--)
	{
		/* Case with first wildcard after total match. */
		all_passed &= test("Hi", "Hi*", true);

		/* Case with mismatch after '*' */
		all_passed &= test("abc", "ab*d", false);

		/* Cases with repeating character sequences. */
		all_passed &= test("abcccd", "*ccd", true);
		all_passed &= test("mississipissippi", "*issip*ss*", true);
		all_passed &= test("xxxx*zzzzzzzzy*f", "xxxx*zzy*fffff", false);
		all_passed &= test("xxxx*zzzzzzzzy*f", "xxx*zzy*f", true);
		all_passed &= test("xxxxzzzzzzzzyf", "xxxx*zzy*fffff", false);
		all_passed &= test("xxxxzzzzzzzzyf", "xxxx*zzy*f", true);
		all_passed &= test("xyxyxyzyxyz", "xy*z*xyz", true);
		all_passed &= test("mississippi", "*sip*", true);
		all_passed &= test("xyxyxyxyz", "xy*xyz", true);
		all_passed &= test("mississippi", "mi*sip*", true);
		all_passed &= test("ababac", "*abac*", true);
		all_passed &= test("ababac", "*abac*", true);
		all_passed &= test("aaazz", "a*zz*", true);
		all_passed &= test("a12b12", "*12*23", false);
		all_passed &= test("a12b12", "a12b", false);
		all_passed &= test("a12b12", "*12*12*", true);

#ifdef COMPARE_PERFORMANCE
		/* From DDJ reader Andy Belf */
		all_passed &= test("caaab", "*a?b", true);
#endif

		/* Additional cases where the '*' char appears in the base string. */
		all_passed &= test("*", "*", true);
		all_passed &= test("a*abab", "a*b", true);
		all_passed &= test("a*r", "a*", true);
		all_passed &= test("a*ar", "a*aar", false);

		/* More double wildcard scenarios. */
		all_passed &= test("XYXYXYZYXYz", "XY*Z*XYz", true);
		all_passed &= test("missisSIPpi", "*SIP*", true);
		all_passed &= test("mississipPI", "*issip*PI", true);
		all_passed &= test("xyxyxyxyz", "xy*xyz", true);
		all_passed &= test("miSsissippi", "mi*sip*", true);
		all_passed &= test("miSsissippi", "mi*Sip*", false);
		all_passed &= test("abAbac", "*Abac*", true);
		all_passed &= test("aAazz", "a*zz*", true);
		all_passed &= test("A12b12", "*12*23", false);
		all_passed &= test("a12B12", "*12*12*", true);
		all_passed &= test("oWn", "*oWn*", true);

		/* Cases with no wildcards. */
		all_passed &= test("bLah", "bLah", true);
		all_passed &= test("bLah", "bLaH", false);

		/* Simple mixed wildcard tests suggested by Marlin Deckert. */
		all_passed &= test("a", "*?", true);
		all_passed &= test("ab", "*?", true);
		all_passed &= test("abc", "*?", true);

		/* More mixed wildcard tests including coverage for false positives. */
		all_passed &= test("a", "??", false);
		all_passed &= test("ab", "?*?", true);
		all_passed &= test("ab", "*?*?*", true);
		all_passed &= test("abc", "?**?*?", true);
		all_passed &= test("abc", "?**?*&?", false);
		all_passed &= test("abcd", "?b*??", true);
		all_passed &= test("abcd", "?a*??", false);
		all_passed &= test("abcd", "?**?c?", true);
		all_passed &= test("abcd", "?**?d?", false);
		all_passed &= test("abcde", "?*b*?*d*?", true);

		/* Single-character-match cases. */
		all_passed &= test("bLah", "bL?h", true);
		all_passed &= test("bLaaa", "bLa?", false);
		all_passed &= test("bLah", "bLa?", true);
		all_passed &= test("bLaH", "?Lah", false);
		all_passed &= test("bLaH", "?LaH", true);

		/* Many-wildcard scenarios. */
		all_passed &= test("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", "a*a*a*a*a*a*aa*aaa*a*a*b", true);
		all_passed &= test("abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajakalaaaaaaaaaaaaaaaaaffafagaagggagaaaaaaaab",
				   "*a*b*ba*ca*a*aa*aaa*fa*ga*b*", true);
		all_passed &= test("abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajakalaaaaaaaaaaaaaaaaaffafagaagggagaaaaaaaab",
				   "*a*b*ba*ca*a*x*aaa*fa*ga*b*", false);
		all_passed &= test("abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajakalaaaaaaaaaaaaaaaaaffafagaagggagaaaaaaaab",
				   "*a*b*ba*ca*aaaa*fa*ga*gggg*b*", false);
		all_passed &= test("abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajakalaaaaaaaaaaaaaaaaaffafagaagggagaaaaaaaab",
				   "*a*b*ba*ca*aaaa*fa*ga*ggg*b*", true);
		all_passed &= test("aaabbaabbaab", "*aabbaa*a*", true);
		all_passed &= test("a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*",
				   "a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*", true);
		all_passed &= test("aaaaaaaaaaaaaaaaa",
				   "*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*", true);
		all_passed &= test("aaaaaaaaaaaaaaaa",
				   "*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*", false);
		all_passed &= test("abc*abcd*abcde*abcdef*abcdefg*abcdefgh*abcdefghi*a\
bcdefghij*abcdefghijk*abcdefghijkl*abcdefghijklm*abcdefghijklmn",
            "abc*abc*abc*abc*abc*abc*abc*abc*abc*abc*abc*abc*abc*abc*abc*abc*a\
            bc*", false);
		all_passed &= test("abc*abcd*abcde*abcdef*abcdefg*abcdefgh*abcdefghi*a\
bcdefghij*abcdefghijk*abcdefghijkl*abcdefghijklm*abcdefghijklmn",
				   "abc*abc*abc*abc*abc*abc*abc*abc*abc*abc*abc*abc*", true);
		all_passed &= test("abc*abcd*abcd*abc*abcd", "abc*abc*abc*abc*abc",
				   false);
		all_passed &= test(
			"abc*abcd*abcd*abc*abcd*abcd*abc*abcd*abc*abc*abcd",
			"abc*abc*abc*abc*abc*abc*abc*abc*abc*abc*abcd", true);
		all_passed &= test("abc", "********a********b********c********",
				   true);
		all_passed &= test("********a********b********c********", "abc",
				   false);
		all_passed &= test("abc", "********a********b********b********",
				   false);
		all_passed &= test("*abc*", "***a*b*c***", true);

		/* A case-insensitive algorithm test. */
		/* all_passed &= test("mississippi", "*issip*PI", true); */

		/* Tests suggested by other DDJ readers */
		all_passed &= test("", "?", false);
		all_passed &= test("", "*?", false);
		all_passed &= test("", "", true);
		all_passed &= test("a", "", false);
	}

	if (all_passed)
		printf("testWild passed\n");
	else
		printf("testWild failed\n");

	return (0);
}


int testTame(void)
{
	int  nReps;
	bool all_passed = true;

#ifdef COMPARE_PERFORMANCE
	/* Can choose as many repetitions as you're expecting in the real world. */
	nReps = 1000000;
#else
	nReps = 1;
#endif

	while (nReps--)
	{
		/* Case with last character mismatch. */
		all_passed &= test("abc", "abd", false);

		/* Cases with repeating character sequences. */
		all_passed &= test("abcccd", "abcccd", true);
		all_passed &= test("mississipissippi", "mississipissippi", true);
		all_passed &= test("xxxxzzzzzzzzyf", "xxxxzzzzzzzzyfffff", false);
		all_passed &= test("xxxxzzzzzzzzyf", "xxxxzzzzzzzzyf", true);
		all_passed &= test("xxxxzzzzzzzzyf", "xxxxzzy.fffff", false);
		all_passed &= test("xxxxzzzzzzzzyf", "xxxxzzzzzzzzyf", true);
		all_passed &= test("xyxyxyzyxyz", "xyxyxyzyxyz", true);
		all_passed &= test("mississippi", "mississippi", true);
		all_passed &= test("xyxyxyxyz", "xyxyxyxyz", true);
		all_passed &= test("m ississippi", "m ississippi", true);
		all_passed &= test("ababac", "ababac?", false);
		all_passed &= test("dababac", "ababac", false);
		all_passed &= test("aaazz", "aaazz", true);
		all_passed &= test("a12b12", "1212", false);
		all_passed &= test("a12b12", "a12b", false);
		all_passed &= test("a12b12", "a12b12", true);

		/* A mix of cases */
		all_passed &= test("n", "n", true);
		all_passed &= test("aabab", "aabab", true);
		all_passed &= test("ar", "ar", true);
		all_passed &= test("aar", "aaar", false);
		all_passed &= test("XYXYXYZYXYz", "XYXYXYZYXYz", true);
		all_passed &= test("missisSIPpi", "missisSIPpi", true);
		all_passed &= test("mississipPI", "mississipPI", true);
		all_passed &= test("xyxyxyxyz", "xyxyxyxyz", true);
		all_passed &= test("miSsissippi", "miSsissippi", true);
		all_passed &= test("miSsissippi", "miSsisSippi", false);
		all_passed &= test("abAbac", "abAbac", true);
		all_passed &= test("abAbac", "abAbac", true);
		all_passed &= test("aAazz", "aAazz", true);
		all_passed &= test("A12b12", "A12b123", false);
		all_passed &= test("a12B12", "a12B12", true);
		all_passed &= test("oWn", "oWn", true);
		all_passed &= test("bLah", "bLah", true);
		all_passed &= test("bLah", "bLaH", false);

		/* Single '?' cases. */
		all_passed &= test("a", "a", true);
		all_passed &= test("ab", "a?", true);
		all_passed &= test("abc", "ab?", true);

		/* Mixed '?' cases. */
		all_passed &= test("a", "??", false);
		all_passed &= test("ab", "??", true);
		all_passed &= test("abc", "???", true);
		all_passed &= test("abcd", "????", true);
		all_passed &= test("abc", "????", false);
		all_passed &= test("abcd", "?b??", true);
		all_passed &= test("abcd", "?a??", false);
		all_passed &= test("abcd", "??c?", true);
		all_passed &= test("abcd", "??d?", false);
		all_passed &= test("abcde", "?b?d*?", true);

		/* Longer string scenarios. */
		all_passed &= test("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab",
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", true);
		all_passed &= test("abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajakalaaaaaaaaaaaaaaaaaffafagaagggagaaaaaaaab",
            "abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajakalaaaaaaaaaaaaaaaaaffafagaagggagaaaaaaaab", true);
		all_passed &= test("abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajakalaaaaaaaaaaaaaaaaaffafagaagggagaaaaaaaab",
            "abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajaxalaaaaaaaaaaaaaaaaaffafagaagggagaaaaaaaab", false);
		all_passed &= test("abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajakalaaaaaaaaaaaaaaaaaffafagaagggagaaaaaaaab",
            "abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajakalaaaaaaaaaaaaaaaaaffafagaggggagaaaaaaaab", false);
		all_passed &= test("abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajakalaaaaaaaaaaaaaaaaaffafagaagggagaaaaaaaab",
            "abababababababababababababababababababaacacacacaca\
cacadaeafagahaiajakalaaaaaaaaaaaaaaaaaffafagaagggagaaaaaaaab", true);
		all_passed &= test("aaabbaabbaab", "aaabbaabbaab", true);
		all_passed &= test("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
				   "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", true);
		all_passed &= test("aaaaaaaaaaaaaaaaa",
				   "aaaaaaaaaaaaaaaaa", true);
		all_passed &= test("aaaaaaaaaaaaaaaa",
				   "aaaaaaaaaaaaaaaaa", false);
		all_passed &= test("abcabcdabcdeabcdefabcdefgabcdefghabcdefghia\
bcdefghijabcdefghijkabcdefghijklabcdefghijklmabcdefghijklmn",
				   "abcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabc", false);
		all_passed &= test("abcabcdabcdeabcdefabcdefgabcdefghabcdefghia\
bcdefghijabcdefghijkabcdefghijklabcdefghijklmabcdefghijklmn",
            "abcabcdabcdeabcdefabcdefgabcdefghabcdefghia\
bcdefghijabcdefghijkabcdefghijklabcdefghijklmabcdefghijklmn", true);
		all_passed &= test("abcabcdabcdabcabcd", "abcabc?abcabcabc", false);
		all_passed &= test("abcabcdabcdabcabcdabcdabcabcdabcabcabcd",
			"abcabc?abc?abcabc?abc?abc?bc?abc?bc?bcd", true);
		all_passed &= test("?abc?", "?abc?", true);
	}

	if (all_passed)
		printf("testTame passed\n");
	else
		printf("testTame failed\n");

	return (0);
}

int testEmpty(void)
{
	int  nReps;
	bool all_passed = true;

#ifdef COMPARE_PERFORMANCE
	/* Can choose as many repetitions as you're expecting in the real world. */
	nReps = 1000000;
#else
	nReps = 1;
#endif

	while (nReps--)
	{
		/* A simple case */
		all_passed &= test("", "abd", false);

		/* Cases with repeating character sequences */
		all_passed &= test("", "abcccd", false);
		all_passed &= test("", "mississipissippi", false);
		all_passed &= test("", "xxxxzzzzzzzzyfffff", false);
		all_passed &= test("", "xxxxzzzzzzzzyf", false);
		all_passed &= test("", "xxxxzzy.fffff", false);
		all_passed &= test("", "xxxxzzzzzzzzyf", false);
		all_passed &= test("", "xyxyxyzyxyz", false);
		all_passed &= test("", "mississippi", false);
		all_passed &= test("", "xyxyxyxyz", false);
		all_passed &= test("", "m ississippi", false);
		all_passed &= test("", "ababac*", false);
		all_passed &= test("", "ababac", false);
		all_passed &= test("", "aaazz", false);
		all_passed &= test("", "1212", false);
		all_passed &= test("", "a12b", false);
		all_passed &= test("", "a12b12", false);

		/* A mix of cases */
		all_passed &= test("", "n", false);
		all_passed &= test("", "aabab", false);
		all_passed &= test("", "ar", false);
		all_passed &= test("", "aaar", false);
		all_passed &= test("", "XYXYXYZYXYz", false);
		all_passed &= test("", "missisSIPpi", false);
		all_passed &= test("", "mississipPI", false);
		all_passed &= test("", "xyxyxyxyz", false);
		all_passed &= test("", "miSsissippi", false);
		all_passed &= test("", "miSsisSippi", false);
		all_passed &= test("", "abAbac", false);
		all_passed &= test("", "abAbac", false);
		all_passed &= test("", "aAazz", false);
		all_passed &= test("", "A12b123", false);
		all_passed &= test("", "a12B12", false);
		all_passed &= test("", "oWn", false);
		all_passed &= test("", "bLah", false);
		all_passed &= test("", "bLaH", false);

		/* Both strings empty */
		all_passed &= test("", "", true);

		/* Another simple case */
		all_passed &= test("abc", "", false);

		/* Cases with repeating character sequences. */
		all_passed &= test("abcccd", "", false);
		all_passed &= test("mississipissippi", "", false);
		all_passed &= test("xxxxzzzzzzzzyf", "", false);
		all_passed &= test("xxxxzzzzzzzzyf", "", false);
		all_passed &= test("xxxxzzzzzzzzyf", "", false);
		all_passed &= test("xxxxzzzzzzzzyf", "", false);
		all_passed &= test("xyxyxyzyxyz", "", false);
		all_passed &= test("mississippi", "", false);
		all_passed &= test("xyxyxyxyz", "", false);
		all_passed &= test("m ississippi", "", false);
		all_passed &= test("ababac", "", false);
		all_passed &= test("dababac", "", false);
		all_passed &= test("aaazz", "", false);
		all_passed &= test("a12b12", "", false);
		all_passed &= test("a12b12", "", false);
		all_passed &= test("a12b12", "", false);

		/* A mix of cases */
		all_passed &= test("n", "", false);
		all_passed &= test("aabab", "", false);
		all_passed &= test("ar", "", false);
		all_passed &= test("aar", "", false);
		all_passed &= test("XYXYXYZYXYz", "", false);
		all_passed &= test("missisSIPpi", "", false);
		all_passed &= test("mississipPI", "", false);
		all_passed &= test("xyxyxyxyz", "", false);
		all_passed &= test("miSsissippi", "", false);
		all_passed &= test("miSsissippi", "", false);
		all_passed &= test("abAbac", "", false);
		all_passed &= test("abAbac", "", false);
		all_passed &= test("aAazz", "", false);
		all_passed &= test("A12b12", "", false);
		all_passed &= test("a12B12", "", false);
		all_passed &= test("oWn", "", false);
		all_passed &= test("bLah", "", false);
		all_passed &= test("bLah", "", false);
	}

	if (all_passed)
		printf("testEmpty passed\n");
	else
		printf("testEmpty failed\n");

	return (0);
}


int main(void)
{
#ifdef COMPARE_TAME
	testTame();
#endif
#ifdef COMPARE_EMPTY
	testEmpty();
#endif
#ifdef COMPARE_WILD
	testWild();
#endif
	return (0);
}
