#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"

class Clothing : public Product {

  public:

    // constructor and destructor
    Clothing(const std::string category, const std::string name, double price, int qty, const std::string& size, const std::string& brand);
    ~Clothing();

    // function prototypes
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream&os) const;

  private:
    std::string size_;
    std::string brand_;

};
#endif