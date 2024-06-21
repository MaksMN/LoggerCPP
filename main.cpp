#include "Logger.h"

class SampleClass
{
private:
    std::shared_ptr<ILogger> logger_pseudonum = Logger::log;
public:
    void sample_function() {
        /* your code */
        logger_pseudonum->console("Hello? Im logger pseudonim");
        logger_pseudonum->write_file("Hello? Im logger pseudonim");
    }
};

int main() {
    auto& logger = Logger::log;
    logger->LogFileInitialize("log.log");
    logger->console("Hello, Logger!");
    logger->con_error("This is error console log.");
    logger->write_file("This is a one log sting in file.");
    logger->write_file("This is a two log sting in file.");

    SampleClass sample;
    sample.sample_function();

    return 0;
}