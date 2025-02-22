#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <map>
#include "util.h"
#include "datastore.h"

class MyDataStore : public DataStore {

  public:

    // constructor and destructor
    MyDataStore();
    ~MyDataStore();

    // function prototypes
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    void addToCart(const std::string& username, Product* p);
    void buyCart(const std::string& username);
    void viewCart(const std::string& username);

  private:

    // store products and users
    std::set<Product*> products_;
    std::set<User*> users_;
    // map of product terms
    // string:set of products
    std::map<std::string, std::set<Product*>> prodMap_;
    // map of user cart
    // User*:set of products
    std::map<User*, std::vector<Product*>> userCart_;

};
#endif