/*
 * Deck.cpp
 *
 *  Created on: 2013/6/16
 *      Author: rogerchuang
 */

#include <string>
#include <algorithm>

#include "Card/Deck.hpp"

#include "../Utils/Log.hpp"
#include "../ZOrderConstant.hpp"

using namespace cocos2d;

namespace ph {

const std::string TAG = "Deck";

Deck::Deck() {
}

Deck::Deck(int nCol, int nRow)
    : m_nColumns(nCol),
      m_nRows(nRow),
      m_direction(ccp(0, 1)),
      m_position(ccp(0, 0)),
      m_size(CCSize(0, 0)) {
    Log::d(TAG, "Deck()");
    m_pNode = initNode();
    //m_pNode->ignoreAnchorPointForPosition(false);
}

Deck::~Deck() {
    Log::d(TAG, "~Deck()");
    for (unsigned int i = 0; i < m_cardSet.size(); ++i) {
        Card *c = m_cardSet[i];
        if (c) {
            delete c;
        }
    }
}

void Deck::addCard(Card *card) {
    Log::d(TAG, "addCard()");
    m_cardSet.push_back(card);

    //card->getNode()->setAnchorPoint(ccp(0, 0));
    //card->getNode()->setPosition(ccp(0, 0));
}

Card* Deck::getCardAt(int index) {
    if (index >= m_cardSet.size()) {
        Log::e(TAG, "getCardAt(): index out of range");
        return 0;
    }
    return m_cardSet[index];
}

void Deck::setDirection(const cocos2d::CCPoint& direction) {
    this->m_direction = direction;
}

void Deck::init() {
    Log::d(TAG, "init()");
    if (m_cardSet.empty()) {
        Log::e(TAG, "card set is empty");
        return;
    }
    Card *card = m_cardSet[0];
    int maxCard = m_nColumns * m_nRows;
    int nCard = (m_cardSet.size() > maxCard) ? maxCard : m_cardSet.size();
    int cardWidth = card->boundingBox().size.width;
    int deckWidth = this->m_size.width;
    int deckHeight = this->m_size.height;
    int cardHeight = card->boundingBox().size.height;
    int paddingH = (deckWidth - m_nColumns * cardWidth) / float(m_nColumns + 1);
    int paddingV = (deckHeight - m_nRows * cardHeight) / float(m_nRows + 1);
    int offsetX = cardWidth / 2.0f;
    int offsetY = cardHeight / 2.0f;

    for (unsigned int i = 0; i < nCard; ++i) {
        cocos2d::CCNode *node = m_cardSet[i];
        int x = i % m_nColumns;
        int y = i / m_nColumns;

        // face up
        if (m_direction.y - m_direction.x >= 0) {
            int originY = this->m_pNode->getContentSize().height;
            node->setPosition(ccp(
                    offsetX + paddingH + x * (cardWidth + paddingH),
                    originY - (offsetY + paddingV + y * (cardHeight + paddingV))
            ));
            //this->getNode()->addChild(node, ph::ZOrderConstant::CARD);

        // face down
        } else {
            //node->setAnchorPoint(ccp(0, 0));
            node->setPosition(ccp(
                    offsetX + paddingH + x * (cardWidth + paddingH),
                    offsetY + paddingV + y * (cardHeight + paddingV)
            ));
            //this->getNode()->addChild(node, ph::ZOrderConstant::CARD);
        }
    }
}

void Deck::init(cocos2d::CCLayer *pLayer) {
    Log::d(TAG, "init()");
    if (m_cardSet.empty()) {
        Log::e(TAG, "card set is empty");
        return;
    }
    Card *card = m_cardSet[0];
    int maxCard = m_nColumns * m_nRows;
    int nCard = (m_cardSet.size() > maxCard) ? maxCard : m_cardSet.size();
    int cardWidth = card->boundingBox().size.width;
    int deckWidth = this->m_size.width;
    int deckHeight = this->m_size.height;
    int cardHeight = card->boundingBox().size.height;
    int paddingH = (deckWidth - m_nColumns * cardWidth) / float(m_nColumns + 1);
    int paddingV = (deckHeight - m_nRows * cardHeight) / float(m_nRows + 1);
    int offsetX = cardWidth / 2.0f;
    int offsetY = cardHeight / 2.0f;

    card->setAnchorPoint(ccp(0.5, 0.5));

    for (unsigned int i = 0; i < nCard; ++i) {
        cocos2d::CCNode *node = m_cardSet[i];
        int x = i % m_nColumns;
        int y = i / m_nColumns;

        // face up
        if (m_direction.y - m_direction.x >= 0) {
            //int originY = this->m_pNode->getContentSize().height;
            node->setPosition(ccp(
                    offsetX + paddingH + x * (cardWidth + paddingH) + this->m_position.x,
                    /*offsetY + paddingV + y * (cardHeight + paddingV) + this->m_position.y*/
                    (this->m_position.y + this->m_size.height) - ((paddingV + y * (cardHeight + paddingV)) + offsetY)

            ));
            if (y == 0) {
                pLayer->addChild(node, ph::ZOrderConstant::CARD_FAR);
            } else {
                pLayer->addChild(node, ph::ZOrderConstant::CARD_FAR);
            }

        // face down
        } else {
            //node->setAnchorPoint(ccp(0, 0));
            node->setPosition(ccp(
                    offsetX + paddingH + x * (cardWidth + paddingH) + this->m_position.x,
                    offsetY + paddingV + y * (cardHeight + paddingV) + this->m_position.y
            ));
            if (y == 0) {
                pLayer->addChild(node, ph::ZOrderConstant::CARD_NEAR);
            } else {
                pLayer->addChild(node, ph::ZOrderConstant::CARD_FAR);
            }
        }
    }
}

cocos2d::CCNode* Deck::initNode() {
    Log::d(TAG, "initNode()");
    //cocos2d::CCNode *node = cocos2d::CCLayerColor::create(ccc4(128, 255, 255, 200));
    cocos2d::CCNode *node = cocos2d::CCNode::create();
    //node->setColor(ccc3(0, 255, 255));
    return node;
}

} /* namespace ph */
