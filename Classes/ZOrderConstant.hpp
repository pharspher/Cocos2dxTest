/*
 * ZOrderConstant.hpp
 *
 *  Created on: 2013/6/23
 *      Author: rogerchuang
 */

#ifndef _Z_ORDER_CONSTANT_HPP_
#define _Z_ORDER_CONSTANT_HPP_

namespace ph {

class ZOrderConstant {
private:
    const static int INTERVAL = 1000;

public:
    const static int SCENE = 0;
    const static int LAYER = SCENE + INTERVAL;
    const static int DECK = LAYER + INTERVAL;
    const static int CARD_FAR = DECK + INTERVAL;
    const static int CARD_NEAR = CARD_FAR + INTERVAL;
    const static int PROJECTILE = CARD_NEAR + INTERVAL;
};

}

#endif /* _Z_ORDER_CONSTANT_HPP_ */
