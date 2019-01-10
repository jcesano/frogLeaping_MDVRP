#ifndef TSPLIBEUC2D_H_   /* Include guard */
#define TSPLIBEUC2D_H_

#include "FrogObject.h"

class FrogObjectCol;
class IndexList;
class Pair;


class TspLibEuc2D : public FrogObject
{
	private:
		char * name;
		char * comment;
		char * type;
		int dimension;
		char * edge_weight_type;
		int capacity;
		FrogObjectCol * nodeCoordSection;
		FrogObjectCol * demand_section;
		IndexList * depot_section;

	public:
		TspLibEuc2D();

		virtual ~TspLibEuc2D();

		void setName(char * v_name);
		char * getName();

		void setComment(char * v_comment);
		char * getComment();

		void setType(char * v_type);
		char * getType();

		void setDimension(int v_dimension);
		int getDimension();

		void setEdgeWeightType(char * v_EdgeWeightType);
		char * getEdgeWeightType();

		void setCapacity(int v_capacity);
		int getCapacity();

		void AddNodeCoordItem(Pair * v_pair_coord);

		void AddDemandItem(Pair * v_pair_demand);

		void AddDepotItem(int depotId);	

		float getEucDistance(int u, int v);

		float calcEuc2D(Pair * origin, Pair * destination);

		int getNumberOfDepots();

		int getNumberOfCustomers();

		FrogObjectCol * getNodeCoordSection();

		FrogObjectCol * getDemandSection();
		IndexList * getDepotSection();

		double getAngularTheta(int customerInternalId, int depotInternalId);

		double getAngularRho(int customerInternalId, int depotInternalId);

		// abstract methods
		void printFrogObj();

		bool isTheSame(FrogObject * fs);
};
#endif