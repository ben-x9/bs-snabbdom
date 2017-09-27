type element = Dom.element;
external focus : Dom.element => unit = "focus" [@@bs.send];
external document : Dom.document = "" [@@bs.val];
external get_element_by_id : Dom.document => string => option Dom.element =
  "getElementById" [@@bs.send] [@@bs.return null_to_opt];

external stop_propagation : Dom.event_like 'a => unit =
  "stopPropagation" [@@bs.send];

external prevent_default : Dom.event_like 'a => unit =
  "preventDefault" [@@bs.send];

external get_target : Dom.event_like 'a => Dom.eventTarget_like 'a =
  "target" [@@bs.get];

external get_event_key : Dom.keyboardEvent => string =
  "key" [@@bs.get];

external get_value : Dom.eventTarget_like 'a => string =
  "value" [@@bs.get];

external is_checked : Dom.eventTarget_like 'a => bool =
  "checked" [@@bs.get];

external set_timeout : (unit => unit) => int => int =
  "setTimeout" [@@bs.val];
