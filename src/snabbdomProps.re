open SnabbdomBase;

external module_props : snabbdom_module =
  "default" [@@bs.module "snabbdom/modules/props"];

/* Prop module */
let prop key (value: string) =>
  SnabbdomVnode.set_in_data [|"props", key|] value;
