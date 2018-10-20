

#include <string.h>
#include <omnetpp.h>
#include "CommunicationMsg_m.h"
using namespace omnetpp;


class Server : public cSimpleModule
{
  protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void forwardMessage(CommunicationMsg *msg);
};

// The module class needs to be registered with OMNeT++
Define_Module(Server);

void Server::initialize()
{
    int n = getParentModule()->par("n");
    int m = getParentModule()->par("m");
    int k = intuniform(0, m-1);
    int j = intuniform(0, n-1);
    CommunicationMsg *msg = new CommunicationMsg("Message");
    msg->setSource(-1);
    msg->setDestination(k);
    msg->setMessageCount(0);
    EV << "Message has been sending from " << ((CommunicationMsg*)msg)->getSource() << " to " << ((CommunicationMsg*)msg)->getDestination()<<"\n";
    send(msg, "out",j);

}
/**
 * handles message and creates another
 */
void Server::handleMessage(cMessage *msg)
{
    int m = getParentModule()->par("m");
    if(((CommunicationMsg*)msg)->getDestination() == -1){
        EV << ((CommunicationMsg*)msg)->getTotalMessageCount() << "th message came from " << ((CommunicationMsg*)msg)->getSource() << " to " << ((CommunicationMsg*)msg)->getDestination()<<"\n";
        if(((CommunicationMsg*)msg)->getMessageCount() == 29) return;
       int k;
       k = intuniform(0, m-1);
       CommunicationMsg *msgOther = new CommunicationMsg("Message");
       msgOther->setSource(getIndex());
       msgOther->setDestination(k);
       msgOther->setMessageCount(((CommunicationMsg*)msg)->getMessageCount()+1);
       EV << ((CommunicationMsg*)msg)->getTotalMessageCount() << "th message has been sending from " << ((CommunicationMsg*)msgOther)->getSource()
               << " to " << ((CommunicationMsg*)msgOther)->getDestination()<<"\n";
       send(msgOther, "out", 0); // send out the message
    }
    else
        forwardMessage((CommunicationMsg*)msg);
}

/**
 * forwards the message which has a different destination. Server forwards it to routers so message can arrive.
 */
void Server::forwardMessage(CommunicationMsg *msg)
{
    send(msg, "out",0); // send out the message
}

