/*
 * NodeCon.cc
 *
 *  Created on: 23 Nis 2017
 *      Author: Ali Yasin Eser
 */


#include <string.h>
#include <omnetpp.h>
#include "CommunicationMsg_m.h"

using namespace omnetpp;


class Node : public cSimpleModule
{
  protected:
    // The following redefined virtual function holds the algorithm.
    virtual void handleMessage(cMessage *msg) override;
};


Define_Module(Node);

// Checks if message came to right place. Sends new message randomly to another node.
void Node::handleMessage(cMessage *msg)
{
    int m = getParentModule()->par("m");


    if(((CommunicationMsg*)msg)->getDestination() == getIndex()){
        EV << ((CommunicationMsg*)msg)->getTotalMessageCount() << "th message came from " << ((CommunicationMsg*)msg)->getSource() << " to " << ((CommunicationMsg*)msg)->getDestination()<<"\n";
        if(((CommunicationMsg*)msg)->getMessageCount() == 29) return;
       int k;
       while(k == getIndex())
           k = intuniform(-1, m-1);
       CommunicationMsg *msgOther = new CommunicationMsg("Message");
       msgOther->setSource(getIndex());
       msgOther->setDestination(k);
       msgOther->setMessageCount(((CommunicationMsg*)msg)->getMessageCount()+1);
       EV << ((CommunicationMsg*)msg)->getTotalMessageCount() << "th message has been sending from " << ((CommunicationMsg*)msgOther)->getSource()
               << " to " << ((CommunicationMsg*)msgOther)->getDestination()<<"\n";
       send(msgOther, "out"); // send out the message

    }
}


