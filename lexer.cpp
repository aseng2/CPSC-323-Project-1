#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

// Constants
const string DIGITS = "0123456789";
const string LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string LETTERS_DIGIT = LETTERS + DIGITS;
const vector<string> KEYWORDS = {"while", "for", "cout", "return"};
const vector<char> OPERATOR = {'+', '<', '>', '='};
const vector<string> DOPERATOR = {"<=", ">=", "==", "<<"};
const vector<char> SEPARATOR = {'"', '(', ')', '{', '}'};
const string BLANKSPACE = " \n\t";

// Errors
class Error {
public:
    string error_name;
    string details;

    Error(string error_name, string details) : error_name(error_name), details(details) {}

    string as_string() {
        return error_name + ": " + details;
    }
};

class illegalCharError : public Error {
public:
    illegalCharError(string details) : Error("Illegal Character", details) {}
};

// Token Types
const string TT_INT = "INT";
const string TT_FLOAT = "REAL";
const string TT_OPERATOR = "OPERATOR";
const string TT_QUOTE = "SEPARATOR";
const string TT_LPAREN = "SEPARATOR";
const string TT_RPAREN = "SEPARATOR";
const string TT_SEMICOL = "PUNCTUATION";
const string TT_EXCLAIM = "PUNCTUATION";
const string TT_OCBRAC = "SEPARATOR";
const string TT_CCBRAC = "SEPARATOR";
const string TT_DQUOTE = "PUNCTUATION";
const string TT_ASSIGN = "EQUALS";
const string TT_IDENTIFIER = "IDENTIFIER";
const string TT_KEYWORD = "KEYWORD";

// Token Class
class Token {
public:
    string type;
    string value;

    Token(string type, string value) : type(type), value(value) {}

    string repr() {
        if (!value.empty()) return type + " " + value;
        return type;
    }
};

// Lexer Class
class Lexer {
private:
    string text;
    int pos;
    char current_char;

    void advance() {
        if (pos < text.length()) {
            current_char = text[pos];
        } else {
            current_char = '\0';
        }
        pos++;
    }

    Token make_Num() {
        string num_str = "";
        int dec_bool = 0;

        while (current_char != '\0' && (DIGITS.find(current_char) != string::npos || current_char == '.')) {
            if (current_char == '.') {
                dec_bool++;
                if (dec_bool > 1) break;
            }
            num_str += current_char;
            advance();
        }

        if (dec_bool == 0) {
            return Token(TT_INT, num_str);
        } else {
            return Token(TT_FLOAT, num_str);
        }
    }

    Token make_Identifier() {
        string id_str = "";

        while (current_char != '\0' && (LETTERS.find(current_char) != string::npos || current_char == '_')) {
            id_str += current_char;
            advance();
        }

        string tok_type = TT_IDENTIFIER;
        if (find(KEYWORDS.begin(), KEYWORDS.end(), id_str) != KEYWORDS.end()) {
            tok_type = TT_KEYWORD;
        }

        return Token(tok_type, id_str);
    }

    Token make_Operator() {
        string id_op = "";
        string tok_type = TT_OPERATOR;

        while (current_char != '\0' && find(OPERATOR.begin(), OPERATOR.end(), current_char) != OPERATOR.end()) {
            id_op += current_char;
            advance();
            if (find(DOPERATOR.begin(), DOPERATOR.end(), id_op) != DOPERATOR.end()) {
                return Token(tok_type, id_op);
            }
        }

        return Token(tok_type, id_op);
    }

public:
    Lexer(string text) : text(text), pos(0), current_char('\0') {
        advance();
    }

    vector<Token> make_tokens() {
        vector<Token> tokens;

        while (current_char != '\0') {
            if (isspace(current_char)) {
                advance();
            } else if (BLANKSPACE.find(current_char) != string::npos) {
                advance();
            } else if (DIGITS.find(current_char) != string::npos) {
                tokens.push_back(make_Num());
            } else if (find(OPERATOR.begin(), OPERATOR.end(), current_char) != OPERATOR.end()) {
                tokens.push_back(make_Operator());
            } else if (current_char == '"') {
                tokens.push_back(Token(TT_DQUOTE, "\""));
                advance();
            } else if (current_char == '(') {
                tokens.push_back(Token(TT_LPAREN, "("));
                advance();
            } else if (current_char == ')') {
                tokens.push_back(Token(TT_RPAREN, ")"));
                advance();
            } else if (current_char == ';') {
                tokens.push_back(Token(TT_SEMICOL, ";"));
                advance();
            } else if (current_char == '!') {
                tokens.push_back(Token(TT_EXCLAIM, "!"));
                advance();
            } else if (current_char == '{') {
                tokens.push_back(Token(TT_OCBRAC, "{"));
                advance();
            } else if (current_char == '}') {
                tokens.push_back(Token(TT_CCBRAC, "}"));
                advance();
            } else if (LETTERS.find(current_char) != string::npos) {
                tokens.push_back(make_Identifier());
            } else {
                char c = current_char;
                advance();
                return illegalCharError("'" + string(1, c) + "'"), vector<Token>{};
            }
        }

        return tokens;
    }
};

unordered_map<string, vector<string>> run(string data) {
    unordered_map<string, vector<string>> sample_dict;
    Lexer lexers(data);
    vector<Token> tokens = lexers.make_tokens();

    for (const Token &token : tokens) {
        sample_dict[token.type].push_back(token.value);
    }

    return sample_dict;
}
