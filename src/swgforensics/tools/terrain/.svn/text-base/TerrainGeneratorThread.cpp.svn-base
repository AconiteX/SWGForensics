/*
 * TerrainGeneratorThread.cpp
 *
 *  Created on: 05/04/2010
 *      Author: TheAnswer
 */

#include "terrainanalizer.h"
#include "TerrainGeneratorThread.h"
#include "AffectorHeightFractal.h"
#include "FilterFractal.h"
#include "simplexnoise1234.h"

#include <QTextStream>
#include <QBitmap>
#include "glwidget.h"

TerrainGeneratorThread::TerrainGeneratorThread(TerrainAnalizer* analizer) {
	this->analizer = analizer;

	ahfr = analizer->getAffectorHeightFractal();

	running = true;

	width = 512, height = 512;

	time = 1;

	pData = NULL;

	connectSignals();
}

void TerrainGeneratorThread::connectSignals() {
	//connect(this, SIGNAL(displayHeight(float)), (QObject*)analizer, SLOT(modifyDisplayHeight(float)));
	connect(this, SIGNAL(outputToConsole(QString)), (QObject*)analizer->getMainApp(), SLOT(printToConsole(QString)));
	connect(this, SIGNAL(printImage(unsigned int*, int, int)), analizer, SLOT(printImage(unsigned int*, int, int)));
	connect(this, SIGNAL(increaseProgress()), analizer, SLOT(increaseProgress()));
}

void TerrainGeneratorThread::generateImage(int width, int height, bool normalize) {
	//for (int i = 0; i < 30; ++i) {
		waitMutex.lock();

		this->width = width;
		this->height = height;
		this->normalize = normalize;

		waitCondition.wakeAll();

		waitMutex.unlock();
	//}
}

void TerrainGeneratorThread::stop() {
	running = false;

	waitMutex.lock();

	waitCondition.wakeAll();

	waitMutex.unlock();
}

float* TerrainGeneratorThread::generatePoints(float& min, float& max) {
	float* pDataFloat = new float[width * height];
	FilterFractal* ffra = analizer->getFilterFractal();

	float filter = 0;


	float seed = float(time += 5) / 100.f;

	//Generate raw float data
	for (unsigned int y = 0; y < height; ++y) {
		for (unsigned int x = 0; x < width; ++x) {
			float total = 0;

			/*total = ahfr->trySubNoise(x, y, 0, 0);

			filter = ffra->processFilter(x, y, 0, 0);*/

			total = ((SimplexNoise1234::noise(x / 100.f, y / 100.f, seed)) + 1.0) * 0.5;

			/*if (filter != 0 && filter != 1.f) {
				QString msg;
				QTextStream stream(&msg);
				stream << "abnormal filter for " << x << " " << y << " with res:" << filter;
				emit outputToConsole(msg);
			}*/

			pDataFloat[y * width + x] = total;

			min = total < min ? total : min;
			max = total > max ? total : max;

		}

		/*if (y % 2 == 0)
			emit increaseProgress();*/
	}

	return pDataFloat;
}

unsigned int* TerrainGeneratorThread::generateBitmapData(float* points) {
	for (unsigned int i = 0; i < width * height; ++i) {
		pData[i] = (255 << 24) | ((unsigned char) (2.0 * (points[i] + 1) * 127.5) << 16) | ((unsigned char) (1.0 * (points[i] + 1) * 127.5) << 8) |
							(unsigned char) (1.0 * (points[i] + 1) * 127.5);
	}

	return pData;
}

unsigned int* TerrainGeneratorThread::generateNormalizedData(float* points, float min, float max) {
	for (unsigned int i = 0; i < width * height; ++i) {
		pData[i] = (255 << 24) | ((unsigned char) (1 * ((points[i] - min) / (max - min)) * 255) << 16) |
				((unsigned char) (1 * ((points[i] - min) / (max - min)) * 255) << 8) | (unsigned char) (1 * ((points[i] - min) / (max - min)) * 255);
	}

	return pData;
}

void TerrainGeneratorThread::run() {
	emit outputToConsole("starting TerrainGeneratorThread thread");

	while (running) {
		waitMutex.lock();

		waitCondition.wait(&waitMutex);

		waitMutex.unlock();

		for (int i = 0; i < 300; ++i) {
			if (!running)
				break;

			float min, max;

			//emit increaseProgress();

			float* pDataFloat = generatePoints(min, max);

			if (pData != NULL)
				delete pData;

			pData = new unsigned int[width * height];

			if (normalize)
				pData = generateNormalizedData(pDataFloat, min, max);
			else
				pData = generateBitmapData(pDataFloat);

			//emit increaseProgress();

			delete pDataFloat;

			emit printImage(pData, width, height);

			wait(10);
		}



	}

	exec();
}
