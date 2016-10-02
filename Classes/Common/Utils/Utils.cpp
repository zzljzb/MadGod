//
//  Utils.cpp
//  ggj-jzb
//
//  Created by jzb on 16/1/29.
//
//

#include "Utils.hpp"

using namespace std;
USING_NS_CC;

Value Utils::valueFromMap(const ValueMapIntKey& map, int key)
{
    CCAssert(map.find(key) != map.end(), "invalid key");
    Value ret = map.at(key);
    CCAssert(!ret.isNull(), "value invalid");
    return ret;
}

Value Utils::valueFromMap(const ValueMap &map, const string &key)
{
    CCAssert(map.find(key) != map.end(), "invalid key");
    Value ret = map.at(key);
    CCAssert(!ret.isNull(), "value invalid");
    return ret;
}

int Utils::integerFromMap(const ValueMapIntKey& map, int key)
{
    return valueFromMap(map, key).asInt();
}

int Utils::integerFromMap(const ValueMap &map, const string &key)
{
    return valueFromMap(map, key).asInt();
}

float Utils::floatFromMap(const ValueMapIntKey& map, int key)
{
    return valueFromMap(map, key).asFloat();
}

float Utils::floatFromMap(const ValueMap &map, const string &key)
{
    return valueFromMap(map, key).asFloat();
}

double Utils::doubleFromMap(const ValueMapIntKey& map, int key)
{
    return valueFromMap(map, key).asDouble();
}

double Utils::doubleFromMap(const ValueMap &map, const string &key)
{
    return valueFromMap(map, key).asDouble();
}

bool Utils::boolFromMap(const ValueMapIntKey& map, int key)
{
    return valueFromMap(map, key).asBool();
}

bool Utils::boolFromMap(const ValueMap &map, const string &key)
{
    return valueFromMap(map, key).asBool();
}

void Utils::stdStringFromMap(const ValueMapIntKey &map, int key, string& str)
{
    str = valueFromMap(map, key).asString();
}

void Utils::stdStringFromMap(const ValueMap &map, const string &key, string& str)
{
    str = valueFromMap(map, key).asString();
}

void Utils::mapFromMap(const ValueMapIntKey &sourceMap, int key, ValueMap& valueMap)
{
    valueMap = valueFromMap(sourceMap, key).asValueMap();
}

void Utils::mapFromMap(const ValueMap &sourceMap, const string &key, ValueMap& valueMap)
{
    valueMap = valueFromMap(sourceMap, key).asValueMap();
}

void Utils::vectorFromMap(const ValueMapIntKey &map, int key, ValueVector& valueVector)
{
    valueVector = valueFromMap(map, key).asValueVector();
}

void Utils::vectorFromMap(const ValueMap &map, const string &key, ValueVector& valueVector)
{
    valueVector = valueFromMap(map, key).asValueVector();
}

void Utils::split(const string& src, const string& token, vector<string>& vect)
{
    size_t end = 0;
    size_t begin = 0;
    while(end != -1)
    {
        end = src.find(token, begin);
        
        if (begin == end)
        {
            begin++;
            end++;
            continue;
        }
        
        if(end == -1)
        {
            vect.push_back(src.substr(begin, src.length()-begin));
        }
        else
        {
            vect.push_back(src.substr(begin, end-begin));
        }
        
        begin = end + token.length();
    }
}
