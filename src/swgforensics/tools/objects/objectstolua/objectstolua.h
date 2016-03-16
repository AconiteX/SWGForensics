#ifndef OBJECTSTOLUA_H
#define OBJECTSTOLUA_H

#include <QtGui/QWidget>
#include <QtGui/QMainWindow>
#include <QMap>
#include <QFileDialog>
#include "ui_objectstolua.h"

//#include "typetreeview.h"

class IffStream;
class SWGForensics;
class Template;
class SharedObjectTemplate;
class SharedTangibleObjectTemplate;
class SharedWeaponObjectTemplate;
class SharedIntangibleObjectTemplate;
class SharedUniverseObjectTemplate;
class SharedStaticObjectTemplate;
class SharedCellObjectTemplate;

class SharedCreatureObjectTemplate;
class SharedShipObjectTemplate;
class SharedResourceContainerObjectTemplate;
class SharedInstallationObjectTemplate;
class SharedFactoryObjectTemplate;
class SharedBuildingObjectTemplate;
class SharedBattlefieldMarkerObjectTemplate;

class SharedDraftSchematicObjectTemplate;
class SharedManufactureSchematicObjectTemplate;
class SharedWaypointObjectTemplate;
class SharedPlayerObjectTemplate;
class SharedMissionObjectTemplate;
class SharedConstructionContractObjectTemplate;
class SharedMissionDataObjectTemplate;
class SharedMissionListEntryObjectTemplate;
class SharedTokenObjectTemplate;

class SharedGuildObjectTemplate;
class SharedGroupObjectTemplate;
class SharedCountingObjectTemplate;

class SharedJediManagerTemplate;

#define SWGTRESDIRECTORY "D:/swg tres/"

class ObjectsToLua : public QWidget
{
    Q_OBJECT

public:
    ObjectsToLua(SWGForensics* mainWin, QWidget *parent = 0);
    ~ObjectsToLua();

private:
    Ui::ObjectsToLuaClass ui;

    //TypeTreeView typeView;
    //IffStream* fileStream;
    SWGForensics* mainWindow;
    Template* openedTemplate;
    unsigned int numberOfFilesOpened;
    //QFile* currentLuaFile;
    int maxRows;
    int currentRow;


    QMap<unsigned int, QStringList*> objectTypes;
    QMap<unsigned int, QStringList*> containerTypes;

    QVector<QString> inheritance;
    QVector<QString> objectLuas;
    QString currentInheritance;

    void connectSignals();
    Template* loadObjectVariables(IffStream* iffStream, Template* previousTemplate);
    void loadDerv(IffStream* stream, Template* previousTemplate);

    SharedObjectTemplate* parseSHOT(IffStream* iffStream, Template* previousTemplate);
    SharedTangibleObjectTemplate* parseSTOT(IffStream* iffStream, Template* previousTemplate);
    SharedWeaponObjectTemplate* parseSWOT(IffStream* iffStream, Template* previousTemplate);
    SharedIntangibleObjectTemplate* parseSITN(IffStream* iffStream, Template* previousTemplate);
    SharedUniverseObjectTemplate* parseSUNI(IffStream* iffStream, Template* previousTemplate);
    SharedStaticObjectTemplate* parseSTAT(IffStream* iffStream, Template* previousTemplate);
    SharedCellObjectTemplate* parseCCLT(IffStream* iffStream, Template* previousTemplate);
    SharedCreatureObjectTemplate* parseSCOT(IffStream* iffStream, Template* previousTemplate);
    SharedShipObjectTemplate* parseSSHP(IffStream* iffStream, Template* previousTemplate);
    SharedResourceContainerObjectTemplate* parseRCCT(IffStream* iffStream, Template* previousTemplate);
    SharedInstallationObjectTemplate* parseSIOT(IffStream* iffStream, Template* previousTemplate);
    SharedFactoryObjectTemplate* parseSFOT(IffStream* iffStream, Template* previousTemplate);
    SharedBuildingObjectTemplate* parseSBOT(IffStream* iffStream, Template* previousTemplate);
    SharedBattlefieldMarkerObjectTemplate* parseSBMK(IffStream* iffStream, Template* previousTemplate);
    SharedDraftSchematicObjectTemplate* parseSDSC(IffStream* iffStream, Template* previousTemplate);
    SharedManufactureSchematicObjectTemplate* parseSMSC(IffStream* iffStream, Template* previousTemplate);
    SharedWaypointObjectTemplate* parseSWAY(IffStream* iffStream, Template* previousTemplate);
    SharedPlayerObjectTemplate* parseSPLY(IffStream* iffStream, Template* previousTemplate);
    SharedMissionObjectTemplate* parseSMSO(IffStream* iffStream, Template* previousTemplate);
    SharedConstructionContractObjectTemplate* parseSCNC(IffStream* iffStream, Template* previousTemplate);
    SharedGuildObjectTemplate* parseSGLD(IffStream* iffStream, Template* previousTemplate);
    SharedGroupObjectTemplate* parseSGRP(IffStream* iffStream, Template* previousTemplate);
    SharedCountingObjectTemplate* parseSCOU(IffStream* iffStream, Template* previousTemplate);
    SharedJediManagerTemplate* parseSJED(IffStream* iffStream, Template* previousTemplate);
    SharedMissionDataObjectTemplate* parseSMSD(IffStream* iffStream, Template* previousTemplate);
    SharedMissionListEntryObjectTemplate* parseSMLE(IffStream* iffStream, Template* previousTemplate);
    SharedTokenObjectTemplate* parseSTOK(IffStream* iffStream, Template* previousTemplate);

    SharedObjectTemplate* parseUnknownType(IffStream* iffStream, Template* previousTemplate, unsigned int type);


public slots:
	bool openObjectIffTemplate();
	bool openObjectIffTemplateDir(QDir dir);
	bool openDir();
	bool convertToLuaDir();

	void openFloorMesh();

	void selectedVariable(QListWidgetItem* item);

};

#endif // OBJECTSTOLUA_H
