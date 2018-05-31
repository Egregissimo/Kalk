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
#include "../binarytree.h"
#include "../binarytreesearch.h"

class mygui: public QWidget{
    Q_OBJECT                                        // Macro

/*  MAIN    -------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
public:
    mygui(QWidget* = 0);
    virtual ~mygui() {}

private:
    QMessageBox msgBox;                             // messaggio a finestra di output
    std::vector<tipo*> vettoreTipo;                 // vettore di tipo tipo* (che si rifà a raz, bin, vet) per creare l'abero
    std::map<string, binarytreebasic*> mappaTree;   // map che memorizza gli alberi creati associandogli un nome (string)

    bool whatChecked[3];                            // vettore di bool VEDI SUO UTILIZZO


    QHBoxLayout* mainHLayout;           // finestra principale di estensione orrizzontale che includerà le seguenti finestre verticali
    QVBoxLayout* mainVLayout1;          // finestra verticale per la sezione di creazione dell'albero (alias Box 1)
    QVBoxLayout* mainVLayout2;          // finestra verticale per la sezione di visualizzazione dell'albero 1 e albero 2 con avanzamento barra di progressine (alias Box 2)
    QVBoxLayout* mainVLayout3;          // finestra verticale per la sezione dei calcoli tra alberi dello stesso tipo e alberi con nodi dello stesso tipo (alias Box 3)

    void costruisciBox1();                       // costruzione Box1 che richima tutte le funzoni di costruzione dei widget
    void costruisciBox2();                       // costruzione Box2 che richima tutte le funzoni di costruzione dei widget
    void costruisciBox3();                       // costruzione Box3 che richima tutte le funzoni di costruzione dei widget

    void creaLayout1();                         // costruzione del layout per Box1
    void creaLayout2();                         // costruzione del layout per Box2
    void creaLayout3();                         // costruzione del layout per Box3

/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

    /*  BOX1    ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
    //  Descrizione di ogni sezione della Box 1 con i relativi campi dati, segnali, slot e funzioni utilizzate:
private:
    /*  Sezione tipologia albero e tipologia nodo   */
    QGridLayout* comboTreeLayout;   QComboBox* ComboTree;                   // Layout per inserire una ComboBox per selezionare il tipo di albero
    QGridLayout* radioTypeLayout;   std::vector<QRadioButton*> radioType;   // Layout per inserire una lista di RadioButton per selezionare il tipo di nodo dell'albero

    /*  -----------------------------------------   */

    /*  Sezione Nome, Struttura e tastierino per la struttura   */
    /*  Nome   */
    QGridLayout* nomeLayout;                                                // Layout pre inserire i widget Label e LineEdit per il Nome dell'albero
    QLabel* LabelNomeTree;
    QLineEdit* LineEditNomeTree;
    /*  Struttura   */
    QGridLayout* strutturaLayout;                                           // Layout pre inserire i widget Label e LineEdit per la Struttura dell'albero
    QLabel* LabelStrutturaTree;
    QLineEdit* LineEditStrutturaTree;
    /*  Tastierino   */
    QGridLayout* tastieraStrutturaLayout;                                   // Layout pre inserire i bottoni per scrivere la struttura dell'albero
    std::vector<QPushButton*> tastierinoStruttura;
    std::vector<QPushButton*> option2;                                      // Bottoni canc e canc all
    /*  ----------------------------------------------------   */

    /*  Sezione di inserimento dati per la creazione dei nodi per l'albero  */
    QGridLayout* displayLayout;                                             // Layout per inserire i seguenti widget
    /*  Sezione inserimento dati per Raz  */
    QLabel* labelNumeratore;    QLineEdit* LineEditNum;
    QLabel* labelDenominatore;  QLineEdit* LineEditDen;

    /*  Sezione inserimento dati per Bin  */
    QLabel* labelKalk;  QLineEdit* display;
    std::vector<QPushButton*> option1;                                      // Bottoni canc e canc all

    /*  Sezione inserimento dati per Vet  */
    QLabel* label_row;      QSpinBox* SpinBox_row;
    QLabel* label_colum;    QSpinBox* SpinBox_colum;

    /*  +++++++++++++++++++++++++++++++++++++++++++++++++++   */

    /*  Sezione tasto Go/Crea per creare i nodi di tipo raz e bin   */
    /*  Per Vet ha la funzione di creare la tabella per popolare la classe di tipo vet  */
    QGridLayout* goLayout;
    QPushButton* go;

    /*  Sezione di inserimento dati nella tabella per la classe Vet*/
    QTableWidget* table;
    QPushButton* creaVet;                                                   // Tabella per inserire i dati per popolare un oggetto di classe vet

    // aggiunta dei widget sul layout del box 1
    void addWidgetComboRadio();
    void addWidgetNomeTreeSezione();
    void addWidgetStrutturaSezione();
    void addWidgetGo();

