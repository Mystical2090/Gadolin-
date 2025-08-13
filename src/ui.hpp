// FUCK YOU
#pragma once
#include <Geode/Geode.hpp>
using namespace geode::prelude;

class GadolinUI : public geode::Popup<> {
protected:
    CCMenu* m_categoryMenu;
    CCMenu* m_contentMenu;
    CCLabelBMFont* m_titleLabel;
    std::string m_currentCategory;

    bool setup() override;
    void setupCategories();
    void setupContent();
    void updateContentForCategory(const std::string& category);
    
    void onCategoryPressed(CCObject* sender);
    void onPlayerOptionPressed(CCObject* sender);
    void onCreatorOptionPressed(CCObject* sender);
    void onMiscOptionPressed(CCObject* sender);
    void onSettingsOptionPressed(CCObject* sender);

    CCMenuItemSpriteExtra* createCategoryButton(const std::string& category);
    CCMenuItemToggler* createToggleOption(const std::string& text, bool enabled, SEL_MenuHandler callback);
    CCMenuItemSpriteExtra* createActionButton(const std::string& text, SEL_MenuHandler callback);

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
