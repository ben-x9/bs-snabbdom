open Snabbdom.Base;
open Snabbdom.Props;
open Snabbdom.Events;
open Snabbdom.Dom;
module Store = Snabbdom.SimpleStore;

let patch = init [|
  moduleProps,
  moduleAttributes,
  moduleEventlisteners,
  moduleStyle
|];

type action =
  | Increment
  | Decrement
  | SetText string
  | AddItem
  | Delete string
  | ToggleShow bool;

type state = {
  count: int,
  name: string,
  items: list string,
  show_items: bool
};

let rec many_items items i max =>
  switch i {
  | _ when i >= max => items
  | _ => many_items (List.append ["Item " ^ string_of_int i] items) (i + 1) max
  };

let checkbox (checked: bool) onCheck (label_text: string) =>
  h "label" [
    content [
      h "input" [
        onChange onCheck,
        prop "type" "checkbox",
        prop "checked" (if checked {"checked"} else {""})
      ],
      h "span" [style "font-weight" "bold", text label_text]
    ]
  ];

let item store s => {
  let del _ => Store.dispatch store (Delete s);
  h "tr" [
    key s,
    style "line-height" "0",
    style "opacity" "1",
    style "transition" "line-height 0.3s, opacity 0.3s",
    styleDelayed "line-height" "1",
    styleRemove "line-height" "0",
    styleRemove "opacity" "0",
    content [
      h "td" [
        content [h "a" [prop "href" "javascript:;", onMouseMove del, text s]]
      ]
    ]
  ]
};

let view store => {
  let state = Store.get_state store;
  let cb action ev => {
    preventDefault ev;
    stopPropagation ev;
    Store.dispatch store action
  };
  let onChange ev =>
    next_tick (
      fun () => {
        let value = ev |> getTarget |> getValue;
        Store.dispatch store (SetText value)
      }
    );
  let onCheck ev => {
    let value = ev |> getTarget |> isChecked;
    Store.dispatch store (ToggleShow value)
  };
  h "div" [
    content [
      h "h1" [text ("Count: " ^ string_of_int state.count)],
      h "button" [onClick (cb Increment), text "+"],
      h "button" [onClick (cb Decrement), text "-"],
      h "p" [
        content [h "strong" [text "bs-snabbdom"]],
        text " demo. ",
        content [h "em" [text state.name]]
      ],
      h "div" [
        content [
          h
            "input"
            [
              onKeyDown onChange,
              prop "placeholder" "Type something, click Add",
              prop "value" state.name
            ],
          h "button" [onClick (cb AddItem), text "Add"]
        ]
      ],
      checkbox state.show_items onCheck "Show item list",
      h "svg" [
        attr "width" "200",
        attr "height" "200",
        content [
          h
            "circle"
            [attr "cx" "50", attr "cy" "50", attr "r" "30", attr "fill" "#000"]
        ]
      ]
    ],
    if state.show_items {
      content [
        h "table" [
          content [h "tr" [content [h "td" [text "Mouse over to delete"]]]],
          prop "border" "1",
          content (List.map (item store) state.items)
        ]
      ]
    } else {
      nothing
    }
  ]
};

exception No_root_element;

let vnode = ref (Snabbdom.VNode.fromDomId "app");

let reducer state action =>
  switch action {
  | Increment => {...state, count: state.count + 1}
  | Decrement => {...state, count: state.count - 1}
  | SetText v => {...state, name: v}
  | AddItem =>
    let item_name = state.name ^ ": " ^ string_of_int state.count;
    {...state, items: List.append [item_name] state.items, name: ""}
  | Delete s =>
    let no_name_match item => not (item === s);
    {...state, items: List.filter no_name_match state.items}
  | ToggleShow show => {...state, show_items: show}
  };

let logging_middleware store next action => {
  print_endline "Action:";
  Js.log action;
  next action;
  print_endline "New state:";
  Js.log (Store.get_state store)
};

let render view store => {
  let newVnode = view store;
  patch !vnode newVnode;
  vnode := newVnode;
  ()
};

let main () => {
  let store =
    Store.create_store_with_middleware
      {count: 0, name: "", items: many_items [] 0 500, show_items: false}
      reducer
      logging_middleware;
  Store.on_change store (render view);
  render view store;
  ()
};

main ();
