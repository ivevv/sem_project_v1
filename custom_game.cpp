#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include<ctime>

using namespace std;

string get_word(string file_name, int size);
bool check_letter(string word, char guess);
int count_letters(string word, char guess);
int find_letter(string word, char guess, int start);
void show_tries(string file_name);

void menu();
void topic();

int count_words()
{
	int n = 0;
	ifstream custom("custom.txt");
	if (custom.is_open())
	{
		string data;
		while (!custom.eof())
		{
			getline(custom, data);
			n++;
		}
		custom.close();
		return n;
	}
	else return n;
}

void create_custom()
{
	ofstream custom("custom.txt");
	if (!custom.is_open())
	{
		cout << "Error! Going back to the menu.";
		//eng_menu();
	}
	else
	{
		cout << "Note: creating a new custom topic will erase the previous one." << endl;
		cout << "How many words does your topic have?" << endl;
		int size;
		cin >> size;
		cin.clear();
		cout << "Enter your words one by one each of new line:" << endl;
		string word;
		for (int i = 0; i < size; i++)
		{
			cin >> word;
			cin.clear();
			custom << word << endl;
			word.clear();
		}
		custom.close();
		cout << "Done! Your custom topic has been saved." << endl;
	}
}

void custom_hangman()
{
	int amount;
	amount = count_words();
	if (amount == 1)
	{
		cout << "A custom topic has not been created yet! Would you like to create one?" << endl;
		cout << "1. Yes" << endl << "2. No" << endl;
		int choice;
		cin >> choice;
		cin.clear();
		switch (choice)
		{
		case 1:
		{
			create_custom();
			topic();
		}
		break;
		case 2:
		{
			topic();
		}
		break;
		default:
		{
			cout << "Error! Going back to the main menu." << endl;
		}
		break;
		}
	}
	else
	{
		string word;
		string mask;
		word = get_word("custom.txt", amount);
		unsigned int size = word.length();
		for (int i = 0; i < size; i++)
		{
			mask.push_back('_');
		}
		int tries = 9;
		while ((mask != word) && (tries != 0))
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
				int *place = new int[count + 1];
				place[0] = -1;
				for (int i = 1; i < (count + 1); i++)
				{
					place[i] = find_letter(word, guess, place[i - 1]);
					mask[place[i]] = word[place[i]];
				}
				delete[]place;
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
}

void show_custom()
{
	ifstream custom("custom.txt");
	if (!custom.is_open())
	{
		cout << "Error! Going back to the menu." << endl;
	}
	else
	{
		int temp;
		temp = count_words();
		if (temp == 1)
		{
			cout << "A custom topic hasn't been created yet!" << endl;
		}
		else
		{
			string word;
			while (!custom.eof())
			{
				getline(custom, word);
				cout << word << endl;
			}
		}
		custom.close();
	}
}

void add_custom()
{
	ofstream custom;
	custom.open("custom.txt", ios::app);
	if (!custom.is_open())
	{
		cout << "Error! Going back to the menu.";
		//eng_menu();
	}
	else
	{
		cout << "How many words do you want to add?" << endl;
		int size;
		cin >> size;
		cin.clear();
		cout << "Enter your words one by one each of new line:" << endl;
		string word;
		for (int i = 0; i < size; i++)
		{
			cin >> word;
			cin.clear();
			custom << word << endl;
			word.clear();
		}
		custom.close();
		cout << "Done! Your custom topic has been saved." << endl;
	}
}
