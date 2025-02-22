#include "mydatastore.h"

using namespace std;

MyDataStore::MyDataStore() {

  // create set of users?

}

MyDataStore::~MyDataStore() {

  set<Product*>::iterator pit = products_.begin();
  while (pit != products_.end()) {
    delete *pit;
    pit++;
  }
  products_.clear();

  set<User*>::iterator uit = users_.begin();
  while (uit != users_.end()) {
    delete *uit;
    uit++;
  }
  users_.clear();

  // deallocate prodMap_ and userCart_

  map<string,set<Product*>>::iterator pmit;
  pmit = prodMap_.begin();
  while (pmit != prodMap_.end()) {
    pmit->second.clear();
    pmit++;
  }
  prodMap_.clear();

  map<User*,vector<Product*>>::iterator ucit;
  ucit = userCart_.begin();
  while (ucit != userCart_.end()) {
    ucit->second.clear();
    ucit++;
  }
  userCart_.clear();

}

void MyDataStore::addProduct(Product* p) {

  // add to products set
  products_.insert(p);

  // add to products map
  // access the keywords of the product
  set<string> pKeywords = p->keywords();
  // loop through product's keywords
  set<string>::iterator pIter = pKeywords.begin();
  while (pIter != pKeywords.end()) {
    // update prodMap_
    prodMap_[*pIter].insert(p);
    //std::cout << *pIter << " " << prodMap_[*pIter].size() << endl;
    pIter++;
  }

  // update prodMap_
  set<string>::iterator pmit = pKeywords.begin();
  while (pmit != pKeywords.end()) {
    prodMap_[*pmit].insert(p);
    pmit++;
  }

}

void MyDataStore::addUser(User* u) {
  // add to users set
  users_.insert(u);

  // add user's cart to map of carts
  userCart_[u] = vector<Product*>();

}

vector<Product*> MyDataStore::search(vector<string>& terms, int type) {

  // empty terms set means no results
  if (terms.empty()) {
    return vector<Product*>();
  }

  // establish set of search results
  set<Product*> searchResults;

  // loop through terms
  for (unsigned int i = 0; i < terms.size(); i++) {
    
    //cout << "here is term read in " << terms[i] << " endl" << endl;


    // if we're just starting the loop
    if (prodMap_.find(terms[i]) != prodMap_.end()) {
      if (searchResults.empty()) {
        //cout << "SEARCH RESULTS IS EMPTY" << endl;
        // adding first term
        searchResults = prodMap_[terms[i]];
      }
      // if we're continuing the loop
      else {
        // AND search
        if (type == 0) {
          //cout << "AND SEARCH IN ELSE" << endl;
          searchResults = setIntersection(searchResults,prodMap_[terms[i]]);
        }
        // OR search
        else if (type == 1) {
          //cout << "OR SEARCH IN ELSE" << endl;
          searchResults = setUnion(searchResults,prodMap_[terms[i]]);
        }
      }
    }
  }

  // returning a vector of Product*s
  vector<Product*> searchResultsVec;
  set<Product*>::iterator srit = searchResults.begin();
  while (srit != searchResults.end()) {
    searchResultsVec.push_back(*srit);
    srit++;
  }

  return searchResultsVec;

}

void MyDataStore::dump(ostream& ofile) {

  // just printing all the products and users
  set<Product*>::iterator pit = products_.begin();
  set<User*>::iterator uit = users_.begin();

  // products loop
  ofile << "<products>" << endl;
  while (pit != products_.end()) {
    (*pit)->dump(ofile);
    pit++;
  }
  ofile << "</products>" << endl;

  // users loop
  ofile << "<users>" << endl;
  while (uit != users_.end()) {
    (*uit)->dump(ofile);
    uit++;
  }
  ofile << "</users>" << endl;

}

