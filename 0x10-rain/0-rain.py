#!/usr/bin/python3

"""
Module rain
"""


def rain(walls):
    """
    Given a list of non-negative integers representing walls of width 1,
    calculate how much water will be retained after it rains.
    walls is a list of non-negative integers. Return: Integer indicating total amount of rainwater retained.
    """

    water = 0
    length = len(walls)

    for i in range(1, length - 1):
        right = walls[i]
        for j in range(i + 1, length):
            right = max(right, walls[j])

        left = walls[i]
        for j in range(i):
            left = max(left, walls[j])

        water = water + (min(left, right) - walls[i])
    return water
