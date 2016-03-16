/*
 * TemplateBase.h
 *
 *  Created on: 22-feb-2009
 *      Author: TheAnswer
 */

#ifndef TEMPLATEBASE_H_
#define TEMPLATEBASE_H_

#include "../../../../../system/iff/chunk/Chunk.h"
#include "../../../../../system/iff/IffStream.h"

#include "Param.h"

#include <QTextStream>

template <class V> class TemplateBase : public Param {
protected:
	V value;
	//T unknown;

public:
	TemplateBase(const V& defaultValue) : Param() {
		create(defaultValue);
	}

	virtual ~TemplateBase() {

	}

	void create(const V& val) {
		value = val;
	}

	virtual int compareTo(const V& val) const {
		if (value < val)
			return 1;
		else if (value > val)
			return -1;
		else return 0;
	}

	/*TemplateBase& operator= (const V& val) {
		create(val);

		return *this;
	}*/

	/*V& operator= (const V& val) {
		create(val);

		return value;
	}*/

	virtual bool operator== (const V& val) const {
		return compareTo(val) == 0;
	}

	virtual bool operator< (const V& val) const {
		return compareTo(val) < 0;
	}

	virtual bool operator> (const V& val) const {
		return compareTo(val) > 0;
	}

	virtual bool operator!= (const V& val) const {
		return compareTo(val) != 0;
	}

	/*virtual V& operator+= (const V& val) {
		return value += val;
	}

	virtual V& operator-= (const V& val) {
		return value -= val;
	}*/

	virtual V getValue() {
		return value;
	}

	virtual V get() {
		return value;
	}

	virtual void setValue(const V& val/*, const T& unk*/) {
		value = val;
		//unknown = unk;
	}
};

#endif /* TEMPLATEBASE_H_ */
