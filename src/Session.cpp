//
// Created by spl211 on 09/11/2020.
//
#include <iostream>
#include <fstream>
#include "json.hpp"
#include "Session.h"
#include "Agent.h"

using json = nlohmann::json;
using namespace std;

Session::Session(const std::string &path) : g(vector<vector<int>>()), treeType(), agents(vector<Agent*>()), cycle(0)
{
    ifstream i(path);
    json j;
    i >> j;
    g = Graph(j["graph"]);
    if(j["tree"] == "M")
        treeType = MaxRank;
    if(j["tree"] == "R")
        treeType = Root;
    if(j["tree"] == "C")
        treeType = Cycle;
    for(auto elem: j["agents"])
    {
        if(elem[0] == "V"){
            agents.push_back(new Virus(elem[1]));
            g.putVirus(elem[1]);
        }
        else
            agents.push_back(new ContactTracer());
    }
}


void Session::simulate() {
    while (!terminationIndicator()){
        //std::cout << "run number:" + to_string(cycle) << endl;
        int size = agents.size();
        for (int i = 0; i< size; i ++){
            agents[i]->act(*this);
        }
        cycle++;
       // cout << toString() << endl;
    }
    output();
}

void Session::addAgent(const Agent &agent)
{
    agents.push_back(agent.clone());
}



string Session::toString()
{
    string s = "tree type: " + to_string(treeType) + "\n";
    s = s + "Agents: " + "\n";
    for (auto & agent : agents)
    {
        s += agent->toString() + '\n';
    }
    s = s + "graph: " + "\n" + g.toString();
    return s;
}

void Session::setGraph(const Graph &graph) {
    g = graph;
}

void Session::enqueueInfected(int node) {
    g.infectNode(node);
    //g.enqueueInfected(node);
}

TreeType Session::getTreeType() const {
    return treeType;
}

int Session::dequeueInfected() {
    return g.dequeueInfected();
}

const Graph &Session::getGraph() {
    return g;
}

int Session::getCycle() const {
    return cycle;
}

int Session::getTheMotherFuckerNode() {
    int node = dequeueInfected();
    if(node == -1)
        return -1;
    return g.getTheMotherFuckerNode(*this, node);
}

bool Session::terminationIndicator() { // returns true if all connected components has the same status (o or !0)
    return g.terminatorCondicator();
}

Session *Session::clone() { // TODO
    return new Session(*this);
}

void Session::output() {
    json output;
    output["graph"] = g.getEdges();
    output["infected"] = g.getInfecteds();
    ofstream o("output.json");
    o << output << endl;
}

void Session::clear() {
    for(auto & agent : agents){
        delete agent;
        agent = nullptr;
    }
    agents.clear();
    cycle = 0;
    // no deletion for g (graph)
}

void Session::nullAgents() {
    for(auto & agent : agents){
        agent = nullptr;
    }
    agents.clear();
}

vector<Agent *> Session::copyAgents() const {
    vector<Agent*> res;
    for (auto agent: agents)
        res.push_back(agent->clone());
    return res;
}

/** destructor */
Session::~Session() {
    clear();
}
/** copy constructor */
Session::Session(const Session &other) : g(vector<vector<int>>()), treeType(), agents(), cycle(0)
{
    for(auto agent: other.agents)
        agents.push_back(agent->clone());
    g = other.g;
    treeType = other.treeType;
    cycle = other.cycle;
}

/** copy assignment operator */
const Session &Session::operator=(const Session &other) {
    if(this != &other)  // self assignment condition
    {
        agents = other.copyAgents();    // TODO maybe exception safety
        g = other.g;
        treeType = other.treeType;
        cycle = other.cycle;
    }
    return *this;
}

/** move constructor */
Session::Session(Session &&other) : g(other.g), treeType(other.treeType), agents(other.agents), cycle(other.cycle)
{
    other.nullAgents(); // TODO check why it works.
}

/** move assignment */
const Session &Session::operator=(Session &&other) {
    if(this != &other){
        clear();
        agents = other.agents;
        g = other.g;
        treeType = other.treeType;
        cycle = other.cycle;
        other.nullAgents();
    }
    return *this;
}

void Session::putVirus(int node) {
    g.putVirus(node);
}

void Session::disconnectNode(int node) {
    g.disconnectNode(node);
}




