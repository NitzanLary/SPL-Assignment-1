//
// Created by spl211 on 09/11/2020.
//
#include "Graph.h"
#include "Session.h"
#include "Tree.h"

#include <utility>

using namespace std;

Graph::Graph(std::vector<std::vector<int>> matrix) : edges(std::move(matrix)), status(std::vector<int>()), infectionQ() ,infecteds(), totalViruses(0) {
    for (unsigned int i = 0; i<edges.size(); i++){
        status.push_back(0);
    }
}

bool Graph::hasVirus(int nodeInt) const
{
    return (status[nodeInt] != 0);
}

void Graph::infectNode(int nodeInd)
{
    if(status[nodeInd] == 2)
        return;
    status[nodeInd] = 2;
    enqueueInfected(nodeInd);
    infecteds.push_back(nodeInd);
}

bool Graph::isInfected(int nodeInd) const
{
    return status[nodeInd] == 2;
}

bool Graph::isConnected(int nodeInd)
{
    for(unsigned int i = 0; i< edges.size(); i++){
        if (edges[nodeInd][i] == 1)
            return true;
    }
    return false;
}

string Graph:: toString(){
    string s = "[";
    for (auto & edge : edges)
    {
        s += "[";
        for (unsigned  int i = 0; i < edges[0].size(); i++ )
        {
            if (edge[i] == 1)
                s+= '1';
            else
                s+= '0';
        }
        s += "]\n";
    }
    string ret = s.substr(0,s.size()-1);
    ret += ']';
    return ret;
}

void Graph::putVirus(int node) {
    status[node] = 1;
    totalViruses++;
}

void Graph::enqueueInfected(int node) {
    infectionQ.push(node);
}

int Graph::dequeueInfected() {
    if(infectionQ.empty())
        return -1;
    int node = infectionQ.front();
    infectionQ.pop();
    return node;
}

int Graph::getMatrixSize() const {
    return edges.size();
}

const vector<vector<int>> &Graph::getEdges() const {
    return edges;
}

int Graph::getTheMotherFuckerNode(const Session& session ,int rootLabel) {

    int allSize = getMatrixSize();

    //creating array in size of the nodes amount, each index will contain 0 - for white, 1- for grey, 2- for black
    int tmpHash[allSize];
    for(int i = 0; i < allSize; i++){
        tmpHash[i] = 0;
    }

    //main queue of the BFS algorithm
    queue<Tree*> Q;

    Tree *root = Tree::createTree(session, rootLabel);
    Q.push(root);
    while (!Q.empty()) {
        Tree *curTree = Q.front();  // maybe should be used correctly with references/pointers/etc
        Q.pop();
        for (int i = 0; i < allSize; i++) {
            if (edges[curTree->getNode()][i] == 1 && tmpHash[i] == 0) {
                tmpHash[i] = 1;
                Tree *AChild = Tree::createTree(session, i);
                curTree->addChild(*AChild);
                delete AChild;
                //Q.push(AChild);
                Q.push(curTree->getChildren()[curTree->getChildren().size()-1]); // pushing the last children in the current tree to the queue.
            }
        }
        tmpHash[curTree->getNode()] = 2;
    }
    /* TODO here we need to save the integer, then delete the tree, and only then return the integer. otherwise it is a memory leak */
    int nodeInd = root->traceTree();

    //std::cout << "in graph :" + to_string(nodeInd) << endl;
    //std::cout << "still in graph :" + root->toString() << endl;
    delete root;
    return nodeInd;
}

void Graph::disconnectNode(int node) {
    for(unsigned int i = 0; i <edges.size(); i++)
    {
        if(edges[node][i] == 1)
        {
            edges[node][i] = 0;
            edges[i][node] = 0;
        }
    }
}

bool Graph::terminatorCondicator() const { // returns true at the end of the session.
    return infecteds.size() == totalViruses;

/*    int size = edges.size();
    int mainHash[size];
    for (int i = 0 ; i < size ; i++){
        mainHash[i] = 0;
    }

    //main loop
    for (int i = 0 ; i < size ; i++){
        if (mainHash[i] == 0){
            int flag = status[i];
            if (status[i] == 1)
                return false;
            queue<int> Q;
            Q.push(i);
            mainHash[i] = 1;
            while(!Q.empty()){
                int cur = Q.front();
                for (int j = 0 ; j < size ; j++){
                    if(edges[cur][j] == 1 && mainHash[j]==0){
                        if (status[j] != flag)
                            return false;
                        Q.push(j);
                        mainHash[j] = 1;
                    }
                }
                mainHash[i] = 2;
                Q.pop();
            }
        }
    }
    return true;*/
}

vector<int> Graph::getInfecteds() const {
    return infecteds;
}


