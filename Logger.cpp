#include "Logger.h"

std::shared_ptr<AbstractLogger> Logger::instance = nullptr;

std::shared_ptr<AbstractLogger> Logger::i()
{
    // При многопоточном запросе неинициализированного инстанса может возникнуть гонка данных 
    // Для предотвращения гонки можно
    // Инициализировать инстанс до использования в многопоточности вызвав Logger::i()
    // Или добавить сюда мьютекс, но после первого вызова надобность в нем отпадает.
    if (!instance)
        instance = std::shared_ptr<AbstractLogger>(new Logger::_log);
    return instance;
}
