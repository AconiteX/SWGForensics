#include "terrainanalizer.h"
#include "src/debugger/DebuggerEngine.h"
#include "src/swgforensics/swgforensics.h"

#include "InjectedCode.h"
#include "Mfrc.h"
#include "BoundaryRectangle.h"
#include "BoundaryPolygon.h"
#include "BoundaryPolyline.h"
#include "AffectorHeightFractal.h"
#include "TerrainGeneratorThread.h"

#include <QTextStream>
#include <QBitmap>

#include "glwidget.h"
#include "FilterFractal.h"


TerrainAnalizer::TerrainAnalizer(SWGForensics* mainWin, QWidget *parent)
    : QWidget(parent) {
	ui.setupUi(this);

	mainApp = mainWin;
	debugger = mainWin->getDebuggerEngine();
	reader = new HeightReader(this);

	mfrc = NULL;
	ahfr = NULL;
	filterFractal = NULL;

	startMfrc();

        BoundaryRectangle* brec = new BoundaryRectangle();
        float res = brec->process(-58.8, 68.6);
        float res2 = brec->process2(-58.8, 68.6);
        float res3 = brec->process2(-33.3, 42.0);
        float res4 = brec->process2(-36.1, 54.3);

        mainWin->printToConsole("brec process::" + QString::number(res) + " "+ QString::number(res2) + " "
                                + QString::number(res3) + " " + QString::number(res4) + " ");

        BoundaryPolygon* bpol = new BoundaryPolygon();
        float res5 = bpol->process(0, -64);
        float res6 = bpol->process(-64, 0);
        float res7 = bpol->process2(-64, 0);

        mainWin->printToConsole("bpol process::" + QString::number(res6) + " "+ QString::number(res7));
	x = 0;
	y = 0;

	i = 0, j = 0;

	lastX = 0, lastY = 0;
	lastI = 0, lastJ = 0;

	times = 0;

	terrainGenerator = new TerrainGeneratorThread(this);

	ui.graphicsView->setScene(&scene);

	ui.graphicsView->show();

	ui.progressBar->reset();

	terrainGenerator->start();

	connect(this, SIGNAL(outputToConsole(QString)), (QObject*)mainWin, SLOT(printToConsole(QString)));
	//connect(this, SIGNAL(enableAnalizer()), this, SLOT(enableAnalizerSlot()));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(injectCode()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(catchClientApeearance()));
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(interceptSMAP()));
	connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(startMfrc()));
	connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(startAnalizeNoiseData()));
	connect(ui.pushButton_6, SIGNAL(clicked()), this, SLOT(catchAffectorHeightFractalAddy()));
	connect(ui.pushButton_7, SIGNAL(clicked()), this, SLOT(showImage()));
	connect(ui.doubleSpinBox_posx, SIGNAL(valueChanged(double)), this, SLOT(modifyX()));
	connect(ui.doubleSpinBox_posy, SIGNAL(valueChanged(double)), this, SLOT(modifyY()));
	connect(ui.plainTextEdit_3, SIGNAL(textChanged()), this, SLOT(modifyI()));
	connect(ui.plainTextEdit_4, SIGNAL(textChanged()), this, SLOT(modifyJ()));
	connect(ui.spinBox_seed, SIGNAL(valueChanged(int)), this, SLOT(modifySeed()));
	connect(ui.doubleSpinBox_ahfr_height, SIGNAL(valueChanged(double)), this, SLOT(modifyAfhrHeight()));
	connect(ui.spinBox_afhrunk1, SIGNAL(valueChanged(int)), this, SLOT(modifyAfhrInt()));
	connect(ui.spinBox_bias, SIGNAL(valueChanged(int)), this, SLOT(modifyBias()));
	connect(ui.doubleSpinBox_bias_value, SIGNAL(valueChanged(double)), this, SLOT(modifyBiasValue()));
	connect(ui.spinBox_gain, SIGNAL(valueChanged(int)), this, SLOT(modifyGain()));
	connect(ui.doubleSpinBox_gain_value, SIGNAL(valueChanged(double)), this, SLOT(modifyGainValue()));
	connect(ui.spinBox_octaves, SIGNAL(valueChanged(int)), this, SLOT(modifyOctaves()));
	connect(ui.doubleSpinBox_octaves_value, SIGNAL(valueChanged(double)), this, SLOT(modifyOctavesParam()));
	connect(ui.doubleSpinBox_amplitud, SIGNAL(valueChanged(double)), this, SLOT(modifyAmplitude()));
	connect(ui.doubleSpinBox_xfreq, SIGNAL(valueChanged(double)), this, SLOT(modifyXFreq()));
	connect(ui.doubleSpinBox_yfreq, SIGNAL(valueChanged(double)), this, SLOT(modifyYFreq()));
	connect(ui.doubleSpinBox_xoffset, SIGNAL(valueChanged(double)), this, SLOT(modifyXOffset()));
	connect(ui.doubleSpinBox_zoffset, SIGNAL(valueChanged(double)), this, SLOT(modifyZOffset()));
	connect(ui.spinBox_combination, SIGNAL(valueChanged(int)), this, SLOT(modifyCombinational()));
	connect(ui.checkBox_3dview, SIGNAL(stateChanged(int)), this, SLOT(toggle3DView(int)));
	connect(ui.spinBox_var1, SIGNAL(valueChanged(int)), this, SLOT(modifyUnkownFilter1()));
	connect(ui.doubleSpinBox_var2, SIGNAL(valueChanged(double)), this, SLOT(modifyUnkownFilter2()));
	connect(ui.doubleSpinBox_var3, SIGNAL(valueChanged(double)), this, SLOT(modifyUnkownFilter3()));
	connect(ui.doubleSpinBox_var4, SIGNAL(valueChanged(double)), this, SLOT(modifyUnkownFilter4()));
	connect(ui.doubleSpinBox_var5, SIGNAL(valueChanged(double)), this, SLOT(modifyUnkownFilter5()));



	//connect()

	view = new GLWidget(this, 0);
	view->resize(800, 600);
	//view->show();

}

