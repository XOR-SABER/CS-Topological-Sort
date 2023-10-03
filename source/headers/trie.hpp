#ifndef _ALEX_TRIE_HPP
#define _ALEX_TRIE_HPP

#include <unordered_map>
#include <iostream>
#include <vector>
#include <memory>
#include <set>
#include <map>

struct TrieNode{
    std::unordered_map<char, std::shared_ptr<TrieNode>> NodeMap;
    bool isEnd = false; 
    std::string cid; 
    ~TrieNode() {
        NodeMap.clear();
    }
};


// This is really for searching through strings.. 
class Trie {
protected: 
    std::shared_ptr<TrieNode> rootptr;
    // Private traversal function..
    TrieNode *traverse(const std::string&);
    // Private Recursive function for collecting suggestions..
    virtual void collectSuggestions(TrieNode*, const std::string&, std::set<std::string>&);
public: 
    Trie();
    // I always add a intializer list constructor., 
    Trie(const std::initializer_list<std::string>&);
    ~Trie();
    inline bool empty() const;
    virtual bool insert(const std::string&);
    // If the prefix is in the trie 
    bool prefix_search(const std::string&);
    // If the word is in the trie (Whole word)
    bool word_search(const std::string&);
    //Returns a list of suggested strings from the trie
    std::set<std::string> suggestions(const std::string&);
    //Collect 6 suggestions or if the prefix is empty return the vector.. 
    std::set<std::string> auto_correct(std::string);
    // Just prints out the fucking trie
    friend std::ostream &operator<<(std::ostream&, const Trie&);
};

class Title_Trie : public Trie {
protected:
    virtual void collectSuggestions(TrieNode*, const std::string&, std::map<std::string, std::string>&);
public:
    //Returns a list of suggested strings from the trie
    virtual std::map<std::string, std::string> suggestions(const std::string &);
    //Collect 6 suggestions or if the prefix is empty return the vector.. 
    virtual std::map<std::string, std::string> auto_correct(std::string);
    virtual bool insert(const std::string&, const std::string&);
};

#endif