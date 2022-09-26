#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DbParser {
private:
	ifstream in;
	ofstream out;
	vector<string> lines;
	int size;
	int ENTRIES = 5;

	bool isGoodLine(string line) {
		int count = 0;
		for (int i = 0; i < line.size(); i++) {
			if (line[i] == ',')
				count++;
		}
		return count == 4;
	}

	void deleteBad() {
	}

	vector<string> splitLine(int lineInd) {
		int a;
		vector<string> res;
		string line = ',' + lines[lineInd] + ',';
		int ind = 0, prevind, resInd = 0;
		ind = line.find(",");
		while (true) {
			prevind = ind;
			ind = line.find(",", prevind + 1);
			if (ind == string::npos)
				break;
			res.push_back(line.substr(prevind + 1, ind - prevind - 1));
		}
		return res;
	}

	bool isBadCity(string city) {
		for (int i = 0; i < city.size(); i++) {
			if (city[i] >= '!' && city[i] < '@') {
				return true;
			}
		}
		return false;
	}

	bool isBadDigits(string time) {
		string digits = ":.0123456789";
		for (int i = 0; i < time.size(); i++) {
			if (digits.find(time[i]) == string::npos) {
				return true;
			}
		}
		return false;
	}

public:
	DbParser(string name) {
		in.open("db.csv", ios::out);
		out.open("err.txt", ios::trunc);
	};

	void trim() {
		string tmp;
		for (int i = 0; i < lines.size(); i++) {
			tmp = "";
			for (int j = 0; j < lines[i].size(); j++) {
				if (lines[i][j] != ' ') {
					tmp = tmp + lines[i][j];
				}
			}
			lines[i] = tmp;
		}
	}

	vector<string> findTripDest(string from, string to) {
		vector<string> data;
		vector<string> res;
		for (int i = 0; i < lines.size(); i++) {
			data = splitLine(i);
			if (from == data[0] && to == data[1]) {
				res.push_back(
					data[0] + " " + data[1] + " " + data[2] + " " + data[3] + " " + data[4]);
			}
		}
		return res;
	}

    vector<string> findTripDate(string day) {
		vector<string> data;
		vector<string> res;
		for (int i = 0; i < lines.size(); i++) {
			data = splitLine(i);
			if (data[2] == day) {
				res.push_back( data[0] + " " + data[1] + " " + data[2] + " " + data[3] + " " + data[4]);
			}
		}
		return res;
	}

	void checkLines() {
		vector<string> tmp;
		vector<int> toErase;
		for (int i = 0; i < lines.size(); i++) {
			tmp = splitLine(i);
			if (tmp.size() != 5) {
				out << lines[i] << endl;
				toErase.push_back(i);
			} else {
				if (isBadCity(tmp[0]) || isBadCity(tmp[1]) ||
					isBadCity(tmp[2]) || isBadDigits(tmp[3]) ||
					isBadDigits(tmp[4])) {
					out << lines[i] << endl;
					toErase.push_back(i);
				} 
			}
		}
		for (int i = 0; i < toErase.size(); i++) {
			lines.erase(lines.begin() + (toErase[i] - i));
		}
		out.close();
	}

	void read() {
		string line;
		int x;
		if (in.is_open()) {
			while (getline(in, line)) {
				if (line != "")
					lines.push_back(line);
			}
		}
		in.close();
	}

	void print(int file) {
		if (file == 0) {
			// print db csv formatted
			for (vector<string>::iterator it = lines.begin(); it != lines.end();++it)
				cout << *it << endl;
		} else if (file == 1) {
			// print error.txt
			string line;
			in.open("err.txt", ios::out);
			while (getline(in, line)) {
				cout << line << endl;
			}
		}
	}

	virtual ~DbParser() {
		in.close();
		out.close();
	}
};

int main() {
	// TODO make parser.lines dynamically resized arrray;
	string line, line1;
	vector<string> trips;
	DbParser parser("db.csv");

	char ch;
	parser.read();
	parser.trim();
	parser.checkLines();
    parser.print(0);
	while (true) {
		cin>>ch;
		switch (ch) {
		case 'a':
			cin>>line;
            cin>>line1;
            cout<<"result:"<<endl;
			trips = parser.findTripDest(line, line1);
			for (int i = 0; i < trips.size(); i++) {
				cout << trips[i] <<endl;
			}
			break;
		case 'b':
        	cin>>line;
			trips = parser.findTripDate(line);
            cout<<"result:"<<endl;
			for (int i = 0; i < trips.size(); i++) {
				cout << trips[i] <<endl;
			}
			break;
		case 'c':
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
	cout << endl;
	return 0;
}
