# CTUIX TODO

## Events

* Define events
* Button emits CLICKED
* Entry emits SUBMITTED
* Quit emits QUIT_REQUESTED
* Add event handlers
* Register handlers before `ctuix_run`
* Pass UI context to handlers
* Let handlers access other nodes

## Input

* Widgets read their own input
* Widgets interpret keys
* Keep widget actions inside widgets

## XML

* Parse node IDs and names
* Connect XML events to handlers

## API

* Find nodes
* Read node values
* Change node values
* Application can control TUI

## Test

* Button → CLICKED → handler → find Entry → read value → change TUI → return to run

## Later

* Improve node lookup if needed
* Refactor after it works
