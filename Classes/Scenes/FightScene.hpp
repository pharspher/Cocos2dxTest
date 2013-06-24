/*
 * FightScene.hpp
 *
 *  Created on: 2013/6/14
 *      Author: rogerchuang
 */

#ifndef _FIGHT_SCENE_HPP_
#define _FIGHT_SCENE_HPP_

#include <vector>
#include <string>

#include "cocos2d.h"

#include "../Card/Card.hpp"
#include "../Card/Deck.hpp"

namespace ph {

class FightScene : public cocos2d::CCLayerColor
{
public:
    static cocos2d::CCScene *scene();

    virtual ~FightScene();

    virtual bool init();
    virtual void keyBackClicked();

    static cocos2d::CCLayer* create(const cocos2d::ccColor4B &color);
    virtual bool initWithColor(const cocos2d::ccColor4B &color);

    //CREATE_FUNC(FightScene);

private:
    FightScene();
    Deck* initPlayerDeck();
    Deck* initEnemyDeck();

    void startFight();
    void nextCard();

    static cocos2d::CCScene *sm_pMainScene;
    static cocos2d::CCLayer *sm_pMainLayer;

    const static int sm_nPlayerCard = 6;
    const static int sm_nEnemyCard = 6;

    Deck *m_playerDeck;
    Deck *m_enemyDeck;
    int m_currentCard;
    int m_currentSide;
};

} /* namespace ph */
#endif /* _FIGHT_SCENE_HPP_ */
