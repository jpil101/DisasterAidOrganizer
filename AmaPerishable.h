#ifndef SICT_AMAPERISHABLE_H_
#define SICT_AMAPERISHABLE_H_

#include <fstream>
#include <iostream>
#include "AmaProduct.h"
#include "Date.h"
#include "ErrorMessage.h"

namespace sict
{
    class AmaPerishable : public AmaProduct
    {
    private:
        Date expiry_;
    public:
        AmaPerishable();
        const Date& expiry()const;
        void expiry(const Date&);
        virtual std::fstream& store(std::fstream& file,bool = true) const;
        virtual std::fstream& load(std::fstream&);
        virtual std::ostream& write(std::ostream&,bool) const;
        virtual std::istream& read(std::istream&);
    };
}

#endif
