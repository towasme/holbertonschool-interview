#!/usr/bin/python3
"""
Module for 0-making_change
"""


def makeChange(coins, total):
    """
    Given a pile of coins of different values, determine the fewest number
    of coins needed to meet a given amount `total`.
    """
    if total <= 0:
        return 0

    fewest = 0
    sorted_coins = sorted(coins, reverse=True)
    sorted_index = 0

    while(total > 0 and sorted_index < len(coins)):
        if total >= sorted_coins[sorted_index]:
            fewest = fewest + 1
            total = total - sorted_coins[sorted_index]
        else:
            sorted_index = sorted_index + 1

    if total != 0:
        return -1

    return fewest
