#include "../header/Graph.h"
#include <cfloat>

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

    while (!q.empty()) {
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
    s->setVisited(true);
    preOrder.push_back(s);
    for (const std::shared_ptr<Edge>& e : s->getAdj()){
        if (e->isSelected()){
            std::shared_ptr<Vertex> v = e->getDest();
            pre_order(v, preOrder);
        }
    }
}

bool Graph::triangular_approximation(std::shared_ptr<Vertex>& s, const std::shared_ptr<Vertex>& d, std::vector<std::shared_ptr<Edge>>& path) const {
    s->setVisited(true);
    std::vector<std::shared_ptr<Vertex>> mst = prim(s);
    if (mst.size() != vertexSet.size()){ /// The graph is not connected, so there is no hamiltonian
        return false;
    }
    mst.clear();
    pre_order(s, mst); /// Using the mst, store the vertex in pre order

    for (size_t i = 0; i < mst.size() - 1; i++) {
        std::shared_ptr<Edge> e = mst[i]->findEdge(mst[i + 1]);
        if (e == nullptr){ /// Edge does not exist, we must create one
            if (mst[i]->getCoordinates().getLat() == DBL_MAX) return false; /// There is no coordinates to calculate the distance

            double distance = haversine(mst[i]->getCoordinates(), mst[i+1]->getCoordinates());
            mst[i]->addEdge(mst[i], mst[i+1], distance);
            mst[i+1]->addEdge(mst[i+1], mst[i], distance);
            e = mst[i]->findEdge(mst[i+1]);
        }
        path.push_back(e);
    }
    std::shared_ptr<Edge> last_edge = mst.back()->findEdge(s);
    if (last_edge == nullptr){ /// Edge does not exist, we must create one
        if (mst.back()->getCoordinates().getLat() == DBL_MAX) return false; /// There is no coordinates to calculate the distance
        double distance = haversine(s->getCoordinates(), mst.back()->getCoordinates());
        mst.back()->addEdge(mst.back(), s, distance);
        s->addEdge(s, mst.back(), distance);
        last_edge = mst.back()->findEdge(s);
    }
    last_edge->setSelected(true);
    path.push_back(last_edge);

    return true;
}


