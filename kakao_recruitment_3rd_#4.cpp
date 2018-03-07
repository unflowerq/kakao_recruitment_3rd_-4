#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Music
{
public:
	int input_index;
	string music_name;
	int music_time;
	string real_melody;
	bool correct_flag = false;

	void input(int index, string name, int time, string melody)
	{
		input_index = index;
		music_name = name;
		music_time = time;
		real_melody = melody;
	}

	void correct(bool correct)
	{
		correct_flag = correct;
	}
};

bool comp(Music a, Music b)
{
	if (a.music_time == b.music_time)
		return a.input_index < b.input_index;
	else
		return a.music_time > b.music_time;
}

string answer(string m, vector<string> musicinfos)
{
	Music *music = new Music[musicinfos.size()];

	vector<string> information;
	int split_index = 0;
	string result = "None";

	for (int i = 0; i < musicinfos.size(); i++)
	{
		information.clear();
		split_index = 0;

		for (int j = 0; j < musicinfos[i].length(); j++)
		{
			if (musicinfos[i][j] == ',')
			{
				information.push_back(musicinfos[i].substr(split_index, j - split_index));
				split_index = j+1;
			}
		}

		information.push_back(musicinfos[i].substr(split_index, musicinfos[i].length() - split_index));

		int time_length = 60 * (stoi(information[1].substr(0, 2)) - stoi(information[0].substr(0, 2))) + (stoi(information[1].substr(3, 2)) - stoi(information[0].substr(3, 2)));

		string music_code = "";
		int music_index = 0;

		for (int j = 0; j < time_length; j++)
		{
			if (music_index == information[3].length())
				music_index = 0;

			music_code += information[3][music_index];
			music_index++;
		}

		music[i].input(i, information[2], time_length, music_code);

		for (int j = 0; j < music_code.length() - m.length(); j++)
		{
			if (music_code.length() < m.length())
				break;

			if (m == music_code.substr(j, m.length()))
			{
				if (music_code[(j + m.length())] == '#')
					continue;
				else
				{
					//result.push_back(information[2]);
					music[i].correct(true);
					break;
				}
			}
		}
	}

	sort(music, music + musicinfos.size(), comp);

	for (int i = 0; i < musicinfos.size(); i++)
	{
		if (music[i].correct_flag)
		{
			result =  music[i].music_name;
			delete[] music;
			return result;
		}
	}

	delete[] music;
	
	return result;
}

int main()
{
	string m = "ABC";
	vector<string> musicinfos = { "12:00,12:14,HELLO,CDEFGAB#" , "13:00,13:13,WORLD,ABCDEF" , "10:56,11:10,WOW,ABC" , "17:00,17:30,SONG,AB#C"};

	string result = "";

	result = answer(m, musicinfos);

	cout << result << endl;

	return 0;
}