#include "database.hpp"

database::database() {
    // init con_ here
}

database::~database() {
    // close con_ here
}

bool database::insert_query(std::string query) {
    //bool ok = con_->exeq(query);
    //return ok;
    query = "a";
    return true;
}

char *database::select_query(std::string query) {
    //char* res = con_->exeq(query);
    //return res;
    query = "a";
    return new char[12];
}

char *database::get_recommendations(const std::vector<int> &v) {
    // std::string query = ... // make query from vector
    //char* res = con_->exeq(query);
    //return res;
    std::vector<int> temp;
    temp = v;
    return new char[12];
}