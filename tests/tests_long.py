import random
import sys

import sympy
from sympy import QQ, Rational

#sys.setrecursionlimit(10000000000)
sys.path.insert(0, "../")
sys.path.insert(0, "./")
import lumper
import utils

def evalp(poly, point):
    pdict = poly.to_dict()
    result = 0
    for m, c in pdict.items():
        to_add = c
        for i in range(len(m)):
            to_add = to_add * point[i]**m[i]
        result += to_add

    return result

def dot_product(a, b):
    return sum([x * y for x, y in zip(a, b)])

def check_lumping(test_name, polys, lumping, correct_size):
    lumped_system = lumping["polynomials"]
    new_vars = lumping["subspace"]
    try:
        assert(len(lumped_system) == correct_size)
    except AssertionError:
        print(f"{test_name}: wrong size {len(lumped_system)}, expected {correct_size}")
    print("{test_name}: size is correct")

    specialization = [random.randint(1, 100) for _ in range(len(polys))]
    polys_values = [evalp(p, specialization) for p in polys]
    polys_values_lumped = [dot_product(polys_values, var) for var in new_vars]

    specialization_lumped = [dot_product(specialization, var) for var in new_vars]
    lumped_polys_values = [evalp(p, specialization_lumped) for p in lumped_system]

    try:
        assert(polys_values_lumped == lumped_polys_values)
    except AssertionError:
        print("Lumping is incorrect")
        print(polys_values_lumped)
        print(lumped_polys_values)
    print("{test_name}: lumping is correct")
        
###############################################

if __name__ == "__main__":
    # M4
    R = sympy.polys.rings.vring(["x" + str(i + 1) for i in range(4107)], QQ)
    subs_params = {
        "pEtot": "Rational(1, 1)",
        "pFtot": "Rational(1, 1)",
        "pStot": "Rational(1, 1)",
        "pkOnE": "Rational(1, 1)",
        "pkOffE": "Rational(1, 1)",
        "pkCatE": "Rational(1, 1)",
        "pkOnF": "Rational(1, 1)",
        "pkOffF": "Rational(1, 1)",
        "pkCatF": "Rational(1, 1)"
    }
    
    polys = utils.read_polys("long_system.poly", R, subs_params)
    
    lumping = lumper.do_lumping(polys, [x1], verbose = False)
    check_lumping("M4", polys, lumping, 12)
