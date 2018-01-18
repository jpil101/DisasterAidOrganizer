#include <cstring>
#include "Product.h"
#include "general.h"

using namespace std;

namespace sict
{
	Product::Product()
	{
		sku_[0]='\0';
		name_=nullptr;
		price_=0.00;
		quantity_=0;
		qtyNeeded_=0;
		taxed_= true;
	}

	Product::Product(const char* sk,const char* nm,bool tax,double pr,int qtyN)
	{
		strncpy(sku_,sk,MAX_SKU_LEN);
		sku_[MAX_SKU_LEN]='\0';
		quantity_=0;
		taxed_=tax;
		price_=pr;
		qtyNeeded_=qtyN;
		if(nm!=nullptr)
		{
			name_ = new char[strlen(nm)+1];
			strcpy(name_,nm);
			name_[strlen(nm)]='\0';
		}
		else	name_=nullptr;
	}

	Product::Product(const Product& src)
	{
		if(src.name()!=nullptr)
		{
			name_ = new char[strlen(src.name())+1];
			strcpy(name_,src.name());
			name_[strlen(src.name())]='\0';
		}
		else	name_=nullptr;
		strncpy(sku_,src.sku(),MAX_SKU_LEN);
		sku_[MAX_SKU_LEN] = '\0';
		price_=src.price();
		quantity_=src.quantity();
		qtyNeeded_=src.qtyNeeded();
		taxed_=src.taxed();
	}

	Product::~Product()
	{
		delete [] name_;
		name_ = nullptr;
	}

	void Product::sku(const char* sk)
	{
		strncpy(sku_,sk,MAX_SKU_LEN);
		sku_[MAX_SKU_LEN]='\0';
	}

	void Product::price(double dbl)
	{
		price_ = dbl;
	}

	void Product::name(const char* nm)
	{
		if(nm!=nullptr)
		{
			delete [] name_;
			name_ = new char[strlen(nm)+1];
			strcpy(name_,nm);
			name_[strlen(nm)]='\0';
		}
		else	name_=nullptr;
	}

	void Product::taxed(bool tax)
	{
		taxed_ = tax;
	}

	void Product::quantity(int quant)
	{
		quantity_ = quant;
	}

	void Product::qtyNeeded(int qtyN)
	{
		qtyNeeded_ = qtyN;
	}

	const char* Product::sku()const
	{
		return sku_;
	}

	double Product::price()const
	{
		return price_;
	}

	const char* Product::name()const
	{
		return name_;
	}

	bool Product::taxed()const
	{
		return taxed_;
	}

	int Product::quantity()const
	{
		return quantity_;
	}

	int Product::qtyNeeded()const
	{
		return qtyNeeded_;
	}

	double Product::cost()const
	{
		double ret = 0;
		if(taxed_==true)	ret = price_ + (price_ * TAX);
		else	ret = price_;
		return ret;
	}

	bool Product::isEmpty()const
	{
		return (sku_[0]=='\0' && name_==nullptr && price_==0.00 && quantity_==0 && qtyNeeded_==0 && taxed_== true);
	}

	Product& Product::operator=(Product& src)
	{
		if(this!=&src)
		{
			if(src.name()!=nullptr)
			{
				delete [] name_;
				name_ = new char[strlen(src.name())+1];
				strcpy(name_,src.name());
				name_[strlen(src.name())]='\0';
			}
			else	name_=nullptr;
			strncpy(sku_,src.sku(),MAX_SKU_LEN);
			sku_[MAX_SKU_LEN] = '\0';
			price_=src.price();
			quantity_=src.quantity();
			qtyNeeded_=src.qtyNeeded();
			taxed_=src.taxed();
		}
		else	name_=nullptr;
		return *this;
	}

	bool Product::operator==(const char* sk)
	{
		return (strncmp(sku_,sk,MAX_SKU_LEN)==0);
	}

	int Product::operator+=(int qty)
	{
		quantity_+=qty;
		return quantity_;
	}

	int Product::operator-=(int qty)
	{
		quantity_-=qty;
		return quantity_;
	}

	double operator+=(double& pr,Product& src)
	{
		pr += (src.cost() * src.quantity());
		return pr;
	}

	std::istream& operator>>(std::istream& istr,Product& dest)
	{
		dest.read(istr);
		return istr;
	}

	std::ostream& operator<<(std::ostream& ostr,const Product& src)
	{
		src.write(ostr,true);
		return ostr;
	}
}
