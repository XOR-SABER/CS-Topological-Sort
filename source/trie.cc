#include "headers/trie.hpp"

// Private traversal function..
TrieNode* Trie::traverse(const std::string &prefix) { 
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
void Trie::collectSuggestions(TrieNode* node, const std::string& prefix, std::set<std::string>& suggestions) {
    if(suggestions.size() > 6) return;
    if (node->isEnd) suggestions.insert(prefix);
    for (const auto& pair : node->NodeMap) 
        collectSuggestions(pair.second.get(), prefix + char(std::toupper(pair.first)), suggestions);
}
Trie::Trie() {
    rootptr = std::make_shared<TrieNode>();
}

// I always add a intializer list constructor., 
Trie::Trie(const std::initializer_list<std::string> &list) {
    rootptr = std::make_shared<TrieNode>();
    for (const std::string &str : list) insert(str);
}
    
Trie::~Trie() { 
    // Deconstructor.. 
    rootptr->NodeMap.clear();
}

inline bool Trie::empty() const{
    return (rootptr.get()->NodeMap.empty());
}

bool Trie::insert(const std::string &prefix) {
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
bool Trie::prefix_search(const std::string &prefix) {
    TrieNode* current = traverse(prefix);
    if(!current) return false;
    else return true;
}

// If the word is in the trie (Whole word)
bool Trie::word_search(const std::string &prefix) {
    TrieNode* current = traverse(prefix);
    if(current && current->isEnd) return true;
    else return false;
}

//Returns a list of suggested strings from the trie
std::set<std::string> Trie::suggestions(const std::string &prefix) {
    std::set<std::string> retval;
    TrieNode* current = traverse(prefix);
    if (current) collectSuggestions(current, prefix, retval);
    return retval;
}

//Collect 6 suggestions or if the prefix is empty return the vector.. 
std::set<std::string> Trie::auto_correct(std::string prefix) {
    std::set<std::string> retval;
    //Collect 6 suggestions or if the prefix is empty 
    while((retval.size() < 6)) {
        if(prefix.empty()) break;
        TrieNode* current = traverse(prefix);
        if (current) collectSuggestions(current, prefix, retval);
        prefix.pop_back();
    }
    return retval;
}


// Just prints out the fucking trie
std::ostream &operator<<(std::ostream &outs, const Trie &t) {
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

void Title_Trie::collectSuggestions(TrieNode* node, const std::string& prefix, std::map<std::string, std::string>& suggestions) {
    if(suggestions.size() > 6) return;
    if (node->isEnd) suggestions.insert(std::make_pair(prefix, (std::string)node->cid));
    for (const auto& pair : node->NodeMap) 
        collectSuggestions(pair.second.get(), prefix + char(std::toupper(pair.first)), suggestions);
}
//Returns a list of suggested strings from the trie
std::map<std::string, std::string> Title_Trie::suggestions(const std::string &prefix) {
    std::map<std::string, std::string> retval;
    TrieNode* current = traverse(prefix);
    if (current) collectSuggestions(current, prefix, retval);
    return retval;
}
//Collect 6 suggestions or if the prefix is empty return the vector.. 
std::map<std::string, std::string> Title_Trie::auto_correct(std::string prefix) {
    std::map<std::string, std::string> retval;
    //Collect 6 suggestions or if the prefix is empty 
    while((retval.size() < 6)) {
        if(prefix.empty()) break;
        TrieNode* current = traverse(prefix);
        if (current) collectSuggestions(current, prefix, retval);
        prefix.pop_back();
    }
    return retval;
}
bool Title_Trie::insert(const std::string &prefix, const std::string &cid) {
    // Grab a pointer to the current node!
    TrieNode* current = rootptr.get();
    for(const char &c : prefix) {
        char upperChar = std::toupper(c);
        current->NodeMap.insert({upperChar, std::make_shared<TrieNode>()});
        current = current->NodeMap.at(upperChar).get();
    }
    current->isEnd = true;
    current->cid = cid;
    return true; 
}

