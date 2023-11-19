#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Node structure to represent a node and its distance
struct Node {
    string name;
    int distance;

    Node(string n, int d) : name(n), distance(d) {}

    // Operator overloading for priority_queue
    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};

// Dijkstra's Algorithm function
pair<int, vector<string>> dijkstra(const unordered_map<string, unordered_map<string, int>>& graph, const string& start, const string& end) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    unordered_map<string, int> distance;
    unordered_map<string, string> previous;

    // Initialize distances
    for (const auto& pair : graph) {
        distance[pair.first] = numeric_limits<int>::max();
    }
    distance[start] = 0;

    pq.push(Node(start, 0));

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.name == end) {
            // Reconstruct the path
            vector<string> path;
            string current_node = end;
            while (!previous[current_node].empty()) {
                path.insert(path.begin(), current_node);
                current_node = previous[current_node];
            }
            path.insert(path.begin(), start);

            return {distance[end], path};
        }

        for (const auto& neighbor : graph.at(current.name)) {
            int new_distance = distance[current.name] + neighbor.second;
            if (new_distance < distance[neighbor.first]) {
                distance[neighbor.first] = new_distance;
                previous[neighbor.first] = current.name;
                pq.push(Node(neighbor.first, new_distance));
            }
        }
    }

    // If no path is found
    return {numeric_limits<int>::max(), {}};
}

int main() {
    // Example graph represented as an unordered_map
    unordered_map<string, unordered_map<string, int>> exampleGraph = {
        {"A", {{"B", 10}, {"E", 3}}},
        {"B", {{"E", 4}, {"C", 2}}},
        {"C", {{"D", 9}}},
        {"D", {{"C", 7}}},
        {"E", {{"B", 1}, {"D", 2}, {"C", 8}}}
    };

    // Prompt the user for the starting and ending nodes
    string startNode, endNode;
    cout << "Enter the starting node: ";
    cin >> startNode;
    cout << "Enter the ending node: ";
    cin >> endNode;

    // Call Dijkstra's Algorithm
    auto result = dijkstra(exampleGraph, startNode, endNode);

    // Display the result
    if (result.first == numeric_limits<int>::max()) {
        cout << "There is no path from " << startNode << " to " << endNode << "." << endl;
    } else {
        cout << "The cost of the shortest path from " << startNode << " to " << endNode << " is " << result.first << "." << endl;
        cout << "The shortest path is: ";
        for (const auto& node : result.second) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}

