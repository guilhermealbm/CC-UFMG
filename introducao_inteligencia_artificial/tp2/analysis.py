# analysis.py
# -----------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


######################
# ANALYSIS QUESTIONS #
######################

# Set the given parameters to obtain the specified policies through
# value iteration.

def passo3():
    answerDiscount = 0.9
    answerNoise = 0.0015
    return answerDiscount, answerNoise


def passo4a():
    answerDiscount = 0.1
    answerNoise = 0.000015
    answerLivingReward = 0.8
    return answerDiscount, answerNoise, answerLivingReward
    # If not possible, return 'NOT POSSIBLE'


def passo4b():
    answerDiscount = 0.1
    answerNoise = 0.001
    answerLivingReward = 0.8
    return answerDiscount, answerNoise, answerLivingReward
    # If not possible, return 'NOT POSSIBLE'


def passo4c():
    answerDiscount = 0.8
    answerNoise = 0.01
    answerLivingReward = 0.2
    return answerDiscount, answerNoise, answerLivingReward
    # If not possible, return 'NOT POSSIBLE'


def passo4d():
    answerDiscount = 0.8
    answerNoise = 0.2
    answerLivingReward = 0.2
    return answerDiscount, answerNoise, answerLivingReward
    # If not possible, return 'NOT POSSIBLE'


def passo4e():
    answerDiscount = 0.99
    answerNoise = 0.2
    answerLivingReward = 0.99
    return answerDiscount, answerNoise, answerLivingReward
    # If not possible, return 'NOT POSSIBLE'


def passo7():
    answerEpsilon = 0.9
    answerLearningRate = 0.01
    return 'NOT POSSIBLE'
    # If not possible, return 'NOT POSSIBLE'


if __name__ == '__main__':
    print 'Answers to analysis questions:'
    import analysis

    for q in [q for q in dir(analysis) if q.startswith('passo')]:
        response = getattr(analysis, q)()
        print '  Question %s:\t%s' % (q, str(response))
