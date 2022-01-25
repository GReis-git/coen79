#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

void program1() {

	string text;

	// input string into text
	cout << "Please Type Something: ";
	getline(cin, text);

	// count number of alphanumerics in string
	int alphanumeric = 0;
	int whitespace = 0;
	for (int i = 0; i < text.length(); i++) {
		if (isalnum(text.at(i))) alphanumeric++;
		else if (std::isspace(text.at(i))) whitespace++;
		else;
	}

	cout << "\n" << text << " has " << alphanumeric << " characters and " << text.length() - alphanumeric - whitespace << " non-alphanumeric characters\n";
}


void program2() {

	string text;
	string returnText = "";

	cout << "Please type a string of 10 digits (0 to 9) with no space: ";
	cin >> text;


	// inverse text into returnText string
	for (int i = text.length()-1; i >= 0; i--) {
		returnText.append(text.substr(i,1));
	}


	// print each with indentation as specified in lab doc
	for(int i = 0; i < 5; i++) {
		cout << std::setw(10+i) << text << "     " << returnText << "\n";
	}

	// previous code without setw()
	//cout << "\n" << text << "\t" << returnText;
	//cout << "\n " << text << "\t " << returnText;
	//cout << "\n  " << text << "\t  " << returnText;
	//cout << "\n   " << text << "\t   " << returnText;
	//cout << "\n    " << text << "\t    " << returnText;
}

void program3() {
	int MAXWORDS = 255; // maximum number of words in file
	
	string words[MAXWORDS]; 
	int i;
	string check;

	// read file into string array words
	ifstream file("file.txt");
	while (file) {
		file >> check;
		words[i] = check;
		i++;
	}
	file.close();


	// remove all non alphabetical characters from the array of strings
	for (int i = 0; i < MAXWORDS; i++) {
		for (int j = 0; j < words[i].length(); j++) {
			if (!isalpha(words[i].at(j))) {
				words[i].erase(j, 1);
				j--;
			}
		}
	}

	string returnWords[MAXWORDS];
	int iterator = 0;
	// isolate all words with length >= 10 to a new string array
	for (int i = 0; i < MAXWORDS; i++) {
		if (words[i].length() >= 10) {
			returnWords[iterator] = words[i];
			iterator++;
		}
	}
	// change every string to full caps
	for (int i = 0; i < iterator; i++) {
		std::transform(returnWords[i].begin(), returnWords[i].end(), returnWords[i].begin(), ::toupper);
		cout << "\n" << (returnWords[i]);
	}
}

// helper function for program4
bool yesOrNo() {
	string response;
	cin >> response;
	if (response == "Y" || response == "yes") return true;
	else if (response == "N" || response == "no") return false;
	else {
		cout << "Please respond with Y or N to indicate Yes or No \n";
		yesOrNo();
	}
}

void program4() {
	bool result;
	int steps = 0;
	int num;

	// this is some of the worst spaghetti i've ever written, but due to time and lack of specification on lab doc... it is what it is
	// it asks > or < 10, then > or < 5/15, then individual numbers.

	cout << "\n\nThink of a number between 1 and 20.";
	cout << "\n\nIs your number less than 10? ";
	result = yesOrNo();
	steps++;
	if (result) {
		cout << "\nIs your number less than 5? ";
		result = yesOrNo();
		steps++;
		if (result) {
			cout << "\nIs your number 1? ";
			result = yesOrNo();
			steps++;
			num = 1;
			if (!result) {
				cout << "\nIs your number 2? ";
				result = yesOrNo();
				steps++;
				num = 2;
				if (!result) {
					cout << "\nIs your number 3? ";
					result = yesOrNo();
					steps++;
					num = 3;
					if (!result) {
						cout << "\nIs your number 4? ";
						result = yesOrNo();
						steps++;
						num = 4;
					}
				}
			}
		}
		else {
			cout << "\nIs your number 5? ";
			result = yesOrNo();
			steps++;
			num = 5;
			if (!result) {
				cout << "\nIs your number 6? ";
				result = yesOrNo();
				steps++;
				num = 6;
				if (!result) {
					cout << "\nIs your number 7? ";
					result = yesOrNo();
					steps++;
					num = 7;
					if (!result) {
						cout << "\nIs your number 8? ";
						result = yesOrNo();
						steps++;
						num = 8;
						if (!result) {
							cout << "\nIs your number 9? ";
							result = yesOrNo();
							steps++;
							num = 9;
						}
					}
				}
			}
		}
	}
	else {
		cout << "\nIs your number less than 15? ";
		result = yesOrNo();
		steps++;
		if (result) {
			cout << "\nIs your number 11? ";
			result = yesOrNo();
			steps++;
			num = 11;
			if (!result) {
				cout << "\nIs your number 12? ";
				result = yesOrNo();
				steps++;
				num = 12;
				if (!result) {
					cout << "\nIs your number 13? ";
					result = yesOrNo();
					steps++;
					num = 13;
					if (!result) {
						cout << "\nIs your number 14? ";
						result = yesOrNo();
						steps++;
						num = 14;
					}
				}
			}
		}
		else {
			cout << "\nIs your number 15? ";
			result = yesOrNo();
			steps++;
			num = 15;
			if (!result) {
				cout << "\nIs your number 16? ";
				result = yesOrNo();
				steps++;
				num = 16;
				if (!result) {
					cout << "\nIs your number 17? ";
					result = yesOrNo();
					steps++;
					num = 17;
					if (!result) {
						cout << "\nIs your number 18? ";
						result = yesOrNo();
						steps++;
						num = 18;
						if (!result) {
							cout << "\nIs your number 19? ";
							result = yesOrNo();
							steps++;
							num = 19;
							if (!result) {
								cout << "\nIs your number 20? ";
								result = yesOrNo();
								steps++;
								num = 20;
							}
						}
					}
				}
			}
		}
	}
	cout << "Your number was " << num << " and it was guessed in " << steps << " steps";
}

int main() {
	program2();
}