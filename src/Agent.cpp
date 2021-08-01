//
// Created by spl211 on 09/11/2020.
//
#include "Agent.h"
#include "Session.h"
#include "iostream"
using namespace std;

// AGENT
Agent::Agent() = default;
void Agent::act(Session &session) {}


// VIRUS
Virus::Virus(int _nodeInt) : nodeInd{_nodeInt}{}

void Virus::act(Session &session)
{
    session.enqueueInfected(nodeInd);
    session.getGraph();
    for(int i = 0; i < session.getGraph().getMatrixSize(); i++)
    {
        int relation = session.getGraph().getEdges()[nodeInd][i]; // getEdges, getGraph return a const reference
        if (relation == 1){
            if(!session.getGraph().hasVirus(i)) {
                session.putVirus(i);
                session.addAgent(Virus(i));
                return;
            }
        }
    }
}

string Virus::toString() {
    string s = "Hi, I'm a Virus, I live in node: ";
    s += to_string(nodeInd);
    return s;
}

Agent *Virus::clone() const {
    return new Virus(*this);
}

ContactTracer::ContactTracer() = default;

void ContactTracer::act(Session &session)
{
    int node = session.getTheMotherFuckerNode(); //Returns the node we want to disconnect from the graph, after the BFS.
    if(node == -1)
        return;
    session.disconnectNode(node);
}

string ContactTracer::toString() {
    return "Hi, I'm a Contact Tracer";
}

Agent *ContactTracer::clone() const {
    return new ContactTracer(*this);
}


