//
// Created by ortur on 01.04.2022.
//

#ifndef DSL_TOKEN_H
#define DSL_TOKEN_H

#include <unordered_map>
#include <vector>
#include <string_view>
#include <regex>

#include <boost/regex.hpp>


struct Token {

    // ТЕРМИНАЛЫ
    enum class Type {
        VAR_KEYWORD,
        TRUE_KEYWORD,
        FALSE_KEYWORD,



        ADD_OPERATOR,
        SUB_OPERATOR,
        MUL_OPERATOR,
        DIV_OPERATOR,
        MOD_OPERATOR,
        DOT_OPERATOR,

        GTOE_OPERATOR,  // >=
        GT_OPERATOR,    // >
        LT_OPERATOR,    // <
        LTOE_OPERATOR,  // <=
        EQ_OPERATOR,    // ==
        NEQ_OPERATOR,   // !=
        AND_OPERATOR,   // &&
        OR_OPERATOR,    // ||


        //NEW_OPERATOR,
        GET_OPERATOR,
        IS_VALID_OPERATOR,
        HAS_NEXT_OPERATOR,
        HAS_PREV_OPERATOR,
        INSERT_AFTER_OPERATOR,
        INSERT_BEFORE_OPERATOR,
        ERASE_OPERATOR,




        ASSIGN_OPERATOR,

        /*CURLY_OPEN_BRACE,
        CURLY_CLOSE_BRACE,
         */
        OPEN_PARENTHESIS,
        CLOSE_PARENTHESIS,
        //OPEN_SQUARE_BRACE,
        //CLOSE_SQUARE_BRACE,

        NUMBER_CONSTANT,
        STRING_CONSTANT,
        IDENTIFIER,

        ENDLINE,
        SPACE,
        TAB,

        COMMA,
        SEMICOLON,
        UNDEFINED,


        VAR_NAME,

        BASIC_INT,
        BASIC_STRING,
        BASIC_BOOL,
        BASIC_LINKED_LIST,
        BASIC_ITERATOR,

    };

    explicit Token(Type type, std::string_view value = "")
        : type(type), value(std::string(value)){};


    const std::string value;
    Type type;
    int line_number;
};



