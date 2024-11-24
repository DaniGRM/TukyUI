/*
  ==============================================================================

    TukyUI.h
    Created: 23 Nov 2024 2:03:27pm
    Author:  danii

  ==============================================================================
*/

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "TukyColors.h"


namespace TukyUI
{
    class TukyUI : public juce::LookAndFeel_V4
    {
    public:
        TukyUI()
        {
            setColour(juce::Slider::thumbColourId, Colors::beige);
            setColour(juce::Slider::trackColourId, Colors::green);
            setColour(juce::Label::textColourId, Colors::green);
        }
    };
}