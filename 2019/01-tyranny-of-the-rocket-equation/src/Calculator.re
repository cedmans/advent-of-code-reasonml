let inputFilename = "input.txt";

let splitStringContents = string => Js.String.split("\n", string);

let calculateFuel = (mass: float): int =>
  mass /. 3.0 |> Js.Math.floor |> (+)(-2);

inputFilename
|> File.loadFile
|> splitStringContents
|> Array.map(Js.Float.fromString)
|> Array.map(calculateFuel)
|> Array.fold_left((+), 0)
|> Js.log;