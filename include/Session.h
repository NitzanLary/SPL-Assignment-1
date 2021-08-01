//
// Created by spl211 on 05/11/2020.
//

#ifndef HW1_SESSION_H
#define HW1_SESSION_H


#include <vector>
#include <string>
#include <queue>
#include "Graph.h"

class Agent;

enum TreeType{
    Cycle,
    MaxRank,
    Root
};


class Session{
public:
    Session(const std::string& path);
    /* Rule of 5 */     // TODO check correctness for each one.
    ~Session(); // destructor
    Session(const Session &other); // copy constructor
    const Session& operator=(const Session &other); // copy assignment operator
    Session(Session &&other); // move constructor
    const Session& operator=(Session &&other); // move assignment

    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    const Graph& getGraph();

    int getCycle() const;
    int getTheMotherFuckerNode();
    Session* clone();
    vector<Agent *> copyAgents() const;
    string toString();
    void putVirus(int i);
    void disconnectNode(int i);

private:
    Graph g;
    TreeType treeType;
    vector<Agent*> agents;
    int cycle;

    void clear();
    bool terminationIndicator();
    void output();

    void nullAgents();
};


#endif //HW1_SESSION_H
