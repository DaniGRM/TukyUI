/*
  ==============================================================================

    TukyComponents.h
    Created: 24 Nov 2024 5:47:48pm
    Author:  danii

  ==============================================================================
*/
#include <JuceHeader.h>
#pragma once

namespace TukyUI {
    namespace Components {
        struct LookAndFeel : juce::LookAndFeel_V4
        {
            void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                float sliderPosProportional, float rotaryStartAngle,
                float rotaryEndAngle, juce::Slider& slider) override;
        };

        struct TukyRotarySlider : juce::Slider
        {
            TukyRotarySlider(juce::RangedAudioParameter& rap, const juce::String& unitSuffix) :
                juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                    juce::Slider::TextEntryBoxPosition::NoTextBox),
                param(&rap),
                suffix(unitSuffix)
            {
                setLookAndFeel(&lnf);
            }

            ~TukyRotarySlider() {
                setLookAndFeel(nullptr);
            }

            void paint(juce::Graphics& g) override;
            juce::Rectangle<int> getSliderBounds() const;
            int getTextHeight() const { return 14; }
            juce::String getDisplayString() const;
        private:
            LookAndFeel lnf;

            juce::RangedAudioParameter* param;
            juce::String suffix;
        };
    }
}