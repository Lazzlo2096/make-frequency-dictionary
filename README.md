# make-frequency-dictionary

Есть 4-ре этапа:
1) Чтение текста из файла
2) Разбивка текста на массив слов (split)
3) Подсчет и вставка слов в ассоц. массив (std::map<key, value>) (key = слово ; value = чатотность)
4) Сортировка по value (по кол-ву слов в тексте).


------

При реализации в c++, 1ый и 2ой этапы можно объеденить:


``` c++
std::vector<std::string> getWordList(const char* filename)
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
```
