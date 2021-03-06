#include "MySimpleDemoPanelColors.h"

MySimpleDemoPanelColors::MySimpleDemoPanelColors()
    : Gui3D::PanelColors()
{
    // General
    transparent = Gorilla::rgb(0, 0, 0, 0);

    // Panel
    panelBackgroundSpriteName = "panelBackground";
    panelCursorSpriteName = "mousepointer";
    panelCursorSpriteSizeX = 12;
    panelCursorSpriteSizeY = 18;

    // Button
    // In the demo, sprites are used for the "click me!" button
    buttonInactiveSpriteName = "buttonInactive";
    buttonOveredSpriteName = "buttonOvered";
    buttonNotOveredSpriteName = "buttonNotOvered";
    buttonClickedSpriteName = "buttonClicked";

    // In the demo, those are used by the combobox previous and next buttons
    buttonBackgroundClickedGradientType = Gorilla::Gradient_NorthSouth;
    buttonBackgroundClickedGradientStart = Gorilla::rgb(255, 255, 255, 200);
    buttonBackgroundClickedGradientEnd = Gorilla::rgb(255, 255, 255, 170);

    buttonBackgroundOveredGradientType = Gorilla::Gradient_NorthSouth;
    buttonBackgroundOveredGradientStart = Gorilla::rgb(255, 255, 255, 128);
    buttonBackgroundOveredGradientEnd = Gorilla::rgb(255, 255, 255, 100);

    buttonBackgroundNotOveredGradientType = Gorilla::Gradient_NorthSouth;
    buttonBackgroundNotOveredGradientStart = Gorilla::rgb(255, 255, 255, 80);
    buttonBackgroundNotOveredGradientEnd = Gorilla::rgb(255, 255, 255, 50);

    buttonBackgroundInactiveGradientType = Gorilla::Gradient_NorthSouth;
    buttonBackgroundInactiveGradientStart = Gorilla::rgb(255, 255, 255, 15);
    buttonBackgroundInactiveGradientEnd = Gorilla::rgb(255, 255, 255, 5);

    buttonText = Gorilla::rgb(255, 255, 255, 255);
    buttonTextInactive = Gorilla::rgb(255, 255, 255, 70);
    buttonTextSize = 14;

    buttonBorder = Gorilla::rgb(70, 70, 70, 50);
    buttonBorderHighlight = Gorilla::rgb(255, 100, 100, 170);
    buttonBorderInactive = Gorilla::rgb(70, 70, 70, 15);
    buttonBorderSize = 1;

    // Checkbox
    checkboxOveredBackgroundSpriteName = "checkboxOvered";
    checkboxNotOveredBackgroundSpriteName = "checkboxNotOvered";
    checkboxCheckedNotOveredBackgroundSpriteName = "checkboxCheckedNotOvered";
    checkboxCheckedOveredBackgroundSpriteName = "checkboxCheckedOvered";

    // Combobox
    comboboxButtonPreviousOveredSpriteName = "comboboxpreviouselementbuttonovered";
    comboboxButtonPreviousNotOveredSpriteName = "comboboxpreviouselementbuttonnotovered";
    comboboxButtonPreviousInactiveSpriteName = "comboboxpreviouselementbuttoninactive";

    comboboxButtonNextOveredSpriteName = "comboboxnextelementbuttonovered";
    comboboxButtonNextNotOveredSpriteName = "comboboxnextelementbuttonnotovered";
    comboboxButtonNextInactiveSpriteName = "comboboxnextelementbuttoninactive";

    comboboxBackgroundGradientType = Gorilla::Gradient_NorthSouth;
    comboboxBackgroundGradientStart = Gorilla::rgb(255, 255, 255, 0);
    comboboxBackgroundGradientEnd = Gorilla::rgb(255, 255, 255, 0);

    comboboxOveredElement = Gorilla::rgb(255, 255, 255, 100);
    comboboxNotOveredElement = Gorilla::rgb(255, 255, 255, 30);
    comboboxSelectedElement = Gorilla::rgb(120, 20, 120, 200);

    comboboxText = Ogre::ColourValue::White;
    comboboxTextSize = 14;

    comboboxBorder = Gorilla::rgb(70, 70, 70, 50);
    comboboxBorderHighlight = Gorilla::rgb(255, 100, 100, 170);
    comboboxBorderSize = 0;

    // Caption
    captionBackgroundGradientType = Gorilla::Gradient_NorthSouth;
    captionBackgroundGradientStart = transparent;
    captionBackgroundGradientEnd = transparent;

    captionBorder = transparent;
    captionText = Ogre::ColourValue::White;
    captionTextSize = 14;
    captionBorderSize = 0;
}