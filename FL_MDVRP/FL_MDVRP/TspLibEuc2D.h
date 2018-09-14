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
		short int dimension;
		char * edge_weight_type;
		short int capacity;
		FrogObjectCol * nodeCoordSection;
		FrogObjectCol * demand_section;
		IndexList * depot_section;

	public:
		TspLibEuc2D();

		~TspLibEuc2D();

		void setName(char * v_name);
		char * getName();

		void setComment(char * v_comment);
		char *getComment();

		void setType(char * v_type);
		char * getType();

		void setDimension(short int v_dimension);
		short int getDimension();

		void setEdgeWeightType(char * v_EdgeWeightType);
		char * getEdgeWeightType();

		void setCapacity(short int v_capacity);
		short int getCapacity();

		void AddNodeCoordItem(Pair * v_pair_coord);

		void AddDemandItem(Pair * v_pair_demand);

		void AddDepotItem(short int depotId);	

		float getEucDistance(short int u, short int v);

		float calcEuc2D(Pair * origin, Pair * destination);

		short int getNumberOfDepots();

		short int getNumberOfCustomers();

		FrogObjectCol * getNodeCoordSection();

		FrogObjectCol * getDemandSection();
		IndexList * getDepotSection();

		// abstract methods
		void printFrogObj();

		bool isTheSame(FrogObject * fs);
};
#endif