/*
  ==============================================================================

    TukyComponents.cpp
    Created: 24 Nov 2024 5:47:48pm
    Author:  danii

  ==============================================================================
*/

#include "TukyComponents.h"
#include "TukyColors.h"
#include "BinaryData.h"

// =============
// ROTARY SLIDER
// =============

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
    size -= getTextHeight() * 2;

    // Create rectangle in order to be the bounds itself
    juce::Rectangle<int> r;
    r.setSize(size, size);
    r.setCentre(bounds.getCentreX(), 0);
    r.setY(2);

    return r;
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
        auto logoWidth = (logoHeight * 3.0f); // Relación de aspecto 4:3
        auto logoBounds = juce::Rectangle<float>(10.0f, (bounds.getHeight() - logoHeight) / 2.0f, logoWidth, logoHeight);


        auto logoImage = juce::ImageFileFormat::loadFrom(BinaryData::TUKY_imagotipo2_png, BinaryData::TUKY_imagotipo2_pngSize);

        // Only draw it if is valid
        if (logoImage.isValid())
        {
            g.drawImage(logoImage, logoBounds);

        }
    }
}