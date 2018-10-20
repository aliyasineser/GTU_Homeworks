//
// Generated file, do not edit! Created by nedtool 5.1 from CommunicationMsg.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __COMMUNICATIONMSG_M_H
#define __COMMUNICATIONMSG_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0501
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>CommunicationMsg.msg:20</tt> by nedtool.
 * <pre>
 * //
 * // TODO generated message class
 * //
 * message CommunicationMsg
 * {
 *     int messageCount;
 *     int source;
 *     int destination;
 * }
 * </pre>
 */
class CommunicationMsg : public ::omnetpp::cMessage
{
  protected:
    int messageCount;
    int source;
    int destination;

  private:
    void copy(const CommunicationMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const CommunicationMsg&);

  public:
    CommunicationMsg(const char *name=nullptr, short kind=0);
    CommunicationMsg(const CommunicationMsg& other);
    virtual ~CommunicationMsg();
    CommunicationMsg& operator=(const CommunicationMsg& other);
    virtual CommunicationMsg *dup() const override {return new CommunicationMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getMessageCount() const;
    virtual void setMessageCount(int messageCount);
    virtual int getSource() const;
    virtual void setSource(int source);
    virtual int getDestination() const;
    virtual void setDestination(int destination);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const CommunicationMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, CommunicationMsg& obj) {obj.parsimUnpack(b);}


#endif // ifndef __COMMUNICATIONMSG_M_H

