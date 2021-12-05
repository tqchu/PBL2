#include <iostream>
#include <exception>
using namespace std;
class custom_exception : public exception
{
    protected: 
    string field;
    public:
        custom_exception(string field) : field(field){};
        virtual const string get_info() const = 0;
};
// số phải dương
class nonPositive_number:public custom_exception{

public:
    nonPositive_number(const string field) : custom_exception(field){};
    const string get_info() const
    {
        return field + " phai la so duong!";
    }
};
// số âm
class negative_number : public custom_exception
{

public:
    negative_number(const string field) : custom_exception(field){};
    const string get_info() const
    {
        return field + " khong the la so am!";
    }
};
// sai định dạng
class invalid_input : public custom_exception
{
    string format;

public:
    invalid_input(const string field,const string format) : custom_exception(field),format(format){};
    invalid_input(const string field) : custom_exception(field) { format = ""; };
    const string get_info() const
    {
        return "Sai dinh dang " + field + (format != "" ? " (" +format +")": "") + "!";
    }
};


