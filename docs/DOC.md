# Declarative TUI Widget System (C / ncurses)

This document describes the core widget model for a declarative, XML-driven TUI framework built on top of **ncurses**.

The goal is to define UI structure declaratively (XML) and render it
using a small, explicit widget system written in C.

## Design Principles

- Declarative layout (XML defines structure, not logic)
- Explicit widget state (no hidden state like CDK)
- Parse XML once, draw many times
- ncurses is the backend, not the architecture
- Small number of orthogonal widgets
- Composition over specialization

## Widget Categories

Widgets are divided into **containers** and **elements**.

## Containers

### 1. PANEL

**General-purpose container**

Responsibilities:
- Owns a `WINDOW *`
- Defines position and size
- Contains child widgets
- Optional border and title
- Clips children to its area

Notes:
- All widgets ultimately live inside a PANEL
- Maps directly to `newwin()` or `derwin()`

### 2. SELECTIONBOX

**Layout and focus management container**

Responsibilities:
- Contains focusable widgets
- Manages navigation (up/down/left/right)
- Supports horizontal or vertical layout
- Maintains selected index

Used for:
- Menus
- Button groups
- Toolbars
- Radio-style selections

### 3. SCROLLPANEL

**Scrollable content container**

Responsibilities:
- Displays content larger than its viewport
- Manages scroll offset
- Handles scrolling keys (up/down/page)

Content types:
- Text (`char *`)
- Lists (`char **`)

## Elements

### 4. LABEL

**Static text**

Characteristics:
- Not focusable
- No input handling
- Used for titles, hints, descriptions

Optional features:
- Text alignment (left/center/right)
- Wrapping or truncation

### 5. BUTTON

**Activatable widget**

Characteristics:
- Focusable
- Activated by ENTER / SPACE
- Triggers a callback by name

### 6. ENTRYBOX

**Text input field**

Responsibilities:
- Stores editable text buffer
- Maintains cursor position
- Handles insertion, deletion, navigation

Initial scope:
- ASCII input
- Left/right/backspace/delete
- Optional max length

## Widget Hierarchy Model

All widgets share a common base structure:

```c
typedef struct Widget {
    WidgetType type;

    int x, y, w, h;
    bool focusable;
    bool focused;

    struct Widget *parent;
    struct Widget *children;
    struct Widget *next;

    void (*draw)(struct Widget *, WINDOW *);
    void (*handle_key)(struct Widget *, int);
} Widget;
```

- Containers use `children`
- Element widgets ignore children

### Focus and Input Handling

Rules:

- Only one widget is focused at a time
- Key events are sent to the focused widget
- If not handled, the event bubbles to the parent container

Flow:

```
Key Press
 
 - Focused Widget
  - Parent (SelectionBox)
    - Root Panel
```

## Layout

Layout is a property of containers, not widgets themselves.

Supported:

- Fixed positioning (x/y)
- Vertical flow
- Horizontal flow

```c
typedef enum {
    LAYOUT_NONE,
    LAYOUT_VERTICAL,
    LAYOUT_HORIZONTAL
} LayoutType;
```

## Runtime Architecture

```
main()
parse_xml()
build widget tree
init_curses()
create_windows()
event loop
draw_ui()
handle_input()
update_state()
```

Key rules:

- XML parsing happens once
- Windows are created once
- Drawing happens repeatedly
- State persists between draws

## Backend Choice

- **ncurses**: required

## Scope

This widget set is sufficient for:

- Configuration tools
- Installers
- Admin panels
- Text-based dashboards
- Interactive CLI applications

