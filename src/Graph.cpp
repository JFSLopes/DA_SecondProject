#include "../header/Graph.h"
#include <cfloat>
#include <stack>
#include <unordered_set>

const std::vector<std::shared_ptr<Vertex>>& Graph::getVertexSet() const {
    return vertexSet;
}

void Graph::addVertex(const std::shared_ptr<Vertex>& vertex) {
    vertexSet.push_back(vertex);
}

std::shared_ptr<Vertex> Graph::findVertex(uint32_t code) const {
    for (const std::shared_ptr<Vertex>& ptr : vertexSet){
        if (ptr->getCode() == code) return ptr;
    }
    return nullptr;
}
#include <iostream>
std::vector<std::shared_ptr<Vertex>> Graph::prim(const std::shared_ptr<Vertex>& s) const {
    std::vector<std::shared_ptr<Vertex>> ans;
    /// Init the values
    for (const std::shared_ptr<Vertex>& v: vertexSet){
        v->setDist(DBL_MAX);
        v->setVisited(false);
        v->setPath(nullptr);
        for (const std::shared_ptr<Edge>& e : v->getAdj()){
            e->setSelected(false);
        }
    }

    MutablePriorityQueue<Vertex> q;
    Vertex* start = s.get();
    start->setDist(0);
    q.insert(start);
    uint32_t count = 0;
    while (!q.empty()) {
        std::cout << count++ << "\n";
        /// The vertex on the top is always relaxed, that is why we can add it to the answer.
        Vertex* minVertex = q.extractMin();
        minVertex->setVisited(true);
        ans.push_back(findVertex(minVertex->getCode()));

        for (const std::shared_ptr<Edge>& edge : minVertex->getAdj()){
            Vertex* dest = edge->getDest().get();
            /// If it was already visited (means added to the mst) we don't do anything else
            if (dest->isVisited()) continue;
            /// If it was not yet processed, we just change its dist and add it to the queue
            else if (dest->getDist() == DBL_MAX){
                edge->setSelected(true);
                dest->setPath(edge);
                dest->setDist(edge->getWeight());
                q.insert(dest);
            }
            /// If it was already added to the queue, but we found a better path, we update it.
            else if (edge->getWeight() < dest->getDist()){
                edge->setSelected(true); /// Used to create the traversal tree
                dest->getPath()->setSelected(false);
                dest->setPath(edge);
                dest->setDist(edge->getWeight());
                q.decreaseKey(dest);
            }
        }
    }
    return ans;
}

void Graph::pre_order(std::shared_ptr<Vertex>& s, std::vector<std::shared_ptr<Vertex>>& preOrder) const {
    std::stack<std::shared_ptr<Vertex>> stack;
    stack.push(s);

    while (!stack.empty()) {
        std::shared_ptr<Vertex> current = stack.top();
        preOrder.push_back(current);
        stack.pop();

        // Push adjacent vertices to the stack in reverse order
        for (const std::shared_ptr<Edge>& e : current->getAdj()) {
            if (e->isSelected()) {
                std::shared_ptr<Vertex> v = e->getDest();
                stack.push(v);
            }
        }
    }
}

bool Graph::triangular_approximation(std::shared_ptr<Vertex>& s, std::vector<std::shared_ptr<Edge>>& path) const {
    std::vector<std::shared_ptr<Vertex>> mst = prim(s);
    if (mst.size() != vertexSet.size()){ /// The graph is not connected, so there is no hamiltonian
        return false;
    }
    mst.clear();
    pre_order(s, mst); /// Using the mst, store the vertex in pre order

    for (size_t i = 0; i < mst.size() - 1; i++) {
        std::shared_ptr<Edge> e = mst[i]->findEdge(mst[i + 1]);
        path.push_back(e);
    }
    std::shared_ptr<Edge> last_edge = mst.back()->findEdge(s);
    path.push_back(last_edge);
    return true;
}

#include <iostream>
void Graph::fully_connected(uint64_t& num_edges) {
    std::unordered_map<uint32_t, std::shared_ptr<Vertex>> all;
    for (const std::shared_ptr<Vertex>& v : vertexSet) all.insert(std::make_pair(v->getCode(), v));
    uint32_t count = 0;
    for (const std::shared_ptr<Vertex>& v : vertexSet){
        std::unordered_map<uint32_t, std::shared_ptr<Vertex>> temp;
        for (const std::shared_ptr<Edge>& e : v->getAdj()){
            temp.insert(std::make_pair(e->getDest()->getCode(), e->getDest()));
        }
        for (const std::pair<uint32_t, std::shared_ptr<Vertex>>& pair : all){
            if (pair.second->getCode() == v->getCode()) continue;
            auto itr = temp.find(pair.first);
            if (itr == temp.end()){
                double dist = haversine(v->getCoordinates(), pair.second->getCoordinates());
                pair.second->addEdge(pair.second, v, dist);
                v->addEdge(v, pair.second, dist);
                num_edges += 2;
                if (count == 1000000){
                    std::cout << num_edges << "\n";
                    count = 0;
                }
                count++;
            }
        }
    }
}

