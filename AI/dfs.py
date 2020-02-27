def dfs(arr, n, k, s):
	stack = []
	visited = []
	stack.append(k)
	while stack:
		e = stack.pop()
		visited.append(e)
		for adj in reversed(arr[e]):
			if adj not in visited and adj not in stack:
				stack.append(adj)
		print(str(e))
		if e == s:
			break

n = 4
k = 0
arr = [[1, 2], [0, 3], [0], [1]]
s = int(input("Search key: "))
dfs(arr, n, k, s)