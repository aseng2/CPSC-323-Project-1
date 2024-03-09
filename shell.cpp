#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_map>
#include <vector>
#include <algorithm>

#include "lexer.cpp"

using namespace std;

string open_file(string filename) {
    ifstream file(filename);
    string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return data;
}

unordered_map<string, vector<string>> addAllDict(unordered_map<string, vector<string>> &new_dict, string key, vector<string> &values) {
    if (new_dict.find(key) == new_dict.end()) {
        new_dict[key] = values;
    } else {
        new_dict[key].insert(new_dict[key].end(), values.begin(), values.end());
    }
    return new_dict;
}

void removeDup(unordered_map<string, vector<string>> &new_dict) {
    for (auto &pair : new_dict) {
        sort(pair.second.begin(), pair.second.end());
        pair.second.erase(unique(pair.second.begin(), pair.second.end()), pair.second.end());
    }
}

int main() {
    string text = open_file("input_sourcecode.txt");

    // Remove comments
    regex comment_pattern("//.*");
    text = regex_replace(text, comment_pattern, " ");

    istringstream iss(text);
    string line;
    unordered_map<string, vector<string>> new_result;

    while (getline(iss, line)) {
        Lexer lexer(line);
        vector<Token> tokens = lexer.make_tokens();

        for (const Token &token : tokens) {
            vector<string> values;
            values.push_back(token.value);
            addAllDict(new_result, token.type, values);
        }
    }

    removeDup(new_result);

    // Print table
    cout << "Token    Lexeme" << endl;
    for (const auto &pair : new_result) {
        for (const string &value : pair.second) {
            cout << pair.first << "    " << value << endl;
        }
    }

    // Write to output file
    ofstream output_file("output.txt");
    for (const auto &pair : new_result) {
        for (const string &value : pair.second) {
            output_file << pair.first << "    " << value << endl;
        }
    }

    return 0;
}
