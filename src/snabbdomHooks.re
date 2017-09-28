module VNode = SnabbdomVnode;

open SnabbdomDom;

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

let (>>) f g x => g (f x);

/**
 * FIXME: I HAVE NO IDEA why I need to make this a higher order function but
 * snabbdom wont keep triggering it after the first insert unless I do this. To
 * be debugged later... (Originally there was no `onInsert` parameter so
 * returning an anonymous function which was then immediately called was just a
 * hack to make it work)
 */
let setFocus onInsert => (fun vnode => {
  switch (VNode.getElm vnode) {
  | Some elm =>
    focus elm;
    if onInsert (setSelectionRange elm 0 (getValue elm |> String.length));
  | None => ()
  };
});

let autoFocus vnode =>
  (onInsert (setFocus true) >> onUpdate (fun _ vnode => (setFocus false) vnode)) vnode;
