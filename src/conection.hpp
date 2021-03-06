#ifndef service_connection
#define service_connection

namespace connection {

    std::string host = {};
    std::string username = {};
    std::string password = {};
    std::string database = {};
    unsigned int port = {};

    void getConnectionProperties() {

        std::ifstream propertiesFile("/etc/connection.properties");

        if (propertiesFile.is_open()) {

            std::string line;
            
            while (getline(propertiesFile, line)) {

                char char_array[line.length() + 1];
                strcpy(char_array, line.c_str());
                char *ptr = strtok(char_array, "=");

                std::string field = ptr;
                ptr = strtok(NULL, "=");
                std::string value = ptr;

                if (field == "connection.host") {
                    host = value;
                } else if (field == "connection.username") {
                    username = value;
                } else if (field == "connection.password") {
                    password = value;
                } else if (field == "connection.database") {
                    database = value;
                } else if (field == "connection.port") {
                    port = std::stoi(value);
                }

            }

            propertiesFile.close();
        }

    }

    MYSQL * get() {

        MYSQL * connection = mysql_init(NULL);

        if (!connection) {
            std::cout << "ERROR (1)" << std::endl;
            return nullptr;
        }

        connection = mysql_real_connect(connection, host.c_str(), username.c_str(), password.c_str(), database.c_str(), port, NULL, 0);

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