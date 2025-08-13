// FUCK YOU
#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class GadolinUI : public geode::Popup<> {
protected:
    CCMenu* m_categoryMenu;
    CCMenu* m_contentMenu;
    std::string m_currentCategory;

    bool setup() override;
    void setupCategories();
    void setupContent();
    void updateContentForCategory(const std::string& category);
    
    void onCategoryPressed(CCObject* sender);
    void onTogglePressed(CCObject* sender);
    void onSliderChanged(CCObject* sender);
    void onPopupPressed(CCObject* sender);

    CCMenuItemSpriteExtra* createCategoryButton(const std::string& category);
    CCMenuItemToggler* createToggleOption(const std::string& saveKey, bool defaultVal);
    CCNode* createSliderOption(const std::string& saveKey, float defaultVal, float min, float max);
    CCMenuItemSpriteExtra* createPopupButton(const std::string& action);

public:
    static GadolinUI* create() {
        auto ret = new GadolinUI();
        if (ret && ret->initAnchored(480.f, 320.f)) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }
};
