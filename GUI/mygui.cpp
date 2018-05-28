#include "mygui.h"

mygui::mygui(QWidget* parent): QWidget(parent){
    for(unsigned int i=0; i<3; i++)
        whatChecked[i] = false;
    table = 0;      //FORSE NECESSARIO METTERE TUTTI I PUNTATORI SETTATI A 0 A INIZIO PROGRAMMA
    mainVLayout3 = 0;

    setWindowTitle("Prova GUI KALK");
    resize(900,300);
    mainHLayout = new QHBoxLayout(this);
    costruiciBox1();
    mainHLayout->addLayout(mainVLayout1);

    mainVLayout2 = new QVBoxLayout();
    mainVLayout2->setContentsMargins(50,0,0,0);
    costruiciBox2();
    mainHLayout->addLayout(mainVLayout2);


}
void mygui::costruiciBox1(){
    creaLayout1();
    addWidgetComboRadio();
    addWidgetNomeTreeSezione();
    addWidgetStrutturaSezione();
    addWidgetDisplayRaz();
    addWidgetGo();
}
void mygui::creaLayout1(){
    mainVLayout1 = new QVBoxLayout();

    /*  Sezione tipologia albero e tipologia nodo   */
    comboTreeLayout = new QGridLayout();
    radioTypeLayout = new QGridLayout();
    /*  Nome, Struttura e tastierino per la struttura   */
    nomeLayout = new QGridLayout();
    strutturaLayout = new QGridLayout();
    tastieraStrutturaLayout = new QGridLayout();
    /*  Sezione display KALK    */
    displayLayout = new QGridLayout();

    /*  Sezione tipologia albero e tipologia nodo   */
    mainVLayout1->addLayout(comboTreeLayout);
    mainVLayout1->addLayout(radioTypeLayout);
    /*  Nome, Struttura e tastierino per la struttura   */
    mainVLayout1->addLayout(nomeLayout);
    mainVLayout1->addLayout(strutturaLayout);
    mainVLayout1->addLayout(tastieraStrutturaLayout);
    /*  Sezione display KALK    */
    mainVLayout1->addLayout(displayLayout);

    /*  sezione dimensione vet*/
    goLayout = new QGridLayout();
    mainVLayout1->addLayout(goLayout);
    /*  ------------------------------------------  */
}

void mygui::addWidgetComboRadio(){
    creaComboRadioButton();
    comboTreeLayout->addWidget(ComboTree);

    radioTypeLayout->addWidget(radioType[0],0,0);
    radioTypeLayout->addWidget(radioType[1],0,1);
    radioTypeLayout->addWidget(radioType[2],0,2);
}
void mygui::addWidgetNomeTreeSezione(){
    creaNomeTreeSezione();
    nomeLayout->addWidget(LabelNomeTree,0,0);
    nomeLayout->addWidget(LineEditNomeTree,0,1);
}
void mygui::addWidgetStrutturaSezione(){
    creaOptionButton();
    creaTastieraOperatori();
    creaStrutturaSezione();
    strutturaLayout->addWidget(LabelStrutturaTree,0,0);
    strutturaLayout->addWidget(LineEditStrutturaTree,0,1);
    strutturaLayout->addWidget(option2[1],0,2);
    strutturaLayout->addWidget(option2[0],0,3);
    for(int i=0; i<tastierinoStruttura.size(); i++)
        tastieraStrutturaLayout->addWidget(tastierinoStruttura[i], 0, i);
}

