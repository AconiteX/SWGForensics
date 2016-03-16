/*
 * Template.cpp
 *
 *  Created on: 19-feb-2009
 *      Author: TheAnswer
 */

#include "Template.h"

#include "../../../../../system/iff/IffStream.h"


Template::Template(IffStream* str) : LuaWriter() {
	fileName = str->getFileName().c_str();

	objectCRC = getFileNameCRC();

	luaObjectName = str->getFileName().c_str();
	luaObjectName.remove(SWGTRESDIRECTORY);
	luaObjectName.replace(QString("/"), QString("_"));
	luaObjectName.replace(QString("-"), QString("_"));
	luaObjectName.remove(".iff");
}

Template::~Template() {

}
