#include <stdlib.h>
#include <stdio.h>
#include <vector>

static std::vector<int> ReadInput()
{
	std::vector<int> result;

	const char* filename = "input.txt";

	FILE* fp = nullptr;
	if (fopen_s(&fp, filename, "r") != 0)
	{
		printf("Error opening input file '%s'.", filename);
		return result;
	}
	
	char buffer[1024];
	while (fgets(buffer, _countof(buffer), fp) != nullptr)
	{
		int n = atoi(buffer);
		result.push_back(n);
	}

	fclose(fp);

	return result;
}

int main(int argc, char** argv)
{
	std::vector<int> instructions;
	int ip = 0;
	int steps = 0;

	if (argc == 1)
	{
		instructions = ReadInput();
	}
	else
	{
		instructions = std::vector<int>({ 0, 3, 0, 1, -3 });
	}

	const int size = instructions.size();
	while (ip >= 0 && ip < size)
	{
		int& instruction = instructions[ip];
		ip += instruction++;
		steps++;
	}

	printf("Result: %d\n", steps);

	return 0;
}