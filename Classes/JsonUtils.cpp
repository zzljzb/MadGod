//
//  JsonUtils.cpp
//  IsLand
//
//  Created by jzb on 16/1/16.
//
//

#include "JsonUtils.hpp"
#include "json/writer.h"
#include "json/prettywriter.h"
#include <fstream>

USING_NS_CC;
using namespace std;

JsonUtils::JsonUtils()
{
    //do nothing
}

JsonUtils::~JsonUtils()
{
    //do nothing
}

ValueMap JsonUtils::valueMapFromJsonStr(const string& str)
{
    ValueMap ret;
    
    rapidjson::Document doc;
    doc.Parse<0>(str.c_str());
    if (doc.HasParseError())
    {
        CCLOG("invalid json str");
        return ret;
    }
    
    if (!doc.IsObject())
    {
        CCLOG("invalid document");
        return ret;
    }
    
    for (auto iter = doc.MemberBegin(); iter != doc.MemberEnd(); ++iter)
    {
        auto key = (iter->name).GetString();
        auto val = JsonUtils::getValueFromRJValue(doc[key]);
        ret.insert(pair<string, Value>(key, val));
    }
    
    return ret;
}

ValueMap JsonUtils::valueMapFromJsonFile(const string& filename)
{
    auto jsonStr = FileUtils::getInstance()->getStringFromFile(filename);
    return JsonUtils::valueMapFromJsonStr(jsonStr);
}

string JsonUtils::jsonStrFromValueMap(const ValueMap& valueMap)
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    
    rapidjson::Value mapVal = JsonUtils::getRJValueFromValueMap(valueMap, allocator);
    for (auto iter = mapVal.MemberBegin(); iter != mapVal.MemberEnd(); ++iter)
    {
        document.AddMember((iter->name), iter->value, allocator);
    }
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    return buffer.GetString();
 }

void JsonUtils::writeValueMapToFile(const ValueMap& valueMap, const string& filePath)
{
    string jsonStr = JsonUtils::jsonStrFromValueMap(valueMap);
    JsonUtils::writeJsonStrToFile(jsonStr, filePath);
}

ValueVector JsonUtils::valueVectorFromJsonStr(const string& str)
{
    ValueVector ret;
    
    rapidjson::Document doc;
    doc.Parse<0>(str.c_str());
    if (doc.HasParseError())
    {
        CCLOG("invalid json str");
        return ret;
    }
    
    if (!doc.IsArray())
    {
        CCLOG("invalid document");
        return ret;
    }
    
    for (auto i = 0; i < doc.Size(); ++i)
    {
        auto val = JsonUtils::getValueFromRJValue(doc[i]);
        ret.push_back(Value(val));
    }
    
    return ret;
}

ValueVector JsonUtils::valueVectorFromJsonFile(const string& filename)
{
    auto jsonStr = FileUtils::getInstance()->getStringFromFile(filename);
    return JsonUtils::valueVectorFromJsonStr(jsonStr);
}

string JsonUtils::jsonStrFromValueVector(const ValueVector& valueVector)
{
    rapidjson::Document document;
    document.SetArray();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    
    rapidjson::Value vectorVal = JsonUtils::getRJValueFromValueVector(valueVector, allocator);
    for (auto i = 0; i < vectorVal.Size(); ++i)
    {
        document.PushBack(vectorVal[i], allocator);
    }
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    return buffer.GetString();
}

void JsonUtils::writeValueVectorToFile(const ValueVector& valueVector, const string& filename)
{
    string jsonStr = JsonUtils::jsonStrFromValueVector(valueVector);
    JsonUtils::writeJsonStrToFile(jsonStr, filename);
}

