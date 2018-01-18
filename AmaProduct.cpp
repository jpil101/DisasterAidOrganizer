#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "AmaProduct.h"

using namespace std;

namespace sict
{
	AmaProduct::AmaProduct(const char ftag)
	{
		fileTag_ = new char[2];
		strncpy(fileTag_,&ftag,1);
		fileTag_[1] = '\0';
	}

	const char* AmaProduct::unit()const
	{
		return unit_;
	}

	void AmaProduct::unit(const char* value)
	{
		strncpy(unit_,value,10);
		unit_[10] = '\0';
	}

	std::fstream& AmaProduct::store(std::fstream& file,bool tof) const
	{
		if(file.is_open())
		{
			if(tof==true)
				file<<fileTag_<<","<<sku()<<","<<name()<<","<<price()<<","<<taxed()<<","<<quantity()<<","<<unit_<<","<<qtyNeeded()<<endl;
			else
				file<<fileTag_<<","<<sku()<<","<<name()<<","<<price()<<","<<taxed()<<","<<quantity()<<","<<unit_<<","<<qtyNeeded();
		}
        return file;
	}

    std::fstream& AmaProduct::load(std::fstream& file)
    {
    	char filetostr[500];
    	double filetod;
    	int filetoi;

    	if(file.is_open())
    	{
    		file.getline(filetostr,499,',');
            sku(filetostr);
            file.getline(filetostr,499,',');
            name(filetostr);
            file >> filetod;
            price(filetod);
            file.ignore();
            file >> filetoi;
            taxed(bool(filetoi));
            file.ignore();
            file >> filetoi;
            quantity(filetoi);
            file.ignore();
            file.getline(filetostr,499,',');
            unit(filetostr);
            file >> filetoi;
            qtyNeeded(filetoi);
    	}
		return file;
    }

    std::ostream& AmaProduct::write(std::ostream& ostr,bool tof) const
    {
    	if(!err_.isClear())    ostr<<err_;
    	else
    	{
    		if(tof==true)
    			ostr<<left<<setw(MAX_SKU_LEN)<<sku()<<"|"<<left<<setw(20)<<name()<<"|"<<right<<setw(7)<<fixed<<setprecision(2)<<cost()<<"|"<<right<<setw(4)<<quantity()<<"|"<<left<<setw(10)<<unit_<<"|"<<right<<setw(4)<<qtyNeeded()<<"|";
            else
            {
                if(taxed())
                    ostr<<"Sku: "<<sku()<<endl<<"Name: "<<name()<<endl<<"Price: "<<price()<<endl<<"Price after tax: "<<cost()<<endl<<"Quantity On Hand: "<<quantity()<<" "<<unit_<<endl<<"Quantity Needed: "<<qtyNeeded();
                else
                    ostr<<"Sku: "<<sku()<<endl<<"Name: "<<name()<<endl<<"Price: "<<price()<<endl<<"Price after tax: N/A"<<endl<<"Quantity On Hand: "<<quantity()<<" "<<unit_<<endl<<"Quantity Needed: " <<qtyNeeded();
            }
    	}
    	return ostr;
    }

    std::istream& AmaProduct::read(std::istream& istr)
    {
        char readstr1[51],readstr2[51],readstr3[51],readstr4;
        double readd;
        int readint1,readint2;

        cout<<"Sku: ";
        istr.getline(readstr1, 50, '\n');
        cout<<"Name: ";
        istr.getline(readstr2, 50, '\n');
        cout<<"Unit: ";
        istr.getline(readstr3, 50, '\n');
        cout<<"Taxed? (y/n): ";
        istr>>readstr4;
        if(readstr4=='y'||readstr4=='Y'||readstr4=='N'||readstr4=='n')
        {
            istr.ignore(1000, '\n');
            cout<<"Price: ";
            istr>>readd;
        }
        else
        {
            err_.message("Only (Y)es or (N)o are acceptable");
            istr.setstate(ios::failbit);
            return istr;
        }
        if(istr.fail())
        {
            err_.message("Invalid Price Entry");
            return istr;
        }
        cout<<"Quantity On hand: ";
        istr>>readint1;
        if(istr.fail())
        {
            err_.message("Invalid Quantity Entry");
            return istr;
        }
        cout<<"Quantity Needed: ";
        istr>>readint2;
        if(istr.fail())
        {
            err_.message("Invalid Quantity Needed Entry");
            return istr;
        }
        sku(readstr1);
        name(readstr2);
        unit(readstr3);
        if(readstr4=='y'||readstr4=='Y')    taxed(true);
        else    taxed(false);
        price(readd);
        quantity(readint1);
        qtyNeeded(readint2);
        err_.clear();
        return istr;
    }
}
