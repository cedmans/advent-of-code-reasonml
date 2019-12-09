exception ClaimParseError;

let filename = "input.txt";

type claim = {
  claimId: int,
  x: int,
  y: int,
  width: int,
  height: int,
};

let parseClaim = (line: string): claim => {
  let re = [%re "/#(\\d+) @ (\\d+),(\\d+): (\\d+)x(\\d+)/"];
  let res = Js.String.match(re, line);

  switch (res) {
  | Some([|_entire, claimId, x, y, width, height|]) =>
    let claimId = int_of_string(claimId);
    let x = int_of_string(x);
    let y = int_of_string(y);
    let width = int_of_string(width);
    let height = int_of_string(height);
    {claimId, x, y, width, height};
  | _ => raise(ClaimParseError)
  };
};
let parseClaims = (lines: array(string)): array(claim) => {
  Belt.Array.map(lines, parseClaim);
};

let buildCanvasAllocations = (claims: array(claim)) => {
  let canvas = Belt.Array.make(1000, Belt.Array.make(1000, 0));

  Belt.Array.forEach(
    claims,
    claim => {
      for (y in claim.y to claim.y + claim.height) {
        {};
      };
      ();
    },
  );
  canvas;
};

let splitBlob = (blob: string) => Js.String.split("\n", blob);
let parseBlob = (blob: string) => {
  blob |> splitBlob |> parseClaims;
};

File.loadFile("./" ++ filename)
|> parseBlob
|> buildCanvasAllocations
|> Js.log;