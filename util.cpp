#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  // create a set of keywords
  set<string> keywords;
  // variable to track current word
  string myWord = "";

  // remove all outer spaces
  trim(rawWords);
  // make every letter lowercase
  rawWords = convToLower(rawWords);

  // iterate through all characters
  for (unsigned int i = 0; i < rawWords.size(); i++) {

    // add to current word if it's a letter
    if (isalpha(rawWords[i])) {
      myWord += rawWords[i];
    }

    // if it's a number, add the whole sequence to keywords
    else if (isdigit(rawWords[i]) || rawWords[i] == '-') {
      myWord += rawWords[i];
    }

    // if not a letter or number, check if word is 2 chars long
    else {
      if (!myWord.empty()) {
        // if 2 chars long or more, add current word to keywords set
        if (myWord.size() >= 2) {
          keywords.insert(myWord);
        }
        // current word becomes empty string
        myWord = "";
      }
    }
  }

  // add last current word to keywords if it's longer or equal to 2 chars
  if (myWord.size() >= 2 && !myWord.empty()) {
    keywords.insert(myWord);
  }
  
  // return keywords set
  return keywords;

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
