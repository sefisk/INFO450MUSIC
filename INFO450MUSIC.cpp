#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <fstream>
using namespace std;




class music
{
	char artistName[50];
	char artistSong[50];
	char rate[3];
public:
	music();
	void setEntry(char a[], char b[], char c[]);
	void display();
	friend class pod;
};

music::music()
{

	strcpy(artistName, "");
	strcpy(artistSong, "");
	strcpy(rate, "");
}

void music::setEntry(char a[], char b[], char c[])
{
	strcpy(artistName, a);
	strcpy(artistSong, b);
	strcpy(rate, c);
}

void music::display()
{
	cout << "Artist: " << artistName << endl;
	cout << "Song: " << artistSong << endl;
	cout << "Rating: " << rate << endl;
}


class pod
{
	char filename[100];
	int listnum = 0;
	music **ml;
	int check();
public:
	pod();
	~pod();
	int getcount();
	void add(music *e);
	void show();
	int save();
	void read();
	int remove();
	void setfilename(char f[]);
};


pod::pod()
{
	ml = new music*[100];
	listnum = 0;
}

pod::~pod()
{
	delete ml;
}
int pod::getcount()
{
	return listnum;
}
void pod::add(music *e)
{
	ml[listnum] = e;
	check();
}
int pod::check()
{
	if (listnum == 0)
	{
		listnum++;
	}
	else
	{
		for (int i = 0; (i < listnum); i++)
		{
			if (strcmp(ml[i]->artistSong, ml[listnum]->artistSong) == 0)
			{
				cout << "You already have that song in this file!" << endl;
				listnum--;
				return -1;
			}
		}
		listnum++;
	}
	return 0;
}
void pod::show()
{
	int count = 0;
	for (int i = 0; i < listnum; i++) {
		if (i % 5 == 0 && i != 0)
		{
			cin.ignore();
			cout << i + 1 << ". " << endl;
			ml[i]->display();
		}
		else
		{
			
			cout << i + 1 << ". " << endl;
			ml[i]->display();

		}
	}
}
void pod::setfilename(char f[])
{
	strcpy(filename, f);
}
int pod::save()
{
	ofstream file(filename);
	if (!file)
	{
		cout << "try again" << endl;
		return -1;
	}
	for (int i = 0; i < listnum; i++)
	{
		file << ml[i]->artistSong << "|";
		file << ml[i]->artistName << "|";
		file << ml[i]->rate << "|\n";
	}
}
int pod::remove()
{
	//Extra Credit
	string line, dartistSong;
	int x;
	cout << "Song to delete: ";
	getline(cin, dartistSong);
	ifstream fin(filename);
	ofstream temp("c:\\a\\temp.txt");

	string songName, artistName, songRate;
	while (fin >> songName >> artistName >> songRate)
	{
		if (dartistSong != songName)
		{
			temp << songName << '|' << artistName << '|' << songRate << '|' << endl;
		}
		if (dartistSong == songName) {
			x = 1;
		}
	}
	if (x == 1) {
		cout << "There is no song with name you entered." << endl;
	}
	else {
		cout << "Song has been deleted." << endl;
	}
	
	temp.close();
	fin.close();
	//rename("c:\\a\\temp.txt", filename);
	
	return 0;
}
void pod::read()
{
	ifstream infile(filename);
	if (!infile)
	{
		return;
	}
	while (!infile.eof())
	{
		music *pl;
		char nme[50];
		char snme[50];
		char rating[3];

		infile.getline(nme, 50, '|');
		if (strlen(nme))
		{
			infile.getline(snme, 50, '|');
			infile.getline(rating, 50, '|');
			pl = new music();
			pl->setEntry(nme, snme, rating);
			add(pl);
		}
	}
	infile.close();
}





int main()
{
	char artistName[50];
	char artistSong[50];
	char rate[3];
	char filename[50];
	bool isReady = true;

	pod *mlr = new pod();
	cout << "Enter path and filename" << endl;
	cin.getline(filename, 50);
	mlr->setfilename(filename);
	mlr->read();
	if (mlr->getcount() != 0)
	{
		cout << "There are " << mlr->getcount() << " songs to choose from" << endl;
		cin.ignore();
	}
	do {
		char opt;
		cout << "What is the next action" << endl;
		cout << "-----------------------" << endl;
		cout << " [A] --> New Song Add" << endl;
		cout << " [S] --> Display Song List" << endl;
		cout << " [D] --> Delete an Entry" << endl;
		cout << " [Q]uit" << endl;
		cin >> opt;
		cin.ignore();
		if (toupper(opt) == 'A')
		{
			
			if (mlr->getcount() < 100)
			{
				cout << "Enter Arist Name" << endl;
				cin.getline(artistName, 50);
				cout << "Enter Artist Song" << endl;
				cin.getline(artistSong, 50);
				cout << "Enter Rating of Song " << endl;
				cin.getline(rate, 50);

				music *song = new music();
				song->setEntry(artistName, artistSong, rate);
				mlr->add(song);

			}
			else
			{
				cout << "No more space on Music Library" << endl;
			}
		}
		else if (toupper(opt) == 'S')
		{
			mlr->show();
			cin.ignore();
			cin.clear();

		}
		else if (toupper(opt) == 'Q')
		{
			mlr->save();
			break;
		}
		else if (toupper(opt) == 'D')
		{
			mlr->save();
			mlr->remove();
			break;
		}
	} while (isReady == true);

	return 0;
}