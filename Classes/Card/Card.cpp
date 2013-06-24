/*
 * Card.cpp
 *
 *  Created on: 2013/6/14
 *      Author: rogerchuang
 */

#include <string>
#include <vector>

#include <GLES/gl.h>

#include "Card/Card.hpp"
#include "Card/Deck.hpp"
#include "../Utils/Log.hpp"
#include "../ZOrderConstant.hpp"

using namespace cocos2d;

namespace ph {

const std::string TAG = "Card";

Card* Card::create(const std::string file) {
    Log::d(TAG, "create()");
    Card *card = new Card();
    if(card && card->initWithFile(file.c_str()))
    {
        card->autorelease();
        return card;
    }
    CC_SAFE_DELETE(card);
    return NULL;
}

bool Card::initWithFile(const char *file) {
    Log::d(TAG, "initWithFile()");
    if (!cocos2d::CCSprite::initWithFile(file)) {
        Log::e(TAG, "CCNode::init() == false");
        return false;
    }

    int cardWidth = 192;
    int cardHeight = 256;

    //this->m_pProjectile->setPosition(this->getAnchorPointInPoints());
    //this->m_pProjectile->setVisible(false);
    //this->addChild(this->m_pProjectile, ph::ZOrderConstant::PROJECTILE);
    //this->getParent()->addChild(this->m_pProjectile, ph::ZOrderConstant::PROJECTILE);

    this->setAnchorPoint(ccp(0.5, 0.5));

    this->setScaleX(cardWidth / (float)(this->getContentSize().width));
    this->setScaleY(cardHeight / (float)(this->getContentSize().height));

    return true;
}

Card::Card()
    : m_pNode(0) {
    Log::d(TAG, "Card()");
    //m_pNode = initNode();
}

Card::~Card() {
    Log::d(TAG, "~Card()");
}

void Card::draw() {
    cocos2d::CCSprite::draw();

    /*
    glLineWidth(20);
    cocos2d::ccDrawColor4F(1, 0, 0, 1.0);
    cocos2d::ccDrawLine(ccp(0-3, 0+3), ccp(0+3, 0-3));
    cocos2d::ccDrawLine(
            ccp(this->getContentSize().width+3, this->getContentSize().height-3),
            ccp(this->getContentSize().width-3, this->getContentSize().height+3)
    );
    cocos2d::ccDrawLine(
            ccp(0-3, this->getContentSize().height-3),
            ccp(0+3, this->getContentSize().height+3)
    );
    cocos2d::ccDrawLine(
            ccp(this->getContentSize().width-3, 0-3),
            ccp(this->getContentSize().width+3, 0+3)
    );
    CCPoint p = this->getAnchorPointInPoints();
    cocos2d::ccDrawLine(
            ccp(p.x-3, p.y-3),
            ccp(p.x+3, p.y+3)
    );
    */
}

cocos2d::CCFiniteTimeAction *Card::getAttackAnimation() {
    cocos2d::CCFiniteTimeAction *visibility = cocos2d::CCFadeIn::create(0.1);

    cocos2d::CCActionInterval *rotate1 = cocos2d::CCRotateBy::create(0.15, 20);
    cocos2d::CCFiniteTimeAction *shake = cocos2d::CCSequence::createWithTwoActions(rotate1, rotate1->reverse());
    cocos2d::CCActionInterval *jump = cocos2d::CCJumpBy::create(0.2, ccp(0, 0), 100, 1);
    cocos2d::CCSpawn *animation = cocos2d::CCSpawn::createWithTwoActions(jump, shake);
    cocos2d::CCFiniteTimeAction *action = cocos2d::CCSequence::create(
            jump,
            NULL
    );
    return action;
}

void Card::attack(Deck *pEnemyDeck, CCNode *canvasLayer, cocos2d::SEL_CallFunc callback) {
    Log::d(TAG, "attack()");

    Card *target = pEnemyDeck->getCardAt(0);
    std::vector<Card*> targets;
    targets.push_back(pEnemyDeck->getCardAt(0));
    targets.push_back(pEnemyDeck->getCardAt(1));
    targets.push_back(pEnemyDeck->getCardAt(2));

    for (int i = 0; i < targets.size(); ++i) {
        cocos2d::CCSprite *projectile = cocos2d::CCSprite::create("CloseSelected.png");

        projectile->setPosition(canvasLayer->convertToNodeSpace(this->convertToWorldSpaceAR(ccp(0,0))));
        projectile->setAnchorPoint(ccp(0.5, 0.5));
        canvasLayer->addChild(projectile, ph::ZOrderConstant::PROJECTILE);

        cocos2d::CCParticleSystem *emitter = cocos2d::CCParticleGalaxy::createWithTotalParticles(200);
        emitter->setAnchorPoint(ccp(0.5, 0.5));
        emitter->setPosition(canvasLayer->convertToNodeSpace(this->convertToWorldSpaceAR(ccp(0,0))));
        emitter->setPosition(projectile->getAnchorPointInPoints());
        //emitter->setEndColor(ccc4f(0, 1, 0.2, 0.5));
        /*
        emitter->setPosition(ccp(0, 0));

        emitter->setLife(0);
        emitter->setLifeVar(0.428);
        emitter->setStartSize(5);
        emitter->setStartSizeVar(20);
        emitter->setEndSize(20);
        emitter->setEndSizeVar(0);
        emitter->setAngleVar(360);
        emitter->setDuration(0.2);
        emitter->setEndSpin(180);

        emitter->setSpeed(196);
        emitter->setSpeedVar(59.21);
        emitter->setRadialAccel(10);

        emitter->setSourcePosition(ccp(0, 0));
        emitter->setPosVar(ccp(1, 30));
        emitter->setStartColor(ccc4f(1, 1, 1, 0));
        emitter->setEndColor(ccc4f(0, 0.49, 0, 0));
        emitter->setStartColorVar(ccc4f(0, 0, 0, 0.82));
        emitter->setEndColorVar(ccc4f(0, 0, 0, 0.74));
        cocos2d::ccBlendFunc func;
        func.src = GL_ONE_MINUS_SRC_ALPHA;
        func.dst = GL_ONE_MINUS_SRC_ALPHA;
        emitter->setBlendFunc(func);
        */
        projectile->addChild(emitter, ph::ZOrderConstant::PROJECTILE);
        //canvasLayer->addChild(emitter, ph::ZOrderConstant::PROJECTILE);

        CCPoint targetWorld = targets[i]->convertToWorldSpaceAR(ccp(0, 0));
        CCPoint targetLocal = canvasLayer->convertToNodeSpace(targetWorld);

        CCFiniteTimeAction *follow = cocos2d::CCMoveTo::create(0.3, targetLocal);
        CCFiniteTimeAction *pShoot = CCSequence::create(
                follow,
                CCCallFuncND::create(this, callfuncND_selector(Card::onEnemyHit), (void*)targets[i]),
                cocos2d::CCActionInterval::create(1.5),
                CCCallFuncND::create(this, callfuncND_selector(Card::attackFinishedInternal), (void*)canvasLayer),
                NULL
        );
        this->getActionManager()->addAction(pShoot, projectile, false);
    }
    CCFiniteTimeAction *attackAndCallback = CCSequence::create(
            this->getAttackAnimation(),
            cocos2d::CCActionInterval::create(0.5),
            CCCallFunc::create(canvasLayer, callback),
            NULL
    );
    this->runAction(attackAndCallback);
}

void Card::onEnemyHit(CCNode *projectile, void *enemy) {
    projectile->setVisible(false);
    CCFiniteTimeAction *rotate = cocos2d::CCRotateBy::create(0.05, 5);
    CCFiniteTimeAction *shake = cocos2d::CCSequence::create(
            rotate,
            rotate->reverse(),
            NULL
    );
    ((CCNode*)enemy)->runAction(shake);
    CCParticleFire* m_emitter;
    //m_emitter = cocos2d::CCParticleExplosion::createWithTotalParticles(200);
    m_emitter = cocos2d::CCParticleFire::create();
    m_emitter->setAutoRemoveOnFinish(true);

    m_emitter->setDuration(0.1);
    /*
    m_emitter->setEndColor(ccc4f(1, 0, 0, 1));
    m_emitter->setStartSize(50);
    m_emitter->setStartColor(ccc4f(1, 0, 0, 1));
    m_emitter->setSpeed(100);
    m_emitter->setEndRadius(200);
    */
    //m_emitter->setStartSize(200);
    //m_emitter->setEndSize(400);
    m_emitter->setPosition(((CCNode*)enemy)->getAnchorPointInPoints());

    ((CCNode*)enemy)->addChild(m_emitter, ph::ZOrderConstant::PROJECTILE);
}

void Card::attackFinishedInternal(CCNode *projectile, void *canvasLayer) {
    ((cocos2d::CCLayer*)canvasLayer)->removeChild(projectile);
}

cocos2d::CCNode* Card::initNode() {
    Log::d(TAG, "initNode()");
    cocos2d::CCNode *node = cocos2d::CCSprite::create("HelloWorld.png");
    node->setScaleX(0.5);
    return node;
}

} /* namespace ph */
