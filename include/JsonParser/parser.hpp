#pragma once

#include <unordered_map>
#include <stack>

#include "tokenizer.hpp"

namespace json
{
    class JsonElement;
    
    typedef vector<JsonElement*> Array;
    typedef unordered_map<string, JsonElement*> Object;

    enum JsonType
    {
        JSON_OBJECT,
        JSON_ARRAY,
        JSON_NUMBER,
        JSON_BOOL,
        JSON_STRING
    };

    class JsonElement
    {
    public:
        JsonElement(JsonType type);

        JsonType Type;

        virtual double& GetAsNumber();
        virtual bool& GetAsBool();
        virtual string& GetAsString();
        virtual Object& GetAsObject();
        virtual Array& GetAsArray();

        template<typename T>
        T& Get();
    };

    class JsonNumber : public JsonElement
    {
    public:
        JsonNumber(double value);

        virtual double& GetAsNumber() override;
        virtual string& GetAsString() override;

    private:
        double _value;
        string _str;
    };

    class JsonBool : public JsonElement
    {
    public:
        JsonBool(bool value);

        virtual bool& GetAsBool() override;
        virtual string& GetAsString() override;

    private:
        bool _value;
    };

    class JsonString : public JsonElement
    {
    public:
        JsonString(string value);

        virtual string& GetAsString() override;

    private:
        string _value;
    };

    class JsonObject : public JsonElement
    {
    public:
        JsonObject();

        void Add(string key, JsonElement* value);

        virtual Object& GetAsObject() override;
        virtual string& GetAsString() override;
    private:
        Object _value;
    };

    class JsonArray : public JsonElement
    {
    public:
        JsonArray();

        void Add(JsonElement* value);

        virtual Array& GetAsArray() override;
        virtual string& GetAsString() override;

    private:
        Array _value{};
    };

    JsonElement* parse(string path);
}