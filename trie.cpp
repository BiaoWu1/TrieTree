#include"trie.h"
TrieTree::TrieTree()
{
	root = new TrieNode();
	root->isEnd = false;
}

bool TrieTree::isEnd(TrieNode* Node) const
{
	return Node->isEnd;
}


//read text and construct TrieTree
void TrieTree::construct_TrieTree(/*const char *filename*/std::string &filename)
{
	std::ifstream file_read(filename, std::ios::in);
	if (file_read)
	{
		std::string line;
		std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
		while (getline(file_read, line))
		{
			//get the chinese part
			auto index = line.find("\t");
			line = line.substr(0, index);

			//construct trieTree
			wstring Chinese = conv.from_bytes(line);
			construct_TrieTree(Chinese); 
		}
	} 
	file_read.close();
}

//insert a word
void TrieTree::construct_TrieTree(const wstring& word)
{
	auto length = word.size();
	if (length == 0)
		return;
	auto temp_root = root;


	//construct tire Tree
	for (decltype(word.size()) sz = 0; sz != length; sz++)
	{

		//attention£º*iter type is  wchar_t
		//convert it to wstring
		wstring convert = L"×ª";
		convert[0] = word[sz];

		//find whether has the fist character
		auto word_iter = temp_root->trie_map.find(convert);
		
		//not find, put it to root
		if (word_iter == temp_root->trie_map.end())
		{
			std::pair<wstring, TrieNode*> temp;
			temp.first = convert;
			TrieNode* next = new TrieNode();
			temp.second = next;
			temp_root->trie_map.insert(temp);

			//mark whether character is the final of word
			if (sz == length - 1)
				temp_root->isEnd = true;
			temp_root = next;
		}
		else {   //when found
			if (sz == length - 1)
				temp_root->isEnd = true;
			temp_root = (*word_iter).second;
		}
	}
}

//insert a group of words to TrieTree
void TrieTree::construct_TrieTree(std::vector<wstring>& word)
{
	auto length = word.size();
	if (length == 0)
		return;
	for (const auto& elem : word)
	{
		construct_TrieTree(elem);
	}

}

//seg word to characters
void TrieTree::split_word(const wstring& word, std::vector<wstring>& character)
{
	auto length = word.size();
	if (length == 0)
		return;

	//wchar_t convert to  wstring
	for (decltype(word.size()) sz = 0; sz != length; sz++)
	{
		wstring temp = L"¿Õ";
		temp[0] = word[sz];
		character.push_back(temp);
	}
}

//find if the character is in dict
TrieNode* TrieTree::search(const TrieNode* befor, const wstring& character, bool& isend, bool &isfind) const
{
	const TrieNode* temp_root = befor;
	auto iter = temp_root->trie_map.find(character);
	if (iter != temp_root->trie_map.end())
	{
		isend = temp_root->isEnd;
		isfind = true;
		return (*iter).second;
	}
	else
		isfind = false;
	return NULL;
}

std::vector<wstring> TrieTree::SegmentSentence(const wstring& sentence)
{
	//get every word of sentence, including punctuations
	std::vector<wstring> character;         
	split_word(sentence, character);

	//store word segmentation result
	std::vector<wstring> result;
	auto length = character.size();
	decltype(length) count = 0;

	while (count != length)
	{
		bool isend = false;
		bool isfind = false;
		auto node = search(get_root(), character[count], isend, isfind);

		//if isfind is false£¬character[count] is not in dict, insert to result.
		if (isfind == false)
		{
			result.push_back(character[count]);
			result.push_back(L" ");
			count++;
		}
		else          //look up based on the curr character
		{
			wstring word = character[count];
			count++;
			bool judge = false;
			while (isfind == true && count != length)
			{
				node = search(node, character[count], isend, isfind);
				if (isfind == false || count == length)
				{
					judge = true;
					result.push_back(word);
					result.push_back(L" ");
					break;
				}
				word += character[count];
				count++;
			}
			if (judge == false && (isfind == false || count == length))
			{
				result.push_back(word);
				result.push_back(L" ");
			}
		}
	}
	return result;
}
