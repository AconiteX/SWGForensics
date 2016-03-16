#include "crccalculator.h"
#include "../../swgforensics.h"

#include <QTextStream>

CRCCalculator::CRCCalculator(SWGForensics* main, QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);

	mainWindow = main;

	ui.label->setText("...");

	connect(ui.plainTextEdit, SIGNAL(textChanged()), this, SLOT(calculateCRC()));
}

CRCCalculator::~CRCCalculator() {

}

void CRCCalculator::calculateCRC() {
	QString text = ui.plainTextEdit->toPlainText();
	QString crcText;

	uint32 crc = SWGForensics::hashCode(text);

	QTextStream stream(&crcText);
	stream << "hex: 0x" << hex << crc << " decimal: " << dec << crc;

	ui.label->setText(crcText);
}
