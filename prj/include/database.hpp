#ifndef PRJ_INCLUDE_DATABASE_H
#define PRJ_INCLUDE_DATABASE_H

#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <iostream>

// test data

static std::map<int, std::string> films = std::map<int, std::string>{{0, "first"}, {1, "second"}, {2, "third"}};

// Your database connection
class database {
public:
    database();
    ~database();

    char* select_query(std::string query); // sql select query
    bool insert_query(std::string query); // sql insert into query
    // might be bad
    char* get_recommendations(const std::vector<int>& v); // sql select query for vector

    // test functions
    char* select_query_test() {
        char* buf = new char[512];

        strcpy(buf, R"({ "Width": 800, "Height": 600})");

        return buf;
    }

    std::string get_recommendations_test(const std::vector<int>& v) {
        std::string res = "{";
        for (auto el : v) {
            auto film = films[el];
        // for (auto film: films) {
            res += "\"" + std::to_string(el) + "\"" + ":" + "\"" + film + "\"" + ",";
        }
        std::string ret = std::string(res.begin(), res.end() - 1);
        ret += "}";
        std::cout << ret << '\n';
        return ret;
//        return R"(
//  {
//    "0": first,
//    "1": "second",
//    "2": "third"
//  }
//)";
    }

private:
    // db* con_;
};

#endif // PRJ_INCLUDE_DATABASE_H
