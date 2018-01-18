#ifndef SICT_DATE_H__
#define SICT_DATE_H__
#include <iostream>

#define NO_ERROR   0  //-- No error the date is valid
#define CIN_FAILED 1  //-- istream failed when entering information
#define YEAR_ERROR 2  //-- Year value is invalid
#define MON_ERROR  3  //-- Month value is invalid
#define DAY_ERROR 4 //-- Day value is invalid

namespace sict
{
    class Date
    {  
        int year_, mon_, day_, readErrorCode_;
        int value()const;
        void errCode(int);
    public:        
	    Date();
	    Date(int,int,int);
        int mdays()const;
        int errCode()const;
        bool bad()const;
        bool operator==(const Date& )const;
		bool operator!=(const Date& )const;
		bool operator<(const Date& )const;
		bool operator>(const Date& )const;
		bool operator<=(const Date& )const;
		bool operator>=(const Date& )const;
		std::istream& read(std::istream&);
		std::ostream& write(std::ostream&)const;
    };
    std::ostream& operator<<(std::ostream&,const Date&);
    std::istream& operator>>(std::istream&,Date&);
}

#endif