TerrainAnalizer::~TerrainAnalizer() {

}

void TerrainAnalizer::changeFilterFractalResult() {
	QString crcText;

	float result = filterFractal->processFilter(x, y, 0, 0);
	QTextStream stream(&crcText);
	stream << "ffra is " << result;

	ui.label_ffra_res->setText(crcText);
}

void TerrainAnalizer::modifyUnkownFilter1() {
	int value = ui.spinBox_var1->value();

	filterFractal->setVar2(value);

	changeFilterFractalResult();

}

void TerrainAnalizer::modifyUnkownFilter2() {
	float val = ui.doubleSpinBox_var2->value();

	filterFractal->setVar3(val);

	changeFilterFractalResult();
}

void TerrainAnalizer::modifyUnkownFilter3() {
	float val = ui.doubleSpinBox_var3->value();

	filterFractal->setVar4(val);

	changeFilterFractalResult();
}

void TerrainAnalizer::modifyUnkownFilter4() {
	float val = ui.doubleSpinBox_var4->value();

	filterFractal->setVar5(val);

	changeFilterFractalResult();
}

void TerrainAnalizer::modifyUnkownFilter5() {
	float val = ui.doubleSpinBox_var5->value();

	filterFractal->setVar6(val);

	changeFilterFractalResult();
}

void TerrainAnalizer::toggle3DView(int val) {
	if (val == Qt::Checked)
		view->show();
	else if (val == Qt::Unchecked)
		view->hide();
}

void TerrainAnalizer::modifyCombinational() {
	int yf = ui.spinBox_combination->value();

	mfrc->setCombination(yf);

	modifyDisplayHeight(ahfr->trySubNoise(x, y, i, j));
}

void TerrainAnalizer::modifyZOffset() {
	float yf = ui.doubleSpinBox_zoffset->value();

	mfrc->setZOffset(yf);

	modifyDisplayHeight(ahfr->trySubNoise(x, y, i, j));
}

void TerrainAnalizer::modifyXOffset() {
	float yf = ui.doubleSpinBox_xoffset->value();

	mfrc->setXOffset(yf);

	modifyDisplayHeight(ahfr->trySubNoise(x, y, i, j));
}

void TerrainAnalizer::modifyYFreq() {
	float yf = ui.doubleSpinBox_yfreq->value();

	mfrc->setYFreq(yf);

	modifyDisplayHeight(ahfr->trySubNoise(x, y, i, j));
}

void TerrainAnalizer::modifyXFreq() {
	float xf = ui.doubleSpinBox_xfreq->value();

	mfrc->setXFreq(xf);

	modifyDisplayHeight(ahfr->trySubNoise(x, y, i, j));
}

