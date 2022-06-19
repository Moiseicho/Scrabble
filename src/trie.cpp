#include "trie.hpp"
#include <iostream>
#include <exception>

Trie::Trie() 
: isEnd(false)
{}

Trie::~Trie() {
    for(auto i: this->characters) {
        delete i.second;
    }
}

bool Trie::checkString(const std::string& word) {
    for(auto i: word) {
        if(isupper(i) && i != word[0]) return false;
        if(!isalpha(i)) return false;
    }
    return true;
}

bool Trie::insert(const std::string& word) {
    Trie *tmp = this;
    const uint length = word.length();

    if(!checkString(word)) return false;

    for(int i = 0; i < length; ++i) {
        if(tmp->characters.find(word[i]) == tmp->characters.end()) {
            tmp->characters[word[i]] = new Trie();
        } 
        
        if(tmp->characters[word[i]] == nullptr) 
        {
            return false;
        }

        tmp = tmp->characters[word[i]];
    }

    if(tmp->isEnd) {
        return false;
    } else {
        tmp->isEnd = true;
    }

    return true;
}

bool Trie::search(const std::string& word) {
    Trie *tmp = this;
    const uint length = word.length();

    for(int i = 0; i < length; ++i) { 
        if(tmp->characters.find(word[i]) == tmp->characters.end() ||
           tmp->characters[word[i]] == nullptr) 
        {
            return false;
        }

        tmp = tmp->characters[word[i]];
    }

    if(tmp->isEnd == false)
        return false;
    
    return true;
}


std::ostream& operator<<(std::ostream& os, const Trie& other) {
    
    return os;
}

bool Trie::hasChildren() {
    if(this->characters.empty()) return false;
    return true;
}

bool Trie::_remove(Trie*& node, const std::string& word) {
    if(node == nullptr) return false;

    if(word.length()) {
        if(node->characters.find(word[0]) == node->characters.end())
            throw std::runtime_error("Word is not present in the dictionary!");

        if(_remove(node->characters[word[0]], word.substr(1)) &&
           node->isEnd == false) 
        {   
            this->characters.erase(word[0]);            
            if(!node->hasChildren()) {
                delete node;
                node = nullptr;
                return true;
            }
        } else if(this->characters[word[0]] == nullptr) {
            this->characters.erase(word[0]);
        }
    } else if(!word.length() && node->isEnd) {
        if(!node->hasChildren()) {
            delete node;
            node = nullptr;
            return true;
        }
        node->isEnd = false;
    }

    return false;
}

void Trie::remove(const std::string& word) {
    Trie *tmp = this;
    this->_remove(tmp, word);
}