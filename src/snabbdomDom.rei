/* Bindings to some standard DOM functions. Some of these might be implemented
   in the Bucklescript, standard libraries, at which point they can be removed
   from here. */

type element = Dom.element;
let focus: element => unit;
let document: Dom.document;
let getElementById: Dom.document => string => option element;
let stopPropagation: Dom.event_like 'a => unit;
let preventDefault: Dom.event_like 'a => unit;
let getTarget: Dom.event_like 'a => Dom.element;
let getValue: Dom.element => string;
let getKey: Dom.keyboardEvent => string;
let getKeyCode: Dom.keyboardEvent => int;
let isChecked: Dom.element => bool;
let setTimeout: (unit => unit) => int => int;
