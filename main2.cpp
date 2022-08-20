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


//---------------------------------


void split(std::string text, std::unordered_map<std::string, int> &m )
{
	//std::vector<std::string> words;
	// ---------- // func inline
	std::string delimiters = " \n,.";

	std::string::size_type sz = 0, sz_2;

	while ( (sz_2 = text.find_first_of(delimiters, sz)) != std::string::npos )
	{
		std::string word = text.substr(sz, sz_2-sz);

		sz = sz_2+1;

		if (word != "")
		{
			//words.push_back(word); // std::move(word) ??

			//std::cout << word << std::endl;

			// m ...
			m[word]++;
			
		}
	} 
	// ----------
	return ;
}


int main()
{



    // read entire file into string
    





	uint64_t countThem_i = 0;
	uint64_t textToWords_i = 0; 
	uint64_t end_i = 0;
	std::chrono::time_point<std::chrono::system_clock> start_0, start, textToWords, countThem, end;
	int n = 500;

	start_0 = std::chrono::system_clock::now();

for (int i = 0; i < n; ++i)
{


	std::unordered_map<std::string, int> m;

	start = std::chrono::system_clock::now();

	// Считывай блоками через read и парсь на слова вручную) // это быстрее ?

	//std::ifstream in("./data/28885.txt");
	std::ifstream in{"./data/28885.txt", std::ios::binary | std::ios::ate}; // if(  )

	//std::string word;



	std::size_t size = 512;
	std::string buf(size, '\0'); // construct string to stream size
	in.seekg(0);



	//while (in >> word) // ".the"
	while ( in.read(&buf[0], size) )
	{

		split(buf, m);
		//std::cout << buf << "^" << std::endl;
		//wordlist.push_back(std::move(s));
		//s.clear();

		//m[word]++;
	}



	textToWords = std::chrono::system_clock::now();
	textToWords_i += std::chrono::duration_cast<std::chrono::milliseconds>( textToWords - start ).count();



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

		std::cout << vk.first << " " << vk.second << std::endl;
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
