import math


class Pow:
    def __init__(self):
        pass

    def __ror__(self, args_tuple):
        return math.pow(*args_tuple)


class Subtract:
    def __init__(self):
        pass

    def __ror__(self, args_tuple):
        def subtract(lhs, rhs):
            return lhs - rhs
        return subtract(*args_tuple)


class Multiply:
    def __init__(self):
        pass

    def __ror__(self, args_tuple):
        def multiply(lhs, rhs):
            return lhs * rhs
        return multiply(*args_tuple)


class Divide:
    def __init__(self):
        pass

    def __ror__(self, args_tuple):
        def divide(lhs, rhs):
            return lhs / rhs
        return divide(*args_tuple)


class Add:
    def __init__(self):
        pass

    def __ror__(self, args_tuple):
        def add(lhs, rhs):
            return rhs + lhs
        return add(*args_tuple)


class Sqrt:
    def __init__(self):
        pass

    def __ror__(self, args_tuple):
        return math.sqrt(*args_tuple)


class Println:
    def __init__(self):
        pass

    def __ror__(self, args_tuple):
        if not isinstance(args_tuple, tuple):
            print(args_tuple)
            return args_tuple
        print(*args_tuple)
        return args_tuple


class Printf:
    def __init__(self):
        pass

    def __ror__(self, args_tuple):
        def _printf(fmt_str, *args):
            print(fmt_str.format(args))
        _printf(*args_tuple)
        return args_tuple


class Tan:
    def __init__(self):
        pass

    def __ror__(self, args):
        return math.tan(*args)


class Cos:
    def __init__(self):
        pass

    def __ror__(self, args):
        return math.cos(*args)


class Sin:
    def __init__(self):
        pass

    def __ror__(self, args_tuple):
        return math.sin(*args_tuple)


def MakeNode(func):
    class Node:
        def __init__(self):
            self.func = func

        def __ror__(self, args_tuple):
            if not isinstance(args_tuple, tuple):
                return self.func(args_tuple)
            return self.func(*args_tuple)
    return Node


MultiplyPrint = MakeNode(lambda x, y: ((x, y) | Multiply() | Println()))
Polynomial = MakeNode(lambda x: (((4, x) | MultiplyPrint(), 7) | Pow(), (x, 5) | Pow()) | Subtract())

4 | Polynomial() | Println()
6 | Polynomial() | Println()
