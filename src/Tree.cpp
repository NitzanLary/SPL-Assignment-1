//
// Created by spl211 on 09/11/2020.
//

#include "Tree.h"
#include "Session.h"
#include <vector>
#include <queue>

using namespace std;

/*  Tree  */

Tree::Tree(int rootLabel) : node(rootLabel), children(vector<Tree*>()) {
}

void Tree::addChild(const Tree &child) {
    children.push_back(child.copy());
}

int Tree::getNode() const {return node;}

const vector<Tree*> Tree::getChildren(){return children;}


Tree* Tree::createTree(const Session &session, int rootLabel){
    Tree *ret;
    if (session.getTreeType() == MaxRank)
        ret = new MaxRankTree(rootLabel);
    if (session.getTreeType() == Root)
        ret = new RootTree(rootLabel);
    if (session.getTreeType() == Cycle)
        ret = new CycleTree(rootLabel,session.getCycle()); //return *CycleTree(rootLabel,session.getCycle())
    return ret;
}

/** destructor */
Tree::~Tree() {
//    for (Tree* child: children){
//        delete child;
//    }
    clear();
}
/** copy constructor */

Tree::Tree(const Tree &other) : node(other.node), children()
{
    for (Tree* child: other.children)
    {
        addChild(*child);
    }
    node = other.node;
}


/** copy assignment operator */
Tree & Tree::operator=(const Tree &other) {

    if (this == &other) // check self assignment
        return *this;
    clear();
    node = other.node;
    for(Tree* child: other.children){
        addChild(*child);
    }
    return *this;
}



/** move constructor */
Tree::Tree(Tree &&other) : node(other.node), children(other.children)
{
    other.nullChildren();
}

/** move assignment*/
const Tree &Tree::operator=(Tree &&other) {
    if(this == &other)
        return *this;
    clear(); // TODO maybe we should add an extra safety in case of exception, and add a temp value.
    children = other.children;
    node = other.node;
    other.nullChildren();
    return *this;
}

void Tree::clear(){
    for(auto & child : children){
        delete child;
        child = nullptr;
    }
    children.clear();
}

string Tree::toString() {
    string s = "[" + to_string(node) + ": {" ;
    for (auto & child : children){
        s += child->toString() + " , ";
    }
    return s + "}]";
}

void Tree::nullChildren() {
    for(auto & child : children){
        child = nullptr;
    }
    children.clear();
}

/*  CycleTree  */

CycleTree::CycleTree(int rootLabel, int cycle): Tree(rootLabel) , currCycle(cycle) {}


int CycleTree::traceTree(){
    Tree *ret = this;   //currently holds the tree's node value
    while(currCycle > 0){
        if(!ret->getChildren().empty())
            ret = ret->getChildren()[0];
        else
            return ret->getNode();
        currCycle--;
    }
    return ret->getNode();
}

CycleTree *CycleTree::copy() const {
    return new CycleTree(*this);
}

std::string CycleTree::toString() {
    string s = to_string(currCycle);
    s += Tree::toString();
    return s;
}

int CycleTree::getCycle() const {
    return currCycle;
}


/*  MaxRankTree  */

MaxRankTree::MaxRankTree(int rootLabel): Tree(rootLabel){}


int MaxRankTree::traceTree() {
    queue<Tree*> Q;
    Q.push(this);
    int curMax = this->children.size();
    int curIndex = this->node;
    while(!Q.empty()){
        Tree* curr = Q.front();
        for(unsigned int i = 0; i<curr->getChildren().size() ; i++){
            Q.push(curr->getChildren()[i]);
        }
        int currSize = curr->getChildren().size();
        if (currSize > curMax){
            curMax = curr->getChildren().size();
            curIndex = curr->getNode();
        }
        Q.pop();
    }
    return curIndex;
}

MaxRankTree *MaxRankTree::copy() const {
    return new MaxRankTree(*this);
}



/*  RootTree  */

RootTree::RootTree(int rootLabel): Tree(rootLabel){}

int RootTree::traceTree(){
    return node;
}

RootTree *RootTree::copy() const {
    return new RootTree(*this);
}
