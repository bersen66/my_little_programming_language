#include "token.h"
#include <vector>
#include <unordered_map>
#include <string_view>
#include <regex>
#include <string>
#include <iostream>

#include <boost/regex.hpp>



bool IsKeyword(const std::string_view &lexem) {
    return KEYWORDS.contains(lexem);
}

bool IsOperator(const std::string_view &lexem) {
    return OPERATORS.contains(lexem);
}

bool IsAssignOperator(const std::string_view &lexem) {
    return ASSIGN_OPERATOR.contains(lexem);
}

bool IsBrace(const std::string_view &lexem) {
    return BRACES.contains(lexem);
}

bool IsSeparator(const std::string_view &lexem) {
    return SEPARATORS.contains(lexem);
}

bool IsIdentifier(const std::string_view &lexem) {
    return boost::regex_match(std::string(lexem), IDENTIFIER_REGEX);
}

bool IsStringConstant(const std::string_view &lexem) {
    return boost::regex_match(std::string(lexem), STRING_CONSTANT_REGEX);
}

bool IsNumberConstant(const std::string_view &lexem) {
    return boost::regex_match(std::string(lexem), NUMBER_CONSTANT_REGEX);
}


std::optional<Token::Type> GetTokenType(std::string_view lexem) {

    if (IsKeyword(lexem)) {
        return KEYWORDS.at(lexem);
    } else if (IsBrace(lexem)) {
        return BRACES.at(lexem);
    } else if (IsAssignOperator(lexem)) {
        return ASSIGN_OPERATOR.at(lexem);
    } else if (IsSeparator(lexem)) {
        return SEPARATORS.at(lexem);
    } else if (IsOperator(lexem)) {
        return OPERATORS.at(lexem);
    } else if (IsIdentifier(lexem)) {
        return Token::Type::IDENTIFIER;
    } else if (IsStringConstant(lexem)) {
        return Token::Type::STRING_CONSTANT;
    } else if (IsNumberConstant(lexem)) {
        return Token::Type::NUMBER_CONSTANT;
    }
    return std::nullopt;
}


std::optional<Token> GetNextToken(std::string_view& str) {

    enum class State {
        WAITING_FOR_SUCCESS,
        WAITING_FOR_UNSUCCESS,
    };

    State current_state = State::WAITING_FOR_SUCCESS;
    Token::Type last_matched = Token::Type::UNDEFINED;

    for (int j = 1; j <= str.size(); j++) {

        auto current_match = GetTokenType(str.substr(0, j));

        if (current_match.has_value()) {
            if (current_state == State::WAITING_FOR_SUCCESS) {
                current_state = State::WAITING_FOR_UNSUCCESS;
            }
            last_matched = current_match.value();
        } else {
            if (current_state == State::WAITING_FOR_UNSUCCESS) {
                Token t(last_matched, str.substr(0, j-1));
                str.remove_prefix(j-1);
                return t;
            }
        }

//        std::cout << str.substr(0, j) << std::endl;
//        auto type = GetTokenType(str.substr(0, j));

    }

    if (last_matched != Token::Type::UNDEFINED && current_state == State::WAITING_FOR_UNSUCCESS) {
        Token t(last_matched, str);
        str.remove_prefix(str.size());
        return t;
    }

    return std::nullopt;
}

std::vector<Token> SplitIntoTokens(std::string_view text) {
    std::vector<Token> result;

    int line_number = 1;

    do {
        auto token = GetNextToken(text);
        if (token.has_value()) {
            if (token.value().type == Token::Type::ENDLINE) {
                line_number++;
            } else {
                if (token.value().type != Token::Type::TAB && token.value().type != Token::Type::SPACE)
                    result.emplace_back(token.value());
            }
        } else {
            std::cerr << "Problem on line " << line_number << std::endl;
            break;
        }

    } while (!text.empty());


    return result;
}

std::ostream &operator<<(std::ostream &out, const Token &t) {
    return out;
}