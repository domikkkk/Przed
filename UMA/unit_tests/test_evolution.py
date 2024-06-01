#Autor: Dominik Sidorczuk, Tomasz Sroka

from evolution import EvolutionAlgorithm, Point 

f = lambda x: 0 # anything

def test_set_population_size():
    population = [Point([0,0]) for p in range(10)]
    ev = EvolutionAlgorithm(population,f)
    assert ev.population_size==10
    ev.change_p_size(-5)
    ev.step()
    assert ev.population_size==5

def test_set_mutation_size():
    population = [Point([0,0]) for p in range(10)]
    ev = EvolutionAlgorithm(population,f,sigma=0.5)
    assert ev.sigma==0.5
    ev.change_sigma(-0.3)
    assert ev.sigma==0.2
    ev.change_sigma(400,percent=True)
    assert ev.sigma==1

def test_replication():
    test = lambda x: x[0] 
    initial = [Point([0,0]) for p in range(10)]
    ev = EvolutionAlgorithm(initial,test, sigma=0.5)
    ev.tournament_selection=lambda points,_,__: points[0] #fake tournaments
    assert ev.population_size==10
    ev.tournament_for_all()
    for p in ev.population:
        assert p==initial[0]





