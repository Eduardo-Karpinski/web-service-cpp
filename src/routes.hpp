#ifndef service_route
#define service_route

#include "crow.h"
#include "conection.hpp"
#include <cstring>

void createRoutes(crow::SimpleApp &app) {

    CROW_ROUTE(app, "/get")([](){

        MYSQL *connection = connection::get();

        mysql_query(connection, "SELECT * FROM user");

        MYSQL_RES *res_set = mysql_store_result(connection);

        std::vector<crow::json::wvalue> users;

        if (res_set != nullptr) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res_set)) != NULL) {

                 crow::json::wvalue user = {
                    {"id", row[0]},
                    {"name", row[1]},
                    {"password", row[2]}
                };

                users.push_back(user);
            }
        } else {
            std::string error = mysql_error(connection);
            connection::close(connection);
            return crow::response(400, error);
        }

        connection::close(connection);
        crow::json::wvalue result = std::move(users);
        return crow::response(200, result);

    });
    
    CROW_ROUTE(app, "/save/<string>/<string>")([](std::string name, std::string password){

        MYSQL *connection = connection::get();

        bool mysql_state = mysql_query(connection, ("INSERT INTO user (name, password) VALUES('" + name + "', '"+password+"');").c_str());

        if (mysql_state) {
            std::string error = mysql_error(connection);
            connection::close(connection);
            return crow::response(400, error);
        }

        connection::close(connection);
        return crow::response(200);

    });

    CROW_ROUTE(app, "/delete/<int>")([](long id){

        MYSQL *connection = connection::get();

        bool mysql_state = mysql_query(connection, ("DELETE FROM user WHERE id="+std::to_string(id)+"").c_str());

        if (mysql_state) {
            std::string error = mysql_error(connection);
            connection::close(connection);
            return crow::response(400, error);
        }

        connection::close(connection);
        return crow::response(200);

    });

    CROW_ROUTE(app, "/update/<int>/<string>/<string>")([](long id, std::string name, std::string password){

        MYSQL *connection = connection::get();

        bool mysql_state = mysql_query(connection, ("UPDATE user SET name='"+name+"', password='"+password+"' WHERE id="+std::to_string(id)+";").c_str());

        if (mysql_state) {
            std::string error = mysql_error(connection);
            connection::close(connection);
            return crow::response(400, error);
        }

        connection::close(connection);
        return crow::response(200);

    });

    CROW_ROUTE(app, "/get/<int>")([](long id){

        MYSQL *connection = connection::get();

        mysql_query(connection, ("SELECT * FROM user WHERE id="+std::to_string(id)+";").c_str());

        MYSQL_RES *res_set = mysql_store_result(connection);

        crow::json::wvalue user;

        if (res_set != nullptr) {
            MYSQL_ROW row = mysql_fetch_row(res_set);

            if (row != NULL) {
                user["id"] = row[0];
                user["name"] = row[1];
                user["password"] = row[2];
            }

        } else {
            std::string error = mysql_error(connection);
            connection::close(connection);
            return crow::response(400, error);
        }

        connection::close(connection);
        return crow::response(200, user);

    });

    CROW_ROUTE(app, "/")([](){
        crow::mustache::set_base(".");
        return crow::mustache::load("static/index.html").render();
    });

}

#endif