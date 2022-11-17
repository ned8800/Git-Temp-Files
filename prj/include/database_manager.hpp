#ifndef PRJ_INCLUDE_DATABASE_MANAGER_H
#define PRJ_INCLUDE_DATABASE_MANAGER_H

#include "json.hpp"
#include "database.hpp"

using json = nlohmann::json;

class database_manager {
public:
    explicit database_manager(database);
    ~database_manager();

    json get_json_from_query(std::string query);
    json get_json_recommends(const std::vector<int>& v);

    // test
    json get_json_from_query_test() {
        return json::parse(db.select_query_test());
    }

    json get_json_recommends_test(const std::vector<int>& v) {
        return json::parse(db.get_recommendations_test(v));
    }

private:
    database db;
};

#endif // PRJ_INCLUDE_DATABASE_MANAGER_H
