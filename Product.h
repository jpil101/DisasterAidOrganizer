#ifndef SICT_PRODUCT_H_
#define SICT_PRODUCT_H_

#include "Streamable.h"
#include "general.h"

namespace sict
{
  class Product: public Streamable
  {
    char sku_[MAX_SKU_LEN+1];
    char* name_;
    double price_;
    int quantity_;
    int qtyNeeded_;
    bool taxed_;
  public:
    Product();
    Product(const char*,const char*,bool = true,double = 0.0,int = 0);
    Product(const Product& src);
    virtual ~Product();
    void sku(const char*);
    void price(double);
    void name(const char*);
    void taxed(bool);
    void quantity(int);
    void qtyNeeded(int);
    const char* sku()const;
    double price()const;
    const char* name()const;
    bool taxed()const;
    int quantity()const;
    int qtyNeeded()const;
    double cost()const;
    bool isEmpty()const;
    Product& operator=(Product&);
    bool operator==(const char*);
    int operator+=(int);
    int operator-=(int);
  };
  double operator+=(double&,Product&);
  std::istream& operator>>(std::istream&,Product&);
  std::ostream& operator<<(std::ostream&,const Product&);
}

#endif
