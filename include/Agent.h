//
// Created by spl211 on 05/11/2020.
//

#ifndef HW1_AGENT_H
#define HW1_AGENT_H

#include <vector>
#include "Session.h"
using namespace std;

class Agent{
public:
    Agent();

    virtual void act(Session& session)=0;
    virtual Agent* clone() const=0;
    virtual string toString()=0;

    virtual ~Agent()=default;


};

class ContactTracer: public Agent{
public:
    ContactTracer();

    virtual void act(Session& session);
    Agent* clone() const override;
    string toString() override; // override because of a warning
};


class Virus: public Agent{
public:
    Virus(int nodeInd);
    virtual void act(Session& session);

    Agent* clone()const override;
    string toString() override;

private:
    const int nodeInd;

};

#endif