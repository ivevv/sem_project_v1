#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include<ctime>

using namespace std;

struct cloud
{
public:
	string word;
};

string get_word(string file_name, int size)
{
	srand(time(NULL));
	int x;
	string rand_word;
	x = (rand() % size);
	ifstream data;
	data.open(file_name);
	if (!data.is_open())
	{
		cout << endl << "Error!" << endl;
		rand_word = "Error";
		return rand_word;
	}
	else
	{
		cloud *topic = new cloud[size];
		for (int i = 0; i < size; i++)
		{
			getline(data, topic[i].word, '\n');
		}
		rand_word = topic[x].word;
		delete[] topic;
		return rand_word;
	}
}

bool check_letter(string word, char guess)
{
	bool check;
	size_t found = word.find(guess);
	if (found != string::npos)
	{
		check = true;
		return check;
	}
	else
	{
		check = false;
		return check;
	}
}

int count_letters(string word, char guess)
{
	unsigned int size = word.length();
	unsigned int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (word[i] == guess)
			count++;
	}
	return count;
}

int find_letter(string word, char guess, int start)
{
	unsigned int size = word.length();
	unsigned int found = 0, count = 0;
	for (int i = (start+1); i < size; i++)
	{
		if (word[i] == guess)
		{
			found = i;
			break;
		}
	}
	return found;
}

void show_tries(string file_name)
{
	ifstream hangman;
	hangman.open(file_name);
	string temp;
	while (!hangman.eof())
	{
		getline(hangman, temp);
		cout << temp << endl;
	}
}

void hangman(string file_name, int amount)
{
	string word;
	string mask;
	word = get_word(file_name, amount);
	unsigned int size = word.length();
	for (int i = 0; i < size; i++)
	{
		mask.push_back('_');
	}
	int tries = 9;
	while ((mask!=word)&&(tries != 0))
	{
		switch (tries)
		{
		case 1:
		{
			show_tries("1_tries.txt");
		}
			break;
		case 2:
		{
			show_tries("2_tries.txt");
		}
			break;
		case 3:
		{
			show_tries("3_tries.txt");
		}
			break;
		case 4:
		{
			show_tries("4_tries.txt");
		}
			break;
		case 5:
		{
			show_tries("5_tries.txt");
		}
			break;
		case 6:
		{
			show_tries("6_tries.txt");
		}
			break;
		case 7:
		{
			show_tries("7_tries.txt");
		}
			break;
		case 8:
		{
			show_tries("8_tries.txt");
		}
			break;
		case 9:
		{
			show_tries("9_tries.txt");
		}
			break;
		}
		for (int i = 0; i < size; i++)
		{
			cout << mask[i] << " ";
		}
		cout << endl << "Guess a letter:" << endl;
		char guess;
		cin >> guess;
		cin.clear();
		bool check = check_letter(word, guess);
		if (check == false)
		{
			tries--;
		}
		else
		{
			int count = count_letters(word, guess);
			int *place = new int[count+1];
			place[0] = -1;
			for (int i = 1; i < (count+1); i++)
			{
				place[i] = find_letter(word, guess, place[i - 1]);
				mask[place[i]] = word[place[i]];
			}
			delete[] place;
		}
	}
	if (mask == word)
	{
		for (int i = 0; i < size; i++)
		{
			cout << mask[i] << " ";
		}
		cout << endl << "Congratulations! You've guessed the word!" << endl;
	}
	if (tries == 0)
	{
		for (int i = 0; i < size; i++)
		{
			cout << mask[i] << " ";
		}
		cout << endl << "GAME OVER" << endl;
		cout << "The word was: " << word << endl;
	}
}
