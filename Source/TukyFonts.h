/*
  ==============================================================================

    TukyFonts.h
    Created: 24 Nov 2024 5:46:59pm
    Author:  danii

  ==============================================================================
*/

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

// Fonts configuration
namespace TukyUI {
    namespace Fonts {
        const juce::Font title = juce::Font("Audiowide", 24.0f, juce::Font::bold);
        const juce::Font label = juce::Font("Audiowide", 15.0f, juce::Font::plain);
        const juce::Font smLabel = juce::Font("Audiowide", 12.0f, juce::Font::plain);
        const juce::Font mark = juce::Font("Audiowide", 10.0f, juce::Font::plain);
    }
}