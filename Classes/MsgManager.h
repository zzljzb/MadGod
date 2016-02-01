//
//  MsgManager.hpp
//  MyGame
//
//  Created by mixi on 16/1/31.
//
//

#ifndef MsgManager_hpp
#define MsgManager_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class MsgManager : public Node
{
public:
    static MsgManager* getInstance();
    void popMsg(string str);
    
private:
    bool init();
    MsgManager();
    ~MsgManager();
    void createLabel(string str);
    void removeLabelTag(Node* sender, int tag);
    void moveAllLabel();
    
    bool _popingMsg;
//    Vector<string> _msgInfo;
    Vector<Label*> _msgLabelVec;
    int _msgIndex;
    
};
#endif /* MsgManager_hpp */
