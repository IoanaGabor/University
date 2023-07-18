//
// Created by ioana on 26.03.2023.
//

#include <cstdio>
#include <iostream>
#include "UI.h"

void UI::printListOfVertices(const std::vector<std::string>& vertices){
    std::cout<<"The vertices are\n";
    for(const auto& vertex:vertices){
        std::cout<<vertex<<' ';
    }
    std::cout<<'\n';
}

void UI::printListOfEdges(const std::vector<std::pair<std::pair<std::string,std::string>,int>>& edges){
    std::cout<<"The edges are\n";
    for(const auto& edge:edges){
        std::cout<<edge.first.first<<' '<<edge.first.second<<' '<<edge.second<<'\n';
    }
    std::cout<<'\n';
}

std::string UI::readAVertex(){
    std::string vertex;
    std::cout<<"Enter a vertex\n";
    std::cin>>vertex;
    return vertex;
}


std::pair<std::string,std::string>  UI::readAnEdgeWithoutCost(){
    std::string firstVertex, secondVertex;
    std::cout<<"Enter the first vertex\n";
    std::cin>>firstVertex;
    std::cout<<"Enter the second vertex\n";
    std::cin>>secondVertex;
    return {firstVertex, secondVertex};
}


std::pair<std::pair<std::string,std::string>,int> UI::readAnEdgeWithCost(){
    std::string firstVertex, secondVertex;
    int cost;
    std::cout<<"Enter the first vertex\n";
    std::cin>>firstVertex;
    std::cout<<"Enter the second vertex\n";
    std::cin>>secondVertex;
    std::cout<<"Enter the cost of the edge\n";
    std::cin>>cost;
    return {{firstVertex, secondVertex}, cost};
}

void UI::printMenu() {
    printf("Options:\n");
    printf("1. Print the number of vertices\n");
    printf("2. Print the set of vertices\n");
    printf("3. Check if this edge exists\n");
    printf("4. Print the in degree and the out degree of an vertex\n");
    printf("5. Print the set of outbound edges of an vertex\n");
    printf("6. Print the set of inbound edges of an vertex\n");
    printf("7. Print the cost of an edge\n");
    printf("8. Modify the cost of an edge\n");
    printf("9. Add edge\n");
    printf("10. Remove edge\n");
    printf("11. Add vertex\n");
    printf("12. Remove vertex\n");
    printf("13. Display all edges\n");
    printf("14. Generate random graph\n");
    printf("15. Read graph with normal format\n");
    printf("16. Write graph with normal format \n");
    printf("17. Read graph with modified format\n");
    printf("18. Write graph with modified format\n");
    printf("19. Check if a vertex exists\n");
    printf("exit\n");
}

void UI::runConsoleMenu() {
    std::string command;
    while(1){
        this->printMenu();
        std::cin>>command;
        if (command == "1"){
            this->handle_print_the_number_of_vertices();
        }else if(command == "2"){
            this->handle_print_list_of_vertices();
        }else if(command == "3"){
            this->handle_checking_if_an_edge_exists();
        }else if(command == "4"){
            this->handle_printing_the_degrees_of_a_vertex();
        }else if(command == "5"){
            this->handle_printing_the_set_of_outbound_vertices();
        }else if(command == "6"){
            this->handle_printing_the_set_of_inbound_vertices();
        }else if(command == "7"){
            this->handle_printing_the_cost_of_an_edge();
        }else if(command == "8"){
            this->handle_modifying_the_cost_of_an_edge();
        }else if(command == "9"){
            this->handle_adding_an_edge();
        }else if(command == "10"){
            this->handle_removing_an_edge();
        }else if(command == "11"){
            this->handle_adding_a_vertex();
        }else if(command == "12"){
            this->handle_removing_a_vertex();
        }else if(command == "13"){
            this->handle_print_list_of_edges();
        }else if(command == "14"){
            this->handle_generating_random_graph();
        }else if(command == "15"){
            this->handle_reading_graph_with_normal_format();
        }else if(command == "16"){
            this->handle_writing_graph_with_normal_format();
        }else if(command == "17"){
            this->handle_reading_graph_with_modified_format();
        }else if(command == "18"){
            this->handle_writing_graph_with_modified_format();
        }else if(command == "19"){
            this->handle_checking_if_a_vertex_exists();
        }else if(command == "exit"){
            break;
        }else{
            std::cout<<"invalid command";
        };

    }
}

UI::UI() {
    this->graph = Graph();
}

void UI::handle_print_the_number_of_vertices() {
    std::cout<<"There are "<< this->graph.getNumberOfVertices()<<' '<<"vertices \n";
}

void UI::handle_print_list_of_vertices() {
    printListOfVertices(this->graph.getAllVertices());
}

void UI::handle_checking_if_an_edge_exists() {
    std::pair<std::string, std::string > edge = this->readAnEdgeWithoutCost();
    if(this->graph.isEdge(edge.first, edge.second)){
        std::cout<<"The edge exists\n";
    }else{
        std::cout<<"The edge doesn't exist\n";
    }
}

