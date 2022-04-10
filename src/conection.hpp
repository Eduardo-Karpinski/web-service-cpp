#ifndef service_connection
#define service_connection

#include <mysql.h>
#include <iostream>

namespace connection {

    MYSQL * get() {

        MYSQL * connection = mysql_init(NULL);

        if (!connection) {
            std::cout << "ERROR (1)" << std::endl;
            return nullptr;
        }

        connection = mysql_real_connect(connection, "localhost", "root", "root", "cpp", 0, NULL, 0);

        if (!connection) {
            std::cout << "ERROR (2)" << std::endl;
            return nullptr;
        }

        std::cout << "connection ("<<mysql_thread_id(connection)<<") open" << std::endl;

        return connection;
    }

    void close(MYSQL *connection) {

        std::cout << "connection ("<<mysql_thread_id(connection)<<") close" << std::endl;
        mysql_close(connection);
        
    }

}

#endif