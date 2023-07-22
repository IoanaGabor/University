#include <QApplication>
#include "app_tests/TestAll.h"
#include "domain/Event.h"
#include "ui/ConsoleUI.h"
#include "controller/EventsController.h"
#include "repository/CSVEventList.h"
#include "repository/DataBaseEventsRepository.h"
#include "repository/TextFileRepository.h"
#include "repository/HTMLEventList.h"
#include "ui/GUI.h"

const std::string TEXT_FILE_REPOSITORY = "1";
const std::string CSV_EVENT_LIST = "1";

int main(int argc, char *argv[]) {
    TestAll::runAllTests();
    QApplication a(argc, argv);
    AbstractRepository<Event> *eventsRepository;
    eventsRepository = new TextFileRepository<Event>("/home/ioana/second_semester/oop/assignments/a89-913-Gabor-Ioana/events.txt");
    std::string userOption = ConsoleUI::getUserStorageMode();
    AbstractUserEventList *userEventListRepository;
    if (userOption == CSV_EVENT_LIST) {
        userEventListRepository = new CSVEventList("/home/ioana/second_semester/oop/assignments/a89-913-Gabor-Ioana/events.csv");
    } else {
        userEventListRepository = new HTMLEventList("/home/ioana/second_semester/oop/assignments/a89-913-Gabor-Ioana/events.html");
    }
    EventsController eventsController(*eventsRepository, *userEventListRepository);
    if (eventsController.listEventsAdministrator().empty()) {
        eventsController.addEventAdministrator("movie", "fda", "/2022/09/23/10:25", 5, "https://www.google.com/");
        eventsController.addEventAdministrator("concert", "fda", "/2022/10/23/10:25", 15, "https://www.infoarena.ro/");
        eventsController.addEventAdministrator("abc", "fda", "/2022/04/23/10:25", 20, "https://www.infoarena.ro/");
        eventsController.addEventAdministrator("contest", "fda", "/2022/10/21/10:25", 20, "https://www.youtube.com/");
        eventsController.addEventAdministrator("party", "fda", "/2022/11/23/10:25", 15, "https://www.infoarena.ro/");
        eventsController.addEventAdministrator("something", "fda", "/2022/12/23/10:25", 20, "https://www.infoarena.ro/");
        eventsController.addEventAdministrator("nothing", "fda", "/2022/01/23/10:25", 34, "https://www.infoarena.ro/");
        eventsController.addEventAdministrator("haha", "fda", "/2022/03/23/10:25", 34, "https://www.infoarena.ro/");
        eventsController.addEventAdministrator("well", "fda", "/2022/04/23/10:25", 10, "https://www.infoarena.ro/");
        eventsController.addEventAdministrator("fda623s", "fda", "/2022/05/23/10:25", 10, "https://www.infoarena.ro/");
        eventsController.addEventAdministrator("fdasfdas", "fda", "/2022/06/23/10:25", 34, "https://www.infoarena.ro/");
    }
    //ConsoleUI consoleUI = ConsoleUI(eventsController);
    //consoleUI.runConsoleMenu();
    GUI gui = GUI(eventsController);
    gui.show();
    //delete eventsRepository;
    //delete userEventListRepository;
    return QApplication::exec();
}
