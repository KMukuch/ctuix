# Description

A C library for building **event driven TUI programs** on UNIX-like systems (macOS, Linux, etc.) using XML

The library helps to avoid the frustration with **ncurses** and **libxml**, which can be difficult to learn, and helps to create user friendly TUIs embed in C code.

# Disclaimer

The library is in early development and should be considered a work in progress.

# Building

The easiest way to install the library is download the source code and run the cmake file. It installs the static library on your system and lets you also build some demo files.

## Dependencies

In order to build the library you need **ncurses** and **libxml** already installed on your system.

# Workflow

There are four main elements in the workflow:

1. initializing

2. parsing the xml file

3. using the core loop

4. proper exiting and freeing all the elements

## XML structure

The XML structure is given should correspond the `ctuix.dtd` file.

Every XML file should start with a root element

```
<ctuix>
    ...
</ctuix>
```

There are seven tags that a user can declare:

- `<ctuix_panel></ctuix_panel>` — a container that groups other UI elements. Can hold labels, buttons, entries, panels, selection boxes, and scroll panels.

- `<ctuix_scroll_panel></ctuix_scroll_panel>` — a scrollable area that contains text content.

- `<ctuix_selection_box></ctuix_selection_box>` — a selectable list that contains one or more `<ctuix_item>` elements.

- `<ctuix_item></ctuix_item>` — an individual option within a selection box. Contains text that represents the selectable choice.

- `<ctuix_label></ctuix_label>` — a static text element used for displaying information or labels to the user. Cannot receive user input.

- `<ctuix_button></ctuix_button>` — an interactive button that users can click or activate. Can trigger actions in the application.

- `<ctuix_entry></ctuix_entry>` — a text input field that allows users to enter or edit data. Supports user input.

**Attributes:**

All elements except the root require `x` and `y` position coordinates. Containers and interactive elements also require `w` (width) and `h` (height). The `name` attribute is optional and can be used to reference elements programmatically. The `user_input` attribute (default: false) controls whether an element can receive focus. The `layout` attribute defines child arrangement (grid, horizontal, or vertical) for container elements.

## Initializing

Since the library is a framework built upon **ncurses** (and **libxml**) the first thing we need to do is initialize the curses system and set it up.

```
ctuix_init(void);
```

## Parsing



## Error parsing

All software is prone to errors. The library provides several functions that users can implement to catch and handle them.



## Core loop



## Program exit (cleaning the allocated resources)

To end the program properly we need to clean all the resources used by **ncurses** and **ctuix** itself.



# Example



# Demo


# Docs

For developer documentation (docs/private) and public API (docs/public) details see the Doxygen-generated HTML files.