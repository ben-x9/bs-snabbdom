module VNode = SnabbdomVnode;

let hook key cb => VNode.setInData [|"hook", key|] cb;
let hook0 key (cb: unit => unit) => hook key cb;
let hook1 key (cb: VNode.t => unit) => hook key cb;
let hook2 key (cb: VNode.t => VNode.t => unit) => hook key cb;

let pre cb => hook0 "pre" cb;
let init cb => hook1 "init" cb;
let create cb => hook2 "create" cb;
let insert cb => hook1 "insert" cb;
let prepatch cb => hook2 "prepatch" cb;
let update cb => hook2 "update" cb;
let postpatch cb => hook2 "postpatch" cb;
let destroy cb => hook1 "destroy" cb;

type removeCallback = unit => unit;
let remove (cb: VNode.t => removeCallback => unit) => hook "remove" cb;

let post cb => hook0 "post" cb;

let autofocus = insert (fun vnode =>
  switch (VNode.getElm vnode) {
  | Some elm => SnabbdomDom.focus elm
  | None => ()
  }
);
