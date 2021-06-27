#include "TFG_ELO_UI.h"

TFG_ELO_UI::TFG_ELO_UI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void TFG_ELO_UI::on_directoryButton_clicked() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
        "c://",
        QFileDialog::ShowDirsOnly
        | QFileDialog::DontResolveSymlinks);
    ui.pathEdit->setText(dir);
}

bool TFG_ELO_UI::checkEditsLineEmpty() {
    int pos = 0;
    if (ui.deltaEloEdit->text().isEmpty()) return false;
    if (ui.numPlayersEdit->text().isEmpty()) return false;
    if (ui.numPlayerTeamEdit->text().isEmpty()) return false;
    if (ui.numRoundsEdit->text().isEmpty()) return false;
    if (ui.numTeamsMatchEdit->text().isEmpty()) return false;
    if (ui.pathEdit->text().isEmpty()) return false;
    return true;
}

bool TFG_ELO_UI::checkEditsLineNumber() {
    int pos = 0;
    QValidator *validator = new QIntValidator(0, numeric_limits<int>::max(), this);
    if (validator->validate(ui.deltaEloEdit->text(), pos) != QValidator::Acceptable) return false;
    if (validator->validate(ui.numPlayersEdit->text(), pos) != QValidator::Acceptable) return false;
    if (validator->validate(ui.numPlayerTeamEdit->text(), pos) != QValidator::Acceptable) return false;
    if (validator->validate(ui.numRoundsEdit->text(), pos) != QValidator::Acceptable) return false;
    if (validator->validate(ui.numTeamsMatchEdit->text(), pos) != QValidator::Acceptable) return false;
    return true;
}

void TFG_ELO_UI::on_startButton_clicked() {
    if (checkEditsLineEmpty() && checkEditsLineNumber()) {

        QString numPlayers = ui.numPlayersEdit->text();
        QString deltaElo = ui.deltaEloEdit->text();
        QString numPlayersTeam = ui.numPlayerTeamEdit->text();
        QString numTeamsMatch = ui.numTeamsMatchEdit->text();
        QString numRounds = ui.numRoundsEdit->text();
        QString path = ui.pathEdit->text();

        domini::TFG_ELO tfg = domini::TFG_ELO();
        tfg.startProgram(numPlayers.toInt(), numPlayersTeam.toInt(), numTeamsMatch.toInt(), deltaElo.toInt(), numRounds.toInt(), path.toStdString());
        
        QMessageBox::information(this, "Success", "The simulation has finished perfectly");
    }
    else {
        QMessageBox::information(this, "Error", "Parameters entered incorrectly");
    }
}
