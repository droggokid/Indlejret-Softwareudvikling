#include <string>

class SmartString
{
public:
    SmartString(std::string *str);
    ~SmartString();
    std::string *get();
    std::string *operator->();
    std::string &operator*();

private:
    SmartString(const SmartString &other);
    SmartString &operator=(const SmartString &other);
    std::string *str_;
};