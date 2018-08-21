#ifndef VERTEX_H_   /* Include guard */
#define VERTEX_H_

enum VertexType { SimpleNode, Customer, Depot };

class Vertex
{
	int distance;
	int marked;
	int id;		// index of vertex in graph. Is the id of the vertex.
	int prevIndex; // index of previous vertex in the shortest path from origin
	int prevPathIndex; // index of previous vertex in the marking vertex path

	VertexType v_type; // type of vertex: "simple node"; "Customer Node"; "Depot".

public:
	Vertex(); //Constructor
	~Vertex();
	int getDistance();
	void setDistance(int distanceV);
	void markVertex();
	void unmarkVertex();
	int isUnmarkedVertex();
	int getId();
	void setId(int v);
	int getPrevIndex();
	VertexType getVertexType();
	void setPrevIndex(int prevInd);
	int getPrevPathIndex();
	void setPrevPathIndex(int v);
	void setVertexType(VertexType v_Type_V);
};


#endif
