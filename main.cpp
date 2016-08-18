#include <iostream>
#include <sstream>
#include <cstdio>
#include "Date.h"
using namespace std;


void printunary(Date &d)
{
    cout<<endl;
    Date original(d);
    try
    {
        cout<<"Original date:         "<<d<<endl;
        cout<<"Post-incremented date: "<<(d++)<<endl;d--;   //Printing, and then going back to original date
        cout<<"Pre-incremented date:  "<<(++d)<<endl;--d;
        cout<<"Post-decremented date: "<<(d--)<<endl;d++;
        cout<<"Pre-decremented date:  "<<(--d)<<endl;++d;
    }
    catch(out_of_range e)
    {
        cout<<"FAILURE\n";
        d=original;
        cout<<e.what()<<endl;
    }
}

void printbinary(Date &d1,const Date &d2)
{
    cout<<"Date 1: "<<d1<<"\t"<<"Date 2: "<<d2<<endl;
    cout<<d1<<" == "<<d2<<" : "<<(d1==d2?"True":"False")<<endl;
    cout<<d1<<" != "<<d2<<" : "<<(d1!=d2?"True":"False")<<endl;
    cout<<d1<<" < "<<d2<<" : "<<(d1<d2?"True":"False")<<endl;
    cout<<d1<<" <= "<<d2<<" : "<<(d1<=d2?"True":"False")<<endl;
    cout<<d1<<" > "<<d2<<" : "<<(d1>d2?"True":"False")<<endl;
    cout<<d1<<" >= "<<d2<<" : "<<(d1>=d2?"True":"False")<<endl;
}
void Test_DateFormat()
{
    //Testing constructor with 3 arguments
    char *days[]={0,"d","dd","random","ee"};
    char *months[]={0,"m","mm","mmm","yyy"};
    char *years[]={0,"y","yy","yyyy","y2k"};
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
        for(int k=0;k<5;k++)
    {
        cout<<endl<<endl;
        try
        {
            cout<<"Trying "<<(days[i]?days[i]:" ")<<"-"<<(months[j]?months[j]:" ")<<"-"<<(years[k]?years[k]:" ")<<endl;
            DateFormat df(days[i],months[j],years[k]);
            cout<<"SUCCESS\nCreated dateformat: "<<(df.getDateFormat()?df.getDateFormat():" ");
            cout<<"-"<<(df.getMonthFormat()?df.getMonthFormat():" ")<<"-"<<(df.getYearFormat()?df.getYearFormat():" ")<<endl;
        }
        catch(invalid_argument e)
        {
            cout<<"FAILURE\n";
            cout<<e.what()<<endl;
        }
        catch(...)
        {
            cout<<"FAILURE\n";
            cout<<"Error occurred";
        }
    }
    //Testing Constructor with single string argument
    cout<<"\nTesting Constructor 2\n";
    char *samplesuccess[]={"-m-yyyy","--yyyy","--","dd--yy","dd--","d-mm-","d-mmm-yyyy","dd-mm-yy"};
    for(int i=0;i<8;i++)
    {
        cout<<endl<<endl;
        try
        {
            cout<<"Trying "<<samplesuccess[i]<<endl;
            DateFormat df(samplesuccess[i]);
            cout<<"SUCCESS\nCreated dateformat: "<<(df.getDateFormat()?df.getDateFormat():" ");
            cout<<"-"<<(df.getMonthFormat()?df.getMonthFormat():" ")<<"-"<<(df.getYearFormat()?df.getYearFormat():" ")<<endl;
        }
        catch(invalid_argument e)
        {
            cout<<"FAILURE\n";
            cout<<e.what()<<endl;
        }
        catch(...)
        {
            cout<<"FAILURE\n";
            cout<<"Error occurred";
        }
    }
    char *samplefailure[]={"m-yyyy","-dd-yyyy","-","ddd--yy","dd-yyy-","d-mm-y","mmm-dd-yyyy","random",""};
    for(int i=0;i<9;i++)
    {
        cout<<endl<<endl;
        try
        {
            cout<<"Trying "<<samplefailure[i]<<endl;
            DateFormat df(samplefailure[i]);
            cout<<"SUCCESS\nCreated dateformat: "<<(df.getDateFormat()?df.getDateFormat():" ");
            cout<<"-"<<(df.getMonthFormat()?df.getMonthFormat():" ")<<"-"<<(df.getYearFormat()?df.getYearFormat():" ")<<endl;
        }
        catch(invalid_argument e)
        {
            cout<<"FAILURE\n";
            cout<<e.what()<<endl;
        }
        catch(...)
        {
            cout<<"FAILURE\n";
            cout<<"Error occurred";
        }
    }
    //Trying default constructor
    cout<<"\n Default Constructor\n\n";
    try
    {
        DateFormat df;
        cout<<"SUCCESS\nCreated dateformat: "<<(df.getDateFormat()?df.getDateFormat():" ");
        cout<<"-"<<(df.getMonthFormat()?df.getMonthFormat():" ")<<"-"<<(df.getYearFormat()?df.getYearFormat():" ")<<endl;
    }
    catch(bad_alloc)
    {
        cout<<"FAILURE\n";
        cout<<"Not enough memory";
    }
    catch(...)
    {
        cout<<"FAILURE\n";
        cout<<"Error occurred";
    }
}

