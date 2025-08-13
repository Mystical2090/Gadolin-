#include <Geode/Geode.hpp>
#include "ui.hpp"
#include <Geode/modify/CCKeyboardDispatcher.hpp>

using namespace geode::prelude;

class $modify(dickshit, cocos2d::CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(cocos2d::enumKeyCodes key, bool isKeyDown, bool isKeyRepeat) {
        if (key == cocos2d::enumKeyCodes::KEY_Tab && isKeyDown) {
            geode::log::info("ui opened");
            ui::create()->show();
        }
        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, isKeyDown, isKeyRepeat);
    }
};
