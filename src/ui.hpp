#pragma once

#include <Geode/Geode.hpp>
#include <unordered_map>
#include <functional>

using namespace geode::prelude;

struct CategoryData;

class GadolinUI : public geode::Popup<> {
protected:
    CCMenu* m_categoryMenu = nullptr;
    CCMenu* m_contentMenu = nullptr;
    CCScrollLayerExt* m_scrollLayer = nullptr;
    
    std::string m_currentCategory = "Player";
    std::unordered_map<std::string, CategoryData> m_categoryData;
    
    bool setup() override;
    void setupBackground();
    void setupCategories();
    void setupContentArea();
    void initializeCategoryData();
    
    void updateContentForCategory(const std::string& category);
    void highlightSelectedCategory(const std::string& category);
    
    void onCategoryPressed(CCObject* sender);
    void onTogglePressed(CCObject* sender);
    void onSliderChanged(CCObject* sender);
    void onPopupPressed(CCObject* sender);
    
    CCMenuItemSpriteExtra* createCategoryButton(const std::string& category);
    CCMenuItemToggler* createToggleOption(const std::string& label, const std::string& saveKey, bool defaultVal);
    CCNode* createSliderOption(const std::string& label, const std::string& saveKey, float defaultVal, float min, float max);
    CCMenuItemSpriteExtra* createPopupButton(const std::string& label, const std::string& action);

    void clearContent();
    void updateSliderValue(CCNode* sliderContainer, const std::string& saveKey, float value);
    CCLabelBMFont* createLabel(const std::string& text, const std::string& font, float scale);

public:
    static GadolinUI* create() {
        auto ret = new GadolinUI();
        if (ret && ret->initAnchored(520.f, 360.f)) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }
    
    void addCustomCategory(const std::string& name, std::function<void()> setupFunc);
    void refreshCurrentCategory();
};

enum class UIElementType {
    TOGGLE,
    SLIDER,
    BUTTON,
    SEPARATOR
};

struct UIElement {
    UIElementType type;
    std::string label;
    std::string saveKey;
    std::string action;
    float defaultValue = 0.0f;
    float minValue = 0.0f;
    float maxValue = 1.0f;
    bool defaultBool = false;
    
    static UIElement createToggle(const std::string& label, const std::string& saveKey, bool defaultVal = false) {
        return {UIElementType::TOGGLE, label, saveKey, "", 0.0f, 0.0f, 1.0f, defaultVal};
    }
    
    static UIElement createSlider(const std::string& label, const std::string& saveKey, 
                                 float defaultVal, float min, float max) {
        return {UIElementType::SLIDER, label, saveKey, "", defaultVal, min, max, false};
    }
    
    static UIElement createButton(const std::string& label, const std::string& action) {
        return {UIElementType::BUTTON, label, "", action, 0.0f, 0.0f, 1.0f, false};
    }
    
    static UIElement createSeparator() {
        return {UIElementType::SEPARATOR, "", "", "", 0.0f, 0.0f, 1.0f, false};
    }
};

struct CategoryData {
    std::string name;
    std::string icon;
    std::vector<UIElement> elements;
    std::function<void()> customSetupFunc = nullptr;
    
    CategoryData() = default;
    CategoryData(const std::string& n, std::vector<UIElement> els) 
        : name(n), elements(std::move(els)) {}
};

// holy fuck
namespace GadolinUIConstants {
    constexpr float CATEGORY_BUTTON_WIDTH = 90.0f;
    constexpr float CATEGORY_BUTTON_HEIGHT = 30.0f;
    constexpr float CONTENT_WIDTH = 350.0f;
    constexpr float CONTENT_HEIGHT = 280.0f;
    constexpr float ELEMENT_SPACING = 8.0f;
    constexpr float CATEGORY_SPACING = 3.0f;
    
    constexpr const char* TITLE_FONT = "bigFont.fnt";
    constexpr const char* LABEL_FONT = "chatFont.fnt";
    constexpr const char* BUTTON_FONT = "goldFont.fnt";
    
    constexpr ccColor3B BACKGROUND_COLOR = {25, 25, 35};
    constexpr ccColor3B SELECTED_CATEGORY_COLOR = {100, 100, 255};
    constexpr ccColor3B DEFAULT_CATEGORY_COLOR = {255, 255, 255};
}
