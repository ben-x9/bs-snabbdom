/* Bindings to some standard DOM functions. Some of these might be implemented
   in the Bucklescript, standard libraries, at which point they can be removed
   from here. */

type element = Dom.element;
let focus: element => unit;
let document: Dom.document;
let get_element_by_id: Dom.document => string => option element;
let stop_propagation: Dom.event_like 'a => unit;
let prevent_default: Dom.event_like 'a => unit;
let get_target: Dom.event_like 'a => Dom.eventTarget_like 'a;
let get_value: Dom.eventTarget_like 'a => string;
let get_event_key: Dom.keyboardEvent => string;
let is_checked: Dom.eventTarget_like 'a => bool;
let set_timeout: (unit => unit) => int => int;
