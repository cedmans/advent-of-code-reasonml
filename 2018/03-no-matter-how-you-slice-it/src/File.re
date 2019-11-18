[@bs.val] external __dirname: string = "__dirname";

let getAbsolutePath = (filename: string) =>
  Node.Path.resolve(__dirname, filename);

let loadFile = (path: string) => {
  let path = getAbsolutePath(path);
  Node.Fs.readFileSync(path, `utf8);
};