/*
  ==============================================================================

    TukyComponents.cpp
    Created: 24 Nov 2024 5:47:48pm
    Author:  danii

  ==============================================================================
*/

#include "TukyComponents.h"
#include "TukyColors.h"
#include "TukyFonts.h"
#include "BinaryData.h"


// LOOK AND FEEL


// Function inherit from LookAndFeel_V4 that draw the slider
void TukyUI::Components::LookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
    float sliderPosProportional, float rotaryStartAngle,
    float rotaryEndAngle, juce::Slider& slider)
{
    using namespace juce;
    // Set bounds
    auto bounds = Rectangle<float>(x, y, width, height);
    // Set color to background to make it seems transparent
    // and fill an ellipse inside of the bounds setted
    g.setColour(Colors::background);
    g.fillEllipse(bounds);


    // Change color to blue to draw a line around the ellipse of width 2.f
    g.setColour(Colors::blue);
    g.drawEllipse(bounds, 2.f);

    // Get the center of the ellipse to take radial reference
    auto center = bounds.getCentre();
    // Create a path to create a little dot that points to current value
    Path p;

    // Create the dot su    bctracting and adding the same amount from left and right
    // regarding the center respectively to make it centered

    // For the y axis we get Y from bounds and adding from top and bottom an amount
    // which it addition have to be the same as X asis
    // In this case:
    // X asis: [-4, 4] regarding the center of ellipse
    // Y asis: [6, 14] regarding bounds' Y asis 
    // 4 - (-4) = 8;
    // 14 - 6   = 8; 
    // so we have a perfect circle
    Rectangle<float> r;
    r.setLeft(center.getX() - 4);
    r.setRight(center.getX() + 4);
    r.setTop(bounds.getY() + 6);
    r.setBottom(bounds.getY() + 14);

    p.addEllipse(r);

    jassert(rotaryStartAngle < rotaryEndAngle);

    auto sliderAngRad = jmap(sliderPosProportional, 0.f, 1.f, rotaryStartAngle, rotaryEndAngle);
    p.applyTransform(AffineTransform().rotated(sliderAngRad, center.getX(), center.getY()));

    g.fillPath(p);
}

void TukyUI::Components::LookAndFeel::drawToggleButton(juce::Graphics& g, juce::ToggleButton& button,
    bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    using namespace juce;

    auto bounds = button.getLocalBounds().toFloat();

    int circleSide = bounds.getHeight() * 0.8f;
    int initCoord = bounds.getHeight() * 0.1f;
    juce::Rectangle<float> rectangleBounds(initCoord, initCoord, circleSide, circleSide);

    float circleRate = 0.6f;
    juce::Rectangle<float> insideBounds(initCoord + circleSide * (1.f - circleRate) / 2.f, initCoord + circleSide * (1.f - circleRate) / 2.f, circleSide * circleRate, circleSide * circleRate);
    auto isOn = button.getToggleState();


    // Borde del botón (cambia si está resaltado)
    g.setColour(shouldDrawButtonAsHighlighted ? TukyUI::Colors::blue.brighter(0.2f) : TukyUI::Colors::blue);
    g.drawEllipse(rectangleBounds, 2.0f);

    if (isOn)
    {
        g.setColour(TukyUI::Colors::blue);
        g.fillEllipse(insideBounds);
    }
    else
    {
        g.setColour(TukyUI::Colors::background);
        g.fillEllipse(insideBounds);
    }

    // Texto del botón
    auto textBounds = bounds.removeFromRight(bounds.getWidth() - bounds.getHeight());
    textBounds.removeFromLeft(5.f);
    g.setFont(TukyUI::Fonts::label);
    g.setColour(TukyUI::Colors::blue);
    g.drawFittedText(button.getButtonText(), textBounds.toNearestInt(), Justification::centredLeft, 1);
}




// =============
// ROTARY SLIDER
// =============


void TukyUI::Components::TukyRotarySlider::paint(juce::Graphics& g) {
    using namespace juce;

    // Set start and end angle
    auto startAng = degreesToRadians(180.f + 45.f);
    auto endAng = degreesToRadians(180.f - 45.f) + MathConstants<float>::twoPi;

    // Get the range (Slider function) and bounds (Own function)
    auto range = getRange();
    auto sliderBounds = getSliderBounds();

    // Draw the slider
    getLookAndFeel().drawRotarySlider(g,
        sliderBounds.getX(),
        sliderBounds.getY(),
        sliderBounds.getWidth(),
        sliderBounds.getHeight(),
        jmap(getValue(), range.getStart(), range.getEnd(), 0.0, 1.0),
        startAng,
        endAng,
        *this);
}

// Function to get the bounds from the slider substracting the textHeight
juce::Rectangle<int> TukyUI::Components::TukyRotarySlider::getSliderBounds() const {

    auto bounds = getLocalBounds();

    // Get original bounds
    auto size = juce::jmin(bounds.getWidth(), bounds.getHeight());

    // Substract for text height
    size -= 5.f;

    // Create rectangle in order to be the bounds itself
    juce::Rectangle<int> r;
    r.setSize(size, size);
    r.setCentre(bounds.getCentreX(), 0);
    r.setY(2);

    return r;
}

// =============
// TOGGLE BUTTON
// =============

void TukyUI::Components::TukyToggleButton::paint(juce::Graphics& g) {
    using namespace juce;

    // Obtener los parámetros necesarios para drawToggleButton
    bool shouldDrawButtonAsHighlighted = isMouseOver();  // Por ejemplo, el botón se destaca si el ratón está sobre él
    bool shouldDrawButtonAsDown = getToggleState(); // El estado del botón (activado o desactivado)

    // Llamada a drawToggleButton para dibujar el toggle con los parámetros obtenidos
    getLookAndFeel().drawToggleButton(g, *this, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);
}

// =============
// HEADER
// =============
// Function to paint a bar on the top with the company logo
void TukyUI::Components::TukyHeader::paint(juce::Graphics& g){
    {
        auto bounds = getLocalBounds().toFloat();
        // Set the background of bar
        g.fillAll(TukyUI::Colors::bluegray);

        // Draw the logo
        auto logoHeight = bounds.getHeight() * 0.8;// Ajustamos el tamaño del logo
        auto logoWidth = (logoHeight * 1.0f); // Relación de aspecto 4:3
        auto logoBounds = juce::Rectangle<float>(10.0f, (bounds.getHeight() - logoHeight) / 2.0f, logoWidth, logoHeight);
        auto nameBounds = juce::Rectangle<float>(logoBounds.getX() + logoBounds.getWidth() + 10.f, (bounds.getHeight() - logoHeight) / 2.0f, bounds.getWidth() - logoWidth, logoHeight);


        auto logoImage = juce::ImageFileFormat::loadFrom(BinaryData::TUKY_logo_png, BinaryData::TUKY_logo_pngSize);

        // Only draw it if is valid
        if (logoImage.isValid())
        {
            g.drawImage(logoImage, logoBounds);
            g.setFont(TukyUI::Fonts::title);
            g.setColour(TukyUI::Colors::beige);
            g.drawText(pluginName, nameBounds, juce::Justification::centredLeft);

        }
    }
}