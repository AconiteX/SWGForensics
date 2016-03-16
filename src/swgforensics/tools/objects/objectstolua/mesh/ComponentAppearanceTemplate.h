#ifndef COMPONENTAPPEARANCETEMPLATE_H
#define COMPONENTAPPEARANCETEMPLATE_H

#include <QString>
#include "../../../../../system/iff/chunk/Chunk.h"
#include "../../../../swgforensics.h"
#include "../floormesh/FloorMesh.h"
#include "../objectstolua.h"
#include <QFile>
#include "MeshAppearanceTemplate.h"
#include "DetailAppearanceTemplate.h"


class ComponentAppearanceTemplate {
public:
        IffStream* iffStream;

public:
        ComponentAppearanceTemplate(const QString& file) {

                try {
                        iffStream = new IffStream(file.toStdString());
                } catch (...) {
                        iffStream = NULL;

                        SWGForensics::instance->printToConsole("unable to open file " + file);

                        return;
                }

                parse();

                SWGForensics::instance->printToConsole("parsed file " + file);

               /* QFile* qFile = new QFile(file);

                QString fileName = qFile->fileName();

                QString name = fileName.remove("D:/swg tres/");

                QString newName = "D:/filesforserver/" + name;

                if (!qFile->copy(newName)) {
                        SWGForensics::instance->printToConsole("unable to copy file " + newName);
                }

                delete qFile;*/


        }

        ~ComponentAppearanceTemplate() {
                delete iffStream;
        }

        void parse() {
                iffStream->openForm('CMPA');

                uint32 version = iffStream->getNextFormType();
                iffStream->openForm(version);


                iffStream->openForm('APPR');
                //ignoring this atm
                iffStream->closeForm('APPR');

                iffStream->openForm('RADR');
                iffStream->closeForm('RADR');

                int subChunks = iffStream->getRemainingSubChunksNumber();// dataChunk->getChunksSize();

                for (int i = 0; i < subChunks; ++i) {
                    iffStream->openChunk('PART');

                   // int var1 = iffStream->getInt();

                    /*QString str;
                    iffStream->getString(str);*/

                    QString meshFile;
                    iffStream->getString(meshFile);

                    /*MeshAppearanceTemplate* tmpl = new MeshAppearanceTemplate( "D:/swg tres/appearance/" + str);
                    delete tmpl,*/
                    QString trePath = "D:/swg tres/appearance/";

                    if (meshFile.contains(".msh")) {
                        MeshAppearanceTemplate* app = new MeshAppearanceTemplate(trePath + meshFile);
                        delete app;
                    } else if (meshFile.contains(".lod")){
                        DetailAppearanceTemplate* dtla = new DetailAppearanceTemplate(trePath + meshFile);
                        delete dtla;
                    } else if (meshFile.contains(".cmp")) {
                        ComponentAppearanceTemplate* dtla = new ComponentAppearanceTemplate(trePath + meshFile);
                        delete dtla;
                    } else {
                        SWGForensics::instance->printToConsole(QString("unknown file format ") + meshFile);
                    }

                    iffStream->closeChunk('PART');
                }

                iffStream->closeForm(version);
                iffStream->closeForm('CMPA');
        }

};


#endif // COMPONENTAPPEARANCETEMPLATE_H
