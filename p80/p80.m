f[x_] := Total[ IntegerDigits[Floor[Sqrt[x]*10^(99 - Floor[Log[10, Sqrt[x]]])]]]
Print[Total[f /@ Range[1, 100]] - Sum[Total[IntegerDigits[x]], {x, 1, 10}]]
