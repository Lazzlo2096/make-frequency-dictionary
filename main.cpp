// g++ ./main.cpp -std=c++2a

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
// #include <time.h>

#include <set>
#include <map>
#include <unordered_map>

// multy_set ?


//---------------------------------
// https://github.com/Lazzlo2096/Zeitgeist/blob/master/utilities.cpp
/*double getTimeInMillis()
{
	clock_t now = clock();
	return 1000.0*now / CLOCKS_PER_SEC;
}*/

inline std::vector<std::string> getWordList(const char* filename)
{
	//First, read in the file
	// I'm not doing much error checking here, because I am a bad person
	std::ifstream in(filename);
	std::string s;
	std::vector<std::string> wordlist;
	while (in >> s)
	{
		wordlist.push_back(std::move(s));
		//s.clear();

		// Если будет некорректно? работать, то можно сделать s.clear() после мува, чтобы вернуть строку в детерменированное состояние
		// Просто после перемещения строка будет в хз каком виде, и я не знаю, как operator>> это обработает и обработает ли
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

	uint64_t countThem_i = 0;
	uint64_t textToWords_i = 0; 
	uint64_t end_i = 0;
	std::chrono::time_point<std::chrono::system_clock> start_0, start, textToWords, countThem, end;
	int n = 500;

	start_0 = std::chrono::system_clock::now();

for (int i = 0; i < n; ++i)
{


	std::map<std::string, int> m;

/*
	std::string text = "However little known the feelings or views of such a man may be on his\
first entering a neighbourhood, this truth is so well fixed in the minds\
of the surrounding families, that he is considered the rightful property\
of some one or other of their daughters.";
*/
	///double start = getTimeInMillis();
	
	start = std::chrono::system_clock::now();

	//std::vector<std::string> words = split(text);
	std::vector<std::string> words = getWordList("./data/28885.txt");

	// ----------

	//double textToWords = getTimeInMillis();
	textToWords = std::chrono::system_clock::now();
	textToWords_i += std::chrono::duration_cast<std::chrono::milliseconds>( textToWords - start ).count();

	// ----------
	for (const auto &word : words)
	{
		//if ( m.contains(word) ) //[[likely]]
			m[word]++;
		//else
		//	m[word] = 1;

		//std::cout << word << " - " << m[word] << std::endl;
	}
	// ----------

	//double countThem = getTimeInMillis();
	countThem = std::chrono::system_clock::now();
	countThem_i += std::chrono::duration_cast<std::chrono::milliseconds>( countThem - textToWords ).count();


	// ---------- sort by value
	// https://stackoverflow.com/a/55401806
	typedef std::pair<int, std::string> PAIR;
	std::set<PAIR, std::greater<PAIR> > s;  // The new (temporary) container.

	for (auto &kv : m)
		s.emplace(std::move(kv.second), std::move(kv.first)); // Flip the pairs.


	/*
	int n = 10;
	for (auto const &vk : s)
	{
		if (n==0)
			break;
		else
			n--;

		//std::cout << vk.first << " " << vk.second << std::endl;
	}
	*/

	// ----------

	//double end = getTimeInMillis();
	end = std::chrono::system_clock::now();
	end_i += std::chrono::duration_cast<std::chrono::milliseconds>( end - countThem ).count();

}

	//=====================

	//std::cout << "start: " << start << std::endl;
	//std::cout << "textToWords: " << textToWords << " [" <<  (textToWords-start) << "] " << std::endl;
	//std::cout << "countThem: " << countThem << " [" <<  (countThem-textToWords) << "] " << std::endl;
	//std::cout << "end(sortThem): " << end << " [" <<  (end-countThem) << "] " << std::endl;


	//const auto textToWords_time = std::chrono::duration_cast<std::chrono::milliseconds>(textToWords - start).count();
	//const auto countThem_time   = std::chrono::duration_cast<std::chrono::milliseconds>(countThem - textToWords).count();
	//const auto end_el  = std::chrono::duration_cast<std::chrono::milliseconds>(end - countThem).count();

	const auto prog_el  =  std::chrono::duration_cast<std::chrono::seconds>(end - start_0 ).count();

	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	std::cout << "finished computation at " << std::ctime(&end_time)
			  << "elapsed time: " << prog_el << "s\n";



	long int average_countThem = countThem_i / n;
	long int average_textToWords = textToWords_i / n;
	long int average_end = end_i / n;

	//std::cout << "start: " << start << std::endl;
	std::cout << "textToWords: \t" << " [" <<  average_textToWords << "] " << std::endl;
	std::cout << "countThem: \t" << " [" <<  average_countThem << "] " << std::endl;
	std::cout << "end(sortThem): \t" << " [" <<  average_end << "] " << std::endl;



	
	
	return 0;
}
