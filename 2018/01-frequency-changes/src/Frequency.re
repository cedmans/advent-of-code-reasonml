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

let addVariance = (initial: int, variance: int) => initial + variance;
let addVariances = (variances: array(int)) =>
  Array.fold_left(addVariance, 0, variances);

inputFilename
|> getAbsolutePath
|> loadFile
|> splitStringContents
|> parseVariances
|> addVariances
|> Js.log;