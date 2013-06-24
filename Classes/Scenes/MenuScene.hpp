/*
 * MenuScene.hpp
 *
 *  Created on: 2013/6/11
 *      Author: rogerchuang
 */

#ifndef _MENU_SCENE_HPP_
#define _MENU_SCENE_HPP_

#include "cocos2d.h"

namespace ph {

typedef struct _MenuItemInfo
{
    std::string title;
    cocos2d::CCMenuItem *item;
} MenuItemInfo;

class MenuScene : public cocos2d::CCScene
{
public:
    virtual ~MenuScene();

    static cocos2d::CCScene *scene();

    virtual bool init();

    CREATE_FUNC(MenuScene);

private:
    MenuScene();
    std::vector<MenuItemInfo> *getMenuItemInfo();
    void onMenuItemClick(cocos2d::CCObject* pSender);

    static cocos2d::CCScene *sm_pScene;

    cocos2d::CCLayer *m_pBackgroundLayer;
    cocos2d::CCLayer *m_pMenuLayer;

    std::vector<MenuItemInfo> *m_itemInfos;
};

} /* namespace ph */
#endif /* _MENU_SCENE_HPP_ */
