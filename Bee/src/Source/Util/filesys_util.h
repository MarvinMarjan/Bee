#pragma once

#include <sys/stat.h>
#include <Windows.h>
#include <direct.h>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../Stream/ostream_snippet.h"

namespace util
{
	enum EntType
	{
		Null,
		File,
		Folder
	};

	inline bool is_hidden(std::string path)
	{
		DWORD att = GetFileAttributesA(path.c_str());

		return ((att != INVALID_FILE_ATTRIBUTES && (att & FILE_ATTRIBUTE_HIDDEN)) ? true : false);
	}

	std::vector<std::string> get_folder_ent(std::string path)
	{
		std::vector<std::string> ents;

		struct dirent* ent;
		DIR* dir = opendir(path.c_str());

		while ((ent = readdir(dir)) != NULL)
			if (ent->d_name != (std::string)"." && ent->d_name != (std::string)"..")
				ents.push_back((std::string)ent->d_name);

		return ents;
	}

	EntType get_ent_type(std::string path)
	{
		DIR* dir = opendir(path.c_str());

		std::fstream file;
		file.open(path.c_str(), std::ios::in);

		if (dir && !file)
			return Folder;

		else if (!dir && file)
			return File;

		else
			return Null;
	}

	std::vector<std::string> read_file(std::string path)
	{
		std::vector<std::string> lines;
		std::string aux;

		std::fstream file;
		file.open(path.c_str(), std::ios::in);

		while (!file.eof())
		{
			std::getline(file, aux);
			lines.push_back(aux);
		}

		return lines;
	}

	inline void write_file(std::string path, std::string content, std::ios::openmode mode = std::ios::app, bool new_line = true)
	{
		std::fstream file;
		file.open(path.c_str(), mode);

		file << content << ((new_line) ? "\n" : "");
		file.close();
	}

	inline void rename_f(std::string path, std::string new_name)
	{
		int __trash = rename(path.c_str(), new_name.c_str());
	}

	inline void create_file(std::string path)
	{
		std::fstream file;
		file.open(path.c_str(), std::ios::out);
		file.close();
	}

	inline void remove_file(std::string path)
	{
		remove(path.c_str());
	}

	inline long long sizeof_file(std::string path)
	{
		struct stat sb {};

		if (!stat(path.c_str(), &sb))
			return sb.st_size;

		return -1;
	}

	inline size_t lineof_file(std::string path)
	{
		std::string buffer;
		size_t lines = 0;

		std::fstream file;
		file.open(path.c_str(), std::ios::in);

		while (!file.eof())
		{
			std::getline(file, buffer);
			lines++;
		}

		return lines;
	}

	size_t linesof_folder(std::string path)
	{
		std::vector<std::string> ents = get_folder_ent(path);
		std::string ent_path;

		size_t lines = 0;

		for (std::string ent : ents)
		{
			ent_path = path + '/' + ent;

			if (get_ent_type(ent_path) == Folder)
				lines += linesof_folder(ent_path);

			else
				lines += lineof_file(ent_path);
		}

		return lines;
	}

	long long sizeof_folder(std::string path, bool print_path = false, bool root = true)
	{
		std::vector<std::string> ents = get_folder_ent(path);
		std::string ent_path;
		long long size = 0;

		if (root)
			std::cout << os::c_move(0) << os::save_c();

		for (std::string ent : ents)
		{
			ent_path = path + '/' + ent;

			if (print_path)
				std::cout << os::load_c() << os::save_c() << os::del_win(0) << os::clr("analyzing: ", os::WT_YELLOW) << os::clr(ent_path, os::WT_GREEN);
			
			if (get_ent_type(ent_path) == Folder)
				size += sizeof_folder(ent_path, print_path, false);

			else
				size += sizeof_file(ent_path);
		}

		if (print_path)
			std::cout << os::load_c() << os::del_win(0) << os::c_move(0);

		return size;
	}

	inline void create_folder(std::string path)
	{
		int _buff = _mkdir(path.c_str());
	}

	inline void remove_folder(std::string path)
	{
		int _buff = _rmdir(path.c_str());
	}

	void remove_not_empty_folder(std::string path, bool print_path = false, bool root = true)
	{
		std::string ent_path;

		if (root)
			std::cout << os::c_move(0) << os::save_c();

		for (std::string ent : get_folder_ent(path))
		{
			ent_path = path + '/' + ent;

			if (print_path)
				std::cout << os::load_c() << os::save_c() << os::del_win(0) << os::clr("removing: ", os::WT_YELLOW) << os::clr(ent_path, os::WT_GREEN);

			if (get_ent_type(ent_path) == File)
				util::remove_file(ent_path);

			else
			{
				if (get_folder_ent(ent_path).size() == 0)
					remove_folder(ent_path);

				else
					remove_not_empty_folder(ent_path, print_path, false);
			}
		}

		if (print_path)
			std::cout << os::load_c() << os::del_win(0) << os::c_move(0);

		remove_folder(path);
	}
}