void mygui::addWidgetDisplayRaz(){
    labelNumeratore = new QLabel("Num");
    labelDenominatore   = new QLabel("Den");
    LineEditNum = new QLineEdit("");
    LineEditDen = new QLineEdit("");
    LineEditNum->setAlignment(Qt::AlignRight);
    LineEditDen->setAlignment(Qt::AlignRight);
    LineEditNum->setMaxLength(15);
    LineEditDen->setMaxLength(15);

    LineEditNum->setValidator( new QDoubleValidator() );
    LineEditDen->setValidator( new QDoubleValidator() );

    displayLayout->addWidget(labelNumeratore,0,0);
    displayLayout->addWidget(labelDenominatore,0,2);
    displayLayout->addWidget(LineEditNum,0,1);
    displayLayout->addWidget(LineEditDen,0,3);

    whatChecked[0]=true;
}
void mygui::addWidgetDisplayBin(){
    labelKalk = new QLabel("KALK");
    display = new QLineEdit("");
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);
    display->setValidator( new QDoubleValidator() );
    displayLayout->addWidget(labelKalk,0,0);
    displayLayout->addWidget(display,0,1);
    displayLayout->addWidget(option1[1],0,2);
    displayLayout->addWidget(option1[0],0,3);
    connectOptionToSlot();
    whatChecked[1]=true;
}
void mygui::addWidgetDisplayVet(){
    label_row = new QLabel("Row");
    label_colum = new QLabel("Colum");

    SpinBox_row = new QSpinBox();
    SpinBox_colum = new QSpinBox();
    SpinBox_row->setMinimum(1);
    SpinBox_row->setMaximum(99);
    SpinBox_row->setSingleStep(1);
    SpinBox_row->setValue(1);
    SpinBox_colum->setMinimum(1);
    SpinBox_colum->setMaximum(99);
    SpinBox_colum->setSingleStep(1);
    SpinBox_colum->setValue(1);

    displayLayout->addWidget(label_row,0,0);
    displayLayout->addWidget(label_colum,0,2);
    displayLayout->addWidget(SpinBox_row,0,1);
    displayLayout->addWidget(SpinBox_colum,0,3);

    whatChecked[2]=true;
}
void mygui::addWidgetGo(){
    go = new QPushButton("Go/Crea");
    goLayout->addWidget(go,0,0);
    connect(go, SIGNAL(clicked()), this, SLOT(slotGo()));
    go->setDisabled(true);
}
void mygui::addWidgetTable(){
    int r = SpinBox_row->value();
    int c = SpinBox_colum->value();
    if(table)
        removeWidgetTable();

    resize(900+c*50,300+r*50);
    table = new QTableWidget(r,c);
    creaVet = new QPushButton("Crea Vet");
    goLayout->addWidget(table,1,0);
    goLayout->addWidget(creaVet,2,0);
}

void mygui::removeWidgetDisplayRaz(){
    displayLayout->removeWidget(labelNumeratore);
    displayLayout->removeWidget(labelDenominatore);
    displayLayout->removeWidget(LineEditNum);
    displayLayout->removeWidget(LineEditDen);

    delete labelNumeratore;
    delete labelDenominatore;
    delete LineEditNum;
    delete LineEditDen;
    whatChecked[0]=false;
}
void mygui::removeWidgetDisplayBin(){
    displayLayout->removeWidget(labelKalk);
    displayLayout->removeWidget(display);
    displayLayout->removeWidget(option1[1]);
    displayLayout->removeWidget(option1[0]);
    delete labelKalk;
    delete display;
    for(unsigned int i=0; i<option1.size(); i++)
        delete option1[i];
    option1.clear();
    whatChecked[1]=false;
}
void mygui::removeWidgetDisplayVet(){
    displayLayout->removeWidget(label_row);
    displayLayout->removeWidget(label_colum);
    displayLayout->removeWidget(SpinBox_row);
    displayLayout->removeWidget(SpinBox_colum);

    delete label_row;
    delete label_colum;
    delete SpinBox_row;
    delete SpinBox_colum;
    whatChecked[2]=false;
}
void mygui::removeWidgetTable(){
    resize(900,300);
    goLayout->removeWidget(table);
    goLayout->removeWidget(creaVet);
    delete table;
    delete creaVet;
    table = 0;
}

