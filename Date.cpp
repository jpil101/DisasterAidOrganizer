#include <iomanip>
#include <iostream>
#include "Date.h"
#include "general.h"
using namespace std;


namespace sict
{
    int Date::value()const
    {
        return year_ * 372 + mon_ * 31 + day_;
    }

    void Date::errCode(int recode)
    {
        readErrorCode_ = recode;
    }

    int Date::errCode()const
    {
        return readErrorCode_;
    }

    Date::Date()
    {
        year_ = 0;
        mon_ = 0;
        day_ = 0;
        readErrorCode_ = NO_ERROR;
    }

    Date::Date(int year,int mon,int day)
    {
        year_ = year;
        mon_ = mon;
        if(day>=1 && day<=mdays())  day_=day;
        readErrorCode_ = NO_ERROR;    
    }

    int Date::mdays()const
    {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
        mon--;
        return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
    }

    bool Date::bad()const
    {
        return (readErrorCode_ != 0);
    }

    bool Date::operator==(const Date& dt)const
    {
        return (value()==dt.value());
    }

    bool Date::operator!=(const Date& dt)const
    {
        return (value()!=dt.value());
    }

    bool Date::operator<(const Date& dt)const
    {
        return (value()<dt.value());
    }

    bool Date::operator>(const Date& dt)const
    {
        return (value()>dt.value());
    }

    bool Date::operator<=(const Date& dt)const
    {
        return (value()<=dt.value());
    }

    bool Date::operator>=(const Date& dt)const
    {
        return (value()>=dt.value());
    }

    std::istream& Date::read(std::istream& istr)
    {
        int day;
        istr >> year_;
        istr.ignore();
        istr >> mon_;
        istr.ignore();
        istr >> day;
        if(istr.fail()) readErrorCode_ = CIN_FAILED;
        else
        {
            if(year_ >= MIN_YEAR && year_<= MAX_YEAR && mon_ >= 1 && mon_ <= 12 && day>=1 && day<=mdays())
            {
                day_=day;
                readErrorCode_ = NO_ERROR;
            }
            else if(year_<MIN_YEAR || year_>MAX_YEAR)
            {
                day_=day;
                readErrorCode_ = YEAR_ERROR;
            }
            else if(mon_<1 || mon_>12)
            {
                day_=day;
                readErrorCode_ = MON_ERROR;
            }
            else if(day<1 || day>mdays())
            {
                day_=day;
                readErrorCode_ = DAY_ERROR;
            }
        }
        return istr;
    }   
     
    std::ostream& Date::write(std::ostream& ostr)const
    {
        if(mon_>=0 && mon_<10 && day_ >=0 && day_<10)
            ostr << year_ << "/" << "0" << mon_ << "/" << "0" << day_;
        else if(mon_>=0 && mon_<10)
            ostr << year_ << "/" << "0" << mon_ << "/" << day_;
        else if(day_ >=0 && day_<10)
            ostr << year_ << "/" << mon_ << "/" << "0" << day_;
        else
            ostr << year_ << "/" << mon_ << "/" << day_;
        return ostr;
    }

    std::ostream& operator<<(std::ostream& ostr,const Date& odate)
    {
        odate.write(ostr);
        return ostr;
    }

    std::istream& operator>>(std::istream& istr,Date& idate)
    {
        idate.read(istr);
        return istr;
    }
}
