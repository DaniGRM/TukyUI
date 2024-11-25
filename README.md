# TukyUI

<!-- ![TukyUI](TukyUI.png) -->

<div style="align-items: center">
  <img src="TukyUI.png" alt="Descripción del logo">
</div>
---

UI Static Library for visual component of Tuky Plugins Bundle
This project contains Source files of static library JUCE project,
so if you want to reply it you must build a Projucer project and then copy this Source files into Source folder.

---

## Configuration
First of all download the package which includes header files and .lib, and then copy it into root folder of your project.
Once you have done that, you have to open Projucer in order to reference the library.

1. On Exporters -> {your IDE} -> { configuration }: Add library path to "Header Searcher Path"
2. On Exporters -> {your IDE} -> { configuration }: Add library path to "External Library Searcher Path"
3. On Exporters -> {your IDE}: Add library *.lib file to "Extra Library to Link"

On this way, when you save Projucer project, it automatically write the right configuration to use it so if you try to add a header from the Library
or to build your plugin it will works.
