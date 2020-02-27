import heapq

def bestfs(graph, heuristic, start, goal):
	openlist = []
	visited = []
	heapq.heappush(openlist, (heuristic[start], start))
	visited.append(start)
	while openlist:
		e = heapq.heappop(openlist)[1]
		if e == goal:
			print(str(goal))
			print("Goal found.")
			break
		for node in graph[e]:
			if node not in visited:
				heapq.heappush(openlist, (heuristic[node], node))
				visited.append(node)		
		print(str(e))

start = 'a'
goal = 'g'
graph = {'a':['b', 'c', 'd', 'f'],
		 'b':['a', 'd', 'e'],
		 'c':['a', 'd', 'g'],
		 'd':['a', 'b', 'e', 'g'],
		 'e':['b', 'd', 'g'],
		 'f':['a', 'b'],
		 'g':['c', 'd', 'e']}
heuristic = {'a':18, 'b':8, 'c':12, 'd':10, 'e':5, 'f': 13, 'g':0}
bestfs(graph, heuristic, start, goal)