void mygui::creaComboRadioButton(){
    ComboTree = new QComboBox();
    ComboTree->addItem("Binary Tree");
    ComboTree->addItem("Binary Tree Search");

    radioType.push_back(new QRadioButton("Raz"));
    radioType.push_back(new QRadioButton("Bin"));
    radioType.push_back(new QRadioButton("Vet"));
    radioType[0]->setChecked(true);
}
void mygui::creaNomeTreeSezione(){
    LabelNomeTree = new QLabel("Nome Tree");
    LineEditNomeTree = new QLineEdit("Albero");
}
void mygui::creaStrutturaSezione(){
    LabelStrutturaTree = new QLabel("Struttura");
    LineEditStrutturaTree = new QLineEdit("(*,(*,_,(*,_,_)),(*,(*,_,_),(*,_,_)))");
    LineEditStrutturaTree->setReadOnly(true);
}
void mygui::creaOptionButton(){
    option1.push_back(new QPushButton("Clear"));
    option1.push_back(new QPushButton("◄"));
    option2.push_back(new QPushButton("Clear"));
    option2.push_back(new QPushButton("◄"));

    for(unsigned int i=0; i<option1.size()-1 && i<option2.size()-1; i++){
        option1[i]->setFixedSize(QSize(40,30));
        option2[i]->setFixedSize(QSize(40,30));

        option1[i+1]->setFixedSize(QSize(30,30));
        option2[i+1]->setFixedSize(QSize(30,30));
    }
    connectOptionToSlot();
}

void mygui::creaTastieraOperatori(){
     tastierinoStruttura.push_back(new QPushButton("("));
     tastierinoStruttura.push_back(new QPushButton(")"));
     tastierinoStruttura.push_back(new QPushButton("_"));
     tastierinoStruttura.push_back(new QPushButton(","));
     tastierinoStruttura.push_back(new QPushButton("*"));
     tastierinoStruttura.push_back(new QPushButton("Add"));

     for(unsigned int i=0; i<tastierinoStruttura.size(); i++)
         tastierinoStruttura[i]->setFixedSize(QSize(30,30));
     connectButtonStructAndRadioToSlot();
}

/* SLOT PER I BOTTONI OPERATORI */
void mygui::clearAll(){
    display->setText("");
}
void mygui::canc(){
    QString text = display->text();
    text.chop(1);
    display->setText(text);
}
void mygui::clearAll2(){
    LineEditStrutturaTree->setText("");
    abi_disab_TastieraStruttura(true);
    abi_disab_go_crea(false);
}
void mygui::canc2(){
    QString text = LineEditStrutturaTree->text();
    text.chop(1);
    LineEditStrutturaTree->setText(text);
    if(!tastierinoStruttura[5]->isEnabled()){
        abi_disab_TastieraStruttura(true);
        abi_disab_go_crea(false);
    }
}

void mygui::slotButtonAQ(){
    LineEditStrutturaTree->setText(LineEditStrutturaTree->text() + "(");
}
void mygui::slotButtonCQ(){
    LineEditStrutturaTree->setText(LineEditStrutturaTree->text() + ")");
}
void mygui::slotButton_(){
    LineEditStrutturaTree->setText(LineEditStrutturaTree->text() + "_");
}
void mygui::slotButtonVirgola(){
    LineEditStrutturaTree->setText(LineEditStrutturaTree->text() + ",");
}
void mygui::slotButtonStar(){
    LineEditStrutturaTree->setText(LineEditStrutturaTree->text() + "*");
}
void mygui::slotButtonAddStruttura(){
    QString testo_struttura = LineEditStrutturaTree->text();
    if(!testo_struttura.isEmpty()){
        string std_testo_struttura = testo_struttura.toStdString();
        string::iterator start = std_testo_struttura.begin();
        int nNodi = binarytreebasic::n_nodes_stringa(start);
        progressBarStruttura->setMaximum(nNodi);

        abi_disab_TastieraStruttura(false);
        abi_disab_go_crea(true);
    }
}

