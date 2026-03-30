# License



# Description

A C library for building **event driven TUI programs** on UNIX-like systems (macOS, Linux, etc.) using XML

The library helps to avoid the frustration with **ncurses** and **libxml**, which can be difficult to learn, and helps to create user-friendly TUIs embedded in C code.

# Disclaimer

The library is in early development and should be considered a work in progress.

This project has purely educational purposes. It began while I was developing a text based game and needed a simple library to handle the output.
This project serves as a personal foundation for understanding how UI systems work.

# Building

The easiest way to install the library is to download the source code and run the cmake file. It installs the static library on your system and lets you also build some demo files.

## Dependencies

In order to build the library you need **ncurses** and **libxml** already installed on your system. If the dependancies are not installed the cmake will output an error.

# Data structure

CTUIX represents XML files using `CTUIX_Node` and `CTUIX_Manager` struct data type:

- `CTUIX_Manager` represents an XML file and contains pointers to the root node and active node

- `CTUIX_Node` is a fundamental building block of the library's tree structure

# Workflow

There are four main elements in the workflow:

1. initializing

2. parsing the xml file

3. using the core loop

4. proper exiting and freeing all the elements

## XML structure

The XML structure is given should correspond the `ctuix.dtd` file.

Every XML file should start with a root element

```xml
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

```c
ctuix_init(void);
```

## Parsing

To parse an xml file use

```c
CTUIX_Manager* ctuix_parse(char *file_path);
```

To parse multiple files use

```c
CTUIX_Manager* ctuix_parse_multiple(char **file_path, int count);
```

The return value for both functions is `CTUIX_Manager`.

## Error parsing

All software is prone to errors. The library provides several functions that users can implement to catch and handle them.

The library provides a function to catch errors:

```c
void ctuix_error_show(const char *title, const char *message);
```

The function stops **ncurses** and prints a titled error message, and waits for the user to press Enter before restoring the UI. It is suitable for non‑critical errors.

## Core

The main function that user must call in order to run the UI is:

```c
int ctuix_run(CTUIX_Manager *ctuix_manager);
```

The ctuix_run function starts the main event loop for a given UI manager (or head UI manager in case of multiple XML files). It first draws the initial window tree, then repeatedly waits for user input, processes key events (including tab navigation and button activation), and handles any generated events (such as loading another UI screen). The loop continues until the user presses `q` or an event triggers an exit. The function returns `1` upon normal termination.

## Exit

To end the program properly we need to clean all the resources used by **ncurses**, **libxml** and **ctuix**.

```c
void ctuix_end(void)
````
restores the terminal to its original state after ncurses mode was activated. It must be called before your program exits to avoid leaving the terminal in an unusable state.

```c
void ctuix_delete(CTUIX_Manager *ctuix_manager)
```
frees all memory associated with the given UI manager, including its window tree, node names, values, and identifiers. It also recursively destroys any child windows. Call this when you no longer need a particular UI screen to prevent memory leaks.

```c
void ctuix_cleanup(void)
```
releases internal resources used by libxml2. It should be invoked after all XML parsing is finished and before the program terminates. This is especially important when multiple XML files are processed.

# Event system

The event system in CTUIX is very simple and is designed to handle user interactions and transitions between different UI screens (XML files).

## Event types and structs

Events are defined by the `CTUIX_Event_Type` enumeration:

```c
typedef enum
{
    CTUIX_EVENT_NONE, // default, no event
    CTUIX_EVENT_QUIT, // exit the application
    CTUIX_EVENT_SUBMIT, // submit user data
    CTUIX_EVENT_LOAD // load new XML file
} CTUIX_Event_Type;
```

Each event is represented by the `CTUIX_Event` struct:

```c
typedef struct CTUIX_Event
{
    CTUIX_Event_Type ctuix_event_type;
    void *user_data; // pointer to user defined data (file path)
} CTUIX_Event;
```

The library provides `ctuix_set_on_click`to assign the user defined event to a specific XML node:

```c
void ctuix_set_on_click(CTUIX_Manager *ctuix_manager, char *file_path, char *ctuix_node_id, CTUIX_Event (*on_click)(CTUIX_Node*, void *user_data), void *user_data);
```

When a button is activated (by pressing Enter), its `on_click` function is called. The function returns an event, which is then stored in the node corresponding.

The user callback must be of this signature:

```c
CTUIX_Event my_button_callback(CTUIX_Node *button_node, void *user_data)
{
    // Create an event of the desired type
    CTUIX_Event event;
    event.ctuix_event_type = CTUIX_EVENT_LOAD; // example
    event.user_data = (void *)"other_screen.xml"; // file path to load
    return event;
}
```

The event system is stiill in development and `CTUIX_EVENT_QUIT` and `CTUIX_EVENT_SUBMIT` are not automatically processed by the core yet.

# Example

see `data` and `demo` folders

# Docs

For developer documentation (docs/private) and public API details (docs/public) see the Doxygen-generated HTML files.