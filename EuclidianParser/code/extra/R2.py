from collections import namedtuple
from itertools import combinations
from math import sqrt

IxPoint = namedtuple('IxPoint', ['x', 'y', 'i'])
ClosestPair = namedtuple('ClosestPair', ['distance', 'i', 'j'])

def check_distance(cp, p1, p2):
    xd = p1.x - p2.x
    yd = p1.y - p2.y
    dist = sqrt(xd * xd + yd * yd)
    if dist < cp.distance:
        return ClosestPair(dist, p1.i, p2.i)
    return cp

def closest_helper(cp, xs, ys):
    n = len(xs)
    if n <= 3:
        for p1, p2 in combinations(xs, 2):
            cp = check_distance(cp, p1, p2)
        return cp

    # Divide
    mid = n // 2
    mid_x = xs[mid].x
    xs_left = xs[:mid]
    xs_right = xs[mid:]
    ys_left = [p for p in ys if p.x < mid_x]
    ys_right = [p for p in ys if p.x >= mid_x]

    # Conquer
    cp_left = closest_helper(cp, xs_left, ys_left)
    cp_right = closest_helper(cp, xs_right, ys_right)
    if cp_left.distance < cp_right.distance:
        cp = cp_left
    else:
        cp = cp_right

    ys_strip = [p for p in ys if abs(p.x - mid_x) < cp.distance]
    n_strip = len(ys_strip)
    for i in range(n_strip):
        for j in range(i + 1, n_strip):
            p1, p2 = ys_strip[j], ys_strip[i]
            if not p1.y - p2.y < cp.distance:
                break
            cp = check_distance(cp, p1, p2)
    return cp

def closest_pair(points):
    points = [IxPoint(p[0], p[1], i)
              for (i, p) in enumerate(points)]
    xs = sorted(points, key = lambda p: p.x)
    xs = [IxPoint(p.x + i * 1e-8, p.y, p.i)
          for (i, p) in enumerate(xs)]
    ys = sorted(xs, key = lambda p: p.y)
    cp = ClosestPair(float('inf'), -1, -1)
    return closest_helper(cp, xs, ys)
   
   
   
def main():
 ##read from file here to get points