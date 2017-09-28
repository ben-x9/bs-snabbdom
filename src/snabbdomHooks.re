module VNode = SnabbdomVnode;

let hook key cb => VNode.setInData [|"hook", key|] cb;
let hook0 key (cb: unit => unit) => hook key cb;
let hook1 key (cb: VNode.t => unit) => hook key cb;
let hook2 key (cb: VNode.t => VNode.t => unit) => hook key cb;

let pre cb => hook0 "pre" cb;
let onInit cb => hook1 "init" cb;
let onCreate cb => hook2 "create" cb;
let onInsert cb => hook1 "insert" cb;
let prepatch cb => hook2 "prepatch" cb;
let onUpdate cb => hook2 "update" cb;
let postpatch cb => hook2 "postpatch" cb;
let onDestroy cb => hook1 "destroy" cb;

type removeCallback = unit => unit;
let onRemove (cb: VNode.t => removeCallback => unit) => hook "remove" cb;

let post cb => hook0 "post" cb;

let autofocus = onInsert (fun vnode =>
  switch (VNode.getElm vnode) {
  | Some elm => SnabbdomDom.focus elm
  | None => ()
  }
);
