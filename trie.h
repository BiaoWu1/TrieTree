#pragma once
#ifndef TRIE_H
#define TRIE_H
#include<iostream>
#include<unordered_map>
#include<string>
#include<vector>
#include<locale.h>
#include<tchar.h>
#include<fstream>
#include <codecvt>
using std::wstring;
//Trie tree
class TrieNode {
public:
	std::unordered_map<std::wstring, TrieNode*> trie_map;
	bool isEnd;
};

class TrieTree {
	//static const wstring split_symbols = L"：`∀´(*ㅂ)و๑ㅂ́✧（）@°∀°ﾉ-🙏。？…！；•，·•?!.:;,<>___《》'~`\\、/〈〉‹›﹛﹜『』～﹏﹏〖〗［］《》〔〕{}「」【】‘’“”〝〞ˆˇ";
private:
	TrieNode* root;
public:
	TrieTree();
	~TrieTree() {};
	bool isEnd(TrieNode *Node)const;
	void construct_TrieTree(/*const char* filename*/std::string &filename);
	void construct_TrieTree(const wstring &word);                  //insert a word to TrieTree
	void construct_TrieTree(std::vector<wstring> &word);          //insert a group of words
	void split_word(const wstring& word, std::vector<wstring>& character);    //depart a word to characters
	TrieNode* get_root() {
		return root;
	}
	TrieNode* search(const TrieNode* befor, const wstring& character, bool& isend, bool& isfind)const;                   //find a character return next TrieNode
	std::vector<wstring> SegmentSentence(const wstring& sentence);                    //seg a sentence
};

//const wstring TrieTree::split_symbols;

#endif // !TIRE_H