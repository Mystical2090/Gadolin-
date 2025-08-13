#include <Geode/Geode.hpp>
#include "ui.hpp"

using namespace geode::prelude;

bool GadolinUI::setup() {
    this->setTitle("Gadolin");
    
    auto bg = CCScale9Sprite::create("square02b_001.png");
    bg->setColor({20, 20, 30});
    bg->setContentSize(this->getContentSize());
    bg->setPosition(this->getContentSize() / 2);
    m_mainLayer->addChild(bg, -1);

    setupCategories();
    setupContent();
    
    m_currentCategory = "Player";
    updateContentForCategory(m_currentCategory);
    
    return true;
}

void GadolinUI::setupCategories() {
    m_categoryMenu = CCMenu::create();
    m_categoryMenu->setLayout(RowLayout::create()->setGap(5.f));
    m_categoryMenu->setContentSize({400.f, 30.f});
    m_mainLayer->addChildAtPosition(m_categoryMenu, Anchor::Top, {0.f, -30.f});

    std::vector<std::string> categories = {"Player", "Creator", "Misc", "Settings"};
    for (const auto& category : categories) {
        auto button = createCategoryButton(category);
        m_categoryMenu->addChild(button);
    }
    m_categoryMenu->updateLayout();
}

void GadolinUI::setupContent() {
    m_contentMenu = CCMenu::create();
    m_contentMenu->setLayout(ColumnLayout::create()->setGap(8.f)->setAxisReverse(true));
    m_contentMenu->setContentSize({400.f, 200.f});
    m_mainLayer->addChildAtPosition(m_contentMenu, Anchor::Center, {0.f, -20.f});
}

CCMenuItemSpriteExtra* GadolinUI::createCategoryButton(const std::string& category) {
    auto sprite = CCSprite::createWithSpriteFrameName("GJ_button_01.png");
    sprite->setScale(0.8f);
    
    auto button = CCMenuItemSpriteExtra::create(
        sprite, this, menu_selector(GadolinUI::onCategoryPressed)
    );
    
    auto label = CCLabelBMFont::create(category.c_str(), "goldFont.fnt");
    label->setScale(0.6f);
    label->setPosition(sprite->getContentSize() / 2);
    sprite->addChild(label);
    
    button->setUserObject(CCString::create(category));
    return button;
}

CCMenuItemToggler* GadolinUI::createToggleOption(const std::string& text, bool enabled, SEL_MenuHandler callback) {
    auto onSprite = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
    auto offSprite = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
    onSprite->setScale(0.8f);
    offSprite->setScale(0.8f);
    
    auto toggle = CCMenuItemToggler::create(offSprite, onSprite, this, callback);
    toggle->toggle(enabled);
    
    auto label = CCLabelBMFont::create(text.c_str(), "chatFont.fnt");
    label->setScale(0.7f);
    label->setPosition({toggle->getContentSize().width + 50.f, toggle->getContentSize().height / 2});
    label->setAnchorPoint({0.f, 0.5f});
    toggle->addChild(label);
    
    return toggle;
}

CCMenuItemSpriteExtra* GadolinUI::createActionButton(const std::string& text, SEL_MenuHandler callback) {
    auto sprite = CCSprite::createWithSpriteFrameName("GJ_button_04.png");
    sprite->setScale(0.7f);
    
    auto button = CCMenuItemSpriteExtra::create(sprite, this, callback);
    
    auto label = CCLabelBMFont::create(text.c_str(), "bigFont.fnt");
    label->setScale(0.5f);
    label->setPosition(sprite->getContentSize() / 2);
    sprite->addChild(label);
    
    return button;
}

void GadolinUI::onCategoryPressed(CCObject* sender) {
    auto button = static_cast<CCMenuItemSpriteExtra*>(sender);
    auto categoryStr = static_cast<CCString*>(button->getUserObject());
    m_currentCategory = categoryStr->getCString();
    updateContentForCategory(m_currentCategory);
}

void GadolinUI::updateContentForCategory(const std::string& category) {
    m_contentMenu->removeAllChildren();
    
    if (category == "Player") {
        auto noclip = createToggleOption("Noclip", false, menu_selector(GadolinUI::onPlayerOptionPressed));
        auto speedhack = createToggleOption("Speedhack", false, menu_selector(GadolinUI::onPlayerOptionPressed));
        auto godmode = createToggleOption("Godmode", false, menu_selector(GadolinUI::onPlayerOptionPressed));
        
        m_contentMenu->addChild(noclip);
        m_contentMenu->addChild(speedhack);
        m_contentMenu->addChild(godmode);
        
    } else if (category == "Creator") {
        auto unlockAll = createActionButton("Unlock All", menu_selector(GadolinUI::onCreatorOptionPressed));
        auto copyHack = createToggleOption("Copy Hack", false, menu_selector(GadolinUI::onCreatorOptionPressed));
        auto freeCam = createToggleOption("Free Camera", false, menu_selector(GadolinUI::onCreatorOptionPressed));
        
        m_contentMenu->addChild(unlockAll);
        m_contentMenu->addChild(copyHack);
        m_contentMenu->addChild(freeCam);
        
    } else if (category == "Misc") {
        auto fps = createActionButton("Show FPS", menu_selector(GadolinUI::onMiscOptionPressed));
        auto practice = createToggleOption("Practice Mode", false, menu_selector(GadolinUI::onMiscOptionPressed));
        auto autoSong = createToggleOption("Auto Song Download", true, menu_selector(GadolinUI::onMiscOptionPressed));
        
        m_contentMenu->addChild(fps);
        m_contentMenu->addChild(practice);
        m_contentMenu->addChild(autoSong);
        
    } else if (category == "Settings") {
        auto saveBtn = createActionButton("Save Config", menu_selector(GadolinUI::onSettingsOptionPressed));
        auto loadBtn = createActionButton("Load Config", menu_selector(GadolinUI::onSettingsOptionPressed));
        auto resetBtn = createActionButton("Reset All", menu_selector(GadolinUI::onSettingsOptionPressed));
        
        m_contentMenu->addChild(saveBtn);
        m_contentMenu->addChild(loadBtn);
        m_contentMenu->addChild(resetBtn);
    }
    
    m_contentMenu->updateLayout();
}

void GadolinUI::onPlayerOptionPressed(CCObject* sender) {
    auto toggle = static_cast<CCMenuItemToggler*>(sender);
    log::info("Player option toggled: {}", toggle->isToggled());
}

void GadolinUI::onCreatorOptionPressed(CCObject* sender) {
    log::info("Creator option pressed");
}

void GadolinUI::onMiscOptionPressed(CCObject* sender) {
    log::info("Misc option pressed");
}

void GadolinUI::onSettingsOptionPressed(CCObject* sender) {
    log::info("Settings option pressed");
}
