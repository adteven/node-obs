// An experimental libobs wrapper for the Node.Js toolset.
// Copyright(C) 2017 General Workings Inc. (Streamlabs)
// 
// This program is free software; you can redistribute it and / or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110 - 1301, USA.

#pragma once
#include <node.h>
#include <obs.h>
#include <locale>
#include <string>

typedef const v8::FunctionCallbackInfo<v8::Value>& v8Arguments;

#define MAKE_ISOLATE(n) v8::Isolate* n = v8::Isolate::GetCurrent()

#pragma region Case-Insensitive String
struct ci_char_traits : public std::char_traits<char> {
	static bool eq(char c1, char c2) {
		return toupper(c1) == toupper(c2);
	}
	static bool ne(char c1, char c2) {
		return toupper(c1) != toupper(c2);
	}
	static bool lt(char c1, char c2) {
		return toupper(c1) < toupper(c2);
	}
	static int compare(const char* s1, const char* s2, size_t n) {
		while (n-- != 0) {
			if (toupper(*s1) < toupper(*s2)) return -1;
			if (toupper(*s1) > toupper(*s2)) return 1;
			++s1; ++s2;
		}
		return 0;
	}
	static const char* find(const char* s, int n, char a) {
		while (n-- > 0 && toupper(*s) != toupper(a)) {
			++s;
		}
		return s;
	}
};

typedef std::basic_string<char, ci_char_traits> istring;
#pragma endregion Case-Insensitive String

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
};
