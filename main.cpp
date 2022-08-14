
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
// #include <time.h>

#include <set>
#include <map>
#include <unordered_map>

// multy_set ?


//---------------------------------
// https://github.com/Lazzlo2096/Zeitgeist/blob/master/utilities.cpp
double getTimeInMillis()
{
	clock_t now = clock();
	return 1000.0*now / CLOCKS_PER_SEC;
}

std::vector<std::string> getWordList(const char* filename)
{
	//First, read in the file
	// I'm not doing much error checking here, because I am a bad person
	std::ifstream in(filename);
	std::string s;
	std::vector<std::string> wordlist;
	while (in >> s){
		wordlist.push_back(s);
	}

	return wordlist;
}
//---------------------------------


std::vector<std::string> split(std::string text)
{
	std::vector<std::string> words;
	// ---------- // func inline
	std::string delimiters = " \n,.";

	std::string::size_type sz = 0, sz_2;

	while ( (sz_2 = text.find_first_of(delimiters, sz)) != std::string::npos )
	{
		std::string word = text.substr(sz, sz_2-sz);

		sz = sz_2+1;

		if (word != "")
		{
			words.push_back(word); // std::move(word) ??

			//std::cout << word << std::endl;

			// m ...
			
		}
	} 
	// ----------
	return words;
}


int main()
{
	std::map<std::string, int> m;

/*
	std::string text = "However little known the feelings or views of such a man may be on his\
first entering a neighbourhood, this truth is so well fixed in the minds\
of the surrounding families, that he is considered the rightful property\
of some one or other of their daughters.";
*/
	double start = getTimeInMillis();

	//std::vector<std::string> words = split(text);
	std::vector<std::string> words = getWordList("./data/28885.txt");

	// ----------

	double textToWords = getTimeInMillis();

	// ----------
	for (auto word : words)
	{
		if ( m.contains(word) ) // ?? only m[word]++ ?
			m[word]++;
		else
			m[word] = 1;

		// std::cout << word << " - " << m[word] << std::endl;
	}
	// ----------

	double countThem = getTimeInMillis();

	// ---------- sort by value
	// https://stackoverflow.com/a/55401806
	typedef std::pair<int, std::string> PAIR;
	std::set<PAIR, std::greater<PAIR> > s;  // The new (temporary) container.

	for (auto const &kv : m)
		s.emplace(kv.second, kv.first); // Flip the pairs.


	int n = 10;
	for (auto const &vk : s)
	{
		if (n==0)
			break;
		else
			n--;

		//std::cout << vk.first << " " << vk.second << std::endl;
	}
	// ----------

	double end = getTimeInMillis();

	//=====================

	std::cout << "start: " << start << std::endl;
	std::cout << "textToWords: " << textToWords << " [" <<  (textToWords-start) << "] " << std::endl;
	std::cout << "countThem: " << countThem << " [" <<  (countThem-textToWords) << "] " << std::endl;
	std::cout << "end(sortThem): " << end << " [" <<  (end-countThem) << "] " << std::endl;

	
	return 0;
}
