open SnabbdomBase;
module VNode = SnabbdomVnode;

external moduleEventlisteners : snabbdomModule =
  "default" [@@bs.module "snabbdom/modules/eventlisteners"];

/* Helper for waiting until post-render before calling a callback */
let next_tick cb => {
  let _ = SnabbdomDom.setTimeout cb 0;
  ()
};

type eventCb 'a = 'a => unit;
let eventListener key cb => VNode.setInData [|"on", key|] cb;

let event event (cb: eventCb Dom.event) => eventListener event cb;
let onChange = event "change";
let onInput = event "input";

let mouse event (cb: eventCb Dom.mouseEvent) => eventListener event cb;

let onClick = mouse "click";
let onMouseDown = mouse "mousedown";
let onMouseUp = mouse "mouseup";
let onMouseMove = mouse "mousemove";

let keyboard event (cb: eventCb Dom.keyboardEvent) => eventListener event cb;
let onKeyDown = keyboard "keydown";
let onKeyUp = keyboard "keyup";
let onKeyPress = keyboard "keypress";

let drag event (cb: eventCb Dom.dragEvent) => eventListener event cb;
let onDragEnter = drag "dragenter";
let onDragOver = drag "dragover";
let onDragLeave = drag "dragleave";
let onDrop = drag "drop";
