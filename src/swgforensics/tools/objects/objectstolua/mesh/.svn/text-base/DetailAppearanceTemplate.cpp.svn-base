#include "DetailAppearanceTemplate.h"
#include "MeshAppearanceTemplate.h"
#include "ComponentAppearanceTemplate.h"

void DetailAppearanceTemplate::parse() {
        iffStream->openForm('DTLA');

        uint32 version = iffStream->getNextFormType();
        iffStream->openForm(version);


        iffStream->openForm('APPR');
        //ignoring this atm
        iffStream->closeForm('APPR');

        iffStream->openChunk('PIVT');
        iffStream->closeChunk('PIVT');

        Chunk* infoChunk = iffStream->openChunk('INFO');

/*                int totalINFOSize = infoChunk->getDataSize();

        for (int i = 0; i < totalINFOSize; i += 12) {
            int var1 = iffStream->getInt();
            float var2 = iffStream->getFloat();
            float var3 = iffStream->getFloat();
        }
*/
        iffStream->closeChunk('INFO');

        Chunk* dataChunk = iffStream->openForm('DATA');

        int subChunks = dataChunk->getChunksSize();

        for (int i = 0; i < subChunks; ++i) {
            iffStream->openChunk('CHLD');

            int var1 = iffStream->getInt();

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

            iffStream->closeChunk('CHLD');
        }

        iffStream->closeForm('DATA');

        iffStream->closeForm(version);
        iffStream->closeForm('DTLA');
}
