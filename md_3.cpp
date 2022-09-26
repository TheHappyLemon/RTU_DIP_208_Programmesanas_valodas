#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DbParser
{
private:
	ifstream in;
	ofstream out;
	vector<string> lines;

	vector<string> splitLine(int lineInd)
	{
		/* Accepts string with , as delimiters */
		/* Splits it into a vector 			   */
		/* Returns the vector				   */
		vector<string> res;
		string line = ',' + lines[lineInd] + ',';
		int ind = 0, prevind;
		ind = line.find(",");
		while (true)
		{
			prevind = ind;
			ind = line.find(",", prevind + 1);
			if (ind == string::npos) break;
			res.push_back(line.substr(prevind + 1, ind - prevind - 1));
		}
		return res;
	}

	bool isBadCity(string city)
	{
		/* Checks if given string does not contain symbols  */
		/* that city or day of a week should not contain    */
		for (int i = 0; i < city.size(); i++)
			if (city[i] >= '!' && city[i] < '@')
				return true;
		return false;
		/* Obviously I could`ve assumed that each symbol should be */
		/* between(a(A)-z(Z)) but it is said that db.csv is ANSII  */
		/* therefore there may be some specials weird letters      */
	}

	bool isBadDigits(string time)
	{
		/* Checks if string contains only digits and :, */
		/* used to check time and price					*/
		string digits = ":.0123456789";
		for (int i = 0; i < time.size(); i++)
			if (digits.find(time[i]) == string::npos)
				return true;
		return false;
	}

public:
	DbParser()
	{
		in.open("db.csv", ios::out);
		out.open("err.txt", ios::trunc);
	};

	void trim()
	{
		/* Replaces every line with new copy  */
		/* of itself without any spaces       */
		string tmp;
		for (int i = 0; i < lines.size(); i++)
		{
			tmp = "";
			for (int j = 0; j < lines[i].size(); j++)
				if (lines[i][j] != ' ')
					tmp = tmp + lines[i][j];
			lines[i] = tmp;
		}
	}

	vector<string> findTripByCond(int cond, string first, string second)
	{
		/* 0 -> find trip where from = first, to = second */
		/* 1 -> find trip where day = first 			  */
		/* 2 -> find trip where price <= first			  */
		/* Returns vector off all good trips			  */
		vector<string> data;
		vector<string> res;
		bool answ = false;
		for (int i = 0; i < lines.size(); i++)
		{
			data = splitLine(i);
			switch (cond)
			{
			case 0:
				answ = (first == data[0] && second == data[1]);
				break;
			case 1:
				answ = (first == data[2]);
				break;
			case 2:
				answ = (stof(first) >= stof(data[4]));
				break;
			default:
				break;
			}
			if (answ)
				res.push_back(data[0] + " " + data[1] + " " + data[2] + " " + data[3] + " " + data[4]);
		}
		return res;
	}

	void checkLines()
	{
		/* Checks every line's every entry. If line is  */
		/* too short or too long or has incorrect data  */
		/* Removes it from the list and writes an error */
		vector<string> tmp;
		vector<int> toErase;
		for (int i = 0; i < lines.size(); i++)
		{
			tmp = splitLine(i);
			if (tmp.size() != 5)
			{
				out << lines[i] << endl;
				toErase.push_back(i);
			}
			else
			{
				if (isBadCity(tmp[0]) || isBadCity(tmp[1]) ||
					isBadCity(tmp[2]) || isBadDigits(tmp[3]) ||
					isBadDigits(tmp[4]))
				{
					out << lines[i] << endl;
					toErase.push_back(i);
				}
			}
		}
		for (int i = 0; i < toErase.size(); i++)
			lines.erase(lines.begin() + (toErase[i] - i));
		out.close();
	}

	void read()
	{
		/* Reads every db.csv line to a vector */
		/* Omits empty newlines 			   */
		string line;
		int x;
		if (in.is_open())
			while (getline(in, line))
				if (line != "")
					lines.push_back(line);
		in.close();
	}

	void print(int file, const vector<string>& vec = vector<string>())
	{
		/* 0 = print db.csv		  */
		/* 1 = print err.txt      */
		/* 2 = print given vector */
		if (file == 0)
		{
			for (vector<string>::iterator it = lines.begin(); it != lines.end(); ++it)
				cout << *it << endl;
		}
		else if (file == 1)
		{
			string line;
			in.open("err.txt", ios::out);
			cout << "result:" << endl;
			while (getline(in, line))
				cout << line << endl;
			in.close();
		}
		else if (file == 2){
			cout << "result:" << endl;
			for (int i = 0;i < vec.size(); i++)
				cout << vec[i] << endl;
		}
	}

	virtual ~DbParser()
	{
		in.close();
		out.close();
	}
};

int main()
{
	string line, line1;
	DbParser parser;
	char ch;
	parser.read();
	parser.trim();
	parser.checkLines();
	while (true)
	{
		cin >> ch;
		switch (ch)
		{
		case 'a':
			cin >> line;
			cin >> line1;
			parser.print(2, parser.findTripByCond(0, line, line1));
			break;
		case 'b':
			cin >> line;
			parser.print(2, parser.findTripByCond(1, line, ""));
			break;
		case 'c':
			cin >> line;
			parser.print(2, parser.findTripByCond(2, line, ""));
			break;
		case 'd':
			parser.print(1);
			break;
		case 'e':
			return 1;
			break;
		default:
			break;
		}
	}
	return 0;
}