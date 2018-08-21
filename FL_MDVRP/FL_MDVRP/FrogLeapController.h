#ifndef FROGLEAPCONTROLLER_H_   /* Include guard */
#define FROGLEAPCONTROLLER_H_

class FrogLeapController
{
	private:

		int successAttempts;
		int failAttempts;

		time_t timeSeedUsed;

	public:

		FrogLeapController();

		~FrogLeapController();

		void setSuccessAttempts(int vsuccessAttempts);
		int getSuccessAttempts();
		void incSuccessAttempts();

		void setFailAttempts(int vfailAttempts);
		int getFailAttempts();
		void incFailAttempts();

		void setRandomSeed();

		void printCtrl();
};
#endif
