/* Use the external Snabbdom bindings via Ex */
exception Not_supported;
module VNode = SnabbdomVnode;
module Data = SnabbdomData;

type vnode = VNode.t;
type patchfn = VNode.t => VNode.t => unit;
type snabbdomModule;

external init : array snabbdomModule =>
  patchfn = "init" [@@bs.module "snabbdom"];

/* ==== Transformers ====  */
/* General */
let namespace ns => VNode.setInData [|"ns"|] ns;
type vnodeTransformer = vnode => vnode;

let rec recursivelySetNamespace ns (vnode: vnode) : unit => {
  let vnode = namespace ns vnode;
  switch (VNode.getChildren vnode) {
  | Some children => Array.iter (recursivelySetNamespace ns) children
  | None => ()
  }
};

let h selector (transformers: list vnodeTransformer) : vnode => {
  /* Start with a blank vnode */
  let vnode = VNode.empty ();
  VNode.setSel vnode selector;

  /* Now run through all the transformers provided to set up the vnode */
  let transform (vnode: vnode) (transformer: vnodeTransformer) => transformer vnode;
  let vnode =
    List.fold_left
      transform
      vnode
      transformers;

  /* Need to know if the node is an SVG so we can add the XML namespace */
  let isSvg =
    switch (String.length selector) {
    | len when len === 3 => selector === "svg"
    | len when len >= 4 =>
      switch (String.sub selector 0 4) {
      | "svg#" => true
      | "svg." => true
      | _ => false
      }
    | _ => false
    };
  if isSvg {
    recursivelySetNamespace "http://www.w3.org/2000/svg" vnode;
    ()
  } else {
    ()
  };
  vnode
};

let textVnode t => {
  let node = VNode.empty ();
  VNode.setText node t;
  node
};

let content (newChildren: list vnode) vnode : vnode => {
  switch (VNode.getChildren vnode, VNode.getText vnode) {
  | (None, Some t) =>
    VNode.clearText vnode;
    VNode.setChildren vnode (Array.of_list ([textVnode t] @ newChildren))
  | (Some children, None) =>
    VNode.setChildren vnode
      (Array.append children (Array.of_list newChildren))
  | (None, None) => VNode.setChildren vnode (Array.of_list newChildren)
  | _ => raise Not_supported
  };
  vnode
};

let text new_text vnode : vnode => {
  switch (VNode.getChildren vnode) {
  | Some children =>
    VNode.setChildren vnode (Array.append children [|textVnode new_text|])
  | None => VNode.setText vnode new_text
  };
  vnode
};

let key (key: string) vnode => {
  VNode.setKey vnode key;
  vnode
};

let nothing (a: vnode) => a;

/* Attribute module */
external moduleAttributes : snabbdomModule =
  "default" [@@bs.module "snabbdom/modules/attributes"];
let attr key (value: string) => VNode.setInData [|"attrs", key|] value;
let value = attr "value";

/* Class module */
external moduleClass : snabbdomModule =
  "default" [@@bs.module "snabbdom/modules/class"];
let class_name key => VNode.setInData [|"class", key|] Js.true_;
let css names vnode =>
  Js.Array.reduce
    (fun vnode name => class_name name vnode) vnode (Js.String.split " " names);

/* Style module */
external moduleStyle : snabbdomModule =
  "default" [@@bs.module "snabbdom/modules/style"];
let style style_attr (value: string) =>
   VNode.setInData [|"style", style_attr|] value;
let styleDelayed style_attr (value: string) =>
  VNode.setInData [|"style", "delayed", style_attr|] value;
let styleRemove style_attr (value: string) =>
  VNode.setInData [|"style", "remove", style_attr|] value;
