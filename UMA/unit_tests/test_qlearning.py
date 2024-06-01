#Autor: Dominik Sidorczuk, Tomasz Sroka

from qlearning import QLearning_evolution
import numpy as np

f = lambda x: 0 # anything

def test_state_binning():
    agent = QLearning_evolution([0,1,2],[0,0.1,0.2],f)
    agent.bins_std=np.array([0,10,20,50,100])
    agent.bins_success_rate=np.array([0,0.2,0.8,1])

    dist_bin,rate_bin = agent.bin_state(12,0.5)
    assert dist_bin==1
    assert rate_bin==1

    dist_bin,rate_bin = agent.bin_state(12345,1)
    assert dist_bin==3
    assert rate_bin==2

# this test is needed because we decided on single Q-table,
# so it requires some clever mapping between bin indices and
# continuous NxM array
def test_action_index_mapping():
    