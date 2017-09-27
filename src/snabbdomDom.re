type element = Dom.element;
external focus : Dom.element => unit = "focus" [@@bs.send];
external document : Dom.document = "" [@@bs.val];
external getElementById : Dom.document => string => option Dom.element =
  "getElementById" [@@bs.send] [@@bs.return null_to_opt];

external stopPropagation : Dom.event_like 'a => unit =
  "stopPropagation" [@@bs.send];

external preventDefault : Dom.event_like 'a => unit =
  "preventDefault" [@@bs.send];

external getTarget : Dom.event_like 'a => Dom.eventTarget_like 'a =
  "target" [@@bs.get];

external getKey : Dom.keyboardEvent => string =
  "key" [@@bs.get];

external getKeyCode : Dom.keyboardEvent => int =
  "keyCode" [@@bs.get];

external getValue : Dom.eventTarget_like 'a => string =
  "value" [@@bs.get];

external isChecked : Dom.eventTarget_like 'a => bool =
  "checked" [@@bs.get];

external setTimeout : (unit => unit) => int => int =
  "setTimeout" [@@bs.val];
