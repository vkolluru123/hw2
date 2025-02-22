#include "clothing.h"
#include <iostream>

using namespace std;

// constructor
Clothing::Clothing(const string category, const string name, double price, int qty, const string& size, const string& brand)
    : Product(category, name, price, qty), size_(size), brand_(brand) {}

// destructor
Clothing::~Clothing() {}

// functions

set<string> Clothing::keywords() const {
  // create vector to hold keywords
  set<string> myKeywords;
  // use parse string to words on each string
  string myName = getName();
  set<string> mymyName = parseStringToWords(myName);
  myKeywords.insert(mymyName.begin(),mymyName.end());
  set<string> mySize = parseStringToWords(size_);
  myKeywords.insert(mySize.begin(),mySize.end());
  set<string> myBrand = parseStringToWords(brand_);
  myKeywords.insert(myBrand.begin(),myBrand.end());
  // return vector
  return myKeywords;
}

string Clothing::displayString() const {
  // create string via concatenation
  string myStr = "";
  myStr += getName();
  myStr += "\n";
  myStr += "Size: ";
  myStr += size_;
  myStr += " Brand: ";
  myStr += brand_;
  myStr += "\n";
  myStr += (to_string(getPrice())).erase(to_string(getPrice()).length()-4);
  myStr += " ";
  myStr += to_string(getQty());
  myStr += " left.";
  // return string
  return myStr;
}

void Clothing::dump(ostream&os) const {
  os << getCategory() << endl;
  os << getName() << endl;
  os << (to_string(getPrice())).erase(to_string(getPrice()).length()-4) << endl;
  os << to_string(getQty()) << endl;
  os << size_ << endl;
  os << brand_ << endl;
}