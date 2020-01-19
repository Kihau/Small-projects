class Solution
{
private:
	bool ASCII[256]{};
	int max{};

public:
	int lengthOfLongestSubstring(std::string napis)
	{
		int i{}, b{};
		int index{}, act{};

		while (i < napis.length())
		{
			index = napis[i];
			if (ASCII[index] == true)
			{
				memset(ASCII, 0, 256 * sizeof(bool));
				if (act > max) max = act;
				act = 0;
				i = b;
				++b;
			}
			else
			{
				++act;
				ASCII[index] = true;
			}
			++i;
		}

		if (act > max) return act;
		else return max;
	}
};

int main()
{
	std::string napis;
	std::getline(std::cin, napis);
	Solution task;
	std::cout << "Length longest substring: " << task.lengthOfLongestSubstring(napis);
}
