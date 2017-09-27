/**
 * The VNode module provides types and functions for interacting with native
 * Snabbdom vdom nodes
 */

/* Represents a Snabbdom vnode */
type t;

/* A transformer is any function which modifies a Snabbdom vnode. */
type transformer = t => t;

let empty: unit => t;
let setSel: t => string => unit;
let setData: t => SnabbdomData.t => unit;
let setChildren: t => array t => unit;
let setText: t => string => unit;
let setKey: t => string => unit;
let clearText: t => unit;

let getChildren: t => option (array t);
let getElm: t => option Dom.element;
let getText: t => option string;

/**
 * Sets an object property somewhere in the vnode data object.Pass an array of
 * strings representing the path to the property to be set, followed
 * by the property value. Intermediate objects will be created if they don't
 * already exist
 *
 * For example, to set the vnode's key property like the following (in
 * JavaScript):
 * {[vnode.data.ns = "xyz"]}
 *
 * Use:
 * {[let vnode = setInData \[|"ns"|\] "xyz" vnode]}
 */

let setInData: array string => 'a => t => t;


/**
 * Exception raised when {!val:from_dom_id} is called with an
 * element id that does not exist.
 */

exception ElementWithIdNotFound string;

/**
 * Create a VNode from an element in the DOM with the specified id.
 * This function may raise an {!exception:Element_with_id_not_found} exception.
 */

let fromDomId: string => t;

/**
 * Compile-time conversion of DOM elements to a Snabbdom vnode.
 * This function doesn't actually do anything at runtime.
 * Since the Snabbdom patch function allows us to use
 * an existing DOM element as an 'old' vnode, this function
 *  just explicitly tells the compiler that we know what we're
 * doing.
 */

let ofDomElement: Dom.element => t;
