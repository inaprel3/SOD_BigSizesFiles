// СОД_ФайлиВеликогоРозміру.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <iostream>
#include <fstream>
#include <windows.h>
#include <set>
#include <map>
#include <iomanip>
#include <json-develop/single_include/nlohmann/json.hpp>
using json = nlohmann::json;
void controller();
void first();
void second();
void third();
void four();
void fifth();
void sixth();
char* calculateBuffer(unsigned long long& bufferSize, int& pairs);
json* jsonObjects;
int count = 0;
int bs = 0;
int main()
{
    std::cout << "First\n\n\r";
    first();
    std::cout << "\n\nSecond\n\r";
    second();
    std::cout << "\n\nThird\n\r";
    third();
    std::cout << "\n\nFour\n\r";
    four();
    std::cout << "\n\nFifth\n\r";
    fifth();
    std::cout << "\n\nSixth\n\r";
    sixth();
    return 0;
}
void controller()
{
    std::cout << "1,2,3,4,5,6\n";
    int choice;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        first();
        break;
    case 2:
        second();
        break;
    case 3:
        third();
        break;
    case 4:
        four();
        break;
    case 5:
        fifth();
        break;
    case 6:
        sixth();
        break;
    default:
        break;
    }
}
void first()
{
    char* buffer;
    unsigned long long bufferSize = 0;
    int pairs = 0;
    buffer = calculateBuffer(bufferSize, pairs);
    std::string currentJSON;
    pairs = 0;
    int index = 0;
    bool isScobka = false;
    for (int index = 0; index <= bufferSize; ++index)
    {
        if (buffer[index] == '\"')
        {
            if ((buffer[index - 1] == ' ' && buffer[index - 1] != '{') && !isScobka)
            {
                isScobka = true;
            }
            else if (((buffer[index + 1] == ' ' && (buffer[index + 2] == '}' || buffer[index + 2] == ':')) ||
                (buffer[index + 1] == ',' && buffer[index + 2] == ' ')) && isScobka)
            {
                isScobka = false;
            }
        }
        if (!isScobka)
        {
            if (buffer[index] == '{')
            {
                ++pairs;
            }
            else if (buffer[index] == '}')
            {
                --pairs;
                if (pairs < 0)
                {
                    pairs = 0;
                }
                if (pairs == 0)
                {
                    ++count;
                }
            }
        }
    }
    jsonObjects = new json[count];
    std::cout << count;
}
void second()
{
    char* buffer;
    unsigned long long bufferSize = 0;
    int pairs = 0;
    buffer = calculateBuffer(bufferSize, pairs);
    json jsonObject;
    char* currentJSON = new char[100000];
    std::set<std::string> senders;
    std::string sender;
    pairs = 0;
    int i = 0;
    int index = 0;
    bool isScobka = false;
    int sCount = 0;
    for (int index = 0, index2 = 0; index < bufferSize && i < count; ++index)
    {
        currentJSON[index2++] = buffer[index];
        if (buffer[index] == '\"')
        {
            ++sCount;
            if ((buffer[index - 1] == ' ' && buffer[index - 1] != '{') && !isScobka)
            {
                isScobka = true;
            }
            else if (((buffer[index + 1] == ' ' && (buffer[index + 2] == '}' || buffer[index + 2] == ':')) ||
                (buffer[index + 1] == ',' && buffer[index + 2] == ' ')) && isScobka)
            {
                isScobka = false;
                sCount = 0;
            }
        }
        if (!isScobka)
        {
            if (buffer[index] == '{')
            {
                ++pairs;
            }
            else if (buffer[index] == '}')
            {
                --pairs;
                if (pairs < 0)
                {
                    pairs = 0;
                }
                if (pairs == 0)
                {
                    currentJSON[index2] = '\0';
                    jsonObjects[i] = json::parse(currentJSON);
                    sender = jsonObjects[i]["headers"]["From"];
                    senders.insert(sender);
                    ++index;
                    ++i;
                    index2 = 0;
                    continue;
                }
            }
        }
    }
    std::cout << senders.size();
}
void third()
{
    int pairs = 0;
    char* buffer;
    unsigned long long bufferSize = 0;
    std::string search = "ebass@enron.com";
    std::map<std::string, int> daysOfWeek;
    std::string strg;
    std::string strg1;
    bool isEmail = true;
    int index = 0;
    pairs = 0;
    int i = 0;
    bool isScobka = false;
    int sCount = 0;
    std::string currentJSON;
    json jsonObject;
    try
    {
        for (int index = 0, length = count; index < length; ++index)
        {
            if (!(jsonObjects[index])["headers"]["To"].is_null() &&
                !(jsonObjects[index])["headers"]["Date"].is_null())
            {
                std::string sender = (jsonObjects[index])["headers"]["To"];
                if (sender.compare(search) == 0 && sender.length() == search.length())
                {
                    strg = (jsonObjects[index])["headers"]["Date"];
                    strg1 += strg[0];
                    strg1 += strg[1];
                    strg1 += strg[2];
                    ++daysOfWeek[strg1];
                    strg.clear();
                    strg1.clear();;
                }
            }
        }
    }
    catch (json::exception ex)
    {
        std::cout << ex.what() << std::endl;
    }
    for (std::map<std::string, int>::iterator itr = daysOfWeek.begin();
        itr != daysOfWeek.end(); itr++)
    {
        std::cout << itr->first << '\t' << itr->second << std::endl;
    }
}
void four() {
    std::string search1 = "Shanna Husser", search2 = "Eric Bass";
    std::string currentJSON;
    std::string sender;
    std::string to;
    std::map<std::string, int> messages;
    for (int index = 0, length = count; index < length; ++index)
    {
        if (!(jsonObjects[index])["headers"]["X-To"].is_null() &&
            !(jsonObjects[index])["headers"]["X-From"].is_null())
        {
            sender = jsonObjects[index]["headers"]["X-From"];
            to = jsonObjects[index]["headers"]["X-To"];
            if ((search1.compare(sender) == 0 && search2.compare(to) == 0) ||
                (search2.compare(sender) == 0 && search1.compare(to) == 0))
                ++messages[sender];
        }
    }
    for (std::map<std::string, int>::iterator itr = messages.begin(); itr != messages.end(); itr++)
    {
        std::cout << itr->first << '\t' << itr->second << std::endl;
    }
}
void fifth()
{
    std::string search = "Laurie Ellis";
    std::string strg;
    std::string strg1;
    std::map<std::string, int> subjects;
    bool isEmail = true;
    for (int index = 0, length = count; index < length; ++index)
    {
        if (!(jsonObjects[index])["headers"]["X-To"].is_null() &&
            !(jsonObjects[index])["headers"]["X-From"].is_null())
        {
            std::string sender = (jsonObjects[index])["headers"]["X-From"];
            if (search.find(sender) != std::string::npos)
            {
                strg = (jsonObjects[index])["headers"]["Date"];
                strg1 += strg[12];
                strg1 += strg[13];
                strg1 += strg[14];
                strg1 += strg[15];
                if (strg1 == "2000")
                {
                    std::string sender1 = (jsonObjects[index])["headers"]["Subject"];
                    ++subjects[sender1];
                }
                strg.clear();
                strg1.clear();
            }
        }
        isEmail = true;
    }
    for (std::map<std::string, int>::iterator itr = subjects.begin(); itr != subjects.end(); itr++)
    {
        std::cout << itr->first << '\t' << itr->second << std::endl;
    }
}
void sixth()
{
    std::map<std::string, int> daysOfWeek;
    std::string strg;
    std::string strg1;
    for (int index = 0, length = count; index < length; ++index)
    {
        strg = ((jsonObjects[index]))["headers"]["Date"];
        strg1 += strg[0];
        strg1 += strg[1];
        strg1 += strg[2];
        ++daysOfWeek[strg1];
        strg.clear();
        strg1.clear();
    }
    std::map<std::string, int>::iterator biggest = daysOfWeek.begin();
    for (std::map<std::string, int>::iterator itr = ++daysOfWeek.begin(); itr != daysOfWeek.end(); itr++)
    {
        if (biggest->second < itr->second)
        {
            biggest = itr;
        }
    }
    std::cout << biggest->first << '\t' << biggest->second << '\t';
}
int findSize(std::ifstream& ist)
{
    ist.seekg(0, std::ios::end);
    int size = ist.tellg();
    ist.seekg(0, std::ios::beg);
    return size;
}
char* calculateBuffer(unsigned long long& bufferSize, int& pairs)
{
    std::ifstream ist("mails.json");
    bufferSize = findSize(ist);
    char* buffer = new char[bufferSize];
    ist.read(buffer, bufferSize);
    buffer[bufferSize] = 0;
    return buffer;
}
