#ifndef FROGLEAPSOLUTION_H_   /* Include guard */
#define FROGLEAPSOLUTION_H_

//=================================
// included dependencies
#include "FrogObject.h"

class FeasibleSolution;
class DecodedFrogLeapSolution;
class Graph;
class FrogLeapController;
class FrogObjectCol;
class FrogObject;
class Pair;
enum class SolutionGenerationType;
enum class SourceType;

class FrogLeapSolution: public FrogObject
{
	private:
	
		float * values;
		int size;			// number of customers

		int n_depots;		// number of depots
		int nElementsToSort;
		//time_t timeSeedUsed;
		SolutionGenerationType sgt;
		SourceType st;		

		FeasibleSolution * customerSelectionList;

	public:
	
		FrogLeapSolution(SolutionGenerationType v_sgt, SourceType v_sourceType, int ncustomers, int n_depots_v, int id);

		~FrogLeapSolution();

		float getFLValue(int i);

		void setFLValue(int i, float v_float);

		void setSize(int size_v);

		int getSize();

		bool genRandomSolution(FrogLeapController * controller);

		bool genRandomSolution2(FrogLeapController * controller);

		bool genRandomSolution3(FrogLeapController * controller);

		bool genRandomSolution4(FrogLeapController * controller);

		bool genSolution5(FrogLeapController * controller);

		bool genRandomSolutionFromTestCase(FrogLeapController * controller);

		float normalRandomAssigment(FrogLeapController * controller);

		float assignRandomFeasibleDepot(FrogObjectCol * feasibleDepotList, FrogLeapController * controller, int customerIndex);

		float assignRandomFeasibleDepot2(FrogLeapController * controller, int customerIndex);

		float assignRandomFeasibleDepot3(FrogLeapController * controller, FrogObjectCol * localDepotCol, int customerIndex);		

		float assignRandomFeasibleDepot4(FrogLeapController * controller, FrogObjectCol * localDepotCol, int customerIndex);

		FrogObjectCol * initializeFeasibleDepotList(FrogLeapController * controller);

		DecodedFrogLeapSolution * decodeSolution(FrogLeapController * g);				

		DecodedFrogLeapSolution * decodeFrogLeapSolution(FrogLeapController * controller, bool adjustVehicleRoutes = false);

		DecodedFrogLeapSolution * FrogLeapSolution::decodeSolutionWithAngularCriteria(FrogLeapController * controller);

		DecodedFrogLeapSolution * FrogLeapSolution::decodeFrogLeapSolutionWithAngularCriteria(FrogLeapController * controller, bool adjustVehicleRoutes);
		
		void setSolutionGenerationType(SolutionGenerationType v_sgt);

		SolutionGenerationType getSolutionGenerationType();

		void initCustomerSelection(FrogLeapController * controller);

		void destroyRandomCustomerSelectionList();

		int selectRandomCustomerIndex(int i, FrogLeapController * controller);
		
		// abstract methods
		void printFrogObj();

		bool isTheSame(FrogObject * fs);
};

#endif
