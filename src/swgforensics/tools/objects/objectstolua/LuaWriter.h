/*
 * LuaWriter.h
 *
 *  Created on: 23-feb-2009
 *      Author: TheAnswer
 */

#ifndef LUAWRITER_H_
#define LUAWRITER_H_

#include <QTextStream>

class LuaWriter {

public:
	LuaWriter();
	virtual ~LuaWriter();

	static void writeLuaHeader(QTextStream& header);

	virtual void toLua(QTextStream& buffer) = 0;
	virtual void variablesToLua(QTextStream& buffer) = 0;

};

#endif /* LUAWRITER_H_ */
