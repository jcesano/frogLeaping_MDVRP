#ifndef FROGOBJECT_H_   /* Include guard */
#define FROGOBJECT_H_

class FrogObject
{
private:
	float value;
	float value2;
	int id;

public:

	FrogObject();

	virtual ~FrogObject();

	FrogObject(int id_v);

	float getValue();

	float getValue2();

	void setValue(float valueV);

	void setValue2(float valueV);

	int getId();

	void setId(int id_v);

	bool isTheSame(int objid);

	virtual void printFrogObj() = 0;

	virtual bool isTheSame(FrogObject * fs) = 0;	
};

#endif