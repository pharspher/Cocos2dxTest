/*
 * MenuScene.cpp
 *
 *  Created on: 2013/6/11
 *      Author: rogerchuang
 */

#include "MenuScene.hpp"
#include "FightScene.hpp"
#include "../Utils/Log.hpp"

#include <string>

#include "platform/android/jni/JniHelper.h"
#include <jni.h>

using namespace cocos2d;

namespace ph {

const std::string TAG = "MenuScene";

// constant definition
const int TAG_MENU_ITEM_DUMMY = 0;
const int TAG_MENU_ITEM_EXIT = 1;
const int TAG_MENU_ITEM_ENTER_GAME_SCENE = 2;

// static member initialization
cocos2d::CCScene *MenuScene::sm_pScene = 0;

MenuScene::MenuScene()
    : m_itemInfos(0) {
    Log::d(TAG, "MenuScene()");
}

MenuScene::~MenuScene() {
    Log::d(TAG, "~MenuScene()");
    if (m_itemInfos) {
        delete m_itemInfos;
    }
}

cocos2d::CCScene* MenuScene::scene() {
    Log::d(TAG, "scene()");
    if (!sm_pScene) {
        sm_pScene = MenuScene::create();
    }
    return sm_pScene;
}

bool MenuScene::init() {
    Log::d(TAG, "init()");
    if (!cocos2d::CCScene::init()) {
        Log::e(TAG, "CCScene::init() == false");
        return false;
    }

    m_pBackgroundLayer = cocos2d::CCLayerGradient::create(ccc4(255, 0, 255, 200), ccc4(255, 255, 0, 200));
    this->addChild(m_pBackgroundLayer, 0);

    m_itemInfos = getMenuItemInfo();
    for (int i = 0; i< m_itemInfos->size(); i++) {
        MenuItemInfo info = (*m_itemInfos)[i];
        info.item->setPosition(0, -i * info.item->getContentSize().height * 2);
        cocos2d::CCMenu *itemLayer = cocos2d::CCMenu::createWithItem(info.item);
        this->addChild(itemLayer, 1);
    }

    return true;
}

// Local function
void MenuScene::onMenuItemClick(cocos2d::CCObject* pSender) {
    int tag = ((cocos2d::CCMenuItem*)pSender)->getTag();
    switch (tag) {
    case TAG_MENU_ITEM_EXIT:
        CCDirector::sharedDirector()->end();
        break;
    case TAG_MENU_ITEM_ENTER_GAME_SCENE:
    {
        cocos2d::CCTransitionFade *sceneTran = cocos2d::CCTransitionFade::create(0.8, FightScene::scene());
        cocos2d::CCDirector::sharedDirector()->pushScene(sceneTran);
        break;
    }
    default:
        Log::e(TAG, "Unknown menu item tag: " + tag);
        break;
    }
}

std::vector<MenuItemInfo> *MenuScene::getMenuItemInfo() {
    std::vector<MenuItemInfo> *itemInfo = new std::vector<MenuItemInfo>();

    MenuItemInfo info1;
    info1.title = "Start";
    cocos2d::CCLabelTTF *infoLabel1 = cocos2d::CCLabelTTF::create(info1.title.data(), "Thonburi", 64);
    info1.item = cocos2d::CCMenuItemLabel::create(infoLabel1, this, menu_selector(MenuScene::onMenuItemClick));
    info1.item->setTag(TAG_MENU_ITEM_ENTER_GAME_SCENE);
    itemInfo->push_back(info1);

    MenuItemInfo info2;
    info2.title = "Quit";
    cocos2d::CCLabelTTF *infoLabel2 = cocos2d::CCLabelTTF::create(info2.title.data(), "Thonburi", 64);
    info2.item = cocos2d::CCMenuItemLabel::create(infoLabel2, this, menu_selector(MenuScene::onMenuItemClick));
    info2.item->setTag(TAG_MENU_ITEM_EXIT);
    itemInfo->push_back(info2);

    return itemInfo;
}

} /* namespace ph */
