#include "book.h"
#include <iostream>

using namespace std;

// constructor
Book::Book(const string category, const string name, double price, int qty, const string& isbn, const string& author)
    : Product(category, name, price, qty), isbn_(isbn), author_(author) {}

// destructor
Book::~Book() {}

// functions

set<string> Book::keywords() const {
  // create vector to hold keywords
  set<string> myKeywords;
  // use parse string to words on each string
  string myName = getName();
  set<string> mymyName = parseStringToWords(myName);
  myKeywords.insert(mymyName.begin(),mymyName.end());
  set<string> myAuthor = parseStringToWords(author_);
  myKeywords.insert(myAuthor.begin(),myAuthor.end());
  set<string> myISBN = parseStringToWords(isbn_);
  myKeywords.insert(myISBN.begin(),myISBN.end());
  // return vector
  return myKeywords;
}

string Book::displayString() const {
  // create string via concatenation
  string myStr = "";
  myStr += getName();
  myStr += "\n";
  myStr += "Author: ";
  myStr += author_;
  myStr += " ISBN: ";
  myStr += isbn_;
  myStr += "\n";
  myStr += (to_string(getPrice())).erase(to_string(getPrice()).length()-4);
  myStr += " ";
  myStr += to_string(getQty());
  myStr += " left.";
  // return string
  return myStr;
}

void Book::dump(ostream&os) const {
  os << getCategory() << endl;
  os << getName() << endl;
  os << (to_string(getPrice())).erase(to_string(getPrice()).length()-4) << endl;
  os << to_string(getQty()) << endl;
  os << isbn_ << endl;
  os << author_ << endl;
}