const std::regex IDENTIFIER_REGEX       ( R"([a-zA-Z_]+)");
const std::regex STRING_CONSTANT_REGEX  ( R"("(\\.|[^\\"])*")" );
//const std::regex STRING_CONSTANT_REGEX  ( R"("(?:\\\\.|\\\\\\n|[^\"\\\\\\n])*")" );
const std::regex NUMBER_CONSTANT_REGEX  ( R"([-]?\d+)"        );


const std::unordered_map<std::string_view, Token::Type> KEYWORDS = {
        //{"for",         Token::Type::FOR_KEYWORD},
        //{"while",       Token::Type::WHILE_KEYWORD},
        //{"if",          Token::Type::IF_KEYWORD},
        //{"else",        Token::Type::ELSE_KEYWORD},
        //{"load",        Token::Type::LOAD_KEYWORD},
        //{"return",      Token::Type::RETURN_KEYWORD},
        //{"do",          Token::Type::DO_KEYWORD},
        //{"struct",      Token::Type::STRUCT_KEYWORD},
        //{"func",        Token::Type::FUNC_KEYWORD},
        //{"field",       Token::Type::FIELD_KEYWORD},
        {"var",         Token::Type::VAR_KEYWORD},
        {"True",        Token::Type::TRUE_KEYWORD},
        {"False",       Token::Type::FALSE_KEYWORD},
};





const std::unordered_map<std::string_view, Token::Type> OPERATORS = {
        {"+", Token::Type::ADD_OPERATOR},
        {"-", Token::Type::SUB_OPERATOR},
        {"*", Token::Type::MUL_OPERATOR},
        {"/", Token::Type::DIV_OPERATOR},
        {"%", Token::Type::MOD_OPERATOR},
        {".", Token::Type::DOT_OPERATOR},

        {"<",  Token::Type::LT_OPERATOR},
        {"<=", Token::Type::LTOE_OPERATOR},
        {">",  Token::Type::GT_OPERATOR},
        {">=", Token::Type::GTOE_OPERATOR},
        {"==", Token::Type::EQ_OPERATOR},
        {"!=", Token::Type::NEQ_OPERATOR},
        {"&&", Token::Type::AND_OPERATOR},
        {"||", Token::Type::OR_OPERATOR},

        //{"New",   Token::Type::NEW_OPERATOR},
        {"Erase", Token::Type::ERASE_OPERATOR},
        {"InsertBefore", Token::Type::INSERT_BEFORE_OPERATOR},
        {"InsertAfter", Token::Type::INSERT_AFTER_OPERATOR},
        {"HasPrev", Token::Type::HAS_PREV_OPERATOR},
        {"HasNext", Token::Type::HAS_NEXT_OPERATOR},
        {"IsValid", Token::Type::IS_VALID_OPERATOR},
        {"Get", Token::Type::GET_OPERATOR},
};

const std::unordered_map<std::string_view, Token::Type> BASIC_DATA_TYPES = {
        {"Int", Token::Type::BASIC_INT},
        {"String", Token::Type::BASIC_STRING},
        {"Bool", Token::Type::BASIC_BOOL},
        {"LinkedList", Token::Type::BASIC_LINKED_LIST},
        {"Iterator", Token::Type::BASIC_ITERATOR},
};

const std::unordered_map<std::string_view, Token::Type> ASSIGN_OPERATOR = {
        {"=",  Token::Type::ASSIGN_OPERATOR},
       //{"+=", Token::Type::ASSIGN_OPERATOR},
       //{"-=", Token::Type::ASSIGN_OPERATOR},
       //{"*=", Token::Type::ASSIGN_OPERATOR},
       //{"/=", Token::Type::ASSIGN_OPERATOR},
       //{"%=", Token::Type::ASSIGN_OPERATOR},
};

const std::unordered_map<std::string_view, Token::Type> BRACES = {
        {"(",  Token::Type::OPEN_PARENTHESIS},
        {")",  Token::Type::CLOSE_PARENTHESIS},
        //{"{",  Token::Type::CURLY_OPEN_BRACE},
        //{"}",  Token::Type::CURLY_CLOSE_BRACE},
        //{"[",  Token::Type::OPEN_SQUARE_BRACE},
        //{"]",  Token::Type::CLOSE_SQUARE_BRACE},
};

const std::unordered_map<std::string_view, Token::Type> SEPARATORS = {
        {" ",  Token::Type::SPACE},
        {"\t", Token::Type::TAB},
        {"\n", Token::Type::ENDLINE},
        {";",  Token::Type::SEMICOLON},
        {",",  Token::Type::COMMA},
};


bool IsKeyword(const std::string_view& lexem);
bool IsOperator(const std::string_view& lexem);
bool IsAssignOperator(const std::string_view& lexem);
bool IsBrace(const std::string_view& lexem);
bool IsSeparator(const std::string_view& lexem);
bool IsIdentifier(const std::string_view& lexem);
bool IsStringConstant(const std::string_view& lexem);
bool IsNumberConstant(const std::string_view& lexem);
bool IsBasicDataType(const std::string_view& lexem);

std::optional<Token::Type> GetTokenType(std::string_view lexem);
std::optional<Token> GetNextToken(std::string_view& text);


class TokenStream {
public:


    explicit TokenStream(const std::vector<Token>& token_sequence);
    explicit TokenStream(std::vector<Token>&& token_sequence);

    TokenStream(TokenStream&&) = default;
    TokenStream(const TokenStream&) = delete;
    TokenStream& operator=(const TokenStream&) = delete;


    Token& GetCurrentToken();
    const Token& GetCurrentToken() const;

    bool HasNext() const;
    bool HasCurrent() const;


    const Token& GetNextToken() const;
    Token& GetNextToken();

    void MoveToNextToken();
    void MoveToPrevToken();

    const auto begin() const {
        return tokens_.begin();
    }

    const auto end() const {
        return tokens_.end();
    }
private:
    std::vector<Token> tokens_;
    size_t curr_idx = 0;
};

std::vector<Token> SplitIntoTokens(std::string_view text);



#endif //DSL_TOKEN_H
