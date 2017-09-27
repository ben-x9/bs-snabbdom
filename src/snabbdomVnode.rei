/**
 * The VNode module provides types and functions for interacting with native
 * Snabbdom vdom nodes
 */

/* Represents a Snabbdom vnode */
type t;

/* A transformer is any function which modifies a Snabbdom vnode. */
type transformer = t => t;

let empty: unit => t;
let set_sel: t => string => unit;
let set_data: t => SnabbdomData.t => unit;
let set_children: t => array t => unit;
let set_text: t => string => unit;
let set_key: t => string => unit;
let clear_text: t => unit;

let get_children: t => option (array t);
let get_elm: t => option Dom.element;
let get_text: t => option string;

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
 * {[let vnode = set_in_data \[|"ns"|\] "xyz" vnode]}
 */

let set_in_data:
  array string => 'a => t => t;


/**
 * Exception raised when {!val:from_dom_id} is called with an
 * element id that does not exist.
 */

exception Element_with_id_not_found string;

/**
 * Create a VNode from an element in the DOM with the specified id.
 * This function may raise an {!exception:Element_with_id_not_found} exception.
 */

let from_dom_id: string => t;

/**
 * Compile-time conversion of DOM elements to a Snabbdom vnode.
 * This function doesn't actually do anything at runtime.
 * Since the Snabbdom patch function allows us to use
 * an existing DOM element as an 'old' vnode, this function
 *  just explicitly tells the compiler that we know what we're
 * doing.
 */

let of_dom_element: Dom.element => t;
