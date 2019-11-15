exception InvalidVarianceString(string);
exception InvalidSign;

let splitStringContents = string => Js.String.split("\n", string);

let parseVariance = (varianceString: string) => {
  let r = [%re "/([+-])(\\d+)/"];
  let result = Js.String.match(r, varianceString);
  switch (result) {
  | Some([|_entire, sign, value|]) =>
    switch (sign) {
    | "+" => int_of_string(value)
    | "-" => int_of_string(value) * (-1)
    | _ => raise(InvalidSign)
    }
  | _ => raise(InvalidVarianceString(varianceString))
  };
};
let parseVariances = (varianceStrings: array(string)) =>
  Array.map(parseVariance, varianceStrings);

let parseFile = (contents: string) =>
  splitStringContents(contents)->parseVariances;