void mygui::slotRadioRaz(){
    if(radioType[0]->isChecked()){
        if(whatChecked[1])
            removeWidgetDisplayBin();
        if(whatChecked[2]){
            if(table)
                removeWidgetTable();
            removeWidgetDisplayVet();
        }
        addWidgetDisplayRaz();
    }
}
void mygui::slotRadioBin(){
    if(radioType[1]->isChecked()){

        if(whatChecked[0])
            removeWidgetDisplayRaz();
        if(whatChecked[2]){
            if(table)
                removeWidgetTable();
            removeWidgetDisplayVet();
        }

        option1.push_back(new QPushButton("Clear"));
        option1.push_back(new QPushButton("◄"));
        option1[0]->setFixedSize(QSize(40,30));
        option1[1]->setFixedSize(QSize(30,30));
        addWidgetDisplayBin();
    }
}
void mygui::slotRadioVet(){
    if(radioType[2]->isChecked()){
        if(whatChecked[0])
            removeWidgetDisplayRaz();

        if(whatChecked[1])
            removeWidgetDisplayBin();
        addWidgetDisplayVet();
    }
}
void mygui::slotComboTree(){
    aggiornaComboBoxListaTree();
}
void mygui::slotGo(){
    if(radioType[0]->isChecked())
        creazioneNodiRaz();

    if(radioType[2]->isChecked())
        addWidgetTable();
}

void mygui::connectOptionToSlot(){
    QObject::connect(option1[0], SIGNAL(clicked()), this, SLOT(clearAll()));
    QObject::connect(option1[1], SIGNAL(clicked()), this, SLOT(canc()));
    QObject::connect(option2[0], SIGNAL(clicked()), this, SLOT(clearAll2()));
    QObject::connect(option2[1], SIGNAL(clicked()), this, SLOT(canc2()));
}
void mygui::connectButtonStructAndRadioToSlot(){
    connect(tastierinoStruttura[0], SIGNAL(clicked()), this, SLOT(slotButtonAQ()));
    connect(tastierinoStruttura[1], SIGNAL(clicked()), this, SLOT(slotButtonCQ()));
    connect(tastierinoStruttura[2], SIGNAL(clicked()), this, SLOT(slotButton_()));
    connect(tastierinoStruttura[3], SIGNAL(clicked()), this, SLOT(slotButtonVirgola()));
    connect(tastierinoStruttura[4], SIGNAL(clicked()), this, SLOT(slotButtonStar()));
    connect(tastierinoStruttura[5], SIGNAL(clicked()), this, SLOT(slotButtonAddStruttura()));
    connect(radioType[2], SIGNAL(toggled(bool)), this, SLOT(slotRadioVet()));
    connect(radioType[1], SIGNAL(toggled(bool)), this, SLOT(slotRadioBin()));
    connect(radioType[0], SIGNAL(toggled(bool)), this, SLOT(slotRadioRaz()));
    connect(ComboTree, SIGNAL(activated(int)), this, SLOT(slotComboTree()));
}
/*  ----------------------------------------------------    */
void mygui::creazioneNodiRaz(){
    QMessageBox msgBox;
    double num; double den;
    QString text;

    text = LineEditNum->text();
    text.remove( QChar( '.' ) );
    num = text.toDouble();
    text = LineEditDen->text();
    text.remove( QChar( '.' ) );
    den = text.toDouble();

    if(den == 0)
        den = 1.0;

    vettoreTipo.push_back(new raz(num,den));
    LineEditNum->setText("");LineEditDen->setText("");
    avanzaProgressBar();

    if(progressBarStruttura->value() == progressBarStruttura->maximum()){
        if(!mainVLayout3)
            costruiciBox3();


        msgBox.setText("Hai completato la creazione dei nodi!\nAlbero creato");
        msgBox.exec();

        QString nome = LineEditNomeTree->text();
        string nomeTree = nome.toStdString();

        if(ComboTree->currentText() == "Binary Tree")
            mappaTree[nomeTree] = new binarytree();

        if(ComboTree->currentText() == "Binary Tree Search")
            mappaTree[nomeTree] = new binarytreesearch();


        aggiornaComboBoxListaTree();
        abi_disab_TastieraStruttura(true);
        abi_disab_go_crea(false);

        progressBarStruttura->setValue(0);
        LineEditNomeTree->setText("Albero" + QString::number(mappaTree.size()) );
    }
}

