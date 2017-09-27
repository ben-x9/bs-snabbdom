/* Use the external Snabbdom bindings via Ex */
exception Not_supported;
module VNode = Snabbdom_vnode;
module Data = Snabbdom_data;

type vnode = VNode.t;
type patchfn = VNode.t => VNode.t => unit;
type snabbdom_module;

external init : array snabbdom_module =>
  patchfn = "init" [@@bs.module "snabbdom"];

/* ==== Transformers ====  */
/* General */
let namespace ns => VNode.set_in_data [|"ns"|] ns;
type vnode_transformer = vnode => vnode;

let rec recursively_set_namespace ns (vnode: vnode) :unit => {
  let vnode = namespace ns vnode;
  switch (VNode.get_children vnode) {
  | Some children => Array.iter (recursively_set_namespace ns) children
  | None => ()
  }
};

let h selector (transformers: list vnode_transformer) :vnode => {
  /* Start with a blank vnode */
  let vnode = VNode.empty ();
  VNode.set_sel vnode selector;

  /* Now run through all the transformers provided to set up the vnode */
  let transform (vnode: vnode) (transformer: vnode_transformer) => transformer vnode;
  let vnode =
    List.fold_left
      transform
      vnode
      transformers;

  /* Need to know if the node is an SVG so we can add the XML namespace */
  let is_svg =
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
  if is_svg {
    recursively_set_namespace "http://www.w3.org/2000/svg" vnode;
    ()
  } else {
    ()
  };
  vnode
};

let text_vnode t => {
  let node = VNode.empty ();
  VNode.set_text node t;
  node
};

let children (new_children: list vnode) vnode :vnode => {
  switch (VNode.get_children vnode, VNode.get_text vnode) {
  | (None, Some t) =>
    VNode.clear_text vnode;
    VNode.set_children vnode (Array.of_list ([text_vnode t] @ new_children))
  | (Some children, None) =>
    VNode.set_children vnode
      (Array.append children (Array.of_list new_children))
  | (None, None) => VNode.set_children vnode (Array.of_list new_children)
  | _ => raise Not_supported
  };
  vnode
};

let text new_text vnode :vnode => {
  switch (VNode.get_children vnode) {
  | Some children =>
    VNode.set_children vnode (Array.append children [|text_vnode new_text|])
  | None => VNode.set_text vnode new_text
  };
  vnode
};

let key (key: string) vnode => {
  VNode.set_key vnode key;
  vnode
};

let nothing (a: vnode) => a;

/* Attribute module */
external module_attributes : snabbdom_module =
  "default" [@@bs.module "snabbdom/modules/attributes"];
let attr key (value: string) => VNode.set_in_data [|"attrs", key|] value;
let value = attr "value";

/* Class module */
external module_class : snabbdom_module =
  "default" [@@bs.module "snabbdom/modules/class"];
let class_name key => VNode.set_in_data [|"class", key|] Js.true_;
let css names vnode =>
  Js.Array.reduce
    (fun vnode name => class_name name vnode) vnode (Js.String.split " " names);

/* Style module */
external module_style : snabbdom_module =
  "default" [@@bs.module "snabbdom/modules/style"];
let style style_attr (value: string) =>
   VNode.set_in_data [|"style", style_attr|] value;
let style_delayed style_attr (value: string) =>
  VNode.set_in_data [|"style", "delayed", style_attr|] value;
let style_remove style_attr (value: string) =>
  VNode.set_in_data [|"style", "remove", style_attr|] value;
