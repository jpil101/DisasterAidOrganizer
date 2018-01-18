#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "AmaPerishable.h"

using namespace std;

namespace sict
{
    AmaPerishable::AmaPerishable() : AmaProduct('P'){}

    const Date& AmaPerishable::expiry()const
    {
    	return expiry_;
    }

    void AmaPerishable::expiry(const Date& value)
    {
        expiry_ = value;
    }

    std::fstream& AmaPerishable::store(std::fstream& file,bool tof) const
    {
    	AmaProduct::store(file,false);

    	if(tof==true)  file<<","<<expiry_<<endl;
    	else   file<<","<<expiry_;
    	return file;
    }

    std::fstream& AmaPerishable::load(std::fstream& file)
    {
        AmaProduct::load(file);
        file.ignore();
    	expiry_.read(file);
    	return file;
    }

    std::ostream& AmaPerishable::write(std::ostream& ostr,bool tof) const
    {
    	AmaProduct::write(ostr,tof);
    	if(AmaProduct::err_.isClear() && !Product::isEmpty())
    	{
    		if(tof==true) cout<<expiry_;
    		else  cout<<endl<<"Expiry date: "<<expiry_;
    	}
    	return ostr;
    }

    std::istream& AmaPerishable::read(std::istream& istr)
    {
    	Date temp;
    	AmaProduct::read(istr);
    	if(err_.isClear())
		{
			cout<<"Expiry date (YYYY/MM/DD): ";
    		cin>>temp;
    		if(temp.bad())
			{
				if(temp.errCode()==CIN_FAILED)  
                    AmaProduct::err_.message("Invalid Date Entry");
				else if(temp.errCode()==YEAR_ERROR) 
                    AmaProduct::err_.message("Invalid Year in Date Entry");
				else if(temp.errCode()==MON_ERROR)
					AmaProduct::err_.message("Invalid Month in Date Entry");
				else if(temp.errCode()==DAY_ERROR)
					AmaProduct::err_.message("Invalid Day in Date Entry");

				istr.setstate(ios::failbit);
			}
            else
                expiry(temp);
		}
		return istr;
    }
}
