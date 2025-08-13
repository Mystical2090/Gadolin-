#include <Geode/Geode.hpp>
#include "ui.hpp"

using namespace geode::prelude;

bool GadolinUI::setup() {
    this->setTitle("Gadolin");
    
    auto bg = CCScale9Sprite::create("square02_001.png");
    bg->setColor({25, 25, 35});
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
    m_categoryMenu->setLayout(ColumnLayout::create()->setGap(3.f)->setAxisReverse(true));
    m_categoryMenu->setContentSize({80.f, 250.f});
    m_mainLayer->addChildAtPosition(m_categoryMenu, Anchor::Left, {50.f, 0.f});

    std::vector<std::string> categories = {"Player", "Misc", "Editor", "Labels", "Favorites", "Button"};
    for (const auto& category : categories) {
        auto button = createCategoryButton(category);
        m_categoryMenu->addChild(button);
    }
    m_categoryMenu->updateLayout();
}

void GadolinUI::setupContent() {
    m_contentMenu = CCMenu::create();
    m_contentMenu->setLayout(ColumnLayout::create()->setGap(8.f)->setAxisReverse(true));
    m_contentMenu->setContentSize({300.f, 200.f});
    m_mainLayer->addChildAtPosition(m_contentMenu, Anchor::Right, {-80.f, -10.f});
}

CCMenuItemSpriteExtra* GadolinUI::createCategoryButton(const std::string& category) {
    auto sprite = CCSprite::createWithSpriteFrameName("GJ_button_01.png");
    sprite->setScale(0.5f);
    
    auto button = CCMenuItemSpriteExtra::create(
        sprite, this, menu_selector(GadolinUI::onCategoryPressed)
    );
    
    auto label = CCLabelBMFont::create(category.c_str(), "bigFont.fnt");
    label->setScale(0.3f);
    label->setPosition(sprite->getContentSize() / 2);
    sprite->addChild(label);
    
    button->setUserObject(CCString::create(category));
    return button;
}

CCMenuItemToggler* GadolinUI::createToggleOption(const std::string& saveKey, bool defaultVal) {
    bool currentVal = Mod::get()->getSavedValue<bool>(saveKey, defaultVal);
    
    auto onSprite = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
    auto offSprite = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
    onSprite->setScale(0.6f);
    offSprite->setScale(0.6f);
    
    auto toggle = CCMenuItemToggler::create(offSprite, onSprite, this, menu_selector(GadolinUI::onTogglePressed));
    toggle->toggle(currentVal);
    toggle->setUserObject(CCString::create(saveKey));
    
    auto label = CCLabelBMFont::create(saveKey.c_str(), "chatFont.fnt");
    label->setScale(0.5f);
    label->setPosition({toggle->getContentSize().width + 30.f, toggle->getContentSize().height / 2});
    label->setAnchorPoint({0.f, 0.5f});
    toggle->addChild(label);
    
    return toggle;
}

CCNode* GadolinUI::createSliderOption(const std::string& saveKey, float defaultVal, float min, float max) {
    float currentVal = Mod::get()->getSavedValue<float>(saveKey, defaultVal);
    
    auto container = CCNode::create();
    container->setContentSize({200.f, 30.f});
    
    auto sliderBG = CCSprite::createWithSpriteFrameName("slidergroove_01.png");
    sliderBG->setScale(0.7f);
    sliderBG->setPosition({100.f, 15.f});
    container->addChild(sliderBG);
    
    auto sliderThumb = CCSprite::createWithSpriteFrameName("sliderBtn_01.png");
    sliderThumb->setScale(0.6f);
    
    auto slider = CCMenuItemSpriteExtra::create(sliderThumb, this, menu_selector(GadolinUI::onSliderChanged));
    slider->setUserObject(CCString::create(saveKey));
    
    auto label = CCLabelBMFont::create(saveKey.c_str(), "chatFont.fnt");
    label->setScale(0.4f);
    label->setPosition({100.f, 5.f});
    container->addChild(label);
    
    auto sliderMenu = CCMenu::create();
    sliderMenu->addChild(slider);
    sliderMenu->setPosition({100.f, 15.f});
    container->addChild(sliderMenu);
    
    return container;
}

