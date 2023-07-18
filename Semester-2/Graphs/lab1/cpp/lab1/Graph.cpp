//
// Created by ioana on 26.03.2023.
//

#include "Graph.h"
#include <algorithm>
#include <fstream>
#include <set>
#include <iostream>
#include <sstream>
#include <random>
#include <chrono>

using namespace std;

Graph::Graph() {}

Graph::~Graph() {
    this->inNeighbours.clear();
    this->outNeighbours.clear();
    this->cost.clear();
}

Graph::Graph(const std::vector<std::string> &vertices,
             const std::vector<std::pair<std::pair<std::string, std::string>, int>> &edges) {
    this->inNeighbours.clear();
    this->outNeighbours.clear();
    this->cost.clear();
    for (const auto &vertex: vertices) {
        this->addVertex(vertex);
    }
    for (const auto &edge: edges) {
        this->addEdge(edge.first.first, edge.first.second, edge.second);
    }
}


Graph::Graph(const Graph &another) {
    this->inNeighbours = another.inNeighbours;
    this->outNeighbours = another.outNeighbours;
    this->cost = another.cost;
}

Graph &Graph::operator=(const Graph &another) {
    this->inNeighbours = another.inNeighbours;
    this->outNeighbours = another.outNeighbours;
    this->cost = another.cost;
    return *this;
}

bool Graph::isVertex(const std::string &vertex) {
    if (this->inNeighbours.find(vertex) != this->inNeighbours.end()) {
        return true;
    }
    return false;
}

bool Graph::isEdge(const std::string &firstVertex, const std::string &secondVertex) {
    if (!this->isVertex(firstVertex) || !this->isVertex(secondVertex)) {
        return false;
    }
    return find(this->outNeighbours[firstVertex].begin(), this->outNeighbours[firstVertex].end(), secondVertex) !=
           this->outNeighbours[firstVertex].end();
}


void Graph::addVertex(const std::string &vertex) {
    if (this->isVertex(vertex)) {
        throw std::exception();
    }
    this->inNeighbours[vertex] = std::vector<std::string>();
    this->outNeighbours[vertex] = std::vector<std::string>();
}

void Graph::addEdge(const std::string &firstVertex, const std::string &secondVertex, int edgeCost) {
    if (isEdge(firstVertex, secondVertex)) {
        throw std::exception();
    }
    if (!this->isVertex(firstVertex) || !this->isVertex(secondVertex)) {
        throw std::exception();
    }
    this->outNeighbours[firstVertex].push_back(secondVertex);
    this->inNeighbours[secondVertex].push_back(firstVertex);
    this->cost[{firstVertex, secondVertex}] = edgeCost;
}

int Graph::getInDegreeOfVertex(const std::string &vertex) {
    if (!this->isVertex(vertex)) {
        throw std::exception();
    }
    return (int) this->inNeighbours[vertex].size();
}

int Graph::getOutDegreeOfVertex(const std::string &vertex) {
    if (!this->isVertex(vertex)) {
        throw std::exception();
    }
    return (int) this->outNeighbours[vertex].size();
}

int Graph::getCostOfEdge(const std::string &firstVertex, const std::string &secondVertex) {
    if (!this->isEdge(firstVertex, secondVertex)) {
        throw std::exception();
    }
    return this->cost[{firstVertex, secondVertex}];
}

void Graph::setCostOfEdge(const std::string &firstVertex, const std::string &secondVertex, int newCost) {
    if (!this->isEdge(firstVertex, secondVertex)) {
        throw std::exception();
    }
    this->cost[{firstVertex, secondVertex}] = newCost;
}

std::vector<std::string> Graph::getInboundNeighbours(const std::string &vertex) {
    return this->inNeighbours[vertex];
}

std::vector<std::string> Graph::getOutboundNeighbours(const std::string &vertex) {
    return this->outNeighbours[vertex];
}

void Graph::removeEdge(const std::string &firstVertex, const std::string &secondVertex) {
    if (!this->isEdge(firstVertex, secondVertex)) {
        throw std::exception();
    }
    this->outNeighbours[firstVertex].erase(
            std::remove(this->outNeighbours[firstVertex].begin(), this->outNeighbours[firstVertex].end(), secondVertex),
            this->outNeighbours[firstVertex].end());
    this->inNeighbours[secondVertex].erase(
            std::remove(this->inNeighbours[secondVertex].begin(), this->inNeighbours[secondVertex].end(),
                        firstVertex), this->inNeighbours[secondVertex].end());
    this->cost.erase({firstVertex, secondVertex});
}

void Graph::removeVertex(const std::string &vertex) {
    if (!this->isVertex(vertex)) {
        throw std::exception();
    }
    for (const auto &neigh: this->inNeighbours[vertex]) {
        this->outNeighbours[neigh].erase(
                std::remove(
                        this->outNeighbours[neigh].begin(),
                        this->outNeighbours[neigh].end(),
                        vertex
                ), this->outNeighbours[neigh].end());
        this->cost.erase({neigh, vertex});
    }
    this->inNeighbours.erase(vertex);
    for (const auto &neigh: this->outNeighbours[vertex]) {
        this->inNeighbours[neigh].erase(
                std::remove(
                        this->inNeighbours[neigh].begin(),
                        this->inNeighbours[neigh].end(),
                        vertex
                ), this->inNeighbours[neigh].end());
        this->cost.erase({vertex,neigh});
    }
    this->outNeighbours.erase(vertex);
}