void TerrainAnalizer::modifyAmplitude() {
	float ampl = ui.doubleSpinBox_amplitud->value();

	mfrc->setAmplitud(ampl);

	modifyDisplayHeight(ahfr->trySubNoise(x, y, i, j));
}

void TerrainAnalizer::modifyOctavesParam() {
	float octaves = ui.doubleSpinBox_octaves_value->value();

	mfrc->setOctavesParam(octaves);

	modifyDisplayHeight(ahfr->trySubNoise(x, y, i, j));
}

void TerrainAnalizer::modifyOctaves() {
	int gainType = ui.spinBox_octaves->value();

	mfrc->setOctaves(gainType);

	modifyDisplayHeight(ahfr->trySubNoise(x, y, i, j));
}

void TerrainAnalizer::modifyGainValue() {
	float gainValue = ui.doubleSpinBox_gain_value->value();

	mfrc->setGainValue(gainValue);

	modifyDisplayHeight(ahfr->trySubNoise(x, y, i, j));
}

void TerrainAnalizer::modifyGain() {
	int gainType = ui.spinBox_gain->value();

	mfrc->setGainType(gainType);

	modifyDisplayHeight(ahfr->trySubNoise(x, y, i, j));
}

void TerrainAnalizer::modifyBiasValue() {
	float bias = ui.doubleSpinBox_bias_value->value();

	mfrc->setBiasValue(bias);

	modifyDisplayHeight(ahfr->trySubNoise(x, y, i, j));
}


void TerrainAnalizer::modifyBias() {
	int bias = ui.spinBox_bias->value();

	mfrc->setBias(bias);

	modifyDisplayHeight(ahfr->trySubNoise(x, y, i, j));
}

void TerrainAnalizer::modifySeed() {
	//QString text = ui.plainTextEdit_seed->spinBox_seed();

	int seed = ui.spinBox_seed->value();

	mfrc->setSeed(seed);

	modifyDisplayHeight(ahfr->trySubNoise(x, y, i, j));
}

void TerrainAnalizer::modifyAfhrInt() {
	int unkn = ui.spinBox_afhrunk1->value();

	//int unkn = text.toInt();

	ahfr->setUnknownValue(unkn);

	modifyDisplayHeight(ahfr->trySubNoise(x, y, i, j));
}

void TerrainAnalizer::printImage(unsigned int* pData, int width, int height) {
	scene.clear();

	QImage image((uchar *) pData, width, height, QImage::Format_RGB32);
	QPixmap  pixmap = QPixmap::fromImage(image);
	//if (bitmap->loadFromData((const uchar*) pData, width * height * sizeof(int), NULL, QImage::Format_RGB32)) {

	scene.addPixmap(pixmap);

	ui.pushButton_7->setEnabled(true);
}

void TerrainAnalizer::increaseProgress() {
	ui.progressBar->setValue(++generatorProgress);
}

void TerrainAnalizer::showImage() {
	startMfrc();

	scene.clear();

	ui.progressBar->reset();

	ui.pushButton_7->setEnabled(false);

	generatorProgress = 0;

	int width = 512;
	int height = 512;

	ui.progressBar->setMinimum(0);

	ui.progressBar->setMaximum((height / 2) + 2);

	bool normalized = ui.normalize_checkBox->isChecked();
	terrainGenerator->generateImage(width, height, normalized);

	if (view->isEnabled())
		view->recalculateTerrain();
}

void TerrainAnalizer::startMfrc() {
	if (mfrc != NULL)
		return;

	mfrc = new Mfrc();
	ahfr = new AffectorHeightFractal(mfrc);
	filterFractal = new FilterFractal(mfrc);
}

void TerrainAnalizer::interceptSMAP() {
	bool res = debugger->addBreakpoint(0x00B9AC94, this);

	if (!res)
		emit outputToConsole("could not add breakpoint");
	else
		emit outputToConsole("added breakpoint");
}

void TerrainAnalizer::modifyDisplayHeight(float height) {
	changeFilterFractalResult();

	QString crcText;

	QTextStream stream(&crcText);
	stream << "height is " << height;

	ui.label_3->setText(crcText);
}

