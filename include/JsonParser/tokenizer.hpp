#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

namespace json
{
    using namespace std;

    enum TokenState
    {
        PARSE_DEFAULT,
        PARSE_STRING,
        PARSE_NUMBER,
        PARSE_BOOL
    };

    enum TokenType
    {
        LEFT_BRACE,
        RIGHT_BRACE,
        LEFT_BRACKET,
        RIGHT_BRACKET,
        STRING,
        COLON,
        COMMA,
        NUMBER,
        BOOL
    };

    struct Token
    {
        TokenType Type;
    };

    struct StringToken : public Token
    {
        string Str;

        StringToken();

        void Append(char c);
    };

    struct NumberToken : public Token
    {
        double Number;

        NumberToken();

        void Append(char c);
        double GetNum();

    private:
        int _decimalCount = 0;
    };

    struct BoolToken : public Token
    {
        BoolToken();

        void Append(char c);
        bool GetBool();

    private:
        string _str;
    };

    vector<Token*>& tokenize(string path);
}
