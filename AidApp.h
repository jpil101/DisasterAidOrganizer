#ifndef SICT_AIDAPP_H_
#define SICT_AIDAPP_H_
#include "AmaPerishable.h"
#include "AmaProduct.h"

namespace sict
{
	class AidApp
	{
        char filename_[256];
        Product* product_[MAX_NO_RECS];
        std::fstream datafile_;
        int noOfProducts_;

        void pause()const;
        int menu();
        void loadRecs();
        void saveRecs();
        void listProducts()const;
        int SearchProducts(const char*) const;
        void addQty(const char*);
        void addProduct(bool);
        AidApp(const AidApp&) = delete;
        AidApp& operator=(const AidApp&) = delete;

	public:
    	AidApp(const char*);
    	int run();
    };

}

#endif