void UI::handle_printing_the_degrees_of_a_vertex() {
    std::string vertex= this->readAVertex();
    try {
        int in_degree = this->graph.getInDegreeOfVertex(vertex);
        int out_degree = this->graph.getOutDegreeOfVertex(vertex);
        std::cout<<in_degree<<' '<<out_degree<<'\n';
    } catch (std::exception &exception) {
        std::cout<<"the vertex doesn't exist\n";
    }

}

void UI::handle_printing_the_set_of_outbound_vertices() {
    std::string vertex= this->readAVertex();
    try {
        std::vector<std::string > outboundVertices = this->graph.getOutboundNeighbours(vertex);
        this->printListOfVertices(outboundVertices);
    } catch (std::exception &exception) {
        std::cout<<"the vertex doesn't exist\n";
    }
}

void UI::handle_printing_the_set_of_inbound_vertices() {
    std::string vertex= this->readAVertex();
    try {
        std::vector<std::string > inboundVertices = this->graph.getInboundNeighbours(vertex);
        this->printListOfVertices(inboundVertices);
    } catch (std::exception &exception) {
        std::cout<<"the vertex doesn't exist\n";
    }
}

void UI::handle_printing_the_cost_of_an_edge() {
    std::pair<std::string, std::string> edge = this->readAnEdgeWithoutCost();
    try {
        int cost = this->graph.getCostOfEdge(edge.first, edge.second);
        std::cout<<"the cost is "<<cost<<'\n';
    } catch (std::exception &exception) {
        std::cout<<"the edge doesn't exist\n";
    }
}

void UI::handle_adding_an_edge() {
    std::pair<std::pair<std::string, std::string>,int> edge = this->readAnEdgeWithCost();
    try {
        this->graph.addEdge(edge.first.first, edge.first.second, edge.second);
    } catch (std::exception &exception) {
        std::cout<<"the edge couldn't be added\n";
    }
}

void UI::handle_removing_an_edge() {
    std::pair<std::string, std::string> edge = this->readAnEdgeWithoutCost();
    try {
        this->graph.removeEdge(edge.first, edge.second);
    } catch (std::exception &exception) {
        std::cout<<"the edge does not exist\n";
    }
}

void UI::handle_adding_a_vertex() {
    std::string vertex = readAVertex();
    try{
        this->graph.addVertex(vertex);
    }catch (std::exception &exception){
        std::cout<<"vertex already exists";
    }
}

void UI::handle_removing_a_vertex() {
    std::string vertex = readAVertex();
    try{
        this->graph.removeVertex(vertex);
    }catch (std::exception &exception){
        std::cout<<"vertex doesn't exist";
    }
}

void UI::handle_print_list_of_edges() {
    printListOfEdges(this->graph.getAllEdges());
}

void UI::handle_generating_random_graph() {
    int numberOfVertices, numberOfEdges;
    std::cout<<"Please enter the number of vertices\n";
    std::cin>>numberOfVertices;
    std::cout<<"Please enter the number of edges\n";
    std::cin>>numberOfEdges;
    try{
        this->graph = generateRandomGraph(numberOfVertices, numberOfEdges);
    }catch(std::exception &exception){
        this->graph = Graph();
        std::cout<<"invalid arguments";
    }
}

void UI::handle_reading_graph_with_normal_format() {
    std::cout<<"Enter the file name\n";
    std::string filename;
    std::cin>>filename;
    try{
        this->graph = readGraphInNormalFormatFromFile(filename);
    }catch (std::exception &exception){
        std::cout<<"an error occurred, the file might not exist";
    }

}

void UI::handle_modifying_the_cost_of_an_edge() {
    std::pair<std::pair<std::string,std::string>,int> edgeWithCost = readAnEdgeWithCost();
    try{
        this->graph.setCostOfEdge(
                edgeWithCost.first.first,
                edgeWithCost.first.second,
                edgeWithCost.second
                );
    }catch (std::exception &exception){
        std::cout<<"the edge doesn't exist";
    }
}

void UI::handle_writing_graph_with_normal_format() {
    std::cout<<"Enter the file name\n";
    std::string filename;
    std::cin>>filename;
    try{
        writeGraphInNormalFormatToFile(filename, this->graph);
    }catch (std::exception &exception){
        std::cout<<"an error occurred";
    }
}

void UI::handle_reading_graph_with_modified_format() {
    std::cout<<"Enter the file name\n";
    std::string filename;
    std::cin>>filename;
    try{
        this->graph = readGraphInModifiedFormatFromFile(filename);
    }catch (std::exception &exception){
        std::cout<<"an error occurred, the file might not exist or the format could be invalid";
    }
}

void UI::handle_writing_graph_with_modified_format() {
    std::cout<<"Enter the file name\n";
    std::string filename;
    std::cin>>filename;
    try{
        writeGraphInModifiedFormatToFile(filename, this->graph);
    }catch (std::exception &exception){
        std::cout<<"an error occurred";
    }
}

void UI::handle_checking_if_a_vertex_exists() {
    std::string vertex = readAVertex();
    if(this->graph.isVertex(vertex)){
        std::cout<<"this vertex exists\n";
    }else{
        std::cout<<"this vertex doesn't exist\n";
    }
}