void TerrainAnalizer::modifyAfhrHeight() {
	float i = ui.doubleSpinBox_ahfr_height->value();

	ahfr->setHeight(i);

	modifyDisplayHeight(ahfr->trySubNoise(x, y, i, j));
}
void TerrainAnalizer::modifyI() {
	positionMutex.lock();

	QString text = ui.plainTextEdit_3->toPlainText();

	i = text.toInt();

	//positionChanged.wakeAll();

	if (ahfr != NULL)
		modifyDisplayHeight(ahfr->trySubNoise(x, y, i, j));

	positionMutex.unlock();
}

void TerrainAnalizer::modifyJ() {
	positionMutex.lock();

	QString text = ui.plainTextEdit_4->toPlainText();

	j = text.toInt();

	//positionChanged.wakeAll();
	if (ahfr != NULL)
		modifyDisplayHeight(ahfr->trySubNoise(x, y, i, j));

	positionMutex.unlock();
}

void TerrainAnalizer::modifyX() {
	positionMutex.lock();

	x = ui.doubleSpinBox_posx->value();


	//positionChanged.wakeAll();
	if (ahfr != NULL)
		modifyDisplayHeight(ahfr->trySubNoise(x, y, i, j));

	positionMutex.unlock();
}

void TerrainAnalizer::modifyY() {
	positionMutex.lock();

	y = ui.doubleSpinBox_posy->value();


	//positionChanged.wakeAll();

	if (ahfr != NULL)
		modifyDisplayHeight(ahfr->trySubNoise(x, y, i, j));

	positionMutex.unlock();
}

void TerrainAnalizer::startAnalizeNoiseData() {
	bool res = debugger->addBreakpoint(0x013E7C1B, this);
	//bool res2 = debugger->addBreakpoint(0x00B768EE, this);

	if (!res)
		emit outputToConsole("could not add breakpoint");
	else
		emit outputToConsole("added breakpoint");


}

void TerrainAnalizer::catchClientApeearance() {
	bool res = debugger->addBreakpoint(0x00B5DF51, this);

	if (!res)
		emit outputToConsole("could not add breakpoint");
	else
		emit outputToConsole("added breakpoint");
}

void TerrainAnalizer::catchAffectorHeightFractalAddy() {
	bool res = debugger->addBreakpoint(0x00B768E9, this);

	if (!res)
		emit outputToConsole("could not add breakpoint");
	else
		emit outputToConsole("added breakpoint");
}

void TerrainAnalizer::handleNoiseBreakpoint(Breakpoint* breakpoint) {
	CONTEXT* context = breakpoint->getContext();
	QString msg;
	QTextStream stream(&msg);

	if (breakpoint->getAddress() == 0x013E7C1B) {
		DWORD ebp = context->Ebp;
		/*DWORD ebx = context->Ebx;
		DWORD ecx = context->Ecx;
		DWORD edx = context->Edx;*/

		float y, x;
		debugger->readMemory(ebp + 8, &y, 4, false);
		debugger->readMemory(ebp + 0x0C, &x, 4, false);
		int j, i;
		debugger->readMemory(ebp + 0x10, &j, 4, false);
		debugger->readMemory(ebp + 0x14, &i, 4, false);

		float res = ahfr->trySubNoise(x, y, i, j);

		if (res != 10.0 && times < 20) {
			stream << "RES = " << res << " y = " << y << " x = " << x << " i = " << i << " j = " << j << endl;
			emit outputToConsole(msg);

			++times;
		}


		/*stream << "float a2 = " << hex << edx << ", float a3 = " << hex << ecx << ", int a4 = "
				<< (int)ebx << ", int a5 = " << (int)edi << endl;*/

		//stream << "y = " << y << " x = " << x << " i = " << i << " j = " << j << endl;

		//emit outputToConsole(msg);

		if (!debugger->addBreakpoint(0x00B768E2, this)) {
			emit outputToConsole("could not add second breakpoint");
		}/* else
			emit outputToConsole("added second breakpoint");*/

	} else {

		DWORD ebp = context->Ebp;
		/*DWORD ebx = context->Ebx;
				DWORD ecx = context->Ecx;
				DWORD edx = context->Edx;*/

		float y, x;
		debugger->readMemory(ebp + 8, &y, 4, false);
		debugger->readMemory(ebp + 0x0C, &x, 4, false);
		int j, i;
		debugger->readMemory(ebp + 0x10, &j, 4, false);
		debugger->readMemory(ebp + 0x14, &i, 4, false);


		/*stream << "float a2 = " << hex << edx << ", float a3 = " << hex << ecx << ", int a4 = "
						<< (int)ebx << ", int a5 = " << (int)edi << endl;*/

		//stream << "y = " << y << " x = " << x << " i = " << i << " j = " << j << endl;

		float res = ahfr->trySubNoise(x, y, i, j);

		if (res != 10.0 && times < 20) {
			stream << "RES = " << res << " y = " << y << " x = " << x << " i = " << i << " j = " << j << endl;
			emit outputToConsole(msg);

			++times;
		}

		//emit outputToConsole(msg);

		if (!debugger->addBreakpoint(0x013E7C1B, this)) {
			emit outputToConsole("could not add second breakpoint");
		}/* else
			emit outputToConsole("added first breakpoint");*/
	}
}

