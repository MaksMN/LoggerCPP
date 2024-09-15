#include "Logger.h"

class SampleClass
{
private:
    std::shared_ptr<AbstractLogger> logger_pseudonym = Logger::i();
public:
    void sample_function() {

        logger_pseudonym->console("Hello? Im logger pseudonym");
        logger_pseudonym->write_file("Hello? Im logger pseudonym");
    }
};

int main() {
    auto logger = Logger::i();
    logger->LogFileInitialize("log.log");
    logger->console("Hello, Logger!");
    logger->con_error("This is error console log.");
    logger->write_file("This is a one log sting in file.");
    logger->write_file("This is a two log sting in file.");

    SampleClass sample;
    sample.sample_function();

    return 0;
}