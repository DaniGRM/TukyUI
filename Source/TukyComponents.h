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

        // =============
        // ROTARY SLIDER
        // =============

        // Slider own lookAndFeel to override drawRotarySlider
        struct LookAndFeel : juce::LookAndFeel_V4
        {

            void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                float sliderPosProportional, float rotaryStartAngle,
                float rotaryEndAngle, juce::Slider& slider) override;

            void drawToggleButton(juce::Graphics&, juce::ToggleButton&,
                bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
        };

        // TukyRotarySlider inherit from Slider, we are goind to declare and define
        // neede functions overriding Slider originals one
        // in addition we are going to declare a function to get Slider Bounds and text height
        // according to label
        struct TukyRotarySlider : juce::Slider
        {
            TukyRotarySlider(juce::RangedAudioParameter& rap) :
                juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                    juce::Slider::TextEntryBoxPosition::NoTextBox),
                param(&rap)
            {
                setLookAndFeel(&lnf);
            }

            ~TukyRotarySlider() {
                setLookAndFeel(nullptr);
            }

            void paint(juce::Graphics& g) override;
            juce::Rectangle<int> getSliderBounds() const;

            void setMarks(juce::Array<juce::String> m) {
                marks = m;
            }

            juce::Array<juce::String> getMarks() {
                return marks;
            }
        private:
            
            // Slider own LookAndFeel
            LookAndFeel lnf;

            // String array for marks
            juce::Array<juce::String> marks;
            // Param itself to attach component
            juce::RangedAudioParameter* param;
        };

        // =============
        // TOGGLE BUTTON
        // =============

        struct TukyToggleButton : juce::ToggleButton
        {
            TukyToggleButton()
            {
                setLookAndFeel(&lnf);
            }

            ~TukyToggleButton() {
                setLookAndFeel(nullptr);
            }

            void paint(juce::Graphics& g) override;
        private:

            // Slider own LookAndFeel
            LookAndFeel lnf;
        };

        // =============
        // HEADER
        // =============

        struct TukyHeader : public juce::Component
        {
        public:
            TukyHeader(juce::String p) {
                pluginName = p;
            }

            void paint(juce::Graphics& g) override;

            juce::String pluginName;
        };
    }
}