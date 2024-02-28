#pragma once

#include <unordered_map>
#include <stack>

#include "tokenizer.hpp"

namespace json
{
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
        virtual string GetAsString();
        virtual unordered_map<string, JsonElement*>& GetAsObject();
        virtual vector<JsonElement*>& GetAsArray();
    };

    class JsonNumber : public JsonElement
    {
    public:
        JsonNumber(double value);

        virtual double& GetAsNumber() override;
        virtual string GetAsString() override;

    private:
        double _value;
    };

    class JsonBool : public JsonElement
    {
    public:
        JsonBool(bool value);

        virtual bool& GetAsBool() override;
        virtual string GetAsString() override;

    private:
        bool _value;
    };

    class JsonString : public JsonElement
    {
    public:
        JsonString(string value);

        virtual string GetAsString() override;

    private:
        string _value;
    };

    class JsonObject : public JsonElement
    {
    public:
        JsonObject();

        void Add(string key, JsonElement* value);

        virtual unordered_map<string, JsonElement*>& GetAsObject() override;
        virtual string GetAsString() override;
    private:
        unordered_map<string, JsonElement*> _value;
    };

    class JsonArray : public JsonElement
    {
    public:
        JsonArray();

        void Add(JsonElement* value);

        virtual vector<JsonElement*>& GetAsArray() override;
        virtual string GetAsString() override;

    private:
        vector<JsonElement*> _value{};
    };

    JsonElement* parse(string path);
}