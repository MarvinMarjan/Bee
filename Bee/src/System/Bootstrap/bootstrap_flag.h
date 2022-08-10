#pragma once

#include <string>
#include <vector>

namespace bt
{
	enum BootFlag
	{
		Pause,
		HidePath,
		HideWindow
	};

	class Bootstrap_Flag
	{
	public:
		Bootstrap_Flag() {};
		Bootstrap_Flag(std::vector<BootFlag> flags) { this->flags = flags; }

		inline void operator=(std::vector<BootFlag> flags) { this->flags = flags; }

		inline bool is_active(BootFlag flag)
		{
			for (BootFlag fl : this->flags)
				if (fl == flag)	return true;

			return false;
		}

	private:
		std::vector<BootFlag> flags;
	};

	std::vector<BootFlag> check_bt_flag(int argc, char* argv[])
	{
		std::vector<BootFlag> flags;
		std::string flag;

		for (size_t i = 0; i < argc; i++)
		{
			if (argv[i][0] == '-')
			{
				flag = util::erase_first((std::string)argv[i]);

				if (flag == "hp") flags.push_back(HidePath);
				else if (flag == "hw") flags.push_back(HideWindow);
				else if (flag == "p") flags.push_back(Pause);
			}
		}

		return flags;
	}
}