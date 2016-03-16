/*
 * TerrainGeneratorThread.h
 *
 *  Created on: 05/04/2010
 *      Author: TheAnswer
 */

#ifndef TERRAINGENERATORTHREAD_H_
#define TERRAINGENERATORTHREAD_H_

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class TerrainAnalizer;
class AffectorHeightFractal;

class TerrainGeneratorThread : public QThread {
	Q_OBJECT

	TerrainAnalizer* analizer;
	QMutex waitMutex;
	QWaitCondition waitCondition;

	AffectorHeightFractal* ahfr;

	int time;

	unsigned int* pData;
	int width, height;

	bool normalize;

	bool running;
public:
	TerrainGeneratorThread(TerrainAnalizer* analizer);

	void run();
	void connectSignals();

signals:
	void outputToConsole(const QString& string);
	void printImage(unsigned int* pData, int width, int height);
	void increaseProgress();
	//void remove

public slots:
	void generateImage(int width, int height, bool normalize);

	unsigned int* generateBitmapData(float* points);
	unsigned int* generateNormalizedData(float* points, float min, float max);

	void stop();

protected:
	float* generatePoints(float& min, float& max);
};


#endif /* TERRAINGENERATORTHREAD_H_ */
