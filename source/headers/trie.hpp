#ifndef _ALEX_TRIE_HPP
#define _ALEX_TRIE_HPP

#include <memory>
#include <vector>
#include <unordered_map>

struct TrieNode{
    std::unordered_map<char, std::shared_ptr<TrieNode>> NodeMap;
    bool isEnd = false; 
    ~TrieNode() {
        NodeMap.clear();
    }
};


// This is really for searching through strings.. 
class Trie {
private: 
    std::shared_ptr<TrieNode> rootptr;
protected: 
    // Private traversal function..
    TrieNode *traverse(const std::string &prefix) { 
        TrieNode* current = rootptr.get();
        for(const char &c : prefix) {
            // if exists
            const char upperChar = std::toupper(c);
            if(current->NodeMap.count(upperChar)) {
                current = current->NodeMap.at(upperChar).get();
            } else return nullptr;
        }
        return current;
    }

    // Private Recursive function for collecting suggestions..
    void collectSuggestions(TrieNode* node, const std::string& prefix, std::vector<std::string>& suggestions) {
        if (node->isEnd) suggestions.push_back(prefix);
        for (const auto& pair : node->NodeMap) 
            collectSuggestions(pair.second.get(), prefix + char(std::tolower(pair.first)), suggestions);
    }

public: 
    Trie() {
        rootptr = std::make_shared<TrieNode>();
    }

    // I always add a intializer list constructor., 
    Trie(const std::initializer_list<std::string> &list) {
        rootptr = std::make_shared<TrieNode>();
        for (const std::string &str : list) insert(str);
    }
    
    ~Trie() { 
        // Deconstructor.. 
        rootptr->NodeMap.clear();
    }

    inline bool empty() const{
        return (rootptr.get()->NodeMap.empty());
    }

    bool insert(const std::string &prefix) {
        // Grab a pointer to the current node!
        TrieNode* current = rootptr.get();
        for(const char &c : prefix) {
            char upperChar = std::toupper(c);
            current->NodeMap.insert({upperChar, std::make_shared<TrieNode>()});
            current = current->NodeMap.at(upperChar).get();
        }
        current->isEnd = true;
        return true; 
    }

    // If the prefix is in the trie 
    bool prefix_search(const std::string &prefix) {
        TrieNode* current = traverse(prefix);
        if(!current) return false;
        else return true;
    }

    // If the word is in the trie (Whole word)
    bool word_search(const std::string &prefix) {
        TrieNode* current = traverse(prefix);
        if(current && current->isEnd) return true;
        else return false;
    }

    //Returns a list of suggested strings from the trie
    std::vector<std::string> suggestions(const std::string &prefix) {
        std::vector<std::string> retval;
        TrieNode* current = traverse(prefix);
        if (current) {
            collectSuggestions(current, prefix, retval);
        }
        return retval;
    }


    // Just prints out the fucking trie
    friend std::ostream &operator<<(std::ostream &outs, const Trie &t) {
        // Okay we got a node to front of the trie
        if (t.rootptr.get()->NodeMap.empty()) return outs;
        std::vector<std::pair<TrieNode*, std::string>> q;
        q.push_back({t.rootptr.get(), ""});    
        while (!q.empty()) {
            auto curr = q.back();
            q.pop_back();
            
            if (curr.first->isEnd) outs << curr.second << std::endl;
            for (const auto& pair : curr.first->NodeMap) {
                q.push_back({pair.second.get(), curr.second + pair.first});
            }
        }
        return outs;
    }
    



};

#endif