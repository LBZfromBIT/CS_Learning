# Thesis Report For  'A Polynomial Time Algorithm for Computing an Arrow-Debreu Market Equilibrium for Linear Utilities'

**Liu Bingzhi**

## 0.Abstract

 In this paper, the author presents the first polynomial time algorithm for calculating Arrow-Debreu market equilibrium under linear utility function. The algorithm is based on the use of the elliptic algorithm and the simultaneous Diophantine approximation method to solve a Convex programming.

 Incidentally, the author also gives other conclusions about equilibrium in this paper. The author proves that the distribution set is convex under equilibrium and the equilibrium price itself is logarithmically convex.

## 1.Explanations of the presupposition

- **Arrow-Debreu Market Equilibrium**
  
  Arrow-debreu market equilibrium is an economic theory developed in 1954 by Kenneth Arrow and Gérard Debreu to describe how goods and services balance supply and demand in a perfectly competitive market.
  
  Under this model, the market as a whole is called an economy, consisting of several consumers and several commodities. Every consumer has a certain initial object, that is, the number of goods they own. Each consumer can exchange goods according to his own preference and under his own budget constraints.
  
  The function that characterizes each consumer's preference for different combinations of goods -- types of goods and quantities -- is called the utility function. In this paper, we focus on the linear utility function, that is, consumer satisfaction is a linear function of the number of goods they own.
  
  Each consumer's consumption is limited, we call budget constraints. We require each consumer to spend no more than the total market value of their initial objects,which means for each customer $i$,we have $ \sum_{j} p_{j} x_{ij} \leq \sum_{j} p_{j} w_{ij}$ .Among them,$p_{j}$ is  the price of good $j$,$x_{ij}$ is the number of the good $j$ which is consume  by the customer $i$,and $w_{ij}$ is the number of the  good $j$ which is owned by customer $i$ initally.
  
  Arrow-debreu market equilibrium consists of a price vector $p$ and a commodity distribution vector $x$, which satisfy the following conditions:
  
  - 1.Consumer Optimization
    
    Each consumer chooses a consumption vector $x$ at a given price vector $p$ , maximizing their utility function $u_{i}(x_{i})$ while meeting their budget constraints.
    
  - 2.Market Clearing
    
    Market clearing require that supply equals demand for each commodity,which means for each good $j$,we have $\sum_{i} x_{ij} = \sum_{i} w_{ij}$.
    
- **Convex Programming**
  
  Convex programming is a special optimization problem in which the objective function is convex and all constraints (inequality and equality constraints) are defined on convex sets.Convex programming is very important in the solution of linear programming, because the objective function and constraints in linear programming are linear, so it is convex.
  
  These problems have some very good mathematical properties:
  
  - 1.**Global Optimality**: in convex programming, any local optimal solution is a global optimal solution.
    
  - 2.**Duality**: convex programming problems usually satisfy duality, that is, the optimal value of the primal problem and the dual problem are equal.
    
- **Ellipsoid Method**
  
  Elliptic algorithm is an iterative algorithm for solving convex optimization problems. It was proposed in 1979 by Leonid Khachiyan, a Soviet mathematician, and was the first algorithm to be shown to solve linear programming problems in polynomial time.
  
  The basic idea of the algorithm is to create a large ellipse that contains all possible solutions, and then start iterating. In each iteration, a smaller ellipse is generated based on the current solution and constraints, the Ellipse still contains all possible solutions. Finally, the optimal solution is approached by decreasing the size of the ellipse.
  
  At each iteration, the algorithm finds a probe point in the current ellipse and checks that the probe point satisfies the constraint. If the probe does not satisfy a constraint, a smaller ellipse is generated using the constraint. By repeating this step, the ellipse size can be reduced until it is small enough to obtain an approximate optimal solution.
  
- **Diophantine Approximation**
  
  The Diophantine approximation is a branch of number theory that deals with the approximation of real numbers by rational numbers. The goal is to find rational number approximation as close as possible to a given real number.
  
  Given a real number $\alpha$, we want to find the rational number $\frac{p}{q} $ so that the difference between $\alpha$ and $\frac{p}{q}$ is as small as possible.Formally defined as:
  
  $$
\left | \alpha - \frac{p}{q} \right | \leq \epsilon
  $$
  
  which $\epsilon$ is a very small positive.
  
## 2.**Model**

In this paper,the author defines the model as:

- Economy:
  
  There are $n$ individuals in the economic system, each with their own initial divisible goods. In order to simplify the numerical representation, we can scale down the size of each person's initial commodity proportionally under the linear utility function, so we assume that each person owns only one commodity, and each person owns only one unit of commodity.
  
  Each person has a linear utility function expressed as $\sum_{j}u_{ij}x_{ij}$,which $u_{ij}$ is the utility coefficient of person $i$ for good $j$ which also means the consumer's love of a commodity, and $x_{ij}$ is the quantity of good $j$ consumed by person $i$.
  
