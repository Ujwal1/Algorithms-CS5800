class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.adj = [[0] * vertices for _ in range(vertices)]
        self.height = [0] * vertices
        self.excess_flow = [0] * vertices

    def add_edge(self, u, v, w):
        self.adj[u][v] = w

    def preflow(self, source, height, excess_flow):
        for i in range(self.V):
            height[i] = 0
            excess_flow[i] = 0

        height[source] = self.V
        excess_flow[source] = float("inf")

        for v, w in enumerate(self.adj[source]):
            if w > 0:
                excess_flow[v] = w
                self.adj[source][v] = 0
                self.adj[v][source] = w

    def overflow_vertex(self, excess_flow):
        for i in range(1, len(excess_flow) - 1):
            if excess_flow[i] > 0:
                return i
        return -1

#     def push(self, u, v, height, excess_flow):
#         flow = min(excess_flow[u], self.adj[u][v])

#         excess_flow[u] -= flow
#         excess_flow[v] += flow

#         self.adj[u][v] -= flow
#         self.adj[v][u] += flow
        
    def push(self, u, v, height, excess_flow):
        residual_capacity = self.adj[u][v]
        flow = min(excess_flow[u], residual_capacity)

        print(f"Before the push:")
        print(f"  Source vertex {u}: e({u}) = {excess_flow[u]}, h({u}) = {height[u]}")
        print(f"  Destination vertex {v}: e({v}) = {excess_flow[v]}, h({v}) = {height[v]}")
        print(f"  Residual capacity of the edge: {residual_capacity}")
        print(f"  Actual flow pushed: {flow}")

        excess_flow[u] -= flow
        excess_flow[v] += flow

        self.adj[u][v] -= flow
        self.adj[v][u] += flow

        print(f"After the push:")
        print(f"  Source vertex {u}: e({u}) = {excess_flow[u]}, h({u}) = {height[u]}")
        print(f"  Destination vertex {v}: e({v}) = {excess_flow[v]}, h({v}) = {height[v]}")
        print(f"  Residual capacity of the edge: {self.adj[u][v]}\n")
        

#     def relabel(self, u, height):
#         min_height = float("inf")
#         for v, w in enumerate(self.adj[u]):
#             if w > 0:
#                 min_height = min(min_height, height[v])


#         height[u] = min_height + 1
        
    def relabel(self, u):
        min_height = float("inf")

        print(f"Before relabel:")
        print(f"  Vertex to be relabeled {u}: e({u}) = {self.excess_flow[u]}, h({u}) = {self.height[u]}")
        print(f"  Neighbors:")

        for v, w in enumerate(self.adj[u]):
            if w > 0:
                min_height = min(min_height, self.height[v])
                print(f"    Neighbor {v}: h({v}) = {self.height[v]}")

        self.height[u] = min_height + 1
        print(f"  New height of vertex {u}: {self.height[u]}")

        print("Residual network after relabel:")
        self.print_residual_network()
        input("Press enter to continue")

    def max_flow(self, source, sink):
        self.preflow(source, self.height, self.excess_flow)

        while self.overflow_vertex(self.excess_flow) != -1:
            u = self.overflow_vertex(self.excess_flow)

            pushed = False
            for v, w in enumerate(self.adj[u]):
                if w > 0 and self.height[u] == self.height[v] + 1:
                    self.push(u, v, self.height, self.excess_flow)
                    pushed = True

            if not pushed:
                self.relabel(u)  # Update this line

        return self.excess_flow[sink]

        return excess_flow[sink]

    # def print_residual_network(self):
    #     print("Residual network:")
    #     for row in self.adj:
    #         print(row)

    def print_residual_network(self):
        for u, row in enumerate(self.adj):
            print(f"Vertex {u}:")
            print(f"  Excess flow: {self.excess_flow[u]}")
            print(f"  Height: {self.height[u]}")
            print("  Residual edges:")
            for v, residual_capacity in enumerate(row):
                if residual_capacity > 0:
                    print(f"    -> Vertex {v}: Residual capacity {residual_capacity}")
        print()

def create_flow_network_from_file(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
        
        # Find the maximum vertex number to determine the number of vertices in the graph
        max_vertex = max([int(x.split()[0]) for x in lines] + [int(x.split()[1]) for x in lines])
        
        # Initialize a graph with the appropriate number of vertices
        g = Graph(max_vertex + 1)
        
        # Add edges to the graph based on the lines from the input file
        for line in lines:
            source, dest, weight = map(int, line.strip().split())
            g.add_edge(source, dest, weight)

    return g


if __name__ == "__main__":
    file_path = "test.txt"  # Replace this with the path to your input file
    g = create_flow_network_from_file(file_path)

    source = 0
    sink = 2

    max_flow = g.max_flow(source, sink)
    print("The maximum flow is", max_flow)

    g.print_residual_network()