void Test_Date()
{
    //Constructors
    //Constructor with 3 arguments
    cout<<"\n\nDate Constructor 1\n";
    Day days[]={D01,D15,D28,D29,D30,D31};
    Month months[]={Jan,Feb,Jun,Dec};
    Year years[]={00,49,50,1949,1950,2016,2049,2050};
    for(int i=0;i<6;i++)
        for(int j=0;j<4;j++)
        for(int k=0;k<8;k++)
    {
        try
        {
            cout<<"\n\nTrying "<<days[i]<<"-"<<months[j]<<"-"<<years[k]<<endl;
            Date d(days[i],months[j],years[k]);
            cout<<"SUCCESS\n"<<"Created date: "<<d;
        }
        catch(domain_error e)
        {
            cout<<"FAILURE\n";
            cout<<e.what()<<endl;
        }
        catch(out_of_range e)
        {
            cout<<"FAILURE\n";
            cout<<e.what()<<endl;
        }
        catch(...)
        {
            cout<<"FAILURE\n";
            cout<<"Error occurred";
        }
    }
    //Default Constructor
    cout<<"\tDefault Constructor\n";
    try
    {
        cout<<"\n\nTrying current date"<<endl;
        Date d;
        cout<<"SUCCESS\n"<<"Created date: "<<d;
    }
    catch(out_of_range e)
    {
        cout<<"FAILURE\n";
        cout<<e.what()<<endl;
    }
    catch(...)
    {
        cout<<"FAILURE\n";
        cout<<"Error occurred";
    }
    //Constructor from string


    cout<<"\nTesting Constructor 2, for format d-m-yyyy\n";
    char *samplesuccess[]={"1-6-2016","31-12-2049","1-1-1950","15-10-2000","29-2-2020","31-1-1998"};
    for(int i=0;i<6;i++)
    {
        cout<<endl<<endl;
        try
        {
            cout<<"Trying "<<samplesuccess[i]<<endl;
            Date d(samplesuccess[i]);
            cout<<"SUCCESS\nCreated date: "<<d;
        }
        catch(invalid_argument e)
        {
            cout<<"FAILURE\n";
            cout<<e.what()<<endl;
        }
        catch(out_of_range e)
        {
            cout<<"FAILURE\n";
            cout<<e.what()<<endl;
        }
        catch(domain_error e)
        {
            cout<<"FAILURE\n";
            cout<<e.what()<<endl;
        }
        catch(...)
        {
            cout<<"FAILURE\n";
            cout<<"Error occurred";
        }
    }
    char *samplefailure[]={"0-6-2016","07-8-2000","7-11-50","29-2-2015","31-11-1965","14-11-1949","1-1-2050","random","-12-1950","--","14-Jan-2016","35-03-2016","nfdj-jfdsvn"};
    for(int i=0;i<13;i++)
    {
        cout<<endl;
        try
        {
            cout<<"\nTrying "<<samplefailure[i]<<endl;
            Date d(samplefailure[i]);
            cout<<"SUCCESS\nCreated date: "<<d<<endl;
        }
        catch(out_of_range e)
        {
            cout<<"FAILURE\n";
            cout<<e.what()<<endl;
        }
        catch(invalid_argument e)
        {
            cout<<"FAILURE\n";
            cout<<e.what()<<endl;
        }
        catch(domain_error e)
        {
            cout<<"FAILURE\n";
            cout<<e.what()<<endl;
        }
        catch(...)
        {
            cout<<"FAILURE\n";
            cout<<"Error occurred";
        }
    }


    //Copy constructor
    cout<<"\tCopy Constructor\n";
    try
    {
        cout<<"\nTrying to copy today's date...\n";
        Date d1;
        Date d2(d1);
        cout<<"SUCCESS\nCreated Date: "<<d2<<endl;
    }
    catch(bad_alloc)
    {
        cout<<"FAILURE\n";
        cout<<"Not enough memory";
    }
    catch(...)
    {
        cout<<"FAILURE\n";
        cout<<"Error occurred";
    }

    //Checking Assignment Operator
    try
    {
        cout<<"\nTrying to assign a date...\n";
        Date d1("26-3-2014");
        Date d2;
        cout<<"Date before assignment: "<<d2<<endl;
        d2=d1;
        cout<<"Date after assignment: "<<d2<<endl;
    }
    catch(bad_alloc)
    {
        cout<<"FAILURE\n";
        cout<<"Not enough memory";
    }
    catch(...)
    {
        cout<<"FAILURE\n";
        cout<<"Error occurred";
    }

    //Unary arithmetic operators
    Date d1;
    Date d2("1-1-1950");
    Date d3("5-1-1950");
    Date d4("31-12-2049");
    Date d5("27-12-2049");
    printunary(d1);
    printunary(d2);
    printunary(d3);
    printunary(d4);
    printunary(d5);

    //Binary operators
    cout<<"\nChecking - operator\n";

    Date d6("31-12-2015");
    Date d7("3-1-2016");
    try
    {
        cout<<d3<<" - "<<d2<<" = "<<d3-d2<<endl;
        cout<<d3<<" - "<<d1<<" = "<<d3-d1<<endl;
        cout<<d5<<" - "<<d2<<" = "<<d5-d2<<endl;
        cout<<d7<<" - "<<d6<<" = "<<d7-d6<<endl;
        cout<<d6<<" - "<<d7<<" = "<<d6-d7<<endl;
    }
    catch(...)
    {
        cout<<"FAILURE\n";
        cout<<"Error occurred";
    }

    cout<<"\nChecking + operator\n";

    try
    {
        cout<<d1<<" + 3 = ";
        cout<<d1+3<<endl;
    }
    catch(out_of_range e)
    {
        cout<<"FAILURE\n";
        cout<<e.what()<<"\n";
    }
    catch(domain_error e)
    {
        cout<<"FAILURE\n";
        cout<<e.what()<<"\n";
    }
    try
    {
        cout<<d2<<" + -3 = ";
        cout<<d2+(-3)<<endl;
    }
    catch(out_of_range e)
    {
        cout<<"FAILURE\n";
        cout<<e.what()<<"\n";
    }
    catch(domain_error e)
    {
        cout<<"FAILURE\n";
        cout<<e.what()<<"\n";
    }
    try
    {
        cout<<d7<<" + -10 = ";
        cout<<d7+(-10)<<endl;
    }
    catch(out_of_range e)
    {
        cout<<"FAILURE\n";
        cout<<e.what()<<"\n";
    }
    catch(domain_error e)
    {
        cout<<"FAILURE\n";
        cout<<e.what()<<"\n";
    }
    try
    {
        cout<<d6<<" + 5 = ";
        cout<<d6+5<<endl;
    }
    catch(out_of_range e)
    {
        cout<<"FAILURE\n";
        cout<<e.what()<<"\n";
    }
    catch(domain_error e)
    {
        cout<<"FAILURE\n";
        cout<<e.what()<<"\n";
    }
    try
    {
        cout<<d5<<" + 9 = ";
        cout<<d5+9<<endl;
    }
    catch(out_of_range e)
    {
        cout<<"FAILURE\n";
        cout<<e.what()<<"\n";
    }
    catch(domain_error e)
    {
        cout<<"FAILURE\n";
        cout<<e.what()<<"\n";
    }

    //Weeknumber Cast
    cout<<endl;

    try
    {
        cout<<"Weeknumber of "<<d1<<": "<<static_cast<int>((WeekNumber)d1)<<endl;
        cout<<"Weeknumber of "<<d2<<": "<<static_cast<int>((WeekNumber)d2)<<endl;
        cout<<"Weeknumber of "<<d3<<": "<<static_cast<int>((WeekNumber)d3)<<endl;
        cout<<"Weeknumber of "<<d4<<": "<<static_cast<int>((WeekNumber)d4)<<endl;
        cout<<"Weeknumber of "<<d5<<": "<<static_cast<int>((WeekNumber)d5)<<endl;
        cout<<"Weeknumber of "<<d6<<": "<<static_cast<int>((WeekNumber)d6)<<endl;
        cout<<"Weeknumber of "<<d7<<": "<<static_cast<int>((WeekNumber)d7)<<endl;
    }
    catch(...)
    {
        cout<<"FAILURE\n";
        cout<<"Error occurred";
    }

    //Month Cast
    cout<<endl;

    try
    {
        cout<<"Month of "<<d1<<": "<<static_cast<int>((Month)d1)<<endl;
        cout<<"Month of "<<d2<<": "<<static_cast<int>((Month)d2)<<endl;
        cout<<"Month of "<<d3<<": "<<static_cast<int>((Month)d3)<<endl;
        cout<<"Month of "<<d4<<": "<<static_cast<int>((Month)d4)<<endl;
        cout<<"Month of "<<d5<<": "<<static_cast<int>((Month)d5)<<endl;
        cout<<"Month of "<<d6<<": "<<static_cast<int>((Month)d6)<<endl;
        cout<<"Month of "<<d7<<": "<<static_cast<int>((Month)d7)<<endl;
    }
    catch(...)
    {
        cout<<"FAILURE\n";
        cout<<"Error occurred";
    }

    //Weekday cast
    cout<<endl;
    char *weekdays[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    Date d8("10-3-2016");
    Date d9("4-3-2016");
    Date d10("30-12-2000");
    Date d11("21-11-2005");
    try
    {
        cout<<"WeekDay of "<<d1<<": "<<weekdays[static_cast<int>((WeekDay)d1)==7?0:static_cast<int>((WeekDay)d1)]<<endl;
        cout<<"WeekDay of "<<d10<<": "<<weekdays[static_cast<int>((WeekDay)d10)==7?0:static_cast<int>((WeekDay)d10)]<<endl;
        cout<<"WeekDay of "<<d11<<": "<<weekdays[static_cast<int>((WeekDay)d11)==7?0:static_cast<int>((WeekDay)d11)]<<endl;
        cout<<"WeekDay of "<<d8<<": "<<weekdays[static_cast<int>((WeekDay)d8)==7?0:static_cast<int>((WeekDay)d8)]<<endl;
        cout<<"WeekDay of "<<d9<<": "<<weekdays[static_cast<int>((WeekDay)d9)==7?0:static_cast<int>((WeekDay)d9)]<<endl;
    }
    catch(...)
    {
        cout<<"FAILURE\n";
        cout<<"Error occurred";
    }
    //Checking for leap year
    cout<<endl;
    cout<<"Checking for leap year\n";
    try
    {
        cout<<d8<<" : ";
        if(d8.leapYear())   cout<<"Yes\n";
        else    cout<<"No\n";
        cout<<d9<<" : ";
        if(d9.leapYear())   cout<<"Yes\n";
        else    cout<<"No\n";
        cout<<d10<<" : ";
        if(d10.leapYear())   cout<<"Yes\n";
        else    cout<<"No\n";
        cout<<d11<<" : ";
        if(d11.leapYear())   cout<<"Yes\n";
        else    cout<<"No\n";
    }
    catch(...)
    {
        cout<<"FAILURE\n";
        cout<<"Error occurred";
    }

    //Binary relational operators

    try
    {
        printbinary(d8,d9);
        cout<<endl;
        printbinary(d8,d8);
        cout<<endl;
        printbinary(d10,d11);
        cout<<endl;
    }
    catch(...)
    {
        cout<<"FAILURE\n";
        cout<<"Error occurred";
    }

    //Testing I/O operators

    try
    {
        stringstream ss;
        Date d;
        char *foo=new char(20);
        ss<<d;
        ss>>foo;
        cout<<foo<<endl;
        ss.str( std::string() );
        ss.clear();
        {
            DateFormat df("d","mm","yy");
            Date::setFormat(df);
            ss<<d;
            ss>>foo;
            cout<<foo<<endl;
            ss.str( std::string() );
            ss.clear();
        }
        {
            DateFormat df("dd-mm-yyyy");
            Date::setFormat(df);
            ss<<d;
            ss>>foo;
            cout<<foo<<endl;
            ss.str( std::string() );
            ss.clear();
        }
        {
            DateFormat df("dd","mmm","yyyy");
            Date::setFormat(df);
            ss<<d;
            ss>>foo;
            cout<<foo<<endl;
            ss.str( std::string() );
            ss.clear();
        }
        {
            DateFormat df("d","mmm","yy");
            Date::setFormat(df);
            ss<<d;
            ss>>foo;
            cout<<foo<<endl;
            ss.str( std::string() );
            ss.clear();
        }
        {
            DateFormat df(NULL,"m","yyyy");
            Date::setFormat(df);
            ss<<d;
            ss>>foo;
            cout<<foo<<endl;
            ss.str( std::string() );
            ss.clear();
        }
        {
            DateFormat df("--yy");
            Date::setFormat(df);
            ss<<d;
            ss>>foo;
            cout<<foo<<endl;
            ss.str( std::string() );
            ss.clear();
        }
        {
            DateFormat df("d--yyyy");
            Date::setFormat(df);
            ss<<d;
            ss>>foo;
            cout<<foo<<endl;
            ss.str( std::string() );
            ss.clear();
        }
        delete[] foo;
    }
    catch (domain_error e)
    {
        cout<<"FAILURE\n";
        cout<<e.what()<<"\n";
    }
    catch(...)
    {
        cout<<"FAILURE\n";
        cout<<"Error occurred";
    }

    cout<<"Checking >> operator...\n";
    //Dates are put through stringstream and brought back, using << and >> operators
    try
    {
        stringstream ss;
        Date d;
        {
            DateFormat df("d-m-yyyy");
            Date::setFormat(df);
            cout<<"Input 6-3-2016:\t Output: ";
            ss<<"6-3-2016";
            ss>>d;
            cout<<d<<endl;
            ss.str(string());
            ss.clear();
        }
        {
            DateFormat df("dd-m-yyyy");
            Date::setFormat(df);
            cout<<"Input 06-3-2016:\t Output: ";
            ss<<"06-3-2016";
            ss>>d;
            cout<<d<<endl;
            ss.str(string());
            ss.clear();
        }
        {
            DateFormat df("dd-mm-yyyy");
            Date::setFormat(df);
            cout<<"Input 06-07-2016:\t Output: ";
            ss<<"06-07-2016";
            ss>>d;
            cout<<d<<endl;
            ss.str(string());
            ss.clear();
        }
        {
            DateFormat df("dd-mm-yy");
            Date::setFormat(df);
            cout<<"Input 06-07-16:\t Output: ";
            ss<<"06-07-16";
            ss>>d;
            cout<<d<<endl;
            ss.str(string());
            ss.clear();
        }
    }
    catch (domain_error e)
    {
        cout<<"FAILURE\n";
        cout<<e.what()<<"\n";
    }
    catch(...)
    {
        cout<<"FAILURE\n";
        cout<<"Error occurred";
    }
}

int main()
{
    //Taking output in a text file
    //freopen("testreport.txt","w",stdout);
    try
    {
        //Setting d-m-yyyy to be initial DateFormat for convenience
        DateFormat df("d-m-yyyy");
        Date::setFormat(df);
        //Function to test different DateFormat methods
        Test_DateFormat();
        //Function to test different Date methods
        Test_Date();
    }
    catch(...)
    {
        cout<<"Some unknown error occurred\n";
    }
}
