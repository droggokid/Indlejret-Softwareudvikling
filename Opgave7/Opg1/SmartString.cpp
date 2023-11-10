#include "SmartString.hpp"

SmartString::SmartString(std::string *str)
    : str_(str)
{
}

SmartString::~SmartString()
{
    delete str_;
}

std::string *SmartString::get()
{
    return str_;
}

SmartString::SmartString(const SmartString &other)
{
}

SmartString &SmartString::operator=(const SmartString &other)
{
}

std::string *SmartString::operator->()
{
    return str_;
}

std::string &SmartString::operator*()
{
    return *str_;
}
