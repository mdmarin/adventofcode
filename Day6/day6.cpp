#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

static const int input[] = { 4, 10, 4, 1, 8, 4, 9, 14, 5, 1, 14, 15, 0, 15, 3, 5 };

class mem_config
{
public:
	mem_config();
	mem_config(const int* banks, int count);
	mem_config(const mem_config& other);

	bool operator==(const mem_config& other);

	void reallocate();

private:
	int m_banks[16];
};

mem_config::mem_config()
	: m_banks{}
{
}

mem_config::mem_config(const int* banks, int count)
{
	memcpy_s(m_banks, sizeof(int) * _countof(m_banks), banks, sizeof(int) * count);
}

mem_config::mem_config(const mem_config& other)
	: mem_config(other.m_banks, _countof(other.m_banks))
{
}

bool mem_config::operator==(const mem_config& other)
{
	bool result = (memcmp(m_banks, other.m_banks, sizeof(int) * _countof(m_banks)) == 0);

	return result;
}

void mem_config::reallocate()
{
	int index = 0;

	// Find starting bank
	for (int i = index + 1; i < _countof(m_banks); ++i)
	{
		if (m_banks[i] > m_banks[index])
		{
			index = i;
		}
	}

	int blocks = 0;
	std::swap(blocks, m_banks[index]);
	while (blocks--)
	{
		index = (index + 1) % _countof(m_banks);
		m_banks[index]++;
	}
}

int main(int argc, char** argv)
{
	std::vector<mem_config> configs;
	mem_config current(input, _countof(input));
	int iterations = 0;

	while (std::find(configs.begin(), configs.end(), current) == configs.end())
	{
		configs.emplace_back(current);
		
		current.reallocate();
		iterations++;
	}

	printf("Result: %d\n", iterations);

	return 0;
}