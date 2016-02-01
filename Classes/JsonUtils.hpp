//
//  JsonUtils.hpp
//  IsLand
//
//  Created by jzb on 16/1/16.
//
//

#ifndef JsonUtils_hpp
#define JsonUtils_hpp

#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/Document.h"

class JsonUtils
{
public:
    static cocos2d::ValueMap valueMapFromJsonStr(const std::string& str);
    static cocos2d::ValueMap valueMapFromJsonFile(const std::string& filename);
    static std::string jsonStrFromValueMap(const cocos2d::ValueMap& valueMap);
    static void writeValueMapToFile(const cocos2d::ValueMap& valueMap, const std::string& filePath);
    
    static cocos2d::ValueVector valueVectorFromJsonStr(const std::string& str);
    static cocos2d::ValueVector valueVectorFromJsonFile(const std::string& filename);
    static std::string jsonStrFromValueVector(const cocos2d::ValueVector& valueVector);
    static void writeValueVectorToFile(const cocos2d::ValueVector& valueVector, const std::string& filename);
    
    static cocos2d::Value getValueFromRJValue(const rapidjson::Value& val);
    static rapidjson::Value getRJValueFromValueMap(const cocos2d::ValueMap& map, rapidjson::Document::AllocatorType& allocator);
    static rapidjson::Value getRJValueFromValueVector(const cocos2d::ValueVector& vector, rapidjson::Document::AllocatorType& allocator);
    
    static void writeJsonStrToFile(const std::string& jsonStr, const std::string& filename);
    
private:
    JsonUtils();
    ~JsonUtils();
};

#endif /* JsonUtils_hpp */
