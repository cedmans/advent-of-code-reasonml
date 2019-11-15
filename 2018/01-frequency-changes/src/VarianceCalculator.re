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

let calculate = variances => addVariances(0, Belt.Set.Int.empty, variances);