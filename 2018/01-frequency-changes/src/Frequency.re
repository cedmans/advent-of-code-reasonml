let inputFilename = "input.txt";

inputFilename
|> File.getAbsolutePath
|> File.loadFile
|> Parser.splitStringContents
|> Parser.parseVariances
|> VarianceCalculator.addVariances(0, Belt.Set.Int.empty)
|> Js.log;