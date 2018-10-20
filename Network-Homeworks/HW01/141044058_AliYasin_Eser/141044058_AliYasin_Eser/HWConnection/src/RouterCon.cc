

#include <string.h>
#include <omnetpp.h>
#include "CommunicationMsg_m.h"
using namespace omnetpp;


class Router : public cSimpleModule
{
  protected:
    // The following redefined virtual function holds the algorithm.
    virtual void handleMessage(cMessage *msg) override;
    void forwardMessage(CommunicationMsg *msg);
};

// The module class needs to be registered with OMNeT++
Define_Module(Router);

//handle function, only does the forward.
void Router::handleMessage(cMessage *msg)
{
    forwardMessage((CommunicationMsg*)msg);
}

/**
 * forwards message with checking the message destination
 */
void Router::forwardMessage(CommunicationMsg *msg)
{

    int n = getParentModule()->par("n");
    // Debug
    // EV << getIndex() << "  " << msg->getDestination() << "%" << n << " =   " << (msg->getDestination())%n << "\n";
    if(msg->getDestination() == -1)
        send(msg, "swout");
    else if((msg->getDestination())%n == getIndex())
        send(msg, "nodeOut", (int)(msg->getDestination()/n));
    else{
        // if stands for breaking the infinite loop. When connecting, index 0 has a lock.
        if(getIndex() == 0)
            send(msg, "routerOut", 0);
        else
            send(msg, "routerOut", 1);

    }
}


