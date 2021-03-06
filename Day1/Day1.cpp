#include <iostream>
#include <istream>
#include <string>
#include <fstream>
#include <memory>

static std::string ReadInput()
{
	std::string result;
	const char* filename = "day1.input";
	std::filebuf fileBuffer;

	if (fileBuffer.open(filename, std::ios::in))
	{
		std::istream inputStream(&fileBuffer);

		char buffer[256];
		while (!inputStream.eof())
		{
			inputStream.read(buffer, _countof(buffer) - 1);
			buffer[inputStream.gcount()] = NULL;

			result.append(buffer);
		}
	}
	else
	{
		std::cerr << "Couldn't open \"" << filename << "\"." << std::endl;
	}

	return result;
}

int main(int argc, char** argv)
{
	std::string input;

	// Check if we got input through the command line, otherwise read from day1.input
	if (argc > 1)
	{
		input = argv[1];
	}
	else
	{
		input = ReadInput();
	}

	if (input == std::string())
	{
		return -1;
	}

	uint32_t result = 0;

	const std::size_t size = input.size();
	for (std::size_t i = 0; i < size; ++i)
	{
		std::size_t iNext = (i + 1) % size;

		if (input[i] == input[iNext])
		{
			result += (input[i] - '0');
		}
	}

	std::cout << "Input: " << input << std::endl;
	std::cout << "Result: " << result << std::endl;

	return 0;
}