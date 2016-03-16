/*
 * DetailAppearanceTemplate.h
 *
 *  Created on: 10/12/2010
 *      Author: TheAnswer
 */

#ifndef DETAILAPPEARANCETEMPLATE_H_
#define DETAILAPPEARANCETEMPLATE_H_

#include <QString>
#include "../../../../../system/iff/chunk/Chunk.h"
#include "../../../../swgforensics.h"
#include "../floormesh/FloorMesh.h"
#include "../objectstolua.h"
#include <QFile>

class DetailAppearanceTemplate {
public:
        IffStream* iffStream;

public:
        DetailAppearanceTemplate(const QString& file) {

                try {
                        iffStream = new IffStream(file.toStdString());
                } catch (...) {
                        iffStream = NULL;

                        SWGForensics::instance->printToConsole("unable to open file " + file);

                        return;
                }

                parse();

                SWGForensics::instance->printToConsole("parsed file " + file);

                /*QFile* qFile = new QFile(file);

                QString fileName = qFile->fileName();

                QString name = fileName.remove("D:/swg tres/");

                QString newName = "D:/filesforserver/" + name;

                if (!qFile->copy(newName)) {
                        SWGForensics::instance->printToConsole("unable to copy file " + newName);
                }

                delete qFile;*/


        }

        ~DetailAppearanceTemplate() {
                delete iffStream;
        }

        void parse();

};



#endif /* DETAILAPPEARANCETEMPLATE_H_ */