    // aggiunta e rimozione dei seguenti widget
    void addWidgetDisplayRaz();
    void addWidgetDisplayBin();
    void addWidgetDisplayVet();
    void removeWidgetDisplayRaz();
    void removeWidgetDisplayBin();
    void removeWidgetDisplayVet();

    void addWidgetTable();
    void removeWidgetTable();

    // creazione degli oggetti/widget
    void creaComboRadioButton();
    void creaNomeTreeSezione();
    void creaStrutturaSezione();
    void creaOptionButton();

    void creaTastieraOperatori();

    // connessione dei widget ai relativi slot
    void connectOptionToSlot();
    void connectButtonStructAndRadioToSlot();

    // funzioni ausiliarie per la creazione dei nodi raz, bin e vet
    void creazioneNodiRaz();
    void creazioneNodiBin();
    void creazioneNodiVet();
    void add_vet_raz_bin();              // creazine dell'albero popolandolo coi nodi creati prima

    // funzioni per abilitare o disabilitare: la tastiera struttura, il tasto go/crea e i radio button
    void abi_TastieraStruttura(bool);
    void abi_go_crea(bool);
    void abi_radioType(bool);
    void abi_butto_crea(bool);

public slots:
    // slot per i tasti canc e canc all per l'inserimento struttura e per l'inserimento dati nella sezione bin
    void clearAll();
    void canc();
    void clearAll2();
    void canc2();

    // slot per i bottoni della struttura dell'albero
    void slotButtonAQ();                        // "("
    void slotButtonCQ();                        // ")"
    void slotButton_();                         // "_"
    void slotButtonVirgola();                   // ","
    void slotButtonStar();                      // "*"
    void slotButtonAddStruttura();              // bottone "add"

    // slot per i radio button che cambiano la modalità di inserimento dei dati quando cliccati
    void slotRadioRaz();
    void slotRadioBin();
    void slotRadioVet();

    // slot per la creazione del nodo e della tabella
    void slotGo();
    // slot creazione del nodo vet
    void slotCreazioneVet();
    /*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

    /*  BOX2    ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
private:
    QGridLayout* progressLayout;                                            // Layout per inserire i seguenti widget:
    QLabel* labelProgessStruttura;  QProgressBar* progressBarStruttura;     // Barra di avanzamaneto della creazione dell'albero (in base alla struttura dell' albero inserita prima)

    /*  Sezione di visualizzazione della struttura (con nodi) dei due operandi (alberi)  */
    QGridLayout* textEditLayout;                                            // Layout per iserire i seguenti widget
    QLabel* label_struttura_tree1;  QTextEdit* struttura_tree1;
    QLabel* label_struttura_tree2;  QTextEdit* struttura_tree2;

    // aggiunta, creazione e funzionalità dei widget per la box 2
    void addWidgetProgressBar();
    void creaProgessBarStruttura();
    void avanzaProgressBar();
    /*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

    /*  BOX3    ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
private:
    /*  Sezione per operare con due alberi  */
    QGridLayout* operaLayout;                                               // Layout per inserire i seguenti widget:
                                                                            // Operando 1 e 2 sono due ComboBox con la lista di Alberi in base al tipo di albero e al tipo di nodo
                                                                            // selezionati rispettivamente nella ComboBox e nei RadioButton della Box 1
    QComboBox* ComboListaTree1;                                             // Operando 1 (Albero 1)
    QComboBox* ComboListaTree2;                                             // Operando 2 (Albero 2)
    QComboBox* ComboListaOperazioni;                                        // ComboBox con lista operazioni tra due alberi
    QLineEdit* molt_div;                                                    // LineEdit per inserire un valore di intero per le operazioni di moltiplicazione e divisione

    /* Sezione per il tasto calcola  */
    QGridLayout* calcolaLayout;                                             // Layout per inserire il tasto calcola e la TextEdit che mostra a video l'albero risultante
    QPushButton* calcola;
    QTextEdit* struttura_ris;

    // aggiunta, rimozione dei widget e rispettive funzionalità
    void addWidgetOpera();
    void addWidgetCalcola();
    void add_rm_mol_div(bool);
    void aggiornaComboBoxListaTree();

    //connessione ComboListaTree1 e 2 alle relative operazioni
    void connectComboOperazioniToSlot();



public slots:
    void slotComboTree();               // slot per cambiare il secondo operatore (da ComboBox a LineEdit e viceversa)
    void slotComboTextEdit();           // slot per stampare la struttura con nodi degli alberi 1 e 2

    void slotAggiornaCombo();           // slot per aggiornare le liste delle ComboBox 1 e 2 che cambiano dinamicamente in base al tipo di albero e al tipo di nodo

    void slotComboOperazioni(int);      // slot per collegare le operazioni
    void slotCalcola();                 // slot per avviare il calcolo
    /*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
};
#endif // MYGUI_H
