/*
 * Deck.hpp
 *
 *  Created on: 2013/6/16
 *      Author: rogerchuang
 */

#ifndef _DECK_HPP_
#define _DECK_HPP_

#include <vector>

#include "cocos2d.h"

#include "Card.hpp"

namespace ph {

class Deck {
public:
    Deck(int nCol, int nRow);
    virtual ~Deck();

    void addCard(Card *card);
    inline cocos2d::CCNode *getNode() {
        return m_pNode;
    }

    inline int getColumnNumber() const {
        return m_nColumns;
    }

    inline int getRowNumber() const {
        return m_nRows;
    }

    void init();
    void init(cocos2d::CCLayer *pLayer);
    Card* getCardAt(int index);
    void setSize(const cocos2d::CCSize &size) {
        m_size = size;
    }
    void setPosition(const cocos2d::CCPoint &pos) {
        m_position = pos;
    }
    void setDirection(const cocos2d::CCPoint& point);

protected:
    virtual cocos2d::CCNode* initNode();

private:
    Deck();

    cocos2d::CCNode *m_pNode;
    std::vector<Card*> m_cardSet;

    cocos2d::CCPoint m_position;
    cocos2d::CCSize m_size;

    int m_nColumns;
    int m_nRows;

    cocos2d::CCPoint m_direction;
};

} /* namespace ph */
#endif /* _DECK_HPP_ */
