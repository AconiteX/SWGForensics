#include "lairtool.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include "src/swgforensics/swgforensics.h"

LairTool::LairTool(QWidget *parent)
    : QWidget(parent) {
	ui.setupUi(this);

	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(generateLuaScripts()));
}

LairTool::~LairTool() {

}

void LairTool::generateLuaScripts() {
	QSqlDatabase sqlDatabase = QSqlDatabase::addDatabase("QMYSQL");

	sqlDatabase.setHostName("localhost");
	sqlDatabase.setPort(3306);
	sqlDatabase.setDatabaseName("swgemu");
	sqlDatabase.setUserName("root");
	sqlDatabase.setPassword("swgemu");

	if (!sqlDatabase.open()) {
		SWGForensics::instance->showError("could not open db");
		return;
	}

	QSqlQuery query("SELECT name FROM `swgemu`.`client_strings` where stringFile like '%lair_n%';");

	while (query.next()) {
		QString name = query.value(0).toString();



	}

}
