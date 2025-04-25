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
void wordleHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, set<string>& result, int curr);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    set<string> result;
    int curr;

    wordleHelper(in, floating, dict, result, 0);

    return result;
}

// Define any helper functions here
void wordleHelper(const std::string& in, const std::string& floating, const std::set<std::string>& dict, set<string>& result, int curr) {
    
    // if size of floating string is larger than # of unassigned slots, return since not possible
    int count = 0;
    for (int i = 0; i < in.size(); i++) {
        if (in[i] == '-') {
            count++;
        }
    }
    if (floating.size() > count) {
        return;
    }

    // check if curr is at last index
    if (curr == in.size()) {
        // if current string is filled && string is in dictionary && all the floating chars are used
        if (in.find("-") == string::npos && dict.find(in) != dict.end() && floating.size() == 0) {
            result.insert(in);
        }
        return;
    }
    
    // if it IS a dash -> iterate through possiblilities
    if (in[curr] == '-') {

        // first try all letters in floating string
        for (int i = 0; i < floating.size(); i++) {

            string new_in = in;
            new_in[curr] = floating[i];

            // avoid using floating char's twice -> erase current used floating
            string new_floating = floating;
            new_floating.erase(i, 1);
            wordleHelper(new_in, new_floating, dict, result, curr + 1);
        }


        // try all non floating characters
        for (int i = 0; i < 26; i++) {
            char temp = 'a' + i;
            // Not in floating -> if in floating, would be used next time, dont use it here
            if (floating.find(temp) == string::npos) {
                // add temp to curr location
                string new_in = in;
                new_in[curr] = temp;
                wordleHelper(new_in, floating, dict, result, curr + 1);
            }
        }

    } else {
        // move on to next index since current has letter
        wordleHelper(in, floating, dict, result, curr + 1);
    }
}