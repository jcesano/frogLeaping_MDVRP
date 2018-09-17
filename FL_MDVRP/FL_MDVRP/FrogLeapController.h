#ifndef FROGLEAPCONTROLLER_H_   /* Include guard */
#define FROGLEAPCONTROLLER_H_

class DecodedFrogLeapSolution;
class FrogObject;
class FrogObjectCol;
class TspLibEuc2D;
class DistanceTable;
class FloatDistanceTable;
class Graph;
class FrogLeapSolution;
class Pair;
class IndexList;

enum class SourceType { Graph, Tsp2DEuc};

enum class SolutionGenerationType { FrogLeaping, FixedFrogLeaping};

const int VEHICLE_CAPACITY = 500;
const long int TOPE_ITERATIONS = 100;

class FrogLeapController
{
	private:

		long int successAttempts;
		long int failAttempts;
		long int localGeneratedSolutions;

		long int totalImprovements;
		long int localSearchImprovements;
		long int globalImprovements;

		float minCostValue;

		time_t timeSeedUsed;

		DecodedFrogLeapSolution * ptrBestSolution;

		TspLibEuc2D * tspLibEud2DPtr;

		DistanceTable * distTablePtr;
		FloatDistanceTable * floatDistTablePtr;

		Graph * graphPtr;

		SourceType source_t;

		SolutionGenerationType sgt;

		FrogObjectCol * customerList;

		FrogObjectCol * depotList;

		FrogObjectCol * vehiclePairList;

		Pair * * vehiclePairArray;

		Pair * * customerArray;

		Pair * * depotArray;

		int origin;

		int nVehiclesPerDepot;

	public:

		FrogLeapController();

		~FrogLeapController();

		void deleteArray(Pair ** arrayPtr, int v_size);		

		void setSuccessAttempts(int vsuccessAttempts);
		int getSuccessAttempts();
		void incSuccessAttempts();

		void setFailAttempts(int vfailAttempts);
		int getFailAttempts();
		void incFailAttempts();

		int getTotalImprovements();
		void incTotalImprovements();

		int getLocalSearchImprovements();
		void incLocalSearchImprovements();

		int getGlobalSearchImprovements();
		void incGlobalSearchImprovements();

		int getLocalGeneratedSolutions();
		void incLocalGeneratedSolutions();
		
		long int getNumberOfIterations();

		float getMinCostValue();

		void setMinCostValue(float cost);

		void setBestDecodedFrogLeapSolution(DecodedFrogLeapSolution * ptrSolution);

		DecodedFrogLeapSolution * getBestDecodedFrogLeapSolution();

		void setRandomSeed();

		void applyLocalSearch();

		void printCtrl();

		void loadTSPEUC2D_Data(char * fileName);

		void readTSPSection(FILE * filePtr, char * ctrlSectionTag, char * ctrlSeparatorChar, int * off_set);

		void loadTSPSection(char * buf, char * sectionTag);

		void loadCoordinates(FILE * filePtr, TspLibEuc2D * tspLibEuc2DPtr);
		
		void loadDemand(FILE * filePtr, TspLibEuc2D * tspLibEuc2DPtr);

		void loadDepots(FILE * filePtr, TspLibEuc2D * tspLibEuc2DPtr);

		DistanceTable * loadDistanceTable();

		void setDistanceTable(DistanceTable * t);

		DistanceTable * getDistanceTable();

		void setFloatDistanceTable(FloatDistanceTable * t);

		FloatDistanceTable * getFloatDistanceTable();

		int getNumberOfDepots();

		int getNumberOfCustomers();

		void setGraph(Graph * gPtr);

		Graph * getGraph();

		void setSourceType(SourceType sourc);

		SourceType getSourceType();

		void setSolutionGenerationType(SolutionGenerationType v_sgt);

		SolutionGenerationType getSolutionGenerationType();

		void setAsCustomer(int customerId, int demand);

		void setAsDepot(int depotId, int capacity);
				
		void setUpCustomerList();

		void setUpDepotList();

		void setUpCustomerAndDepotLists();

		void setUpVehiclesPerDepot();

		void assignVehiclesToDepots(int depotId, int depotDemand);

		void setUpVehiclePairList();

		int getNumberOfVehicles();

		int getCustomerId(int position);
		
		int getCustomerDemandByIndex(int position);

		int getDepotId(int position);

		int getDepotCapacityByIndex(int position);

		int getDepotRemainingCapacityByIndex(int position);

		void decRemainingDepotCapacity(int position, int capacity_to_dec);

		void setDepotRemainingCapacityByIndex(int position, int remaining_capacity);

		FrogLeapSolution * genRandomFrogLeapSolution();

		long int getTope();

		void resetDepotRemainingCapacities();

		void loadCustomerAndDepotList();

		int getLabel(int internalId);
};
#endif
