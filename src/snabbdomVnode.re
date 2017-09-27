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

external unsafeSetChildren : t => 'a => unit = "children" [@@bs.set];

external setSel : t => string => unit = "sel" [@@bs.set];
external setData : t => Data.t => unit = "data" [@@bs.set];
external setChildren : t => array t => unit = "children" [@@bs.set];
external setText : t => string => unit = "text" [@@bs.set];
external setKey : t => string => unit = "key" [@@bs.set];
let clearText vnode => unsafeSetChildren vnode Js.undefined;

external unsafeGetData : t => Data.t = "data" [@@bs.get];
external getChildren : t => option (array t) =
  "children" [@@bs.get] [@@bs.return null_undefined_to_opt];
external getElm : t => option Dom.element =
  "elm" [@@bs.get] [@@bs.return null_undefined_to_opt];
external getText : t => option string =
  "text" [@@bs.get] [@@bs.return null_undefined_to_opt];
external ofDomElement : Dom.element => t = "%identity";

let setInData path value vnode => {
  setData vnode (Data.setInPath (unsafeGetData vnode) path value);
  vnode
};

exception ElementWithIdNotFound string;
let fromDomId domId =>
  switch (SnabbdomDom.getElementById SnabbdomDom.document domId) {
  | None => raise (ElementWithIdNotFound domId)
  | Some x => ofDomElement x
  };
