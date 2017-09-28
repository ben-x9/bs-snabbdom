type element = Dom.element;

external document : Dom.document = "" [@@bs.val];

external focus : Dom.element => unit =
  "focus" [@@bs.send];

external setSelectionRange : Dom.element => int => int => unit =
  "setSelectionRange" [@@bs.send];

external getElementById : Dom.document => string => option Dom.element =
  "getElementById" [@@bs.send] [@@bs.return null_to_opt];

external stopPropagation : Dom.event_like 'a => unit =
  "stopPropagation" [@@bs.send];

external preventDefault : Dom.event_like 'a => unit =
  "preventDefault" [@@bs.send];

external getTarget : Dom.event_like 'a => Dom.element =
  "target" [@@bs.get];

external getKey : Dom.keyboardEvent => string =
  "key" [@@bs.get];

external getKeyCode : Dom.keyboardEvent => int =
  "keyCode" [@@bs.get];

external getValue : Dom.element => string =
  "value" [@@bs.get];

external isChecked : Dom.element => bool =
  "checked" [@@bs.get];

external setTimeout : (unit => unit) => int => int =
  "setTimeout" [@@bs.val];
