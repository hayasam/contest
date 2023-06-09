Subtask: Find the minimal maximum angriness given that the path length must be at most $K$
We simply do binary search on the angriness, and use dijstkra to determine whether it is possible to get a path length less than or equal to $K$. We do $NlogN$ dijsktra every iteration of binary search, so the complexity for this subtask is $Nlog^2(N)$

Solution for the Problem: 
The tricky part is that one edge can be deleted and we must look for the worst possible scenario. Assume for now that no edge is deleted; call the main path from node $1$ to node $N$ $m$. To get our desired answer, we wish to go through each edge on $m$ and compute the minimum path length that doesn't use that edge. We then take the maximum out of all of these lengths, and check if it is at most $K$.

Look at another edge $e$ not in $m$; note that the shortest path from $1$ to $N$ through $e$ will use a prefix and suffix of $m$. In other words there is an interval of edges in main path which the alternate path through $e$ does not use. The reason for this is because it is never optimal to diverge from $m$ and then come back unless it is to include $e$. Call this interval which the path through $e$ doesn't go through $m$ the "interval of divergence" or $IOD$, which can be found for each edge using a second dijsktras.

We must iterate through all the edges not on $m$, and get the $IOD$ for each edge along with the minimum path length to go through that edge from $1$ to $N$. To get the minimum length of a path not using an edge $f$ in path $m$, we must query for each edge $e$ not in $m$ which has an $IOD$ containing $f$ (i.e. the path through $e$ doesn't use edge $f$). Iterating through each edge and checking its $IOD$ is obviously too slow, so we use a segment tree or a set to store all this information. Each update will be a range and specify a minimum path length over that $IOD$. We will then have point queries, where we look at each interval and see if it includes the queried edge, and get the minimum of them. We do this with every edge on $m$.

Updating and checking the $IOD$ is $logN$ per edge and there are at most $M$ operations per binary search, the complexity is $Nlog^2(N) + Mlog^2(N)$.
