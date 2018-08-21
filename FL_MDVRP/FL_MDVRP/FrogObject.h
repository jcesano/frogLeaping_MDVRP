#ifndef FROGOBJECT_H_   /* Include guard */
#define FROGOBJECT_H_

class FrogObject
{
private:
	float value;
	short int id;

public:

	FrogObject();

	~FrogObject();

	FrogObject(short int id_v);

	float getValue();

	void setValue(float valueV);

	short int getId();

	void setId(short int id_v);

	bool isTheSame(short int objid);

	virtual void printFrogObj() = 0;

	virtual bool isTheSame(FrogObject * fs) = 0;	
};

#endif