import fleauxstd as fstd


def _materialized_rhs_expression_multiply_print(x: float, y: float):
    return (x, y) | fstd.Multiply() | fstd.Println()


MultiplyPrint = fstd.make_node(_materialized_rhs_expression_multiply_print)


def _materialized_rhs_expression_polynomial(x: float):
    return ((((4, ((((('x:{}', x) | fstd.Printf()), 1, None) | fstd.Slice(), 0) | fstd.Extract())) | MultiplyPrint(), 7) | fstd.Pow()), ((x, 5) | fstd.Pow())) | fstd.Subtract()


Polynomial = fstd.make_node(_materialized_rhs_expression_polynomial)

4 | Polynomial() | fstd.Println()
6 | Polynomial() | fstd.Println()

1 | fstd.In() | fstd.ToNum() | Polynomial() | fstd.Println()
