/*
  ==============================================================================

    TukyComponents.cpp
    Created: 24 Nov 2024 5:47:48pm
    Author:  danii

  ==============================================================================
*/

#include "TukyComponents.h"
#include "TukyColors.h"

void TukyUI::Components::LookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
    float sliderPosProportional, float rotaryStartAngle,
    float rotaryEndAngle, juce::Slider& slider)
{
    using namespace juce;

    auto bounds = Rectangle<float>(x, y, width, height);

    g.setColour(Colors::background);
    g.fillEllipse(bounds);

    g.setColour(Colors::blue);
    g.drawEllipse(bounds, 2.f);

    auto center = bounds.getCentre();
    Path p;

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
    auto startAng = degreesToRadians(180.f + 45.f);
    auto endAng = degreesToRadians(180.f - 45.f) + MathConstants<float>::twoPi;

    auto range = getRange();
    auto sliderBounds = getSliderBounds();

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

juce::Rectangle<int> TukyUI::Components::TukyRotarySlider::getSliderBounds() const {

    auto bounds = getLocalBounds();

    auto size = juce::jmin(bounds.getWidth(), bounds.getHeight());

    size -= getTextHeight() * 2;

    juce::Rectangle<int> r;
    r.setSize(size, size);
    r.setCentre(bounds.getCentreX(), 0);
    r.setY(2);

    return r;
}