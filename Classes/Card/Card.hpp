/*
 * Card.hpp
 *
 *  Created on: 2013/6/14
 *      Author: rogerchuang
 */

#ifndef _CARD_HPP_
#define _CARD_HPP_

#include <string>

#include "cocos2d.h"

namespace ph {

class Deck;

class Card : public cocos2d::CCSprite {
public:
    static Card* create(const std::string file);

    virtual bool initWithFile(const char *file);

    virtual ~Card();
    //inline cocos2d::CCNode* getNode() {
    //    return m_pNode;
    //}

    virtual void draw();

    cocos2d::CCFiniteTimeAction *getAttackAnimation();
    void attack(Deck *pEnemyDeck, CCNode *canvasLayer, cocos2d::SEL_CallFunc callback);
    void attackFinishedInternal(CCNode *projectile, void *canvasLayer);
    void onEnemyHit(CCNode *projectile, void *enemy);

protected:
    virtual cocos2d::CCNode* initNode();

public:
    Card();

    cocos2d::CCNode *m_pNode;
    cocos2d::CCSprite *m_pProjectile;
};

} /* namespace ph */
#endif /* _CARD_HPP_ */
