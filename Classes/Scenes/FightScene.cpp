/*
 * FightScene.cpp
 *
 *  Created on: 2013/6/14
 *      Author: rogerchuang
 */

#include "platform/android/jni/JniHelper.h"
#include <jni.h>

#include <string>
#include <sstream>

#include "FightScene.hpp"
#include "../Utils/Log.hpp"
#include "../ZOrderConstant.hpp"

using namespace cocos2d;

namespace ph {

// constant definition
const static std::string TAG = "FightScene";
const int PLAYER_TURN = 0;
const int ENEMY_TURN = 1;

// static member initialization
cocos2d::CCScene *FightScene::sm_pMainScene = 0;
cocos2d::CCLayer *FightScene::sm_pMainLayer = 0;

FightScene::FightScene() {
    Log::d(TAG, "FightScene()");
    m_playerDeck = initPlayerDeck();
    m_enemyDeck = initEnemyDeck();
}

FightScene::~FightScene() {
    Log::d(TAG, "~FightScene()");
    if (this->m_playerDeck) {
        delete this->m_playerDeck;
    }
    if (this->m_enemyDeck) {
        delete this->m_enemyDeck;
    }
    /*
    for (unsigned int i = 0; i < m_playerDeck.size(); ++i) {
        try {
            Card *card = m_playerDeck[i];
            if (m_playerDeck[i]) {
                delete m_playerDeck[i];
            }
        } catch (const std::exception& e) {
            Log::e(TAG, e.what());
        }
    }
    */
}

cocos2d::CCScene *FightScene::scene() {
    Log::d(TAG, "scene()");
    sm_pMainScene = cocos2d::CCScene::create();

    sm_pMainLayer = FightScene::create(ccc4(0, 0, 0, 255));
    sm_pMainLayer->setTouchEnabled(true);
    sm_pMainLayer->setKeypadEnabled(true);

    sm_pMainScene->addChild(sm_pMainLayer, ph::ZOrderConstant::LAYER);
    sm_pMainLayer->schedule(schedule_selector(FightScene::startFight), 1.0f);
    return sm_pMainScene;
}

cocos2d::CCLayer* FightScene::create(const ccColor4B& color) {
    FightScene * pLayer = new FightScene();
    if(pLayer && pLayer->initWithColor(color))
    {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

bool FightScene::init() {
    Log::d(TAG, "init()");
    if (!cocos2d::CCLayerRGBA::init()) {
        Log::e(TAG, "CCLayer::init() == false");
        return false;
    }
    //this->addChild(this->m_playerDeck->getNode(), ph::ZOrderConstant::DECK);
    //this->addChild(this->m_enemyDeck->getNode(), ph::ZOrderConstant::DECK);
    return true;
}

void FightScene::startFight() {
    Log::d(TAG, "startFight()");
    this->unschedule(schedule_selector(FightScene::startFight));
    this->m_currentSide = PLAYER_TURN;
    this->m_currentCard = 0;
    nextCard();

}

void FightScene::nextCard() {
    Card *currentCard;
    if (this->m_currentSide == PLAYER_TURN) {
        currentCard = this->m_playerDeck->getCardAt(m_currentCard);
        this->m_currentSide = ENEMY_TURN;
        currentCard->attack(this->m_enemyDeck, this, callfunc_selector(FightScene::nextCard));
    } else if (this->m_currentSide == ENEMY_TURN) {
        currentCard = this->m_enemyDeck->getCardAt(m_currentCard);
        this->m_currentSide = PLAYER_TURN;
        m_currentCard++;
        m_currentCard = m_currentCard % FightScene::sm_nPlayerCard;
        currentCard->attack(this->m_playerDeck, this, callfunc_selector(FightScene::nextCard));
    }


    /*
    cocos2d::CCFiniteTimeAction *action = cocos2d::CCSequence::create(
            currentCard->getAttackAnimation(),
            cocos2d::CCCallFunc::create(this, callfunc_selector(FightScene::nextCard)),
            NULL
    );
    currentCard->runAction(action);
    */
    //this->addChild(currentCard->m_pProjectile, 100);


}

bool FightScene::initWithColor(const ccColor4B& color) {
    Log::d(TAG, "initWithColor()");
    if (!cocos2d::CCLayerColor::initWithColor(color)) {
        Log::e(TAG, "CCLayerColor::init() == false");
        return false;
    }
    return init();
}

void FightScene::keyBackClicked() {
    Log::d(TAG, "keyBackClicked()");
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(
            methodInfo,
            "org/ph/deckbattle/MainActivity",
            "showLeaveDialog",
            "()V")) {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
    } else {
        Log::e(TAG, "Can't find static method showLeaveDialog() of MainActivity");
    }
}

Deck* FightScene::initPlayerDeck() {
    Log::d(TAG, "initPlayerDeck()");
    Deck *deck = new Deck(3, 2);
    for (unsigned i = 0; i < this->sm_nPlayerCard; ++i) {
        Card *c = Card::create("HelloWorld.png");
        deck->addCard(c);
    }
    /*
    cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    cocos2d::CCNode *deckNode = deck->getNode();
    deckNode->setContentSize(CCSizeMake(winSize.width * 0.9, winSize.height * 0.4));
    deckNode->setAnchorPoint(ccp(0, 0));
    deckNode->setPosition(ccp(winSize.width * 0.05, winSize.width * 0.05));
    deck->init();
    */
    cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    deck->setSize(CCSizeMake(winSize.width * 0.9, winSize.height * 0.4));
    //deck->setPosition(ccp(winSize.width * 0.05, winSize.height - (winSize.width * 0.05)));
    deck->setPosition(ccp(winSize.width * 0.05, winSize.width * 0.05));
    deck->init(this);
    return deck;
}

Deck* FightScene::initEnemyDeck() {
    Log::d(TAG, "initEnemyDeck()");
    Deck *deck = new Deck(3, 2);
    deck->setDirection(ccp(1, 0));
    for (unsigned i = 0; i < this->sm_nEnemyCard; ++i) {
        Card *c = Card::create("HelloWorld.png");
        deck->addCard(c);
    }

    cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    deck->setSize(CCSizeMake(winSize.width * 0.9, winSize.height * 0.4));
    //deck->setPosition(ccp(winSize.width * 0.05, winSize.height - (winSize.width * 0.05)));
    deck->setPosition(ccp(winSize.width * 0.05, winSize.height - ((winSize.width * 0.05) + winSize.height * 0.4)));
    //cocos2d::CCNode *deckNode = deck->getNode();
    //deckNode->setContentSize(CCSizeMake(winSize.width * 0.9, winSize.height * 0.4));
    //deckNode->setAnchorPoint(ccp(0, 1));
    //deckNode->setPosition(ccp(winSize.width * 0.05, winSize.height - (winSize.width * 0.05)));
    deck->init(this);

    return deck;
}

extern "C" {

void Java_org_ph_deckbattle_MainActivity_onLeaveDialogConfirmed() {
    Log::d(TAG, "Java_org_ph_deckbattle_MainActivity_onLeaveDialogConfirmed()");
    //cocos2d::CCDirector::sharedDirector()->popScene();
    cocos2d::CCDirector::sharedDirector()->end();
}

void Java_org_ph_deckbattle_MainActivity_onLeaveDialogCanceled() {
    Log::d(TAG, "Java_org_ph_deckbattle_MainActivity_onLeaveDialogCanceled()");
}

}

} /* namespace ph */
