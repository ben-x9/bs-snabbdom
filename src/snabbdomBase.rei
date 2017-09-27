/* Main snabbdom functions */

/* This snabbdom function is not supported */
exception Not_supported;

/**
 * A Snabbdom patch function (returned by `init`) which takes an old DOM
 * element or vnode and patches it to match a new vnode
 */
type patchfn = SnabbdomVnode.t => SnabbdomVnode.t => unit;

/**
 * This type refers to a Snabbdom Module. Any
 * modules with this type can be passed to `init` to
 * create a patching function.
 * {{:https://github.com/snabbdom/snabbdom#modules-documentation}
 * See the Snabbdom documentation for details on modules}
 *
 * If you've built a custom module, you can define it using:
 * {[external myModule : snabbdomModule =
 *   "default" \[\@\@bs.module "path/to/module"\]]}
 */
type snabbdomModule;

/* Create a Snabbdom patch function from an array of snabbdom modules. */
let init: array snabbdomModule => patchfn;

/**
 * The recommended function for creating Snabbdom vnodes. Note this function
 * doesn't work exactly like
 * {{:https://github.com/snabbdom/snabbdom#snabbdomh} Snabbdom's `h` function}
 *
 * Since we're working in a different language, bs-snabbdom provides a
 * slightly different h function for constructing the vnodes that better works
 * with OCaml.
 *
 * The first parameter is the same as Snabbdom's - an html selector describing
 * the element
 * type and any classes/id to apply to the element.
 *
 * The second parameter takes a list of {!type:SnabbdomVnode.transformer}
 * functions, which specify how to create the vnode. Some transformers are
 * implemented in this module below.
 *
 * Usage example:
 * {[h "div.section" \[
 *   style "border" "1px solid black";
 *   text "Hello World!"
 * \]]}
 */
let h: string => list SnabbdomVnode.transformer => SnabbdomVnode.t;

/* Add child vnodes */
let content: list SnabbdomVnode.t => SnabbdomVnode.transformer;

/* Adds text to the body of the node */
let text: string => SnabbdomVnode.transformer;

/**
 * Sets the Snabbdom key for this node. Use this on
 * lists of items to help Snabbdom reconcile the old
 * and new nodes and reuse nodes that belong to the
 * same key when reordering the list.
 */
let key: string => SnabbdomVnode.transformer;

/**
 * Don't transform the {!type:SnabbdomVnode.t}. Can be useful for if statements:
 * {[if is_active then class_name "is-active" else nothing]}
 */
let nothing: SnabbdomVnode.transformer;

let moduleAttributes: snabbdomModule;
let attr: string => string => SnabbdomVnode.transformer;
let value: string => SnabbdomVnode.transformer;

let moduleClass: snabbdomModule;
let css: string => SnabbdomVnode.transformer;

let moduleStyle: snabbdomModule;
let style: string => string => SnabbdomVnode.transformer;
let styleDelayed: string => string => SnabbdomVnode.transformer;
let styleRemove: string => string => SnabbdomVnode.transformer;
