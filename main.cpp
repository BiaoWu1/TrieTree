#include"trie.h"
using namespace std;
int main()
{
	TrieTree dict;

	//construct trieTree
	long start1 = clock();
	string filename = "dict.txt";
	dict.construct_TrieTree(filename);
	long finish1 = clock();
	cout << "the time of constructing tire is " << (finish1 - start1)*1.0 / CLOCKS_PER_SEC  << "s" << endl;


	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;



	ifstream file("test_pure_text.txt", ios::in);
	ofstream file_write("test_pure_text_result.txt", ios::app);
	int count_word = 0;
	int count_sentence = 0;
	long time = 0;

	long start = clock();
	if (file)
	{
		string line;
		while (getline(file, line))
		{
			
			//convert string to wstring
			wstring lines = conv.from_bytes(line);
			count_word += lines.size();
			vector<wstring> result = dict.SegmentSentence(lines);

			//write to file
			for (auto i : result)
			{
				file_write << conv.to_bytes(i);
			}
			file_write << endl;
			count_sentence++;
		}
	}
	long finish = clock();
	time = finish - start;

	cout << "total counts of characters is " << count_word << endl;
	cout << "The average length of sentence is " << count_word*1.0 / count_sentence << " characters"<< endl;
	cout << "Average segmentation of sentence is " << time*1.0 / count_sentence << " ms" << endl;
	cout << "the count of sentence is " << count_sentence << endl;
	cout << "total segmentation time is " << time / CLOCKS_PER_SEC << "s" << endl;
	file.close();
	file_write.close();
	return 0;
} 