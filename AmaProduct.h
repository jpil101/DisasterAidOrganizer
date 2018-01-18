#ifndef SICT_AMAPRODUCT_H_
#define SICT_AMAPRODUCT_H_

#include "Product.h"
#include "ErrorMessage.h"

namespace sict
{
    class AmaProduct : public Product
    {
    private:
       char* fileTag_;
       char unit_[11];
    protected:
        ErrorMessage err_;
    public:
        AmaProduct(const char = 'N');
    	const char* unit()const;
    	void unit(const char* value);
    	virtual std::fstream& store(std::fstream&,bool = true) const;
        virtual std::fstream& load(std::fstream&);
        virtual std::ostream& write(std::ostream&,bool) const;
        virtual std::istream& read(std::istream&);

    };
}

#endif