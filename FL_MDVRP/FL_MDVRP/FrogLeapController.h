#ifndef FROGLEAPCONTROLLER_H_   /* Include guard */
#define FROGLEAPCONTROLLER_H_

class DecodedFrogLeapSolution;
class FrogObject;
class TspLibEuc2D;
class DistanceTable;
class FloatDistanceTable;
class Graph;

enum class SourceType { Graph, Tsp2DEuc};

enum class SolutionGenerationType { FrogLeaping, FixedFrogLeaping};

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
		
		int getTope();

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
};
#endif
