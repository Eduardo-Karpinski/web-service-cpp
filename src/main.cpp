/**
 * @file main.cpp
 * @author Eduardo William (karpinskipriester@gmail.com)
 * @brief web service with crow and mysql
 * @version 0.1
 * @date 2022-04-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "crow.h"
#include "routes.hpp"
#include <iostream>

int main() {
    crow::SimpleApp app;

    app.loglevel(crow::LogLevel::Warning);

    createRoutes(app);

    std::cout << "Web service online" << std::endl;

    app.port(18080).multithreaded().run();

    return 0;
}

// g++ main.cpp -L /usr/include/mysql -lmysqlclient -I /usr/include/mysql -lpthread -o main && ./main