void MyDataStore::addToCart(const string& username, Product* p) {
  
  User* u = NULL; // we will try to find the user given username
  set<User*>::iterator uit = users_.begin();





  while (uit != users_.end()) {
    string myName = "";
    string inputName = "";
    set<string> mymyName = parseStringToWords((*uit)->getName());
    set<string>inputNamee = parseStringToWords(username);
    
    set<string>::iterator nameit = mymyName.begin();
    set<string>::iterator inameit = inputNamee.begin();

    while (nameit != mymyName.end()) {
      myName += *nameit;
      nameit++;
    }
    while (inameit != inputNamee.end()) {
      inputName += *inameit;
      inameit++;
    }
    if (convToLower(myName) == convToLower(inputName)) {
      u = *uit;
      //cout << u->getBalance() << "DEBUGGINGGNGNIGN" << endl;
      break;
    }
    uit++;
  }

  // add the product to cart
  userCart_[u].push_back(p);
  

  if (u == NULL) {
    cout << "Invalid request" << endl;
    return;
  }

  // if cart is empty
  // either *uit is NULL (user not found) - user was found
  // or p is NULL
    // hits[prodIdx-1] is p
}

void MyDataStore::buyCart(const string& username) {

  User* u = NULL; // we will try to find the user given username
  set<User*>::iterator uit = users_.begin();
  while (uit != users_.end()) {
    if ((*uit)->getName() == username) {
      u = *uit;
      break;
    }
    uit++;
  }

  if (u == NULL) {
    cout << "Invalid username" << endl;
    return;
  }

  // checking money and stock as we go through the products
  vector<Product*>::iterator cit = userCart_[u].begin();
  while (cit != userCart_[u].end()) {
    Product* currprod = *cit;

    if ((currprod->getQty()>0) && ((u->getBalance()) >=(currprod->getPrice()))) {
      u->deductAmount(currprod->getPrice());
      currprod->subtractQty(1);
      cit = userCart_[u].erase(cit);
    }
    else {
      cit++;
    }

  }

  /*// checking money

  // store how much money user has
  double userMoney = u->getBalance();
  // store total value of items in user's cart
  double cartCost = 0;
  vector<Product*>::iterator cit = userCart_[u].begin();
  while (cit != userCart_[u].end()) {   // loop through cart
    cartCost += (*cit)->getPrice();
    cit++;
  }

  // checking stock
  cit = userCart_[u].begin();
  while (cit != userCart_[u].end()) {
    // item out of stock
    if ((*cit)->getQty() == 0) {
      return;
    }
    cit++;
  }

  // if user has enough money & items are in stock, buy
  if (userMoney >= cartCost) {
    // subtract user funds
    u->deductAmount(cartCost);
    // deduct stock

    // usercart is user:vector of products
    // find the vector of products corresponsing to this user
    vector<Product*> myVec = userCart_[u];
    // loop thru this vector of products
    for (unsigned int i = 0; i < myVec.size(); i++) {
      // each product, subtract the qty by 1
      myVec[i]->subtractQty(1);
    }

    // finding this product
    //for (int i = 0; i < userCart_[u].size(); i++)
    cit = userCart_[u].begin();
    while (cit != userCart_[u].end()) {
      (*cit)->subtractQty(1);
      cit++;
    }
    // remove all items from cart
    userCart_[u].clear();
  }*/

}

void MyDataStore::viewCart(const string& username) {

  User* u = NULL; // we will try to find the user given username
  set<User*>::iterator uit = users_.begin();
  while (uit != users_.end()) {
    if ((*uit)->getName() == username) {
      u = *uit;
      break;
    }
    uit++;
  }

  if (u == NULL) {
    cout << "Invalid username" << endl;
    return;
  }

  // if cart is empty and user exists, report that
  if (userCart_[u].empty()) {
    cout << "This cart is empty." << endl;
    return;
  }

  // otherwise, print cart
  vector<Product*>::iterator cit = userCart_[u].begin();
  while (cit != userCart_[u].end()) {
    cout << (*cit)->displayString() << endl;
    cit++;
  }

}