import random


class Node:
    def __init__(self, data):
        self.left = None
        self.right = None
        self.data = data
        self.fitness = None

    # Method 0 = Grow
    # Method 1 = Full
    def generate_expression(self, depth, operators, operands, method):

        operands_len = len(operands)
        operators_len = len(operators)

        if depth == 0 or (method == 0 and random.random() < float(operands_len) / (operands_len + operators_len)):
            self.data = random.choice(operands)
        else:
            self.data = random.choice(operators)
            self.left = Node("")
            self.left.generate_expression(depth - 1, operators, operands, method)
            self.right = Node("")
            self.right.generate_expression(depth - 1, operators, operands, method)

    def get_depth(self):
        l, r = 0, 0
        if self.left is not None:
            l = self.left.get_depth()
        if self.right is not None:
            r = self.right.get_depth()

        if l > r:
            return 1 + l
        else:
            return 1 + r

    def get_expression(self, expression):
        expression.append(self.data)
        if self.left is not None:
            expression = self.left.get_expression(expression)
        if self.right is not None:
            expression = self.right.get_expression(expression)
        return expression