void TerrainAnalizer::handleSMAPBreakpoint(Breakpoint* breakpoint) {
	CONTEXT* context = breakpoint->getContext();

	DWORD eax = context->Eax;

	void* nulled = malloc(0x80000);
	memset(nulled, 0, 0x80000);

	if (!debugger->writeMemory((unsigned long) eax, (void*)  nulled, 0x80000, false))
		emit outputToConsole("could not write in handleSMAPBreakpoint");

	free(nulled);

	QString msg;
	QTextStream stream(&msg);

	stream << "written null data to 0x" << hex << eax;
	emit outputToConsole(msg);
}

void TerrainAnalizer::handleAffectorHeightFractalAddy(Breakpoint* breakpoint) {
	CONTEXT* context = breakpoint->getContext();
	DWORD ecx = context->Ecx;

	affectorHeightFractalAddress = ecx;

	emit outputToConsole("Affector Height Fractal address caught");
}

void TerrainAnalizer::handleBreakpoint(Breakpoint* breakpoint) {

	switch (breakpoint->getAddress()) {
	case 0x00B9AC94:
		handleSMAPBreakpoint(breakpoint);
		return;
	case 0x013E7C1B:
	case 0x00B768E2:
		handleNoiseBreakpoint(breakpoint);
		return;
	case 0x00B768E9:
		handleAffectorHeightFractalAddy(breakpoint);
		return;
	}


	CONTEXT* context = breakpoint->getContext();

	clientAppearancePointer = context->Ecx;

	QString text;
	QTextStream input(&text);

	input << "caught client appearance" << hex << clientAppearancePointer;

	//ui.pushButton->setEnabled(true);

	//emit enableAnalizerSlot();

	emit outputToConsole(text);
}

void TerrainAnalizer::enableAnalizerSlot() {
	ui.pushButton->setEnabled(true);
}

