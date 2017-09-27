open SnabbdomBase;

external moduleProps : snabbdomModule =
  "default" [@@bs.module "snabbdom/modules/props"];

/* Prop module */
let prop key (value: string) =>
  SnabbdomVnode.setInData [|"props", key|] value;
