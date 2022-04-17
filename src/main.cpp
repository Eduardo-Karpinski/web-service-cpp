/**
 * @file main.cpp
 * @author Eduardo William (karpinskipriester@gmail.com)
 * @brief web service with crow and mysql
 * @version 1.0
 * @date 2022-04-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// all includes are here

#include <cstring>
#include <iostream>
#include <fstream>
#include "crow.h"
#include <mysql.h>
#include "conection.hpp"
#include "routes.hpp"

void createTable() {
    MYSQL *connection = connection::get();

    bool mysql_state = mysql_query(connection, "CREATE TABLE IF NOT EXISTS user (id bigint NOT NULL AUTO_INCREMENT, name varchar(20) DEFAULT NULL, password varchar(20) NOT NULL, PRIMARY KEY (id));");

    if (mysql_state) {
        std::cout << mysql_error(connection) << std::endl;
    }

    connection::close(connection);
}

int main() {

    connection::getConnectionProperties();
    createTable();

    crow::SimpleApp app;
    app.loglevel(crow::LogLevel::Warning);
    createRoutes(app);

    std::cout << "Web service online localhost:18080" << std::endl;
    app.port(18080).multithreaded().run();

    return 0;
}

// g++ main.cpp -L /usr/include/mysql -lmysqlclient -I /usr/include/mysql -lpthread -o main && ./main