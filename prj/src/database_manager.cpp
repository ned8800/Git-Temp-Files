#include "database_manager.hpp"

database_manager::database_manager(database database): db(database) {

}

database_manager::~database_manager() {
    // close con here
}

json database_manager::get_json_from_query(std::string query) {
    char* res = db.select_query(query);

    //return json::parse(std::string(res));

    return json::parse(res);
}

json database_manager::get_json_recommends(const std::vector<int> &v) {
    char* res = db.get_recommendations(v);

    // we can convert char* to std::string and then to json
    //return json::parse(std::string(res));
    // or we can serialize it directly
    return json::parse(res);
}