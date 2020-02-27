def bfs(arr, n, k, s):
	queue = []
	visited = []
	queue.append(k)
	while queue:
		e = queue.pop(0)
		visited.append(e)
		for adj in arr[e]:
			if adj not in visited and adj not in queue:
				queue.append(adj)
		print(str(e))
		if e == s:
			break

n = 4
k = 0
arr = [[1, 2], [0, 3], [0], [1]]
s = int(input("Search key: "))
bfs(arr, n, k, s)