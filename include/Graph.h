//
// Created by spl211 on 05/11/2020.
//
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include "iostream"
using namespace std;

class Session;

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);

    void infectNode(int nodeInd);
    bool isInfected(int nodeInd) const;
    bool isConnected(int nodeInd);
    bool hasVirus(int nodeInt) const;
    void putVirus(int node);
    void enqueueInfected(int);
    int dequeueInfected();
    int getMatrixSize() const;
    const vector<vector<int>> & getEdges() const;
    int getTheMotherFuckerNode(const Session& session ,int rootLabel);
    void disconnectNode(int);
    string toString();
    bool terminatorCondicator() const;
    vector<int> getInfecteds() const;

private:
    vector<std::vector<int>> edges;
    vector<int> status; // 0 for virus-free, 1 for has virus, 2 for infected node.
    queue<int> infectionQ;
    vector<int> infecteds;
    unsigned int totalViruses;


};

#endif
