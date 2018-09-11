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

enum class SourceType { Graph, Tsp2DEuc};

enum class SolutionGenerationType { FrogLeaping, FixedFrogLeaping};

const int VEHICLE_CAPACITY = 7;

class FrogLeapController
{
	private:

		int successAttempts;
		int failAttempts;
		int localGeneratedSolutions;

		int totalImprovements;
		int localSearchImprovements;
		int globalImprovements;

		int minCostValue;

		time_t timeSeedUsed;

		DecodedFrogLeapSolution * ptrBestSolution;

		TspLibEuc2D * tspLibEud2DPtr;

		DistanceTable * distTablePtr;
		FloatDistanceTable * floatDistTablePtr;

		Graph * graphPtr;

		SourceType source_t;

		SolutionGenerationType sgt;

		FrogObjectCol * custormerList;

		FrogObjectCol * depotList;

		FrogObjectCol * vehiclePairList;

		Pair * * vehiclePairArray;

		Pair * * customerArray;

		Pair * * depotArray;

		short int origin;

		short int nVehiclesPerDepot;

	public:

		FrogLeapController();

		~FrogLeapController();

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
		
		int getNumberOfIterations();

		int getMinCostValue();

		void setMinCostValue(int cost);

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

		FloatDistanceTable * loadFloatDistanceTable();

		void setDistanceTable(DistanceTable * t);

		DistanceTable * getDistanceTable();

		void setFloatDistanceTable(FloatDistanceTable * t);

		FloatDistanceTable * getFloatDistanceTable();

		short int getNumberOfDepots();

		short int getNumberOfCustomers();

		void setGraph(Graph * gPtr);

		Graph * getGraph();

		void setSourceType(SourceType sourc);

		SourceType getSourceType();

		void setSolutionGenerationType(SolutionGenerationType v_sgt);

		SolutionGenerationType getSolutionGenerationType();

		void setAsCustomer(short int customerId, int demand);

		void setAsDepot(short int depotId, int capacity);

		short int getNumberOfDepots();
		
		void setUpCustomerList();

		void setUpDepotList();

		void setUpCustomerAndDepotLists();

		void setUpVehiclesPerDepot();

		void assignVehiclesToDepots(short int depotId, short int depotDemand);

		void setUpVehiclePairList();

		short int getNumberOfVehicles();

		short int getCustomerId(short int position);

		short int getNumberOfCustomers();

		int getCustomerDemandByIndex(short int position);

		short int getDepotId(short int position);

		int getDepotCapacityByIndex(short int position);

		int getDepotRemainingCapacityByIndex(short int position);

		void setDepotRemainingCapacityByIndex(short int position, int remaining_capacity);

		FrogLeapSolution * genRandomFrogLeapSolution();
};
#endif
