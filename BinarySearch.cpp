#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int binarySearch(vector<string> list, string value);

int main()
{
	//List of lines
	vector<string> lineList;

	//List of lines starting bytes
	vector<istream::pos_type> lineListByte;

	//Enter line to find
	string find;
	cout << "Please enter the line you would like to find: ";
	getline(cin, find);

	//Open stream
	ifstream in("./sorted.txt");

	//Save first line starting byte
	lineListByte.push_back(in.tellg());

	//Read lines into line list
	//Save starting byte for each line
	string line;
	while (getline(in, line))
	{
		lineListByte.push_back(in.tellg());
		lineList.push_back(line);
	}

	int lineNumber = binarySearch(lineList, find);

	if(lineNumber == -1) cout << "Line not found!" << endl;
	else
	{
		//Seek to line starting byte
		in.clear();
		in.seekg(lineListByte[lineNumber]);
		getline(in, line);

		cout << "Line found on line " << lineNumber << endl;
		cout << "Starting byte is " << lineListByte[lineNumber] << endl;
		cout << "The line was \"" << line << "\"" << endl;
	}

	return 0;
}

int binarySearch(vector<string> list, string value)
{
    int position = -1;
    int size = list.size();
    int first = 0, last = size - 1;
    int iterations = 0;

    while ( first <= last )
    {
    	iterations ++;

    	//Get middle line
        int middle = (first + last) / 2;

        //Compare lines
        int result = list[middle].compare(value);

        //Update middle
        if ( result == 0 )
        {
            position = middle;
            break;
        }
        else if ( result > 0 )
        {
            last = middle - 1;
        }
        else
        {
            first = middle + 1;
        }
    }

    cout << "Searching took " << iterations << " iterations to find a result" << endl;

    return position;
}