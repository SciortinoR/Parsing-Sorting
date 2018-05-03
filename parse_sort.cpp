/*
 * Roberto Sciortino - 40069658
 * Alessandro Petrangelo - 40061555
 *
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "json/json.h"
#include "TextTable.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	TextTable t('-','|','+');								//creating text table object for nice formatting of table
	Json::Value root;										//json object

	ifstream inFile(argv[3]);						//opens/reads input json file
	ofstream outFile(argv[4]);					//Opens/reads output .txt file

	if (!inFile.is_open() || !outFile.is_open())			//checks if files both opened correctly
		cout<<"files not opened correctly";

	inFile>>root;											//transfers input file data to json object

	vector<string> item;									//holds each row of table, each item contents
	vector<vector<string>> allItems;						//holds all item in vectors of each item

	//for loops fill up the allItems vector
	for (unsigned int index=0; index<root["items"].size(); index++)
		for (unsigned int i=0; i<root["items"][index]["batter"].size(); i++)
			for (unsigned int j=0; j<root["items"][index]["topping"].size(); j++)
			{
				//fills individual item vector
				item.push_back(root["items"][index]["id"].asString());
				item.push_back(root["items"][index]["type"].asString());
				item.push_back(root["items"][index]["name"].asString());
				item.push_back(root["items"][index]["batter"][i].asString());
				item.push_back(root["items"][index]["topping"][j].asString());

				//COPIES each item vector to allItems vector of vectors
				allItems.push_back(item);
				item.clear();				//clears individual item to iterate through for loop next round
			}

	//sort by id, technically no need for this since json structure is already sorted by id and stored accordingly in vector
	if (argv[2] == string("id"))
		sort(allItems.begin(), allItems.end(), [](const vector<string>& a, const vector<string>& b){return a[0]<b[0];});

	//sorts by type
	else if (argv[2] == string("type"))
		sort(allItems.begin(), allItems.end(), [](const vector<string>& a, const vector<string>& b){return a[1]<b[1];});

	//sort by name
	else if (argv[2] == string("name"))
		sort(allItems.begin(), allItems.end(), [](const vector<string>& a, const vector<string>& b){return a[2]<b[2];});

	//sort by batter
	else if (argv[2] == string("batter"))
		sort(allItems.begin(), allItems.end(), [](const vector<string>& a, const vector<string>& b){return a[3]<b[3];});

	//sort by topping
	else if (argv[2] == string("topping"))
		sort(allItems.begin(), allItems.end(), [](const vector<string>& a, const vector<string>& b){return a[4]<b[4];});

	else
		cout<<"Invalid sort selected, sort by ID will be performed."<<endl;

	//initialize first row of table
	t.add("ID");
	t.add("TYPE");
	t.add("NAME");
	t.add("BATTER");
	t.add("TOPPING");
	t.endOfRow();

	//adds items to table in chosen order
	for (unsigned int i=0; i<allItems.size(); i++)
	{
		t.add(allItems[i][0]);
		t.add(allItems[i][1]);
		t.add(allItems[i][2]);
		t.add(allItems[i][3]);
		t.add(allItems[i][4]);
		t.endOfRow();
	}

	//prints to console and output file
	cout<<t;
	outFile<<t;

	//close both files
	inFile.close();
	outFile.close();

	//checks if files closed
	if (inFile.is_open() || outFile.is_open())
		cout<<"files not closed correctly";

	return 0;
}
