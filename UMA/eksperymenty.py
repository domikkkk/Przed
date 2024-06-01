#Autor: Dominik Sidorczuk, Tomasz Sroka

import sys
from time import time
import matplotlib.pyplot as plt
import numpy as np

try:
    sys.path.append('./')
    from cec2017.functions import *
except Exception:
    sys.path.append('../')
    from cec2017.functions import *
from qlearning import QLearning_evolution


def learn(functions_to_learn, actions_P, actions_M, p_size):
    np.random.seed(2)
    Q = QLearning_evolution(actions_P,
                            actions_M,
                            None,
                            alpha=0.01,
                            epsilon=0.9,
                            epsilon_min=0.2,
                            epsilon_decay=0.995,
                            gamma=0.6,
                            state_size=(5,5),
                            population_size=p_size)
    start = time()
    for f in functions_to_learn:
        Q.objective = f
        Q.fit(episodes=100, steps_per_episode=100)
    print("Done. Learnt in {}".format(round(time() - start, 2)))
    return Q


def test(Q: QLearning_evolution, f):
    Q.objective = f
    c = 0
    for s in range(50):
        # test results
        Q.reset(seed=s)
        # print(f"seed #{s} With Q learning:")
        Q.episode(learn=False,steps=25)
        with_q=Q._env.mean_and_deviation()[0]
        # manual steps without qlearning test
        Q.reset(seed=s)
        # print(f"seed #{s} just evolution:")
        for _ in range(25):
            Q._env.step()
            # print(Q._env.mean_and_deviation(), Q._env.population_size, Q._env.sigma)
        no_q=Q._env.mean_and_deviation()[0]

        c+=1 if with_q<no_q else 0
    print(f"Q learning helped in {c}/50 cases")
    Q.reset()
    return Q.episode(learn=False, steps=200)  # to get population_size and sigma


def find_extremum(Q: QLearning_evolution, f):
    Q.reset()
    Q.episode(steps=200, learn=False)
    population = Q._env.population
    best_p = min(population, key=lambda p: f(p.array))
    return f(best_p.array), best_p.array


def savefig(func_name, P, S):
    X = range(len(P))
    plt.title(func_name)
    plt.xlabel("Step")
    plt.ylabel("Population size")
    plt.plot(X, P)
    plt.savefig("./images/" + func_name + "_population_size.png")
    plt.close()
    plt.title(func_name)
    plt.plot(X, S)
    plt.ylabel("Sigma")
    plt.xlabel("Step")
    plt.savefig("./images/" + func_name + "_sigma.png")
    plt.close()


if __name__=="__main__":
    functions_to_learn = [f2, f4, f6, f8, f22]
    actions_P = [-3, -1, 0, 1, 3]
    actions_M = [-0.1, -0.05, 0, 0.05, 0.1]
    p_size = 30
    Q = learn(functions_to_learn, actions_P, actions_M, p_size)
    while True:
        try:
            func = input("Nazwa funkcji, np. f1: ")
            f = eval(func)
            P, S = test(Q, f)
            savefig(func, P, S)
        except Exception:
            pass
