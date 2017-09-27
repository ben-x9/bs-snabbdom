module Data = SnabbdomData;

type t =
  Js.t {
    .
    sel : Js.undefined string,
    data : Data.t,
    children : Js.undefined (array t),
    elm : Js.undefined Dom.element,
    text : Js.undefined string,
    key : Js.undefined string
  };

type transformer = t => t;

let empty () :t => {
  "sel": Js.undefined,
  "data": Data.empty (),
  "children": Js.undefined,
  "elm": Js.undefined,
  "text": Js.undefined,
  "key": Js.undefined
};

external unsafe_set_children : t => 'a => unit = "children" [@@bs.set];

external set_sel : t => string => unit = "sel" [@@bs.set];
external set_data : t => Data.t => unit = "data" [@@bs.set];
external set_children : t => array t => unit = "children" [@@bs.set];
external set_text : t => string => unit = "text" [@@bs.set];
external set_key : t => string => unit = "key" [@@bs.set];
let clear_text vnode => unsafe_set_children vnode Js.undefined;

external unsafe_get_data : t => Data.t = "data" [@@bs.get];
external get_children : t => option (array t) =
  "children" [@@bs.get] [@@bs.return null_undefined_to_opt];
external get_elm : t => option Dom.element =
  "elm" [@@bs.get] [@@bs.return null_undefined_to_opt];
external get_text : t => option string =
  "text" [@@bs.get] [@@bs.return null_undefined_to_opt];
external of_dom_element : Dom.element => t = "%identity";

let set_in_data path value vnode => {
  set_data vnode (Data.set_in_path (unsafe_get_data vnode) path value);
  vnode
};

exception Element_with_id_not_found string;
let from_dom_id dom_id =>
  switch (SnabbdomDom.get_element_by_id SnabbdomDom.document dom_id) {
  | None => raise (Element_with_id_not_found dom_id)
  | Some x => of_dom_element x
  };
