
#include <vector>
#include <iomanip> 
#include <random>
#include <sstream>
#include <string>
#include <conio.h>
#include <iostream>

using namespace std;

vector<int> suffixes(const string& pattern) {
	int length = pattern.length();
	vector<int> suffix(length, 0);

	int g, f;
	g = f = length - 1;
	for (int i = length - 2; i >= 0; --i) {
		if (i > g && suffix[i + length - 1 - f] < i - g) {
			suffix[i] = suffix[i + length - 1 - f];
		}
		else {
			if (i < g) {
				g = i;
			}
			f = i;
			while (g >= 0 && pattern[g] == pattern[g + length - 1 - f]) {
				--g;
			}
			suffix[i] = f - g;
		}
	}

	return suffix;
}

vector<int> boyerMoore(const string& text, const string& pattern) {
	int n = text.length();
	int m = pattern.length();
	std::vector<int> occurrences;

	std::vector<int> shift(256, m);
	for (int i = 0; i < m - 1; ++i) {
		shift[pattern[i]] = m - i - 1;
	}

	std::vector<int> suffix = suffixes(pattern);

	int i = 0;
	while (i <= n - m) {
		int j = m - 1;
		while (j >= 0 && pattern[j] == text[i + j]) {
			--j;
		}
		if (j < 0) {
			occurrences.push_back(i);
			i += shift[text[i + m]];
		}
		else {
			int x = suffix[j];
			int y = j - x;
			int z = m - 1 - j;
			i += max(shift[text[i + j]] - y, z);
		}
	}

	return occurrences;
}


string cleanString(const string& input) {
	setlocale(0, "");
	string result;
	bool lastWasSpace = false;
	bool lastWasPunctuation = false;

	for (size_t i = 0; i < input.size(); ++i) {
		char ch = input[i];

		if (ch == ' ') {
			if (!lastWasSpace) {
				result += ch;
				lastWasSpace = true;
			}
		}
		else if (ch == '.' || ch == ',' || ch == ';' || ch == ':') {
			if (!lastWasPunctuation) {
				result += ch;
				lastWasPunctuation = true;
			}
		}
		else {
			result += ch;
			lastWasSpace = false;
			lastWasPunctuation = false;
		}
	}

	return result;
}

bool containsDigit(const string& word) {
	for (char c : word) {
		if (isdigit(c)) {
			return true;
		}
	}
	return false;
}

vector<size_t> findSubstring(const string& text, const string& substring) {
	vector<size_t> positions;
	size_t pos = text.find(substring, 0);

	while (pos != string::npos) {
		positions.push_back(pos);
		pos = text.find(substring, pos + 1);
	}

	return positions;
}





int main()
{
	bool tr = true;
	while (tr) {
		system("cls");
		setlocale(LC_ALL, "ru-RU");
		cout << "Введите слова: ";
		string inpute;
		getline(cin >> ws, inpute);
		string input = cleanString(inpute);
		inpute = cleanString(inpute);
		istringstream ss(input);
		string word;

		cout << "\nСлова без цифр: ";
		while (ss >> word) {
			if (!containsDigit(word)) {
				cout << word << " ";
			}
		}
		cout << endl;
		string substring;
		cout << "Подстрока для поиска: ";
		cin >> substring;

		vector<size_t> positions = findSubstring(input, substring);

		if (positions.empty()) {
			cout << "Не найдено." << endl;
		}
		else {
			cout << "Подстрока найдена на позиции: ";
			for (size_t pos : positions) {
				cout << pos << " ";
			}
			cout << endl;
		}


		cout << "Подстрока для поиска методом Бойера-Мура: ";
		string substring2;
		cin >> substring2;
		vector<int> vec = boyerMoore(input, substring2);

		if (!vec.empty()) {
			cout << "Pattern found at positions: ";
			for (int i = 0; i < vec.size(); ++i) {
				std::cout << vec[i] << " ";
			}
		}
		else {
			std::cout << "Pattern not found.";
		}

		cout << "\nВывод строки вертикально: " << endl;
		for (int i = 0; i < inpute.length(); i++)
			cout << inpute[i] << endl;

		cout << "\n\nНажмите 'x', чтобы завершить программу или любую другую кнопку, чтобы продолжить...\n";
		while (true) {
			if (_kbhit()) {
				char ch = _getch();
				if (ch == 'x' || ch == 'X') {
					tr = false;
					break;
				}
				else
					break;
			}
		}
	}
}