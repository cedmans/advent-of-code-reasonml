let inputFilename = "input.txt";

inputFilename
|> File.loadFile
|> Parser.parseFile
|> VarianceCalculator.calculate
|> Js.log;