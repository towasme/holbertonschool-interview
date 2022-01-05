#!/usr/bin/python3
"""Rotate a 2d matrix"""


def rotate_2d_matrix(matrix):
    """Rotate a 2d matrix"""
    size = len(matrix) - 1
    for y in range(len(matrix) // 2):
        for x in range(y, len(matrix) - 1 - y):
            temp = matrix[y][x]
            matrix[y][x] = matrix[size - x][y]
            matrix[size - x][y] = matrix[size - y][size - x]
            matrix[size - y][size - x] = matrix[x][size - y]
            matrix[x][size - y] = temp
