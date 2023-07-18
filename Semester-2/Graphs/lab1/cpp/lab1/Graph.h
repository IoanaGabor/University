//
// Created by ioana on 26.03.2023.
//

#ifndef LAB1_GRAPH_H
#define LAB1_GRAPH_H


#include <map>
#include <string>
#include <vector>

class Graph {

    std::map<std::string, std::vector<std::string>> inNeighbours;
    std::map<std::string, std::vector<std::string>> outNeighbours;
    std::map<std::pair<std::string,std::string>, int> cost;
public:
    Graph();
    ~Graph();
    Graph(const Graph &another);
    Graph& operator = (const Graph &another);
    int getNumberOfVertices();
    bool isVertex(const std::string& vertex);
    bool isEdge(const std::string& firstVertex, const std::string& secondVertex);
    void addVertex(const std::string& vertex);
    void addEdge(const std::string& firstVertex, const std::string& secondVertex, int cost);
    int getInDegreeOfVertex(const std::string& vertex);
    int getOutDegreeOfVertex(const std::string& vertex);
    int getCostOfEdge(const std::string& firstVertex, const std::string& secondVertex);
    void setCostOfEdge(const std::string& firstVertex, const std::string& secondVertex, int newCost);
    std::vector<std::string> getInboundNeighbours(const std::string& vertex);
    std::vector<std::string> getOutboundNeighbours(const std::string& vertex);
    void removeEdge(const std::string& firstVertex, const std::string& secondVertex);
    void removeVertex(const std::string& vertex);
    std::vector<std::string > getAllVertices();
    Graph(const std::vector<std::string>& vertices, const std::vector<std::pair<std::pair<std::string, std::string>, int>>& edges);

    std::vector<std::pair<std::pair<std::string, std::string>, int>> getAllEdges();

    std::vector<std::string> getIsolatedVertices();
};

Graph readGraphInNormalFormatFromFile(const std::string& fileName);
void writeGraphInNormalFormatToFile(const std::string &fileName, Graph graph);
Graph readGraphInModifiedFormatFromFile(const std::string &fileName);
void writeGraphInModifiedFormatToFile(const std::string &fileName, Graph graph);
Graph generateRandomGraph(int numberOfVertices, int numberOfEdges);
#endif //LAB1_GRAPH_H
