#include <iostream>
#include <exception>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <iomanip>
#include "Date.h"
#include<sstream>
using namespace std;


//UTILITY functions

//own to_string general function
    template <typename T>
    std::string to_string(T value)
    {
      //create an output string stream
      std::ostringstream os ;

      //throw the value into the string stream
      os << value ;

      //convert the string stream into a string and return
      return os.str() ;
    }
//own string duplication function with dynamic memory location
char* mystrdup(const char* s)
{
    char *p;
    if(s==0)
    {
        p=NULL;
    }
    else
    {
        p = new char[strlen(s)+1];
        strcpy(p, s);
    }
    return p;
}
//using rata die system to calculate difference between dates
int rdn(Date date) { /* Rata Die day one is 0001-01-01 */
    int d=static_cast<int>(date.getDay());
    int m=static_cast<int>(date.getMonth());
    int y=(date.getYear());
    if (m < 3)
        y--, m += 12;
    return 365*y + y/4 - y/100 + y/400 + (153*m - 457)/5 + d - 306;
}
//using inbuilt C++ libraries to add days
void DatePlusDays( struct tm* date, int days )
{
    const time_t ONE_DAY = 24 * 60 * 60 ;

    time_t date_seconds = mktime( date ) + (days * ONE_DAY) ;

    *date = *localtime( &date_seconds ) ; ;
}
//function that returns number of days in a month, given the month and its year
int numDays(int m, int y)
{
    switch(m)
    {
    case 1:
        return 31;
        break;
    case 2:				//Special case of february
        if(y/100==0)
            return 28+(y%4==0&&y!=0);
        else
            return 28+(y%4==0&&y%100!=0);
        break;
    case 3:
        return 31;
        break;
    case 4:
        return 30;
        break;
    case 5:
        return 31;
        break;
    case 6:
        return 30;
        break;
    case 7:
        return 31;
        break;
    case 8:
        return 31;
        break;
    case 9:
        return 30;
        break;
    case 10:
        return 31;
        break;
    case 11:
        return 30;
        break;
    case 12:
        return 31;
        break;
    default:
        throw invalid_argument("Unknown exception.");

    }

}

	DateFormat::DateFormat(const char* dateFormat, const char* monthFormat, const char* yearFormat)
        {
            //using mystrdup to duplicate strings
            if(dateFormat==0||strcmp(dateFormat,"d")==0||strcmp(dateFormat,"dd")==0)
                this->dateFormat=mystrdup(dateFormat);
            else
                throw invalid_argument("Wrong date format.");
            if(monthFormat==0||strcmp(monthFormat,"m")==0||strcmp(monthFormat,"mm")==0||strcmp(monthFormat,"mmm")==0)
                this->monthFormat=mystrdup(monthFormat);
            else
                throw invalid_argument("Wrong month format.");
            if(yearFormat==0||strcmp(yearFormat,"yy")==0||strcmp(yearFormat,"yyyy")==0)
                this->yearFormat=mystrdup(yearFormat);
            else
                throw invalid_argument("Wrong year format.");
        }
    DateFormat::DateFormat(const char* format)
    {
        //Parsing the input string, and using '-' to find different parts of input string

        int i=0;
        while(format[i]!='-'&&format[i])
            i++;
        if(format[i]=='\0')
            throw invalid_argument("Wrong date format.");
        dateFormat=new char[i+1];
        copy(format,format+i,dateFormat);
        if(i==0)
            dateFormat=NULL;
        else
            dateFormat[i]='\0';
        int j=i+1;
        while(format[j]!='-'&&format[j])
            j++;
        if(format[j]=='\0')
            throw invalid_argument("Wrong date format.");
        monthFormat=new char[j-i+1];
        copy(format+i+1,format+j,monthFormat);
        if(j-i-1==0)
            monthFormat=NULL;
        else
            monthFormat[j-i-1]='\0';
        i=j+1;
        if(format[i])
        {
            while(format[i])
                i++;
            yearFormat=new char[i-j+1];
            copy(format+j+1,format+i+1,yearFormat);
        }
        else
            yearFormat=NULL;
        if(dateFormat!=0&&strcmp(dateFormat,"dd")&&strcmp(dateFormat,"d"))
            throw invalid_argument("Wrong date format.");
        if(monthFormat!=0&&strcmp(monthFormat,"m")&&strcmp(monthFormat,"mm")&&strcmp(monthFormat,"mmm"))
            throw invalid_argument("Wrong month format.");
        if(yearFormat!=0&&strcmp(yearFormat,"yy")&&strcmp(yearFormat,"yyyy"))
            throw invalid_argument("Wrong year format.");
    }
    DateFormat::DateFormat(DateFormat& d)
    {
        dateFormat=mystrdup(d.dateFormat);
        monthFormat=mystrdup(d.monthFormat);
        yearFormat=mystrdup(d.yearFormat);
    }
    DateFormat::DateFormat()
    {
        dateFormat=mystrdup("dd");
        monthFormat=mystrdup("mmm");
        yearFormat=mystrdup("yy");
    }

    DateFormat::~DateFormat()
    {
        delete[] dateFormat;
        delete[] monthFormat;
        delete[] yearFormat;
    }

    //Getter functions
    const char* DateFormat::getDateFormat()
    {
        return dateFormat;
    }
    const char* DateFormat::getMonthFormat()
    {
        return monthFormat;
    }
    const char* DateFormat::getYearFormat()
    {
        return yearFormat;
    }


    //Date Class Methods

    Date::Date(Day d, Month m, Year y)            // Construct a Date from (d, m, y)
        throw(invalid_argument,             // One or more of the arguments d or m is/are invalid (27, 13, 13)
            domain_error,                   // (d, m, y) as a triplet does not define a valid date (30, 2, 61)
            out_of_range)                   // Date is out of range (4, 7, 2053)
    {

        if(d>numDays(m,y)||d<1)
            throw domain_error("Incorrect date.");
        if(d==29 && m==2 && (y%4!=0||y%100==0))
            throw domain_error("Incorrect date.");
        this->day=d;
        month=m;
        if((y/100)!=0)
        {
            if(y>2049||y<1950)
                throw out_of_range("Date out of range...");
            year=y;
        }
        else
        {
            year=(y>=50?1900+y:2000+y);
        }
    }

    Date::Date(const char* date)         // date in string format -- to be parsed as static format member
        throw(invalid_argument, domain_error, out_of_range)
                                            // "13-03-77" for "dd-mm-yy"
                                            // "2-7-2018" for "d-m-yyyy"
        {

            char *tempdate=mystrdup(date);
            for(int i=0;tempdate[i];i++)
                if(tempdate[i]=='-')
                tempdate[i]=' ';

            char *inpdate,*inpmonth,*inpyear;
            inpdate=new char(10);
            inpmonth=new char(10);
            inpyear=new char(10);

            if(sscanf(tempdate,"%s %s %s",inpdate,inpmonth,inpyear)!=3)
                throw invalid_argument("Wrong date format.");

            const char *d=mystrdup(Date::format.getDateFormat());
            const char *m=mystrdup(Date::format.getMonthFormat());
            const char *y=mystrdup(Date::format.getYearFormat());

            if(strcmp(inpmonth,"Jan")==0 or
               strcmp(inpmonth,"Feb")==0 or
               strcmp(inpmonth,"Mar")==0 or
               strcmp(inpmonth,"Apr")==0 or
               strcmp(inpmonth,"May")==0 or
               strcmp(inpmonth,"Jun")==0 or
               strcmp(inpmonth,"Jul")==0 or
               strcmp(inpmonth,"Aug")==0 or
               strcmp(inpmonth,"Sep")==0 or
               strcmp(inpmonth,"Oct")==0 or
               strcmp(inpmonth,"Nov")==0 or
               strcmp(inpmonth,"Dec")==0
               )
                throw invalid_argument("This date format is valid only for output.");
            for(unsigned int i=0;i<strlen(inpdate);i++)
                if(!isdigit(inpdate[i]))
                throw invalid_argument("Not a date, has non-digits.");
            for(unsigned int i=0;i<strlen(inpmonth);i++)
                if(!isdigit(inpmonth[i]))
                throw invalid_argument("Not a month, has non-digits.");
            for(unsigned int i=0;i<strlen(inpyear);i++)
                if(!isdigit(inpyear[i]))
                throw invalid_argument("Not a year, has non-digits.");
            if(strcmp(d,"d")==0)
            {
                if(inpdate[0]=='0')
                    throw invalid_argument("Date not in correct format.");
            }
            if(strcmp(d,"dd")==0)
            {
                if(strlen(inpdate)!=2)
                    throw invalid_argument("Date not in correct format.");
            }
            if(strcmp(m,"m")==0)
            {
                if(inpmonth[0]=='0')
                    throw invalid_argument("Month not in correct format.");
            }
            if(strcmp(m,"mm")==0)
            {
                if(strlen(inpmonth)!=2)
                    throw invalid_argument("Month not in correct format.");
            }
            if(strcmp(y,"yy")==0)
                if(strlen(inpyear)!=2)
                throw invalid_argument("Year not in correct format.");
            if(strcmp(y,"yyyy")==0)
                if(strlen(inpyear)!=4)
                throw invalid_argument("Year not in correct format.");
            day=static_cast<Day>(atoi(inpdate));
            month=static_cast<Month>(atoi(inpmonth));
            year=atoi(inpyear);
            if(day<1 || day>numDays(month,year))
                throw domain_error("Incorrect date.");
            if(strcmp(y,"yyyy")==0)
            {

                if(year>2049||year<1950)
                    {
                        throw out_of_range("Date out of range...");
                    }
            }
            else
            {
                year=(year>=50?1900+year:2000+year);
            }
            delete[] inpdate;
            delete[] inpmonth;
            delete[] inpyear;
            delete[] tempdate;
            delete[] d;
            delete[] m;
            delete[] y;
        }

    Date::Date()                                  // Default Constructor - construct ’today’ (get from system)
        throw(domain_error, out_of_range)
        {
            //using inbuilt time functions to get current time
        	//using strfttime() to get date,month and year out of tstruct
            char *buf;
            time_t     now = time(0);
            struct tm  tstruct;
            tstruct = *localtime(&now);
            buf=new char[3];
            strftime(buf,3,"%d",&tstruct);
            day=static_cast<Day>(atoi(buf));
            delete[] buf;
            buf=new char[3];
            strftime(buf,3,"%m",&tstruct);
            month=static_cast<Month>(atoi(buf));
            delete[] buf;
            buf=new char[5];
            strftime(buf,5,"%Y",&tstruct);
            year=atoi(buf);

            if(year>2049||year<1950)
                throw out_of_range("Date out of range...");
            delete[] buf;
        }
    //Copy Constructor
    Date::Date(const Date& obj)                       // Copy Constructor
    {
        day=obj.getDay();
        month=obj.getMonth();
        year=obj.getYear();
    }
    // DESTRUCTOR
    Date::~Date(){}                                // No virtual destructor needed

    // BASIC ASSIGNMENT OPERATOR
    Date& Date::operator=(const Date& d)
    {
        this->day=d.day;
        this->month=d.month;
        this->year=d.year;
        return *this;
    }

    // UNARY ARITHMETIC OPERATORS

    //Prefix increment
    Date& Date::operator++()         // Next day
    {
        //increment date by one considering different cases where month or year increment may be required
        if(day<numDays(month,year))
            day=static_cast<Day>(static_cast<int>(day)+1);
        else
        {
            if(month<12)
            {
                month=static_cast<Month>(static_cast<int>(month)+1);
                day=D01;
            }
            else
            {
                month=Jan;
                day=D01;
                year++;
                if(year==2050)
                    throw out_of_range("Next date out of range.");
            }
        }
        return *this;
    }
    //Postfix increment
    Date& Date::operator++(int)      // Same day next week
    {
        //increment date by seven considering different cases where month or year increment may be required
        if(day<=numDays(month,year)-7)
            day=static_cast<Day>(static_cast<int>(day)+7);
        else
        {
            if(month<12)
            {
                day=static_cast<Day>((static_cast<int>(day)+7)%numDays(month,year));
                month=static_cast<Month>(static_cast<int>(month)+1);

            }
            else
            {
                day=static_cast<Day>((static_cast<int>(day)+7)%numDays(month,year));
                month=Jan;
                year++;
                if(year==2050)
                    throw out_of_range("Next date out of range.");
            }
        }
        return *this;
    }

    Date& Date::operator--()         // Previous day
    {
        //decrement date by one considering different cases where month or year decrement may be required
        if(day>1)
            day=static_cast<Day>(static_cast<int>(day)-1);
        else
        {
            if(month>1)
            {
                month=static_cast<Month>(static_cast<int>(month)-1);
                day=static_cast<Day>(numDays(month,year));
            }
            else
            {
                month=Dec;
                day=static_cast<Day>(numDays(month,year));
                year--;
                if(year==1949)
                    throw out_of_range("Previous date out of range.");
            }
        }
        return *this;
    }
    Date& Date::operator--(int)      // Same day previous week
    {
        //decrement date by seven considering different cases where month or year decrement may be required
        if(day>7)
            day=static_cast<Day>(static_cast<int>(day)-7);
        else
        {
            if(month>1)
            {
                month=static_cast<Month>(static_cast<int>(month)-1);
                day=static_cast<Day>(numDays(month,year)+static_cast<int>(day)-7);
            }
            else
            {
                month=Dec;
                day=static_cast<Day>(numDays(month,year)+static_cast<int>(day)-7);
                year--;
                if(year==1949)
                    throw out_of_range("Previous date out of range.");
            }
        }
        return *this;
    }
    // BINARY ARITHMETIC OPERATORS
    unsigned int Date::operator-(const Date& otherDate)  // Number of days between otherDate and current date
    {
        //using Rata Die Calendar
        return abs(rdn(*this)-rdn(otherDate));
    }
    Date Date::operator+(int noOfDays)                    // Day noOfDays after (before) the current date
                                                    // (sign of noOfDays decides ahead or behind)
        throw(domain_error, out_of_range)
        {
            //using inbuilt functions of C++
            Date d1(D01,Jan,1950),d2(D31,Dec,2049);
            if((*this)-d1<(unsigned)(abs(noOfDays))&&noOfDays<0)
                throw out_of_range("Requested date out of range...");
            if((*this)-d2<(unsigned)(abs(noOfDays))&&noOfDays>0)
                throw out_of_range("Requested date out of range...");
            tm date={0,0,12};           //arbitrary
            date.tm_year=year-1900;
            date.tm_mon=static_cast<int>(month)-1;
            date.tm_mday=static_cast<int>(day);
            DatePlusDays( &date, noOfDays ) ;
            Date summed((to_string(date.tm_mday)+"-"+to_string(date.tm_mon+1)+"-"+to_string(date.tm_year+1900)).c_str());
            return summed;
        }

    // CAST OPERATORS
    Date::operator WeekNumber() const    // Cast to the week number of the year in which the current date falls
    {
        //using inbuilt C++ feature to get ISO 8601 week number
        //%V does not work for strftime() in Windows
        tm timeStruct = {0,0,12};
        timeStruct.tm_year = year-1900;
        timeStruct.tm_mon=static_cast<int>(month)-1;
        timeStruct.tm_mday=static_cast<int>(day);
        mktime( &timeStruct );					//assigns other fields of timeStruct their values
        char buf[3];
        strftime(buf,3,"%V",&timeStruct);					//C++11, otherwise use %W for normal week number
        return static_cast<WeekNumber>(atoi(buf));		//finally cating to WeekNumber enum
    }
    Date::operator Month() const         // Cast to the month of the year in which the current date falls
    {
        return static_cast<Month>(this->month);				//casting month to Month enum
    }
    Date::operator WeekDay() const       // Cast to the day of the week of the current date
    {
        tm timeStruct = {0,0,12};
        timeStruct.tm_year = year-1900;
        timeStruct.tm_mon=static_cast<int>(month)-1;
        timeStruct.tm_mday=static_cast<int>(day);
        mktime( &timeStruct );						//assigns other fields of timeStruct their values
        //tm_wday gives number of days elapsed since Sunday
        int weekday=(timeStruct.tm_wday?timeStruct.tm_wday:7);			//Sunday is not considered 0, but 7
        return static_cast<WeekDay>(weekday);
    }

    bool Date::leapYear() const          // True if the year of the current date is a leap year
    {
        return year%4==0&&year%100!=0;			//Typical leap year conditions
    }

    // BINARY RELATIONAL OPERATORS
    bool Date::operator==(const Date& otherDate)
    {
        return day==otherDate.day && month== otherDate.month && year==otherDate.year;
    }
    bool Date::operator!=(const Date& otherDate)
    {
        return day!=otherDate.day || month != otherDate.month || year!=otherDate.year;
    }
    //Using Rata Die values to compare dates
    bool Date::operator<(const Date& otherDate)
    {
        return (rdn(*this)<rdn(otherDate));
    }
    bool Date::operator<=(const Date& otherDate)
    {
        return (rdn(*this)<=rdn(otherDate));
    }
    bool Date::operator>(const Date& otherDate)
    {
        return (rdn(*this)>rdn(otherDate));
    }
    bool Date::operator>=(const Date& otherDate)
    {
        return (rdn(*this)>=rdn(otherDate));
    }

    // BASIC I/O using FRIEND FUNCTIONS
    // These functions use Date::format to write or read
    ostream& operator<<(ostream& o, const Date& date)
    {
        //Consider dateformat in terms of length of dateformat, monthformat and yearformat

        DateFormat df=date.getFormat();
        char *dateFormat=mystrdup(df.getDateFormat());
        char *monthFormat=mystrdup(df.getMonthFormat());
        char *yearFormat=mystrdup(df.getYearFormat());
        int d,m,y;
        if(dateFormat==0)
            d=0;
        else
            d=strlen(dateFormat);
        if(monthFormat==0)
            m=0;
        else
            m=strlen(monthFormat);
        if(yearFormat==0)
            y=0;
        else
            y=strlen(yearFormat);

        if(d>2||d<0)
            throw domain_error("Wrong date format n4.");
        if(d==2)
        {
            o << setfill('0') << setw(2) << static_cast<int>(date.getDay()) ;
            o<<'-';
        }
        else
            if(d==1)
        {
            o<<static_cast<int>(date.getDay())<<'-';
        }
        else
            o<<" -";
        if(m>3||m<0)
            throw domain_error("Wrong date format n7.");
        //if m is 3, print Month name
        if(m==3)
        {
            switch(static_cast<int>(date.getMonth()))
            {
                case 1:   o<<"Jan";
                            break;
                case 2:   o<<"Feb";
                            break;
                case 3:   o<<"Mar";
                            break;
                case 4:   o<<"Apr";
                            break;
                case 5:   o<<"May";
                            break;
                case 6:   o<<"Jun";
                            break;
                case 7:   o<<"Jul";
                            break;
                case 8:   o<<"Aug";
                            break;
                case 9:   o<<"Sep";
                            break;
                case 10:   o<<"Oct";
                            break;
                case 11:   o<<"Nov";
                            break;
                case 12:   o<<"Dec";
                            break;
            }

            o<<'-';
        }
        else
        if(m==2)
        {
            o<< setfill('0') << setw(2) << static_cast<int>(date.getMonth()) ;
            o<<'-';
        }
        else
            if(m==1)
        {
            o<<static_cast<int>(date.getMonth())<<'-';
        }
        else
            o<<" -";
        if(y!=0&&y!=2&&y!=4)
            throw domain_error("Wrong date format n0.");
        if(y==2)
        {
            o << date.getYear()%100 ;
        }
        else
            if(y==4)
        {
            o<<date.getYear();
        }
        delete[] dateFormat;
        delete[] monthFormat;
        delete[] yearFormat;
        return o;
    }
    //Similar to << operator
    istream& operator>>(istream& i, Date& date)
    {
        DateFormat df=date.getFormat();
        char *dateFormat=mystrdup(df.getDateFormat());
        char *monthFormat=mystrdup(df.getMonthFormat());
        char *yearFormat=mystrdup(df.getYearFormat());
        int d,m,y;
        if(dateFormat==0)
            d=0;
        else
            d=strlen(dateFormat);
        if(monthFormat==0)
            m=0;
        else
            m=strlen(monthFormat);
        if(yearFormat==0)
            y=0;
        else
            y=strlen(yearFormat);

        //Considering all cases of d,m,y values independently
        if(d>2||d<0)
            throw domain_error("Wrong date format 1.");
        if(d==2)
        {
            char *s=new char[3];
            i.get(s,3);
            if(strlen(s)!=2)
                throw domain_error("Wrong date format 2.");
            if(!isdigit(s[0])||!isdigit(s[1]))
                throw domain_error("Wrong date value.");
            date.day=static_cast<Day>(atoi(s));
            i.get();
            delete[] s;
        }
        else
            if(d==1)
        {
            char *s=new char[3];
            i.get(s,3,'-');
            if(strlen(s)==2)
            {
                if(!isdigit(s[0])||!isdigit(s[1]))
                    throw domain_error("Wrong date value.");
                if(s[0]=='0')
                    throw domain_error("Date entered in wrong format");
            }
            else
                if(strlen(s)==1)
            {
                if(s[0]<'1'||s[0]>'9')
                throw domain_error("Wrong date value.");
            }
            else
                throw domain_error("Wrong date format 3.");
            date.day=static_cast<Day>(atoi(s));
            i.get();
            delete[] s;
        }
        else
            throw domain_error("Invalid date format for input.");
        if(m>3||m<0)
            throw domain_error("Wrong date format 4.");
        if(m==3||m==0)
        {
            throw domain_error("Invalid month format for input.");
        }
        else
        if(m==2)
        {
            char *s=new char[3];
            i.get(s,3);
            if(strlen(s)!=2)
                throw domain_error("Wrong date format. 5");
            if(!isdigit(s[0])||!isdigit(s[1]))
                throw domain_error("Wrong date value.");
            date.month=static_cast<Month>(atoi(s));
            if(date.day<1||date.day>numDays(date.month,date.year))
                throw invalid_argument("Invalid date.");
            i.get();
            delete[] s;
        }
        else
            if(m==1)
        {
            char *s=new char[3];
            i.get(s,3,'-');
            if(strlen(s)==2)
            {
                if(!isdigit(s[0])||!isdigit(s[1]))
                    throw domain_error("Wrong month value.");
                if(s[0]=='0')
                    throw domain_error("Month entered in wrong format");
            }
            else
                if(strlen(s)==1)
            {
                if(s[0]<'1'||s[0]>'9')
                throw domain_error("Wrong month value.");
            }
            else
                throw domain_error("Wrong month format.");
            date.month=static_cast<Month>(atoi(s));
            if(date.day<1||date.day>numDays(date.month,date.year))
                throw invalid_argument("Invalid date.");
            i.get();
            delete[] s;
        }
        if(y!=0&&y!=2&&y!=4)
            throw domain_error("Wrong date format. 6");
        if(y==2)
        {
            char *s=new char[3];
            i.get(s,3);
            if(strlen(s)!=2)
                throw domain_error("Wrong date format. 7");
            if(!isdigit(s[0])||!isdigit(s[1]))
                throw domain_error("Wrong date value.");
            int inpyear=atoi(s);
            date.year=(inpyear>=50?1900+inpyear:2000+inpyear);;
            i.get();
            delete[] s;
        }
        else
            if(y==4)
        {
            char *s=new char[5];
            i.get(s,5);
            if(strlen(s)!=4)
                throw domain_error("Wrong date format. 8");
            if(!isdigit(s[0])||!isdigit(s[1])||!isdigit(s[2])||!isdigit(s[3]))
                throw domain_error("Wrong date value.");
            date.year=atoi(s);
            i.get();
            delete[] s;
        }
        delete[] dateFormat;
        delete[] monthFormat;
        delete[] yearFormat;
        return i;
    }

    // Format Function
    void Date::setFormat(DateFormat& d)
    {
        format=d;	//Using copy constructor
    }
    DateFormat& Date::getFormat()
    {
        return format;
    }
    Day Date::getDay() const
    {
        return day;
    }
    Month Date::getMonth() const
    {

        return month;
    }
    Year Date::getYear() const
    {
        return year;
    }

    DateFormat Date::format;		//Use default constructor
