/*
 * SharedCreatureObjectTemplate.h
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDCREATUREOBJECTTEMPLATE_H_
#define SHAREDCREATUREOBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class SharedCreatureObjectTemplate : public SharedTangibleObjectTemplate {
protected:
	IntegerParam gender;
	IntegerParam niche;
	IntegerParam species;
	IntegerParam race;

	VectorParam<FloatParam> acceleration;
	VectorParam<FloatParam> speed;
	VectorParam<FloatParam> turnRate;

	StringParam animationMapFilename;

	FloatParam slopeModAngle;
	FloatParam slopeModPercent;
	FloatParam waterModPercent;
	FloatParam stepHeight;
	FloatParam collisionHeight;
	FloatParam collisionRadius;

	StringParam movementDatatable;

	VectorParam<BoolParam> postureAlignToTerrain;

	FloatParam swimHeight;
	FloatParam warpTolerance;
	FloatParam collisionOffsetX;
	FloatParam collisionOffsetZ;
	FloatParam collisionLength;
	FloatParam cameraHeight;

public:
	SharedCreatureObjectTemplate(IffStream* str);
	~SharedCreatureObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};


#endif /* SHAREDCREATUREOBJECTTEMPLATE_H_ */
