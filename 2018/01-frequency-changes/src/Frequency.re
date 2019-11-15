[@bs.val] external __dirname: string = "__dirname";
exception InvalidVarianceString(string);
exception InvalidSign;

let inputFilename = "input.txt";

let getAbsolutePath = (filename: string) =>
  Node.Path.resolve(__dirname, filename);

let loadFile = (path: string) => Node.Fs.readFileSync(path, `utf8);

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

type variancePayload = {
  found: Belt.Set.Int.t,
  variance: int,
  recurse: bool,
};
let addVariance = (initial: variancePayload, variance: int) => {
  initial.recurse
    ? {
      let newVariance = initial.variance + variance;
      let found = initial.found;

      let recurse = !Belt.Set.Int.has(found, newVariance);
      let found = Belt.Set.Int.add(found, newVariance);

      {variance: newVariance, found, recurse};
    }
    : initial;
};
let rec addVariances =
        (initial: int, found: Belt.Set.Int.t, variances: array(int)) => {
  let result =
    Array.fold_left(
      addVariance,
      {found, variance: initial, recurse: true},
      variances,
    );

  result.recurse
    ? addVariances(result.variance, result.found, variances) : result.variance;
};

inputFilename
|> getAbsolutePath
|> loadFile
|> splitStringContents
|> parseVariances
|> addVariances(0, Belt.Set.Int.empty)
|> Js.log;