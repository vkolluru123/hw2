#include "movie.h"
#include <iostream>

using namespace std;

// constructor
Movie::Movie(const string category, const string name, double price, int qty, const string& genre, const string& rating)
    : Product(category, name, price, qty), genre_(genre), rating_(rating) {}

// destructor
Movie::~Movie() {}

// functions

set<string> Movie::keywords() const {
  // create vector to hold keywords
  set<string> myKeywords;
  // use parse string to words on each string
  string myName = getName();
  set<string> mymyName = parseStringToWords(myName);
  myKeywords.insert(mymyName.begin(),mymyName.end());
  set<string> myGenre = parseStringToWords(genre_);
  myKeywords.insert(myGenre.begin(),myGenre.end());
  set<string> myRating = parseStringToWords(rating_);
  myKeywords.insert(myRating.begin(),myRating.end());
  // return vector
  return myKeywords;
}

string Movie::displayString() const {
  // create string via concatenation
  string myStr = "";
  myStr += getName();
  myStr += "\n";
  myStr += "Genre: ";
  myStr += genre_;
  myStr += " Rating: ";
  myStr += rating_;
  myStr += "\n";
  myStr += (to_string(getPrice())).erase(to_string(getPrice()).length()-4);
  myStr += " ";
  myStr += to_string(getQty());
  myStr += " left.";
  // return string
  return myStr;
}

void Movie::dump(ostream&os) const {
  os << getCategory() << endl;
  os << getName() << endl;
  os << (to_string(getPrice())).erase(to_string(getPrice()).length()-4) << endl;
  os << to_string(getQty()) << endl;
  os << genre_ << endl;
  os << rating_ << endl;
}