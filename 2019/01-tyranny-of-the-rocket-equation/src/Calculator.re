let inputFilename = "input.txt";

let splitStringContents = string => Js.String.split("\n", string);

let rec calculateFuel = (mass: float): int => {
  switch (mass) {
  | mass when mass <= 0. => 0
  | mass =>
    let m =
      switch (mass /. 3. |> Js.Math.floor |> (+)(-2)) {
      | m when m <= 0 => 0
      | m => m
      };
    m + calculateFuel(Belt.Float.fromInt(m));
  };
};

inputFilename
|> File.loadFile
|> splitStringContents
|> Array.map(Js.Float.fromString)
|> Array.map(calculateFuel)
|> Array.fold_left((+), 0)
|> Js.log;