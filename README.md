#Solving Traveling Salesman Problem Using Ant Colony Optimization
##Proposal

####Group V

###Team leader
ZHANG Pei

###Member
LIANG Xubin,
WANG Ziqiao,
ZHANG Pei,
ZHU Wenyue

##Describe
Describe
The travelling salesman problem (TSP) asks the following question: "[Given a list of cities and the distances between each pair of cities, what is the shortest possible route that visits each city and returns to the origin city?](https://en.wikipedia.org/wiki/Travelling_salesman_problem)" There are many questions in real world can be transformed to the TSP question, such as distribution problem and search route problem. If we can solve the TSP problem cost-effectively, we can use this method in many field in real life. In this project, supposing that there are many delivery points in a city and what we want to do is finding a shortest route that visits each point and returns to the origin point.

##Methodology
The travelling salesman problem is a NP difficult problem in combinatorial optimization, which is very important in operational research and theoretical computer science.
Ant colony algorithm is a probabilistic algorithm used to find optimal paths in the graph, which imitates and abstracts the ant behavior. The basic principle of the shortest path from the principle of ant colony algorithm in ants, ants looking for food source, in its path on the release of a unique element information -- ant secretions, making other ants within a certain range can perceive and thus affect their behavior. When more and more ants through some paths on the left, the pheromone is also more and more, so that the pheromone intensity increases, so choose the ant selection probability filter is also higher, so the path pheromone intensity increases, the selection process is called self catalytic behavior of ants. Because its principle is a positive feedback mechanism, the ant kingdom can also be understood as the so-called enhanced learning system. The ants randomly start from a certain city and select the next city according to the distance between the cities and the concentration of residual pheromone. After the ants have finished all the cities, they leave a pheromone on the path they have traveled. The less total distance the ants takes, the more pheromones are left. After many cycles, we can get the best route.

##Demo
We will use different mazes as the original maze. In demo we will write a program using Python that can perfectly solve the problem. In the demo, we consider the maze map as the input and the best way as the result.

We used the network of traveling salesmen as a maze before, but this may be a special case. We will implement demos based on actual conditions.
