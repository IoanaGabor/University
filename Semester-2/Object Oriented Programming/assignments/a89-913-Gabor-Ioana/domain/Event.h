//
// Created by ioana on 30.03.2023.
//

#ifndef A45_913_GABOR_IOANA_EVENT_H
#define A45_913_GABOR_IOANA_EVENT_H


#include <string>

class Event {
private:
    std::string title;
    std::string description;
    std::string dateAndTime;
    int numberOfAttendants;
    std::string link;
public:
    Event();

    Event &operator=(const Event &other);

    Event(const Event &other);

    Event(const std::string &title, const std::string &description, int numberOfAttendants,
          const std::string &dateAndTime, const std::string &link);

    std::string getTitle() const;

    std::string getDescription() const;

    std::string getDateAndTime() const;

    std::string getLink() const;

    std::string toString() const;

    void setTitle(const std::string &newTitle);

    void setDateAndTime(const std::string &dateAndTime);

    void setDescription(const std::string &newDescription);

    void setLink(const std::string &newLink);

    std::string getId();

    bool operator==(const Event &other) const;

    bool operator!=(const Event &other) const;

    static std::string getIdFromTitleAndDate(const std::string &title, const std::string &date);

    std::string getMonth() const;

    int getNumberOfAttendants() const;

    void setNumberOfAttendants(int newNumberOfAttendants);

    friend std::ostream &operator<<(std::ostream &out, const Event &event);

    friend std::istream &operator>>(std::istream &in, Event &event);

    static std::pair<std::string, std::string> getTitleAndDateFromId(const std::string &id);
};


#endif //A45_913_GABOR_IOANA_EVENT_H
