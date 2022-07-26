#include <iostream>
#include <conio.h>
#include <string>
#include <vector>

#include "src/System/Handle/path_handling.h"
#include "src/System/Bootstrap/bootstrap.h"

#include "src/System/System/system_err.h"
#include "src/System/System/system.h"

#include "src/Source/Stream/ostream_snippet.h"
#include "src/Source/Stream/ostream_clr.h"
#include "src/Source/Stream/istream.h"

#include "src/Source/Cmds/commands.h"

using namespace std;

inline std::ostream& operator<<(std::ostream& os, hand::Path path)
{
	return (os << path.get_path());
}

inline std::ostream& operator<<(std::ostream& os, is::Buffer buff)
{
	return (os << buff.get());
}

int main(int argc, char* argv[])
{
	sys::System _sys;
	bt::Bootstrap boot;
	hand::Path path(boot);

	is::Buffer buff;

	while (!_sys.abort)
	{
		cout << os::path(path);
		buff = is::get_line();

		switch (cmd::check(buff))
		{
		case cmd::Null:
			break;

		case cmd::Exit:
			_sys.abort = true;
			break;
			
		case cmd::Detail:
			sys::details();
			break;

		case cmd::Not_found:
			sys::error(sys::Error(sys::Command_Not_Found), buff.get());
		}
	}
}