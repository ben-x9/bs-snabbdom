type t;

type dataVal;
external toDataVal : 'a => dataVal = "%identity";

let rawEmpty: unit => t = [%bs.raw {|function() { return {} } |}];
let rawSetInPath: t => array string => dataVal => t =
  [%bs.raw {|
    function(data, path, value){
      var base = data || {};
      var ref = base;
      while (path.length > 1) {
        var next = path.shift();
        ref[next] = ref[next] || {};
        ref = ref[next];
      }
      if (path.length == 1) {
        var next = path.shift();
        ref[next] = value;
      }
      return base;
    }
  |}];

let empty () => rawEmpty ();
let setInPath data path value =>
  rawSetInPath data path (toDataVal value);
