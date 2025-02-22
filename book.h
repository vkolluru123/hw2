#ifndef BOOK_H
#define BOOK_H
#include "product.h"

class Book : public Product {

  public:

    // constructor and destructor
    Book(const std::string category, const std::string name, double price, int qty, const std::string& isbn_, const std::string& author_);
    ~Book();

    // function prototypes
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream&os) const;

  private:
    std::string isbn_;
    std::string author_;

};
#endif