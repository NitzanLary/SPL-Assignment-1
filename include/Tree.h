#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include <string>

using namespace std;

class Session;

class Tree{
public:
    Tree(int rootLabel);
    void addChild(const Tree& child);
    int getNode() const;
    const vector<Tree*> getChildren();
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    virtual std::string toString();
    virtual Tree* copy() const=0;
    void clear();
    /* Rule of 5 */     // TODO check correctness for each one, especially on cycleTree.
    virtual ~Tree(); // destructor
    Tree(const Tree &other); // copy constructor
    Tree& operator=(const Tree &other); // copy assignment operator
    Tree(Tree &&other); // move constructor
    const Tree& operator=(Tree &&other); // move assignment

protected:
    int node;
    std::vector<Tree*> children;
    void nullChildren();
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int cycle);
    virtual int traceTree();
    CycleTree* copy() const override;
    std::string toString() override;
    int getCycle() const;

private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
    MaxRankTree* copy() const override;
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
    RootTree* copy() const override;
};

#endif