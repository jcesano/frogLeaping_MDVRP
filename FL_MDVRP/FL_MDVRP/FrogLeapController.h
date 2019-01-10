#ifndef FROGLEAPCONTROLLER_H_   /* Include guard */
#define FROGLEAPCONTROLLER_H_

class DecodedFrogLeapSolution;
class FrogObject;
class FrogObjectCol;
class TspLibEuc2D;
class TestCaseObj;
class DistanceTable;
class FloatDistanceTable;
class Graph;
class FrogLeapSolution;
class Pair;
class IndexList;

enum class SourceType { Graph, Tsp2DEuc};

enum class SolutionGenerationType { FrogLeaping, FixedFrogLeaping};

const int VEHICLE_CAPACITY = 500;
const long int TOPE_ITERATIONS = 10000;


class FrogLeapController
{
	private:

		long int successAttempts;
		long int failAttempts;
		long int localGeneratedSolutions;

		long int totalImprovements;
		long int localSearchImprovements;
		long int globalImprovements;
		long int vehicle_capacity;

		long long int globalVehicleId;

		float minCostValue;

		time_t timeSeedUsed;

		DecodedFrogLeapSolution * ptrBestSolution;

		TspLibEuc2D * tspLibEud2DPtr;

		TestCaseObj * testCaseObjPtr;

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

		FILE * pFile;
		
		char * outPutFileName;		

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

		DecodedFrogLeapSolution * loadTestCaseData(char * fileName);

		void readTSPSection(FILE * filePtr, char * ctrlSectionTag, char * ctrlSeparatorChar, int * off_set);

		void loadTSPSection(char * buf, char * sectionTag);

		void loadAssignations(FILE * filePtr, TestCaseObj * testCaseObjPtr);

		DecodedFrogLeapSolution * loadAssignations2(FILE * filePtr, TestCaseObj * testCaseObjPtr);

		FrogLeapSolution * loadAssignations3(FILE * filePtr, TestCaseObj * testCaseObjPtr);

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

		Pair * getDepotPairByIndex(int position);

		Pair * getCustomerPairByIndex(int position);

		Pair * getPairByInternalId(int position);

		void setAngularValues(Pair * veh_customerPair, int customerInternalId, int depotInternalId);		

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

		void setUpVehicleCapacity();

		long int getVehicleCapacity();

		void setUpVehiclesPerDepot();

		void assignVehiclesToDepots(int depotId, int depotDemand);

		void setUpVehiclePairList();

		int getNumberOfVehicles();

		int getCustomerInternalId(int position);
		
		int getCustomerDemandByIndex(int position);

		int getDepotInternalId(int position);

		int getDepotCapacityByIndex(int position);

		int getDepotRemainingCapacityByIndex(int position);

		void decRemainingDepotCapacity(int position, int capacity_to_dec);

		void setDepotRemainingCapacityByIndex(int position, int remaining_capacity);

		FrogLeapSolution * genRandomFrogLeapSolution(FrogLeapController * controller);

		void resetCapacityOrDemand(Pair * depotPair);

		long int getTope();

		FrogObjectCol * createDepotListOrderedByCapacity();

		FrogObjectCol * createCustomerListOrderedByDemand();

		void resetDepotRemainingCapacities();

		void resetCustomerRemainingDemands();

		void loadCustomerAndDepotList();

		int getLabel(int internalId);

		int getDepotListIndexByInternal(int depotInternalId);

		int getCustomerListIndexByInternal(int customerInternalId);

		int getDepotIndexByLabelId(int depotLabelId);

		int getCustomerIndexByLabelId(int depotLabelId);

		FrogObjectCol * getTestCustomerSectionList();

		long long int getGlobalVehicleId();		

		int getCloserIndexToDepot(int depotIndex, int lowBoundIndex, int topBoundIndex, FrogObjectCol * localDepotCol);

		int getClosestLocalDepotIndexToCustomer(int customerIndex, int lowBoundIndex, int topBoundIndex, FrogObjectCol * localDepotCol, float & distance);

		int getClosestCustomerLocalIndexToDepot(int depotIndex, int lowBoundIndex, int topBoundIndex, FrogObjectCol * localNodeCol);

		int getClosestCustomerLocalIndexToCustomer(int customerIndex, int lowBoundIndex, int topBoundIndex, FrogObjectCol * localCustomerIndexesCol);

		bool existInLocalDepotList(int assignedDepotIndex, FrogObjectCol * localDepotCol, int low, int top);

		int getClosestDepotIndexOfAssignedCustomers(int customerIndex, FrogObjectCol * localDepotCol, int low, int top, float & distanceToCustomer);

		void setCustomerPairAsAssigned(int customerIndex, int depotIndex);

		void resetCustomersAsNotAssigned();

		float genRandomFloatingNumber(float a, float b);

		// functions for writing information in an output file
		void openOutPutFile();

		void closeOutPutFile();
		void writeSeed();
		void writeFrogLeapSolution(FrogLeapSolution * fls);
		void writeIterationInfo(long long int i, float currentValue);
		void writeRandomInfo(float a, float b, float finalRandom);
		void writeExecutionInfo();
};
#endif
