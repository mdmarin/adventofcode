#include <stdlib.h>
#include <stdio.h>
#include <set>
#include <string>

static int index_for_letter(char c)
{
	int result = c - 'a';

	return result;
}

static void compute_letter_count(const std::string& a, int* result)
{
	for (char c : a)
	{
		result[index_for_letter(c)]++;
	}
}

static bool letter_counts_same(int* letterCountA, int* letterCountB, int count)
{
	for (int i = 0; i < count; ++i)
	{
		if (letterCountA[i] != letterCountB[i])
		{
			return false;
		}
	}
	
	return true;
}

static bool are_anagrams(const std::string& a, const std::string& b)
{
	if (a.length() != b.length())
	{
		return false;
	}

	constexpr int numLetters = 'z' - 'a' + 1;

	int letterCountA[numLetters] = {};
	int letterCountB[numLetters] = {};

	compute_letter_count(a, letterCountA);
	compute_letter_count(b, letterCountB);

	return letter_counts_same(letterCountA, letterCountB, numLetters);
}

int main(int argc, char** argv)
{
	FILE* fp = nullptr;

	const char* filename = "input.txt";
	if (fopen_s(&fp, filename, "r") != 0)
	{
		printf("Error opening input file '%s'.\n", filename);
		return -1;
	}

	std::set<std::string> words;
	char buffer[1024];
	int numPassphrases = 0;
	int numInvalidPassphrases = 0;

	while (fgets(buffer, _countof(buffer), fp) != nullptr)
	{
		numPassphrases++;

		const char* current = buffer;
		const char* next = current;

		while (*next != '\n' && *next != '\0')
		{
			while (!isspace(*(++next)) && *next != '\0')
			{
			}

			if (next != current)
			{
				const auto result = words.emplace(current, next);

				// Uniqueness check
				if (!std::get<bool>(result))
				{
					numInvalidPassphrases++;
					break;
				}

				// Anagram check
				bool hasAnagram = false;
				auto position = std::get<decltype(words)::iterator>(result);
				for (auto iter = words.begin(); iter != words.end(); ++iter)
				{
					if (iter != position && are_anagrams(*iter, *position))
					{
						hasAnagram = true;
						break;
					}
				}

				if (hasAnagram)
				{
					numInvalidPassphrases++;
					break;
				}
			}

			current = next + 1;
		}

		words.clear();
	}

	fclose(fp);

	int numValidPassphrases = numPassphrases - numInvalidPassphrases;
	printf("Result: %d\n", numValidPassphrases);

	return 0;
}