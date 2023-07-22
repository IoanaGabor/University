//
// Created by ioana on 03.05.2023.
//

#include "HTMLEventList.h"


void HTMLEventList::save() {
    std::ofstream fileWriter(fileName);
    fileWriter << "<!DOCTYPE html>    <!-- write this exactly as it is here -->\n"
          "<html> <!-- write this exactly as it is here -->\n"
          "<head> <!--  write this exactly as it is here -->\n"
          "    <title>Playlist</title> <!-- replace “Playlist” with the title for your HTML -->\n"
          "</head> <!-- write this exactly as it is here (close head tag) -->\n"
          "<body> <!-- write this exactly as it is here -->";
    fileWriter << "<table border=\"1\"> <!-- write this exactly as it is here -->\n"
          "    <tr> <!-- tr = table row; 1 row for each entity -->\n"
          "        <td>Title</td> <!-- td = table data; 1 td for each attribute of the entity -->\n"
          "        <td>Description</td>\n"
          "        <td>Date and time</td>\n"
          "        <td>Number of attendants</td>\n"
          "        <td>Link</td>\n"
          "    </tr>";
    for (const auto &entity: entities) {
        fileWriter << HTMLEventList::eventToHTMLString(entity);
    }
    fileWriter << "</table>\n"
          "</body>\n"
          "</html>\n";
}

void HTMLEventList::displayEventList() {
    system(("open " + fileName).c_str());
}

std::string HTMLEventList::eventToHTMLString(const Event &event) {
    std::string returnedString = "<tr>\n";
    returnedString += "<td>" + event.getTitle() + "</td>\n";
    returnedString += "<td>" + event.getDescription() + "</td>\n";
    returnedString += "<td>" + event.getDateAndTime() + "</td>\n";
    returnedString += "<td>" + std::to_string(event.getNumberOfAttendants()) + "</td>\n";
    returnedString += "<td>" + event.getLink() + "</td>\n";
    returnedString += "</tr>\n";
    return returnedString;
}
