#ifndef FROGLEAPCONTROLLER_H_   /* Include guard */
#define FROGLEAPCONTROLLER_H_

class DecodedFrogLeapSolution;

class FrogLeapController
{
	private:

		int successAttempts;
		int failAttempts;

		int minCostValue;

		time_t timeSeedUsed;

		DecodedFrogLeapSolution * ptrBestSolution;

	public:

		FrogLeapController();

		~FrogLeapController();

		void setSuccessAttempts(int vsuccessAttempts);
		int getSuccessAttempts();
		void incSuccessAttempts();

		void setFailAttempts(int vfailAttempts);
		int getFailAttempts();
		void incFailAttempts();

		int getMinCostValue();

		void setMinCostValue(int cost);

		void setBestDecodedFrogLeapSolution(DecodedFrogLeapSolution * ptrSolution);

		DecodedFrogLeapSolution * getBestDecodedFrogLeapSolution();

		void setRandomSeed();

		void printCtrl();
};
#endif