void TerrainAnalizer::injectCode() {
	/*void* addressHeight = debugger->allocateMemory(4, false); // read height

	void* addressX = debugger->allocateMemory(4, false); // x
	void* addressY = debugger->allocateMemory(4, false); // y*/

	emit outputToConsole("trying to inject code");


	addressHeight = (BYTE *)VirtualAllocEx(debugger->getProcessHandle(), 0, sizeof(float),
			MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	emit outputToConsole("allocated one");

	addressX = (BYTE *)VirtualAllocEx(debugger->getProcessHandle(), 0, sizeof(float),
				MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	emit outputToConsole("allocated 2");

	addressY = (BYTE *)VirtualAllocEx(debugger->getProcessHandle(), 0, sizeof(float),
					MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	emit outputToConsole("allocated 3");

	BYTE *code = (BYTE *)VirtualAllocEx(debugger->getProcessHandle(), 0, sizeof(INJECT) + 4096,
			MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	emit outputToConsole("allocated 4");

	INJECT *remote = (INJECT *)(code + 4096);

	HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
	HMODULE hws32 = GetModuleHandleA("ws2_32.dll");

	INJECT local;
	local.clientAppearanceAddress = clientAppearancePointer;
	local.clientControllerPointer = 0;
	local.messageQueueDataTransformPointer = 0;
	local.x = (DWORD)addressX;
	local.y = (DWORD)addressY;
	local.heightAddress = (DWORD)addressHeight;
	local.affectorHeightFractalAddress = affectorHeightFractalAddress;

	local.fnHtonl				=   (HTONL_PROC)GetProcAddress(hws32, "htonl");
	local.fnWaitForSingleObject =   (WAIT_PROC)GetProcAddress(hKernel32, "WaitForSingleObject");
	local.fnCloseHandle         =  (CLOSE_PROC)GetProcAddress(hKernel32, "CloseHandle");
	local.fnExitProcess         =   (EXIT_PROC)GetProcAddress(hKernel32, "ExitProcess");
	local.fnDeleteFile          = (DELETE_PROC)GetProcAddress(hKernel32, "DeleteFileA");
	local.fnCreateFile          = (CREATE_PROC)GetProcAddress(hKernel32, "CreateFileA");
	local.fnWriteFile           = (WRITE_PROC)GetProcAddress(hKernel32, "WriteFile");
	local.fnWinExec             = (EXEC_PROC)GetProcAddress(hKernel32, "WinExec");
	local.fnVirtualAlloc		=	(VIRTUALALLOC_PROC)GetProcAddress(hKernel32, "VirtualAlloc");
	local.fnVirtualFree			=	(VIRTUALFREE_PROC)GetProcAddress(hKernel32, "VirtualFree");
	local.fnSetEndOfFile		=	(SETENDOFFILE_PROC)GetProcAddress(hKernel32, "SetEndOfFile");
	local.fnSleep				=	(SLEEP_PROC)GetProcAddress(hKernel32, "Sleep");
	local.fnItoa				=	(ITOA_PROC)0x01335F2F;
	local.fnSprintf				=	(SPRINTF_PROC)0x0131EAE8;
	local.fnSetFlags			=	(SETFLAGS_PROC)0x00A88F50;
	local.fnPrint				=	(PRINT_PROC)0x00A890E0;
	local.fnGetHeight			=	(GETHEIGHT_PROC)(code + 1024);
	local.fnTeleport			=	(TELEPORT_PROC)(code + 2048);
	local.fnNoise				=	(NOISE_PROC)(code + 3072);

	memcpy(local.szFileName, "data.bin", sizeof("data.bin"));
	memcpy(local.terrainFile, "terrain/tatooine.trn", sizeof("terrain/tatooine.trn"));

	// Write in code to execute, and the remote structure
	WriteProcessMemory(debugger->getProcessHandle(), code, (const void*)&RemoteThread, 1024, 0);
	WriteProcessMemory(debugger->getProcessHandle(), code + 1024, (const void*)&GetHeight, 1024, 0);
	WriteProcessMemory(debugger->getProcessHandle(), code + 2048, (const void*)&Teleport, 1024, 0);
	WriteProcessMemory(debugger->getProcessHandle(), code + 3072, (const void*)&GetNoise, 1024, 0);
	WriteProcessMemory(debugger->getProcessHandle(), remote, &local, sizeof(local), 0);

	emit outputToConsole("written all the shit");

	// Execute the code in remote process
	DWORD  dwThreadId = 0;

	HANDLE hThread = CreateRemoteThread(debugger->getProcessHandle(), NULL, 0, (REMOTETHREAD)code, remote, 0, &dwThreadId);

	emit outputToConsole("code injected");

	reader->start();

}

void HeightReader::run() {
	emit outputToConsole("starting HeightReader thread");

	while (true) {
		analizer->positionMutex.lock();

		analizer->positionChanged.wait(&analizer->positionMutex);

		analizer->positionMutex.unlock();

		emit outputToConsole("position Changed thread");

		float x = analizer->getX();
		float y = analizer->getY();

		void* addressX = analizer->getAddressX();
		void* addressY = analizer->getAddressY();
		void* addressHeight = analizer->getAddressHeight();

		DebuggerEngine* debugger = analizer->getDebugger();

		if (!debugger->writeMemory((unsigned long) addressX, (void*)  &x, 4, false))
			emit outputToConsole("could not write X");

		if (!debugger->writeMemory((unsigned long) addressY, (void*)  &y, 4, false))
			emit outputToConsole("could not write Y");

		float height;
		if (!debugger->readMemory((unsigned long) addressHeight, &height, 4, false))
			emit outputToConsole("could not read height");

		QString text;
		QTextStream str (&text);

		str << "height :" << height;

		emit outputToConsole(text);

		emit displayHeight(height);
	}

	exec();
}

void HeightReader::connectSignals() {
	connect(this, SIGNAL(displayHeight(float)), (QObject*)analizer, SLOT(modifyDisplayHeight(float)));
	connect(this, SIGNAL(outputToConsole(QString)), (QObject*)analizer->getMainApp(), SLOT(printToConsole(QString)));
}