/*  BOX2    */
void mygui::costruiciBox2(){
    creaLayout2();
    addWidgetProgressBar();
}
void mygui::creaLayout2(){
    progressLayout = new QGridLayout();
    mainVLayout2->addLayout(progressLayout);
}
void mygui::addWidgetProgressBar(){
    creaProgessBarStruttura();
    progressLayout->addWidget(labelProgessStruttura,0,0);
    progressLayout->addWidget(progressBarStruttura,0,1);
}
void mygui::creaProgessBarStruttura(){
    labelProgessStruttura = new QLabel("Avanzamento creazione");
    progressBarStruttura = new QProgressBar();
    progressBarStruttura->setRange(0,100);

    progressBarStruttura->setValue(0);
}

void mygui::avanzaProgressBar(){
    progressBarStruttura->setValue(progressBarStruttura->value() + 1);
}

/*  BOX3    */
void mygui::costruiciBox3(){
    resize(1200,300);
    creaLayout3();
    addWidgetOpera();
}
void mygui::creaLayout3(){
    mainVLayout3 = new QVBoxLayout();
    mainVLayout3->setContentsMargins(50,0,0,0);
    mainHLayout->addLayout(mainVLayout3);

    operaLayout = new QGridLayout();
    mainVLayout3->addLayout(operaLayout);
}
void mygui::addWidgetOpera(){
    if(radioType[0]->isChecked()){
        ComboListaTree1 = new QComboBox();  ComboListaTree2 = new QComboBox(); ComboListaOperazioni = new QComboBox();
        ComboListaOperazioni->addItem("Somma");
        ComboListaOperazioni->addItem("Sottrazione");
        ComboListaOperazioni->addItem("Moltiplicazione");
        ComboListaOperazioni->addItem("Divisione");
        operaLayout->addWidget(ComboListaTree1,0,0);
        operaLayout->addWidget(ComboListaOperazioni,0,1);
        operaLayout->addWidget(ComboListaTree2,0,2);
    }
}

void mygui::aggiornaComboBoxListaTree(){
    /* va fatto un cast per il tipo di albero e il tipo di nodo */
    if(mainVLayout3){
        ComboListaTree1->clear();
        ComboListaTree2->clear();
        if(ComboTree->currentText() == "Binary Tree"){
            for(std::map<string, binarytreebasic*>::iterator it=mappaTree.begin(); it!=mappaTree.end(); ++it){
                if(dynamic_cast<binarytree*>((it->second))){
                    ComboListaTree1->addItem(QString::fromStdString(it->first));
                    ComboListaTree2->addItem(QString::fromStdString(it->first));
                }
            }
        }
        if(ComboTree->currentText() == "Binary Tree Search"){
            for(std::map<string, binarytreebasic*>::iterator it=mappaTree.begin(); it!=mappaTree.end(); ++it){
                if(dynamic_cast<binarytreesearch*>((it->second))){
                    ComboListaTree1->addItem(QString::fromStdString(it->first));
                    ComboListaTree2->addItem(QString::fromStdString(it->first));
                }
            }
        }
    }
}

/*  Abilita disabilita  */
void mygui::abi_disab_TastieraStruttura(bool flag){
    if(flag){
        for(int i=0; i<tastierinoStruttura.size(); ++i)
            tastierinoStruttura[i]->setEnabled(true);
    }
    else{
        for(int i=0; i<tastierinoStruttura.size(); ++i)
            tastierinoStruttura[i]->setDisabled(true);
    }
}
void mygui::abi_disab_go_crea(bool flag){
    if(flag)
        go->setEnabled(true);
    else
        go->setDisabled(true);
}
