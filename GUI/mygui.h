#ifndef MYGUI_H
#define MYGUI_H
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QProgressBar>
#include <QTableWidget>
#include <QMessageBox>
#include <QTextEdit>

#include "string"
#include <vector>
#include <map>
#include "../binarytreebasic.h"
#include "../binarytree.h"
#include "../binarytreesearch.h"
#include "../raz.h"

class mygui: public QWidget{
    QMessageBox msgBox;
    std::map<string, binarytreebasic*> mappaTree;
    std::vector<tipo*> vettoreTipo;


    Q_OBJECT                                            //Macro
    bool whatChecked[3];

    QHBoxLayout* mainHLayout;
    QVBoxLayout* mainVLayout1;
    QVBoxLayout* mainVLayout2;
    QVBoxLayout* mainVLayout3;
    /*  BOX1    --------------------------------------------------------------------------------------  */
    /*    Sezione tipologia albero e tipologia nodo     */
    QGridLayout* comboTreeLayout;
    QGridLayout* radioTypeLayout;
    QComboBox* ComboTree;
    std::vector<QRadioButton*> radioType;
    /*  ---------------------------------------------   */

    /*  Nome, Struttura e tastierino per la struttura   */
    /*  1   */
    QGridLayout* nomeLayout;
    QLabel* LabelNomeTree;
    QLineEdit* LineEditNomeTree;
    /*  2   */
    QGridLayout* strutturaLayout;
    QLabel* LabelStrutturaTree;
    QLineEdit* LineEditStrutturaTree;
    /*  3   */
    QGridLayout* tastieraStrutturaLayout;
    std::vector<QPushButton*> tastierinoStruttura;
    /*  ---------------------------------------------   */

    /*  Sezione display KALK                            */
    /*  Sezione dimensione Raz  */
    QLabel* labelNumeratore;
    QLabel* labelDenominatore;
    QLineEdit* LineEditNum;
    QLineEdit* LineEditDen;

    // Da switchare con:
    /*  Sezione dimensione Bin  */
    QGridLayout* displayLayout;
    QLabel* labelKalk;
    QLineEdit* display;
    /*  Sezione dimensione Vet  */
    QLabel* label_row;
    QLabel* label_colum;
    QSpinBox* SpinBox_row;
    QSpinBox* SpinBox_colum;
    /*  ---------------------------------------------   */

    /*  Sezione popola vet                              */
    QGridLayout* goLayout;
    QPushButton* go;

    QTableWidget* table;
    QPushButton* creaVet;
    /*  ---------------------------------------------   */

    /*  Altre tastiere, opzioni(canc, canc all), operatori  */
    std::vector<QPushButton*> option2;
    std::vector<QPushButton*> option1;
    /*  --------------------------------------------------  */
    /*  BOX1    --------------------------------------------------------------------------------------  */


    /*  BOX2    --------------------------------------------------------------------------------------  */
    QGridLayout* progressLayout;
    QLabel* labelProgessStruttura;
    QProgressBar* progressBarStruttura;

    QGridLayout* textEditLayout;
    QLabel* label_struttura_tree1;
    QLabel* label_struttura_tree2;
    QTextEdit* struttura_tree1;
    QTextEdit* struttura_tree2;

    /*  BOX3    --------------------------------------------------------------------------------------  */
    QGridLayout* operaLayout;
    QGridLayout* calcolaLayout;
    QComboBox* ComboListaTree1;
    QComboBox* ComboListaTree2;
    QComboBox* ComboListaOperazioni;

    QLineEdit* molt_div;
    QPushButton* calcola;
    QTextEdit* struttura_ris;

public:
    mygui(QWidget* = 0);
    virtual ~mygui() {};

private:
    void costruiciBox1();
    void costruiciBox2();
    void costruiciBox3();

    void creaLayout1();
    void creaLayout2();
    void creaLayout3();

    /*  BOX1    */
    void addWidgetDisplayRaz();
    void addWidgetDisplayBin();
    void addWidgetDisplayVet();

    void removeWidgetDisplayRaz();
    void removeWidgetDisplayBin();
    void removeWidgetDisplayVet();

    void addWidgetComboRadio();
    void addWidgetNomeTreeSezione();
    void addWidgetStrutturaSezione();
    void addWidgetOption();
    void addWidgetTastierino();
    void addWidgetGo();

    void addWidgetTable();
    void removeWidgetTable();

    void creaComboRadioButton();
    void creaNomeTreeSezione();
    void creaStrutturaSezione();
    void creaOptionButton();

    void creaTastieraNum();
    void creaTastieraOperatori();

    void connectOptionToSlot();
    void connectButtonStructAndRadioToSlot();
    void connectComboOperazioniToSlot();

    void creazioneNodiRaz();
    void creazioneNodiBin();
    void creazioneNodiVet();
    void add_vet_raz_bin(QString);

    /*  -----   */

    void addWidgetProgressBar();
    void creaProgessBarStruttura();
    void avanzaProgressBar();

    /*  -----  */

    void addWidgetOpera();
    void addWidgetCalcola();

    void add_rm_mol_div(bool);
    void aggiornaComboBoxListaTree();

    /*  Abilita/Disabilita  */
    void abi_disab_TastieraStruttura(bool);
    void abi_disab_go_crea(bool);
    void abi_disab_radioType(bool);

public slots:
    void clearAll();
    void canc();

    void clearAll2();
    void canc2();

    void slotButtonAQ();
    void slotButtonCQ();
    void slotButton_();
    void slotButtonVirgola();
    void slotButtonStar();
    void slotButtonAddStruttura();

    void slotRadioRaz();
    void slotRadioBin();
    void slotRadioVet();
    void slotComboTree();
    void slotComboTextEdit();

    void slotGo();

    void slotAggiornaCombo();
    void slotCreazioneVet();

    void slotComboOperazioni(int);
    void slotCalcola();
};
#endif // MYGUI_H
