//
//  Utils.hpp
//  ggj-jzb
//
//  Created by jzb on 16/1/29.
//
//

#ifndef Utils_hpp
#define Utils_hpp

#include "cocos2d.h"

class Utils
{
public:
    static int integerFromMap(const cocos2d::ValueMapIntKey& map, int key);
    static int integerFromMap(const cocos2d::ValueMap& map, const std::string& key);
    static float floatFromMap(const cocos2d::ValueMapIntKey& map, int key);
    static float floatFromMap(const cocos2d::ValueMap& map, const std::string& key);
    static double doubleFromMap(const cocos2d::ValueMapIntKey& map, int key);
    static double doubleFromMap(const cocos2d::ValueMap& map, const std::string& key);
    static bool boolFromMap(const cocos2d::ValueMapIntKey& map, int key);
    static bool boolFromMap(const cocos2d::ValueMap& map, const std::string& key);
    static void stdStringFromMap(const cocos2d::ValueMapIntKey& map, int key, std::string& str);
    static void stdStringFromMap(const cocos2d::ValueMap& map, const std::string& key, std::string& str);
    static cocos2d::Value valueFromMap(const cocos2d::ValueMapIntKey& map, int key);
    static cocos2d::Value valueFromMap(const cocos2d::ValueMap& map, const std::string& key);
    static void mapFromMap(const cocos2d::ValueMapIntKey& sourceMap, int key, cocos2d::ValueMap& valueMap);
    static void mapFromMap(const cocos2d::ValueMap& sourceMap, const std::string& key, cocos2d::ValueMap& valueMap);
    static void vectorFromMap(const cocos2d::ValueMapIntKey& map, int key, cocos2d::ValueVector& valueMap);
    static void vectorFromMap(const cocos2d::ValueMap& map, const std::string& key, cocos2d::ValueVector& valueVector);
    
    static void split(const std::string& src, const std::string& token, std::vector<std::string>& vect);
};

#endif /* Utils_hpp */