CCMenuItemSpriteExtra* GadolinUI::createPopupButton(const std::string& action) {
    auto sprite = CCSprite::createWithSpriteFrameName("GJ_button_04.png");
    sprite->setScale(0.5f);
    
    auto button = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(GadolinUI::onPopupPressed));
    button->setUserObject(CCString::create(action));
    
    auto label = CCLabelBMFont::create(action.c_str(), "bigFont.fnt");
    label->setScale(0.4f);
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
        auto label1 = createToggleOption("label1", false);
        auto label2 = createToggleOption("label2", false);
        auto label3 = createToggleOption("label3", false);
        auto label4 = createToggleOption("label4", false);
        auto speedSlider = createSliderOption("speed", 1.0f, 0.1f, 5.0f);
        auto popup1 = createPopupButton("popup1");
        
        m_contentMenu->addChild(label1);
        m_contentMenu->addChild(label2);
        m_contentMenu->addChild(label3);
        m_contentMenu->addChild(label4);
        m_contentMenu->addChild(speedSlider);
        m_contentMenu->addChild(popup1);
        
    } else if (category == "Misc") {
        auto label1 = createToggleOption("misc1", false);
        auto label2 = createToggleOption("misc2", false);
        auto label3 = createToggleOption("misc3", false);
        auto label4 = createToggleOption("misc4", false);
        auto volumeSlider = createSliderOption("volume", 0.8f, 0.0f, 1.0f);
        auto popup2 = createPopupButton("popup2");
        
        m_contentMenu->addChild(label1);
        m_contentMenu->addChild(label2);
        m_contentMenu->addChild(label3);
        m_contentMenu->addChild(label4);
        m_contentMenu->addChild(volumeSlider);
        m_contentMenu->addChild(popup2);
        
    } else if (category == "Editor") {
        auto label1 = createToggleOption("editor1", false);
        auto label2 = createToggleOption("editor2", false);
        auto label3 = createToggleOption("editor3", false);
        auto label4 = createToggleOption("editor4", false);
        auto gridSlider = createSliderOption("gridSize", 30.0f, 10.0f, 100.0f);
        auto popup3 = createPopupButton("popup3");
        
        m_contentMenu->addChild(label1);
        m_contentMenu->addChild(label2);
        m_contentMenu->addChild(label3);
        m_contentMenu->addChild(label4);
        m_contentMenu->addChild(gridSlider);
        m_contentMenu->addChild(popup3);
        
    } else if (category == "Labels") {
        auto preset1 = createPopupButton("preset1");
        auto preset2 = createPopupButton("preset2");
        auto preset3 = createPopupButton("preset3");
        auto preset4 = createPopupButton("preset4");
        auto preset5 = createPopupButton("preset5");
        auto preset6 = createPopupButton("preset6");
        
        m_contentMenu->addChild(preset1);
        m_contentMenu->addChild(preset2);
        m_contentMenu->addChild(preset3);
        m_contentMenu->addChild(preset4);
        m_contentMenu->addChild(preset5);
        m_contentMenu->addChild(preset6);
        
    } else if (category == "Favorites") {
        auto fav1 = createToggleOption("favorite1", false);
        auto fav2 = createToggleOption("favorite2", false);
        auto fav3 = createToggleOption("favorite3", false);
        auto fav4 = createToggleOption("favorite4", false);
        auto favSlider = createSliderOption("favValue", 50.0f, 0.0f, 100.0f);
        
        m_contentMenu->addChild(fav1);
        m_contentMenu->addChild(fav2);
        m_contentMenu->addChild(fav3);
        m_contentMenu->addChild(fav4);
        m_contentMenu->addChild(favSlider);
        
    } else if (category == "Button") {
        auto btn1 = createToggleOption("button1", false);
        auto btn2 = createToggleOption("button2", false);
        auto btn3 = createToggleOption("button3", false);
        auto btn4 = createToggleOption("button4", false);
        auto btnSlider = createSliderOption("buttonSize", 1.0f, 0.5f, 2.0f);
        auto btnPopup = createPopupButton("buttonPopup");
        
        m_contentMenu->addChild(btn1);
        m_contentMenu->addChild(btn2);
        m_contentMenu->addChild(btn3);
        m_contentMenu->addChild(btn4);
        m_contentMenu->addChild(btnSlider);
        m_contentMenu->addChild(btnPopup);
    }
    
    m_contentMenu->updateLayout();
}

void GadolinUI::onTogglePressed(CCObject* sender) {
    auto toggle = static_cast<CCMenuItemToggler*>(sender);
    auto saveKey = static_cast<CCString*>(toggle->getUserObject())->getCString();
    bool newValue = toggle->isToggled();
    
    Mod::get()->setSavedValue<bool>(saveKey, newValue);
    log::info("Toggle {} set to {}", saveKey, newValue);
}

void GadolinUI::onSliderChanged(CCObject* sender) {
    auto button = static_cast<CCMenuItemSpriteExtra*>(sender);
    auto saveKey = static_cast<CCString*>(button->getUserObject())->getCString();

    float value = 1.0f;
    
    Mod::get()->setSavedValue<float>(saveKey, value);
    log::info("Slider {} set to {}", saveKey, value);
}

void GadolinUI::onPopupPressed(CCObject* sender) {
    auto button = static_cast<CCMenuItemSpriteExtra*>(sender);
    auto action = static_cast<CCString*>(button->getUserObject())->getCString();
    
    log::info("Popup {} triggered", action);

    auto alert = FLAlertLayer::create(nullptr, "Popup", fmt::format("Just a popup",), "OK", nullptr, 300.0f);
    alert->show();
}
