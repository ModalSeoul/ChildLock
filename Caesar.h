#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
#ifndef CAESAR_H
#define CAESAR_H

//////////////////////////////////////////////////////
// Initial Caesar Cipher construction
// Purpose:
//		Prevent string searching of familiar strings
//		when reversing the Gunz executable.
//////////////////////////////////////////////////////
class Caesar
{
public:
	char text[100] = { '\0' };
	char cipher[100] = { '\0' };

	// The amount you'd like to shift in the cipher
	int shift_count = 13;
	int get_shift_count()
	{
		return shift_count;
	}
	void set_shift_count(int count)
	{
		shift_count = count;
	}

	// This is a big change to the previous function.
	string encrypt(string to_encrypt)
	{
		int length = to_encrypt.length();
		for (int count = 0; count < length; count++)
		{
			if (isalpha(to_encrypt[count]))
			{
				to_encrypt[count] = tolower(to_encrypt[count]);
				for (int i = 0; i < shift_count; i++)
				{
					if (to_encrypt[count] == 'z')
						to_encrypt[count] = 'a';
					else
						to_encrypt[count]++;
				}
			}
		}
		return to_encrypt;
	}

	string encryptSerial(string to_switch)
	{
		string switchedStr = "";
		for (int i = 0; i < to_switch.length(); i++)
		{
			char c[16];
			sprintf(c, "%d", (int)to_switch[i]);
			switchedStr += c;
			switchedStr += ' '; // I shouldn't have to make a new line for this but whatever.
		}
		return switchedStr;
	}

	string decryptSerial(string to_switch)
	{
		string str = "";
		istringstream iss(to_switch);
		vector<char> biosSerial;
		while (getline(iss, str, ' '))
		{
			biosSerial.push_back(atoi(str.c_str()));
		}
		for (auto& i : biosSerial)
		{
			str += i;
		}
		return str;
	}
};

#endif