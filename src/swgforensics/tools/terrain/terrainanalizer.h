#ifndef TERRAINANALIZER_H
#define TERRAINANALIZER_H

#include <QtGui/QWidget>
#include "ui_terrainanalizer.h"
#include "src/debugger/Breakpoint.h"
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class SWGForensics;
class DebuggerEngine;
class TerrainAnalizer;
class Mfrc;
class AffectorHeightFractal;
class HeightReader;
class TerrainGeneratorThread;
class GLWidget;
class FilterFractal;


class TerrainAnalizer : public QWidget, public BreakpointHandler {
    Q_OBJECT


signals:

    void outputToConsole(const QString& string);
    void enableAnalizer();


public:
    TerrainAnalizer(SWGForensics* mainWin, QWidget *parent = 0);
    ~TerrainAnalizer();

    void handleBreakpoint(Breakpoint* breakpoint);

    void* getAddressX() {
    	return addressX;
    }

    void* getAddressY() {
    	return addressY;
    }

    void* getAddressHeight() {
    	return addressHeight;
    }

    float getX() {
    	return x;
    }

    float getY() {
    	return y;
    }

    DebuggerEngine* getDebugger() {
    	return debugger;
    }

    SWGForensics* getMainApp() {
    	return mainApp;
    }

    AffectorHeightFractal* getAffectorHeightFractal() {
    	return ahfr;
    }

    FilterFractal* getFilterFractal() {
    	return filterFractal;
    }

public:
    QMutex positionMutex;
    QWaitCondition positionChanged;

public slots:
	void catchClientApeearance();
	void modifyX();
	void modifyY();
	void modifyDisplayHeight(float height);
	void injectCode();
	void enableAnalizerSlot();
	void handleSMAPBreakpoint(Breakpoint* breakpoint);
	void interceptSMAP();
	void startMfrc();
	void startAnalizeNoiseData();
	void handleNoiseBreakpoint(Breakpoint* breakpoint);
	void modifyI();
	void modifyJ();
	void modifyAfhrHeight();
	void modifyAfhrInt();
	void modifyBias();
	void modifyBiasValue();
	void modifyGain();
	void modifyGainValue();
	void modifyOctaves();
	void modifyOctavesParam();
	void modifyAmplitude();
	void modifyXFreq();
	void modifyYFreq();
	void modifyXOffset();
	void modifyZOffset();
	void modifyUnkownFilter1();
	void modifyUnkownFilter2();
	void modifyUnkownFilter3();
	void modifyUnkownFilter4();
	void modifyUnkownFilter5();
	void modifyCombinational();
	void catchAffectorHeightFractalAddy();
	void handleAffectorHeightFractalAddy(Breakpoint* breakpoint);
	void showImage();
	void toggle3DView(int val);

	void changeFilterFractalResult();

	void printImage(unsigned int* pData, int width, int height);
	void increaseProgress();

	//Mfrc
	void modifySeed();
	//void modifyBias();
	//void modifyBiasValue();

private:
    Ui::TerrainAnalizerClass ui;
    SWGForensics* mainApp;
    DebuggerEngine* debugger;
    HeightReader* reader;
    Mfrc* mfrc;
    AffectorHeightFractal* ahfr;
    TerrainGeneratorThread* terrainGenerator;
    QGraphicsScene scene;
    GLWidget* view;
    FilterFractal* filterFractal;

    int generatorProgress;


    int times;

    float x, y;

    int i, j;


    float lastX, lastY;
    int lastI, lastJ;



    void* addressX;
    void* addressY;
    void* addressHeight;

    DWORD clientAppearancePointer;
    DWORD affectorHeightFractalAddress;
};

class HeightReader : public QThread {
	Q_OBJECT

	TerrainAnalizer* analizer;
public:
	HeightReader(TerrainAnalizer* analizer) {
		this->analizer = analizer;

		connectSignals();
	}

	void run();
	void connectSignals();

signals:
	void outputToConsole(const QString& string);
	void displayHeight(float height);
};

#endif // TERRAINANALIZER_H
