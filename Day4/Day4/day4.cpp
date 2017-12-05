#include <stdlib.h>
#include <stdio.h>
#include <set>
#include <string>

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
				const bool unique = std::get<bool>(words.emplace(current, next));
				if (!unique)
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