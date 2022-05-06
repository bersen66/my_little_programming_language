#include "token.h"
#include <vector>
#include <unordered_map>
#include <string_view>
#include <regex>
#include <string>
#include <iostream>



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

bool IsBasicDataType(const std::string_view &lexem) {
    return BASIC_DATA_TYPES.contains(lexem);
}

bool IsIdentifier(const std::string_view &lexem) {
    return std::regex_match(std::string(lexem), IDENTIFIER_REGEX);
}

bool IsStringConstant(const std::string_view &lexem) {
    return std::regex_match(std::string(lexem), STRING_CONSTANT_REGEX);
}

bool IsNumberConstant(const std::string_view &lexem) {
    return std::regex_match(std::string(lexem), NUMBER_CONSTANT_REGEX);
}


std::optional<Token::Type> GetTokenType(std::string_view lexem) {
    if (IsBasicDataType(lexem)) {
        return BASIC_DATA_TYPES.at(lexem);
    } else if (IsKeyword(lexem)) {
        return KEYWORDS.at(lexem);
    } else if (IsOperator(lexem)) {
        return OPERATORS.at(lexem);
    } else if (IsIdentifier(lexem)) {
        return Token::Type::IDENTIFIER;
    } else if (IsStringConstant(lexem)) {
        return Token::Type::STRING_CONSTANT;
    } else if (IsNumberConstant(lexem)) {
        return Token::Type::NUMBER_CONSTANT;
    } else if (IsBrace(lexem)) {
        return BRACES.at(lexem);
    } else if (IsAssignOperator(lexem)) {
        return ASSIGN_OPERATOR.at(lexem);
    } else if (IsSeparator(lexem)) {
        return SEPARATORS.at(lexem);
    } else
        return std::nullopt;
}


std::optional<Token> GetNextToken(std::string_view &str) {

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
                Token t(last_matched, str.substr(0, j - 1));
                //TokenHolder t = MakeToken(last_matched, str.substr(0, j-1));
                str.remove_prefix(j - 1);
                return t;
            }
        }

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

    while (!text.empty()) {
        auto token = GetNextToken(text);
        if (token.has_value()) {
            if (token.value().type == Token::Type::ENDLINE) {
                    line_number++;
                continue;
            } else {
                if (token.value().type != Token::Type::TAB && token.value().type != Token::Type::SPACE) {
                    token.value().line_number = line_number;
                    result.emplace_back(token.value());
                }
            }
        } else {
            std::cerr << "Problem on line " << line_number << std::endl;
            break;
        }
    }


    return result;
}

TokenStream::TokenStream(const std::vector<Token> &token_sequence)
        : tokens_(token_sequence) {}

TokenStream::TokenStream(std::vector<Token> &&token_sequence)
        : tokens_(token_sequence) {}

Token &TokenStream::GetCurrentToken() {
    return tokens_[curr_idx];
}

const Token &TokenStream::GetCurrentToken() const {
    return tokens_[curr_idx];
}

bool TokenStream::HasNext() const {
    return curr_idx <= tokens_.size() - 1;
}

bool TokenStream::HasCurrent() const {
    return curr_idx < tokens_.size();
}

const Token &TokenStream::GetNextToken() const {
    return tokens_[curr_idx + 1];
}

Token &TokenStream::GetNextToken() {
    return tokens_[curr_idx];
}

void TokenStream::MoveToNextToken() {
    curr_idx++;
}

void TokenStream::MoveToPrevToken() {
    curr_idx--;
}

