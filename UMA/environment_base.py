#Autor: Dominik Sidorczuk, Tomasz Sroka

import abc

class Environment(abc.ABC):

    @abc.abstractclassmethod
    def step(self):
        # should run tournament and operators (depending on evolution alg type)
        pass
    
    @property
    @abc.abstractmethod
    def population_size(self):
        pass

    @property
    @abc.abstractmethod
    def sigma(self):
        pass

    @abc.abstractclassmethod
    def change_p_size(self,delta: float,percent: bool):
        # should support absolute delta and option to enable proportional change
        pass

    @abc.abstractclassmethod
    def change_sigma(self,delta: float,percent: bool):
        # should support absolute delta and option to enable proportional change
        pass