Value JsonUtils::getValueFromRJValue(const rapidjson::Value& val)
{
    Value ret;
    if (val.IsBool())
    {
        ret = Value(val.GetBool());
    }
    else if (val.IsDouble())
    {
        ret = Value(val.GetDouble());
    }
    else if (val.IsInt())
    {
        ret = Value(val.GetInt());
    }
    else if (val.IsString())
    {
        ret = Value(val.GetString());
    }
    else if (val.IsArray())
    {
        ValueVector tempVec;
        for (auto i = 0; i < val.Size(); ++i)
        {
            auto vecItem = JsonUtils::getValueFromRJValue(val[i]);
            tempVec.push_back(vecItem);
        }
        ret = tempVec;
    }
    else if (val.IsObject())
    {
        ValueMap tempMap;
        for (auto iter = val.MemberBegin(); iter != val.MemberEnd(); ++iter)
        {
            auto key = (iter->name).GetString();
            auto itemVal = JsonUtils::getValueFromRJValue(val[key]);
            tempMap.insert(pair<string, Value>(key, itemVal));
        }
        ret = tempMap;
    }
    else
    {
        //do nothing
    }
    return ret;
}

rapidjson::Value JsonUtils::getRJValueFromValueMap(const ValueMap& map, rapidjson::Document::AllocatorType& allocator)
{
    rapidjson::Value ret(rapidjson::kObjectType);
    for (auto item : map)
    {
        string key = item.first;
        rapidjson::Value keyVal = rapidjson::Value(key.c_str(), allocator);
        Value val = item.second;
        Value::Type type = val.getType();
        if (type == Value::Type::MAP)
        {
            ret.AddMember(keyVal, JsonUtils::getRJValueFromValueMap(val.asValueMap(), allocator), allocator);
        }
        else if(type == Value::Type::VECTOR)
        {
            ret.AddMember(keyVal, JsonUtils::getRJValueFromValueVector(val.asValueVector(), allocator), allocator);
        }
        else if (type == Value::Type::STRING)
        {
            ret.AddMember(keyVal, rapidjson::Value(val.asString().c_str(), allocator), allocator);
        }
        else if (type == Value::Type::BOOLEAN)
        {
            ret.AddMember(keyVal, val.asBool(), allocator);
        }
        else if (type == Value::Type::DOUBLE)
        {
            ret.AddMember(keyVal, val.asDouble(), allocator);
        }
        else if (type == Value::Type::FLOAT)
        {
            ret.AddMember(keyVal, val.asFloat(), allocator);
        }
        else if (type == Value::Type::INTEGER)
        {
            ret.AddMember(keyVal, val.asInt(), allocator);
        }
        else
        {
            //do nothing
        }
    }
    return ret;
}

rapidjson::Value JsonUtils::getRJValueFromValueVector(const ValueVector& vector, rapidjson::Document::AllocatorType& allocator)
{
    rapidjson::Value ret(rapidjson::kArrayType);
    for (auto val : vector)
    {
        Value::Type type = val.getType();
        if (type == Value::Type::MAP)
        {
            ret.PushBack(JsonUtils::getRJValueFromValueMap(val.asValueMap(), allocator), allocator);
        }
        else if(type == Value::Type::VECTOR)
        {
            ret.PushBack(JsonUtils::getRJValueFromValueVector(val.asValueVector(), allocator), allocator);
        }
        else if (type == Value::Type::STRING)
        {
            ret.PushBack(rapidjson::Value(val.asString().c_str(), allocator), allocator);
        }
        else if (type == Value::Type::BOOLEAN)
        {
            ret.PushBack(val.asBool(), allocator);
        }
        else if (type == Value::Type::DOUBLE)
        {
            ret.PushBack(val.asDouble(), allocator);
        }
        else if (type == Value::Type::FLOAT)
        {
            ret.PushBack(val.asFloat(), allocator);
        }
        else if (type == Value::Type::INTEGER)
        {
            ret.PushBack(val.asInt(), allocator);
        }
        else
        {
            //do nothing
        }
    }
    return ret;
}

void JsonUtils::writeJsonStrToFile(const string& jsonStr, const string& filename)
{
    std::ofstream file(filename.c_str(), std::ofstream::out);
    if (file.is_open())
    {
        file << jsonStr << std::endl;
        if (file.bad() || file.fail())
        {
            CCAssert(false, "Write data to json file failed!");
        }
        else
        {
            file.close();
        }
    }
    else
    {
        CCLOG("Open json file faild!");
    }
}
