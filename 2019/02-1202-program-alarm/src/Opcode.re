exception InvalidOpCode(int);

let file = "input.txt";

type op =
  | HALT
  | ADD
  | MULT
  | ERROR(int);

let toOp = (opCode: int) =>
  switch (opCode) {
  | 1 => ADD
  | 2 => MULT
  | 99 => HALT
  | x => ERROR(x)
  };

let deref = (program: array(int), position: int) => program[position];

let rec execute = (position: int, program: array(int)) => {
  let op = toOp(program[position]);
  switch (op) {
  | ADD =>
    let a = deref(program, position + 1);
    let b = deref(program, position + 2);
    let p = deref(program, position + 3);
    Js.log(a);
    Js.log(b);
    Js.log(p);
    program[p] = a + b;
    execute(position + 4, program);
  | MULT =>
    let a = deref(program, position + 1);
    let b = deref(program, position + 2);
    let p = deref(program, position + 3);
    program[p] = a * b;
    execute(position + 4, program);
  | HALT => program
  | ERROR(x) => raise(InvalidOpCode(x))
  };
};

let parse = (payload: string) =>
  Js.String.split(",", payload) |> Array.map(int_of_string);

File.loadFile(file) |> parse |> execute(0) |> Js.log;