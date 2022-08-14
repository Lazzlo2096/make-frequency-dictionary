
#include <iostream>
// #include <fstream>
#include <vector>
#include <string>
// #include <time.h>


#include <set>
#include <map>
#include <unordered_map>

// #include <functional>

// multy_set ?

int main()
{
	std::map<std::string, int> m;

	std::string text = "However little known the feelings or views of such a man may be on his\
first entering a neighbourhood, this truth is so well fixed in the minds\
of the surrounding families, that he is considered the rightful property\
of some one or other of their daughters.";


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



			// ----------
			if ( m.contains(word) ) // ??
				m[word]++;
			else
				m[word] = 1;
			// ----------

			std::cout << word << " - " << m[word] << std::endl;
		}
	} 
	// ----------


	// https://stackoverflow.com/a/55401806
	typedef std::pair<int, std::string> PAIR;
	std::set<PAIR, std::greater<PAIR> > s;  // The new (temporary) container.

	for (auto const &kv : m)
		s.emplace(kv.second, kv.first); // Flip the pairs.

	for (auto const &vk : s)
		std::cout << vk.first << " " << vk.second << std::endl;


	return 0;
}
