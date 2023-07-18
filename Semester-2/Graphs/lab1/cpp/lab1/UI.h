//
// Created by ioana on 26.03.2023.
//

#ifndef LAB1_UI_H
#define LAB1_UI_H


#include "Graph.h"

class UI {
    Graph graph;
public:
    UI();
    ~UI();
    void printMenu();

    void handle_print_the_number_of_vertices();

    void handle_print_list_of_vertices();

    void handle_checking_if_an_edge_exists();

    void handle_printing_the_degrees_of_a_vertex();

    void handle_printing_the_set_of_outbound_vertices();

    void handle_printing_the_set_of_inbound_vertices();

    void handle_printing_the_cost_of_an_edge();

    void handle_adding_an_edge();

    void handle_removing_an_edge();

    void handle_adding_a_vertex();

    void handle_removing_a_vertex();

    void handle_print_list_of_edges();

    void handle_generating_random_graph();

    void handle_reading_graph_with_normal_format();

    void runConsoleMenu();

    void printListOfVertices();

    void printListOfVertices(const std::vector<std::string>& vertices);

    void printListOfEdges(const std::vector<std::pair<std::string, std::string>> &edges);

    void handle_modifying_the_cost_of_an_edge();

    std::string readAVertex();

    std::pair<std::string, std::string> readAnEdgeWithoutCost();

    std::pair<std::pair<std::string, std::string>, int> readAnEdgeWithCost();

    void printListOfEdges(const std::vector<std::pair<std::pair<std::string, std::string>, int>> &edges);

    void handle_writing_graph_with_normal_format();

    void handle_reading_graph_with_modified_format();

    void handle_writing_graph_with_modified_format();

    void handle_checking_if_a_vertex_exists();
};


#endif //LAB1_UI_H
