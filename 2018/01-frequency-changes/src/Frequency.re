[@bs.val] external __dirname: string = "__dirname";

let inputFilename = "input.txt";

let getAbsolutePath = (filename: string) =>
  Node.Path.resolve(__dirname, filename);

let loadFile = (path: string) => Node.Fs.readFileSync(path, `utf8);

inputFilename |> getAbsolutePath |> loadFile |> Js.log;