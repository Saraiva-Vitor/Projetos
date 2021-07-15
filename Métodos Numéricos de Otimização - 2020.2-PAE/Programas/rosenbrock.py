# -*- coding: utf-8 -*-
"""
Created on Mon Apr 19 15:58:00 2021

@author: Sir Viktor
"""

"""
Minimize the Rosenbrock banana function.

http://en.wikipedia.org/wiki/Rosenbrock_function
"""

import numpy

import minhelper

def rosenbrock(X):
    """
    This R^2 -> R^1 function should be compatible with algopy.
    http://en.wikipedia.org/wiki/Rosenbrock_function
    A generalized implementation is available
    as the scipy.optimize.rosen function
    """
    x = X[0]
    y = X[1]
    a = (x - 2)**4
    b = (x - 2*y)**2
    return a + b

def main():
    target = [1, 1]
    easy_init = [2, 2]
    hard_init = [-1.2, 1]
    minhelper.show_minimization_results(
            rosenbrock, target, easy_init, hard_init)

if __name__ == '__main__':
    main()