void Graph::set_in_out_degree() {
    for (const std::shared_ptr<Vertex>& v: vertexSet){
        v->setVisited(false);
        v->setIn(0);
        v->setOut(0);
    }

    for (const std::shared_ptr<Vertex>& v: vertexSet){
        for (const std::shared_ptr<Edge>& e : v->getAdj()){
            if (e->isSelected()){
                e->getOrig()->setOut(e->getOrig()->getOut() + 1);
                e->getDest()->setIn(e->getDest()->getIn() + 1);
            }
        }
    }
}

bool Graph::Christofides(const std::shared_ptr<Vertex>& s, std::vector<std::shared_ptr<Edge>>& hamiltonian) {
    std::vector<std::shared_ptr<Vertex>> mst = prim(s);
    if (mst.size() != vertexSet.size()){ /// The graph is not connected, so there is no hamiltonian
        return false;
    }
    set_in_out_degree();
    findMinimumWeightPerfectMatching();

    std::vector<std::shared_ptr<Vertex>> path;
    formEulerianCircuit(path);

    std::unordered_set<std::shared_ptr<Vertex>> set;
    std::vector<std::shared_ptr<Vertex>> final_path;
    for (const std::shared_ptr<Vertex>& v : path){
        if (set.find(v) == set.end()){
            final_path.push_back(v);
            set.insert(v);
        }
    }

    for (uint32_t k = 0; k < final_path.size() - 1; k++){
        std::shared_ptr<Edge> e = final_path[k]->findEdge(final_path[k+1]);
        hamiltonian.push_back(e);
    }
    std::shared_ptr<Edge> last_edge = final_path.back()->findEdge(s);
    hamiltonian.push_back(last_edge);
    return true;
}

void Graph::findMinimumWeightPerfectMatching() {
    std::vector<std::shared_ptr<Edge>> all_edges;
    /// Select the vertices with odd degree
    for (const std::shared_ptr<Vertex>& v: vertexSet){
        if ((v->getIn() + v->getOut()) % 2 != 0){
            for (const std::shared_ptr<Edge>& e : v->getAdj()){
                all_edges.push_back(e);
            }
        }
    }

    std::sort(all_edges.begin(), all_edges.end(), [] (const std::shared_ptr<Edge>& e1, const std::shared_ptr<Edge>& e2) {return e1->getWeight() < e2->getWeight();});

    for (const std::shared_ptr<Edge>& e : all_edges) {
        /// If the vertex is not matched, find augmenting path
        if (!e->getDest()->isVisited() and !e->getOrig()->isVisited()) {
            e->getDest()->setVisited(true);
            e->getOrig()->setVisited(true);
            e->setSelected(true);
        }
    }
}

void Graph::formEulerianCircuit(std::vector<std::shared_ptr<Vertex>>& visitedVertices) {
    std::stack<std::shared_ptr<Vertex>> stack;

    std::shared_ptr<Vertex> startVertex = findVertex(0);

    stack.push(startVertex);

    while (!stack.empty()) {
        auto currentVertex = stack.top();
        // Check if there are unexplored edges from the current vertex
        bool unexploredEdgeFound = false;
        for (const auto& edge : currentVertex->getAdj()) {
            if (edge->isSelected()) {
                // Mark the edge as explored
                edge->setSelected(false);
                // Move to the next vertex
                stack.push(edge->getDest());
                unexploredEdgeFound = true;
                break;
            }
        }
        // If no unexplored edges are found, backtrack
        if (!unexploredEdgeFound) {
            // Add current vertex to the visited vertices vector
            visitedVertices.push_back(currentVertex);
            stack.pop();
        }
    }
    std::reverse(visitedVertices.begin(), visitedVertices.end());
}

bool Graph::nearest_neighbour(const std::shared_ptr<Vertex> &s, std::vector<std::shared_ptr<Edge>> &hamiltonian) {
    for (const std::shared_ptr<Vertex>& v : vertexSet) v->setVisited(false);

    std::shared_ptr<Vertex> curr = s;
    curr->setVisited(true);
    while (true){
        std::vector<std::shared_ptr<Edge>> edges = curr->getAdj();
        std::sort(edges.begin(), edges.end(), [](const std::shared_ptr<Edge>& e1, const std::shared_ptr<Edge>& e2) {return e1->getWeight() < e2->getWeight();});
        bool found = false;
        for (const std::shared_ptr<Edge>& e : edges){
            if (!e->getDest()->isVisited()){
                hamiltonian.push_back(e);
                e->getDest()->setVisited(true);
                curr = e->getDest();
                found = true;
                break;
            }
        }
        if (!found) break;
    }
    if (!hamiltonian.empty()){
        std::shared_ptr<Edge> last_edge = hamiltonian.back()->getDest()->findEdge(s);
        hamiltonian.push_back(last_edge);
    }
    return hamiltonian.size() == vertexSet.size();
}