- Market Behavior:
  
  Each person earns an income from selling his or her own goods and uses that income to buy goods to maximize his or her utility. Eventually the market should reach market clearing.
  
- Market Equilibrium:
  
  According to Arrow-debreu's theorem, there is a price vector $p$ , which is not all zero, so that everyone can sell their goods at these prices and use the proceeds to buy an optimal portfolio of goods, to achieve a complete liquidation of the market.This vector is the equilibrium price vector we want. 
  
  And since the utility per person is linear and the quantity of the initial goods owned by the consumer in the market does not affect the equilibrium price vector, this combanition of price and economy constitutes a Arrow-Debreu market equilibrium.
  
To simplify the problem, the author also defines the following assumptions in the model:

- Suppose that everyone likes at least one commodity, that is,for each person $i$, there exists at least one commodity $j$ such that $u_{ij}>0$.
  
- Suppose that every commodity is liked by at least one person,that is,for each commodity $j$, there exists at least one person $i$ such that $u_{ij}>0$.
  
- Suppose consumption $x_{ij}$ is non-negative and each price $p_{j}$ is non-negative.
  
## 3.**Non-convex Programming and Convex Programming**

- ### Variable definition
  
  - $x_{ij}$:the quantity of the $j$ commodity representing the $i$ personal consumption
    
  - $p_{j}$:the price of the $j$ commodity
    
  - $u_{ij}$:the utility coefficient of person $i$ for good $j$
    
- ### Formal definition:
  
  $$
  max \qquad \sum_j u_{ij},\forall i \in [n] \\ subject \ \ to \quad \forall j : \sum_i x_{ij}=1
  $$
  
- ### Non-Convex Program
  
  The paper initially presents a non-convex program involving a set of inequality constraints. These constraints include logarithmic functions, which are inherently non-convex. The non-convex constraints are mainly represented as follows:
  
  $$
  \forall i, j \text{ such that } u_{ij} > 0 : \log(p_i) - \log(p_j) \leq \log\left(\frac{\sum_{k} u_{ik} x_{ik}}{u_{ij}}\right)
  $$
  
  To simplify the handling of non-convex constraints, a directed graph $G$ is constructed. The vertices represent different individuals, and the edges represent non-zero utility coefficient $u_{ij} > 0 $. For each edge $ij$, two weights are defined:

  $$
  w(ij) = \frac{\sum_{k} u_{ik} x_{ik}}{u_{ij}}, \quad \log w(ij) = \log\left(\frac{\sum_{k} u_{ik} x_{ik}}{u_{ij}}\right)
  $$
  
  Using Farkas' lemma, the non-convex programming problem is transformed into a negative cycle detection problem in the graph. If there are no negative cycles in the graph, the non-convex program is feasible.
  
- ### Non-linear Utility Functions
  
  The author further talk about the case of non-linear but concave utility functions. Assuming the utility function $u_i(x_i)$is concave and differentiable, for any consumption vectors $x_i$ and $y_i$, it satisfies:

   $$
   u_i(x_i) + u_i(y_i) \leq u_i\left(\frac{x_i + y_i}{2}\right)
   $$
  
  In this case, the non-convex program model still applies, and the feasible region described by non-convex program encompasses the general market equilibrium problem.
  
- ### Conversion to Convex Program
  
  To facilitate solving the problem, the non-convex program is converted into an equivalent convex program, leveraging the concavity of the logarithmic function. The transformed convex program constraint takes the following form:
  
  $$
  \forall j : \sum_{i} x_{ij} = 1, \quad \forall i, j : x_{ij} \geq 0
  $$
  
  And for all cases where $u_{ij} > 0$,we have:
  
  $$
  \log(p_i) - \log(p_j) \leq \log\left(\frac{\sum_{k} u_{ik} x_{ik}}{u_{ij}}\right)
  $$
  
  This leads to the derivation that, on a logarithmic scale, the set of all possible equilibrium prices is convex. Consequently, these equilibrium prices can be found by solving a convex optimization problem.All general market equilibria are feasible points for the above convex programming, and vice versa. Therefore, the ellipsoid method and the simultaneous Diophantine approximation method can be used to obtain the general market equilibrium.
  
- ### General Case
  
  In the model section, an assumption was made that for every proper subset $S$ of persons, there is an $i \notin S$ and $j \in S$ such that $u_{ij} > 0$. This assumption is not without loss of generality. In this section, it is shown that even without this assumption, there is an equilibrium consisting of only non-zero prices. Hence, the convex program remains valid and provides all such equilibria.
  
