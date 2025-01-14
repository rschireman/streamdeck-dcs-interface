<img src="Images/DCS_Interface_Banner.png" width=400>

![GitHub Workflow Status](https://img.shields.io/github/workflow/status/charlestytler/streamdeck-dcs-interface/cpp-tests?label=C%2B%2B%20Tests)
![GitHub Workflow Status](https://img.shields.io/github/workflow/status/charlestytler/streamdeck-dcs-interface/reactjs-tests?label=ReactJS%20Tests)
[![codecov](https://codecov.io/gh/charlestytler/streamdeck-dcs-interface/branch/master/graph/badge.svg?token=9K0CA0IGSM)](https://codecov.io/gh/charlestytler/streamdeck-dcs-interface)
![GitHub Workflow Status](https://img.shields.io/github/workflow/status/charlestytler/streamdeck-dcs-interface/clang-format?label=clang-format)
![GitHub all releases](https://img.shields.io/github/downloads/charlestytler/streamdeck-dcs-interface/total)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/charlestytler/streamdeck-dcs-interface)

`DCS Interface` is a plugin for the Streamdeck that allows communication with DCS via lua UDP sockets for both receiving updates of the simulation state as well as sending commands to interact with the clickable cockpits.

- [Description](#description)
  - [Detailed Documentation](#detailed-documentation)
- [Demo of Operation](#demo-of-operation)
- [Installation](#installation)
    - [Downloads](#downloads)
    - [Version Update](#version-update)
      - [Identify installed version number:](#identify-installed-version-number)
    - [Initial Configuration](#initial-configuration)
    - [Video Walkthrough](#video-walkthrough)
- [Source code](#source-code)
- [Build from source instructions](#build-from-source-instructions)

# Description

`DCS Interface` is a plugin that allows you to create buttons and interfaces that update with DCS events.
There are currently three settings for each Streamdeck button you create:

- DCS Command - Specify which button/switch you want to activate in game (allows setting of any clickable object in a cockpit).
  - Streamdeck buttons support push-button, switch, and increment (dials, levers, etc.) input types.
- Image Change Settings - Specify a function within the DCS simulation to monitor and change the display of the Streamdeck image conditionally.
  - Examples: Lamps for Warnings/Modes, Switch states
- Title Text Change Settings - Specify a function in the DCS simulation which will be monitored and its text is displayed as the Streamdeck button Title.
  - Examples: UFC text displays, scratchpads, radio displays

Can also support multiple physical Streamdecks at once.

## Detailed Documentation

More detailed instructions can be found in: [Settings Help Documentation](Sources/com.ctytler.dcs.sdPlugin/helpDocs/helpContents.md).

---

# Demo of Operation

![Stream Deck AV8BNA ODU Demo](Images/Streamdeck_AV8B_Demo.gif)

**Example of Settings to Display Master Caution Lamp:**

<img src="Images/Configuration_AV8B_Screenshot.jpg" width=600>

# Installation

### Downloads

- For the DCS plugin to work you will first need [DCS-ExportScripts](https://github.com/asherao/DCS-ExportScripts) installed, detailed instructions are on their [Wiki](https://github.com/s-d-a/DCS-ExportScripts/wiki). This is the backend that is relied on for communication with the DCS game.

- To install the DCS Interface Streamdeck plugin, you will need to download and run the installer `com.ctytler.dcs.streamDeckPlugin` from [Releases](https://github.com/charlestytler/streamdeck-dcs-interface/releases).

- Also within [Releases](https://github.com/charlestytler/streamdeck-dcs-interface/releases) is an optional `icon_library.zip` you can download for use with Streamdeck Profiles.

### Version Update

If you have a prior version already installed on your StreamDeck, you will have to uninstall it first before installing the latest version. To do this right-click on one of the DCS Interface button types in the right-side panel and click "Uninstall".

#### Identify installed version number:
To see the version of the plugin installed on the StreamDeck, right-click on one of the DCS Interface button types in the right-side panel.

### Initial Configuration

If you plan to only use DCS Interface for Streamdeck with the DCS-ExportScript and not [Ikarus](https://github.com/s-d-a/Ikarus), you can modify the file `DCS-ExportScript\Config.lua` to have the following settings (where `IkarusPort` is changed from `1625` to `1725` for DCS Interface) to get everything connected:

```
-- Ikarus a Glass Cockpit Software
ExportScript.Config.IkarusExport    = true         -- false for not use
ExportScript.Config.IkarusHost      = "127.0.0.1"  -- IP for Ikarus
ExportScript.Config.IkarusPort      = 1725         -- Port Ikarus (1625)
ExportScript.Config.IkarusSeparator = ":"
```

If you are interested in using the export script to support both Streamdeck and Ikarus, instructions can be found in the [Settings Help Documentation - Enabling Both DCS Interface & Ikarus](Sources/com.ctytler.dcs.sdPlugin/helpDocs/helpContents.md#enabling-both-dcs-interface--ikarus).

### Video Walkthrough

A walkthrough of installation and configuration can be found at the below link, along with other instructional videos.  
[DCS Interface for Streamdeck Video Instructions](https://www.youtube.com/playlist?list=PLcYO7a2ywThz7nIT4CjRTn737ZM26aqDq)

# Source code

The Sources folder contains the source code of the plugin. The primary components are as follows:

```
Sources
├── com.ctytler.dcs.sdPlugin  Plugin package where the built frontend and backend are combined
│   ├── manifest.json           Definition of Streamdeck plugin metadata
│   ├── bin                     Location for compiled C++ and lua scripts called by plugin
│   ├── helpDocs                Help documentation within plugin
│   ├── images                  Default icon images
│   └── propertyinspector       Javascript and html used by plugin (Button settings and windows)
├── backend-cpp               The backend of the plugin (Manages Simulator/Streamdeck State), written in C++
│   ├── ElgatoSD                Elgato Streamdeck SDK source and utilities
│   ├── SimulatorInterface      Classes for interacting with the simulator state
│   ├── StreamdeckContext       Classes for maintaining state of individual Streamdeck buttons
│   │   ├── ExportMonitors      Classes that monitor simulator export data for individual buttons
│   │   ├── SendActions         Classes that define button press and release actions
│   ├── StreamdeckInterface     Executable that interfaces C++ code with Streamdeck plugin
│   ├── Test                    Unit test infrastructure and target
│   ├── Utilities               Generic utilities for UDP socket and string manipulation
│   ├── Vendor                  Third party source code
│   └── Windows                 Visual Studio solution settings
└── frontend-react-js         The frontend of the plugin (Configuration window), written in ReactJS
```

# Build from source instructions

A build script is included which will build both the C++ executable which handles the communcation with DCS as well as the package for the Stream Deck plugin: `Tools/build_plugin.bat`

You will need Visual Studio installed, and may need to edit the location of the Visual Studio install location inside the batch file if it does not match for your machine. Running the batch script will build the Streamdeck plugin and run all unit tests, generating the plugin file at `Release/com.ctytler.dcs.streamDeckPlugin`.

Current version was built with Visual Studio Community 2019.

Additional convenient one-liner to build if using Windows Subsystem for Linux (WSL):
```
cmd.exe /C """C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat" \& devenv D:\\code\\DCS\\streamdeck-dcs-interface\\Sources\\Windows\\com.ctytler.dcs.sdPlugin.sln /build "Release^|x64"""
```