std::vector<std::string> Graph::getAllVertices() {
    std::vector<std::string> allVertices;
    for (const auto &vertex: this->inNeighbours) {
        allVertices.push_back(vertex.first);
    }
    return allVertices;
}


std::vector<std::string> Graph::getIsolatedVertices() {
    std::vector<std::string> isolatedVertices;
    for (const auto &vertex: this->inNeighbours) {
        if(vertex.second.empty() && this->outNeighbours[vertex.first].empty()){
            isolatedVertices.push_back(vertex.first);
        }
    }
    return isolatedVertices;
}

std::vector<std::pair<std::pair<std::string, std::string>, int>> Graph::getAllEdges() {
    std::vector<std::pair<std::pair<std::string, std::string>, int>> allEdges;
    for (const auto &edge: this->cost) {
        allEdges.push_back({{edge.first.first, edge.first.second}, edge.second});
    }
    return allEdges;
}



int Graph::getNumberOfVertices() {
    return this->inNeighbours.size();
}


Graph readGraphInNormalFormatFromFile(const string &fileName) {
    ifstream fi(fileName);
    int n, m;
    fi >> n >> m;
    std::set<std::string> vertices;
    std::vector<std::pair<std::pair<std::string, std::string>, int>> edges;
    std::string firstVertex, secondVertex;
    int cost;
    for (int i = 1; i <= m; i++) {
        fi >> firstVertex >> secondVertex >> cost;
        vertices.insert(firstVertex);
        vertices.insert(secondVertex);
        edges.push_back({{firstVertex, secondVertex}, cost});
    }
    fi.close();
    std::vector<std::string> vertices_as_vector(vertices.begin(), vertices.end());
    return {vertices_as_vector, edges};
}

void writeGraphInNormalFormatToFile(const string &fileName, Graph graph) {
    ofstream fo(fileName);
    int n, m;
    n = graph.getNumberOfVertices();
    std::vector<std::pair<std::pair<std::string, std::string>, int>> edges = graph.getAllEdges();
    m = (int)edges.size();
    fo<<n<<' '<<m<<'\n';
    for (int i = 0; i < m; i++) {
        fo<<edges[i].first.first<<' '<<edges[i].first.second<<' '<<edges[i].second<<'\n';
    }
    fo.close();
}

Graph readGraphInModifiedFormatFromFile(const string &fileName) {
    std::string endFormat = "modified.txt";
    if(fileName.find(endFormat) + endFormat.size()!=fileName.size()){
        throw exception();
    }
    ifstream fi(fileName);
    int n, m;
    fi >> n >> m;
    std::set<std::string> vertices;
    std::vector<std::pair<std::pair<std::string, std::string>, int>> edges;
    std::string firstVertex, secondVertex;
    int cost;
    std::string all_isolated_vertices_as_string;
    getline(fi,all_isolated_vertices_as_string);
    std::istringstream readerForIsolatedVertices(all_isolated_vertices_as_string);
    std::string isolated_vertex;
    while(readerForIsolatedVertices>>isolated_vertex){
        vertices.insert(isolated_vertex);
    }
    for (int i = 1; i <= m; i++) {
        fi >> firstVertex >> secondVertex >> cost;
        vertices.insert(firstVertex);
        vertices.insert(secondVertex);
        edges.push_back({{firstVertex, secondVertex}, cost});
    }
    fi.close();
    std::vector<std::string> vertices_as_vector(vertices.begin(), vertices.end());
    return {vertices_as_vector, edges};
}

void writeGraphInModifiedFormatToFile(const string &fileName, Graph graph) {
    std::string endFormat = "modified.txt";
    if(fileName.find(endFormat) + endFormat.size()!=fileName.size()){
        throw exception();
    }
    ofstream fo(fileName);
    int n, m;
    n = graph.getNumberOfVertices();
    std::vector<std::string> isolatedVertices =graph.getIsolatedVertices();
    std::vector<std::pair<std::pair<std::string, std::string>, int>> edges = graph.getAllEdges();
    m = (int)edges.size();
    fo<<n<<' '<<m<<'\n';
    for (const auto & isolatedVertex : isolatedVertices) {
        fo<<isolatedVertex<<' ';
    }
    fo<<'\n';
    for (int i = 0; i < m; i++) {
        fo<<edges[i].first.first<<' '<<edges[i].first.second<<' '<<edges[i].second<<'\n';
    }
    fo.close();
}

Graph generateRandomGraph(int numberOfVertices, int numberOfEdges){
    if(!(numberOfVertices >= 0 && numberOfEdges >= 0 && numberOfEdges <= numberOfVertices * numberOfVertices)){
        throw exception();
    }
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    std::vector<std::pair<std::pair<std::string,std::string>,int>> allEdges;
    vector<string> allVertices;
    for(int i = 0;i < numberOfVertices;i++){
        allVertices.push_back(to_string(i));
    }
    for(int i = 0;i < numberOfVertices;i++) {
        for(int j = 0;j < numberOfVertices;j++){
            allEdges.push_back({{to_string(i), to_string(j)}, (rng() % 10000000)});
        }
    }
    shuffle(allEdges.begin(),allEdges.end(), rng);
    std::vector<std::pair<std::pair<std::string,std::string>,int>> selectedEdges;
    for(int i=0;i<numberOfEdges;i++){
        selectedEdges.push_back(allEdges[i]);
    }
    return {allVertices, selectedEdges};

}