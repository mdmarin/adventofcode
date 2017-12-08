#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

struct program
{
	program();
	program(program&& other);
	program& operator=(program&& other);

	std::string name;
	int number;
	std::vector<std::string> children_names;

	program* parent;
	std::set<program*> children;
};

program::program()
	: number{ 0 }
	, parent{ nullptr }
{
}

program::program(program&& other)
{
	*this = std::move(other);
}

program& program::operator=(program&& other)
{
	if (this != &other)
	{
		name = std::move(other.name);
		number = other.number;
		children_names = std::move(other.children_names);

		parent = other.parent;
		children = std::move(other.children);

		other.number = 0;
		other.parent = nullptr;
		other.children.clear();
		other.children_names.clear();
	}

	return *this;
}

static program parse_program(const char* line)
{
	program result;

	const char* begin = line;
	const char* end = line + 1;

	// Read name
	while (!isspace(*end))
	{
		end++;
	}

	result.name = std::string(begin, end);

	begin = end + 1;

	while (*begin != '(')
	{
		begin++;
	}
	begin++;

	result.number = atoi(begin);

	while (*begin != ')')
	{
		begin++;
	}
	begin++;

	if (*begin == '\n' || *begin == '\r' || *begin == '\0')
	{
		return result;
	}

	begin += 4; // ' -> '
	end = begin + 1;

	while (true)
	{
		while (*end != ',' && *end != '\n' && *end != '\r' && *end != '\0')
		{
			end++;
		}

		result.children_names.emplace_back(begin, end);

		if (*end == ',')
		{
			begin = end + 2; // ', '
			end = begin + 1;
		}
		else
		{
			break;
		}
	}

	return result;
}

static std::vector<program> read_input()
{
	std::vector<program> result;
	const char* filename = "input.txt";

	FILE *fp = nullptr;
	if (fopen_s(&fp, filename, "r") != 0)
	{
		printf("Error opening file '%s'.", filename);
		return result;
	}

	char buffer[4096];
	while (fgets(buffer, _countof(buffer), fp) != nullptr)
	{
		result.push_back(parse_program(buffer));
	}

	fclose(fp);

	return result;
}

int main(int argc, char** argv)
{
	std::vector<program> programs = read_input();

	// Build tree using worst algorithm possible
	int n = programs.size();
	for (int i = 0; i < n; ++i)
	{
		for (int j = i + 1; j < n; ++j)
		{
			program& a = programs[i];
			program& b = programs[j];

			for (const auto& c : a.children_names)
			{
				if (c == b.name)
				{
					b.parent = &a;
					a.children.emplace(&b);
					break;
				}
			}

			for (const auto& c : b.children_names)
			{
				if (c == a.name)
				{
					a.parent = &b;
					b.children.emplace(&a);
					break;
				}
			}
		}
	}

	// Now from any node go to the root, that is the answer.
	program* current = programs.data();
	while (current->parent != nullptr)
	{
		current = current->parent;
	}

	printf("Result: %s\n", current->name.c_str());

	return 0;
}
