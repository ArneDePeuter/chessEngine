#ifndef CHESS_LOGGER_H
#define CHESS_LOGGER_H

#include "ostream"
#include "string"

class Logger {
public:
    static void writeError(std::ostream &errorStream, const std::string &message) {
        errorStream << "Error: " <<  message << std::endl;
    }
    static void writeLog(std::ostream &logStream, const std::string &message) {
        logStream << "Log: " << message << std::endl;
    }
};


#endif //CHESS_LOGGER_H
