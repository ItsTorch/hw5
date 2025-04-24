#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
// recursive helper function
void createWords(
    std::string current,
    const std::string& floating,
    const std::set<std::string>& dict,
    std::set<std::string>& results,
    unsigned int idx)
{
    // base case - all spots filled
    if (idx == current.size()) {
        if (floating.empty() && dict.find(current) != dict.end()) {
            results.insert(current);
        }
        return;
    }

    // recursive call, if at fixed character, move to next character
    if (current[idx] != '-') {
        createWords(current, floating, dict, results, idx + 1);
        return;
    }

    // counts how many '-' remain from current index
    int blanks_left = 0;
    for (unsigned int i = idx; i < current.size(); ++i) {
        if (current[i] == '-') ++blanks_left;
    }

    // prevents placing floating letters if there's not enough empty space
    if (blanks_left < (int)floating.size()) return;

    // prevent duplicate words being outputted
    std::set<char> tried;
    
    // place floating letters in blank spots first
    if (blanks_left == (int)floating.size()) {
        for (size_t i = 0; i < floating.size(); ++i) {
            char c = floating[i];
            if (tried.count(c)) continue;
            tried.insert(c);

            std::string next = current;
            next[idx] = c;

            std::string newFloating = floating;
            newFloating.erase(newFloating.begin() + i);

            createWords(next, newFloating, dict, results, idx + 1);
        }
    }
    // run through all letters to fill in remaining blank spots
    else {
        for (char c = 'a' ; c <= 'z'; ++c) {
            std::string next = current;
            next[idx] = c;

            std::string newFloating = floating;
            size_t pos = floating.find(c);
            if (pos != std::string::npos) {
                newFloating.erase(pos, 1);
            }
            createWords(next, newFloating, dict, results, idx + 1);
        }
    }
}

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> results;
    createWords(in, floating, dict, results, 0);
    return results;
}

// Define any helper functions here
