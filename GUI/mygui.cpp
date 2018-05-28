#include "mygui.h"

mygui::mygui(QWidget* parent): QWidget(parent), mainHLayout(0), mainVLayout1(0), mainVLayout2(0),
mainVLayout3(0), comboTreeLayout(0), radioTypeLayout(0), ComboTree(0), radioType(0), nomeLayout(0),
LabelNomeTree(0), LineEditNomeTree(0), strutturaLayout(0), LineEditStrutturaTree(0), tastieraStrutturaLayout(0),
tastierinoStruttura(0), labelNumeratore(0), labelDenominatore(0), LineEditNum(0), LineEditDen(0),
displayLayout(0), labelKalk(0), display(0), label_row(0), label_colum(0), SpinBox_row(0),
SpinBox_colum(0), goLayout(0), go(0), table(0), creaVet(0), progressLayout(0), progressBarStruttura(0),
operaLayout(0), calcolaLayout(0), ComboListaTree1(0), ComboListaTree2(0), ComboListaOperazioni(0),
molt_div(0), calcola(0), struttura_ris(0){
    for(unsigned int i=0; i<3; i++)
        whatChecked[i] = false;

    setWindowTitle("KALK");
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

    for(int i=0; i<r; ++i){
        for(int j=0; j<c; ++j){
            QLineEdit* tmp_lineEdit = new QLineEdit("0");
            tmp_lineEdit->setValidator(new QIntValidator());
            table->setCellWidget(i,j,tmp_lineEdit);
        }
    }

    creaVet = new QPushButton("Crea Vet");
    connect(creaVet, SIGNAL(clicked()), this, SLOT(slotCreazioneVet()));
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
    abi_disab_radioType(true);
}
void mygui::canc2(){
    QString text = LineEditStrutturaTree->text();
    text.chop(1);
    LineEditStrutturaTree->setText(text);
    if(!tastierinoStruttura[5]->isEnabled()){
        abi_disab_TastieraStruttura(true);
        abi_disab_go_crea(false);
        abi_disab_radioType(true);
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
    abi_disab_radioType(false);
    QString testo_struttura = LineEditStrutturaTree->text();
    if(!testo_struttura.isEmpty() && binarytreebasic::controlla_stringa(testo_struttura.toStdString())){
        string std_testo_struttura = testo_struttura.toStdString();
        string::iterator start = std_testo_struttura.begin();
        int nNodi = binarytreebasic::n_nodes_stringa(start);
        progressBarStruttura->setMaximum(nNodi);

        abi_disab_TastieraStruttura(false);
        abi_disab_go_crea(true);
    }
    else{
        msgBox.setText("Stringa della struttura non corretta");
        msgBox.exec();
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
void mygui::slotComboTextEdit(){
    if(!(ComboListaTree1->size().isNull()) && !(ComboListaTree2->size().isNull())){
        string s=to_string(*(mappaTree[ComboListaTree1->currentText().toStdString()]));
        struttura_tree1->setText(QString::fromStdString(s));


        s=to_string(*(mappaTree[ComboListaTree2->currentText().toStdString()]));
        struttura_tree2->setText(QString::fromStdString(s));
    }
}
void mygui::slotGo(){
    if(radioType[0]->isChecked())
        creazioneNodiRaz();

    if(radioType[1]->isChecked())
        creazioneNodiBin();

    if(radioType[2]->isChecked())
        addWidgetTable();
}
void mygui::slotAggiornaCombo(){
    aggiornaComboBoxListaTree();
}
void mygui::slotCreazioneVet(){
    creazioneNodiVet();
}
void mygui::slotComboOperazioni(int){
    if(ComboListaOperazioni->currentIndex()==0 || ComboListaOperazioni->currentIndex()==1)
        add_rm_mol_div(false);
    else
        add_rm_mol_div(true);
}
void mygui::slotCalcola(){
    string nomeTree1 = ComboListaTree1->currentText().toStdString();
    binarytreebasic* a=mappaTree[nomeTree1], *c=0;
    binarytreesearch* a1=0, *c1=0;
    binarytree* a2=0, *c2=0;

    if(dynamic_cast<binarytreesearch*>(a))
        a1=dynamic_cast<binarytreesearch*>(a);
    else
        a2=dynamic_cast<binarytree*>(a);
    if(ComboListaOperazioni->currentIndex() == 0){   //somma
        string nomeTree2 = ComboListaTree2->currentText().toStdString();
        binarytreebasic* b=mappaTree[nomeTree2];
        binarytreesearch* b1=0;
        binarytree* b2=0;
        if(dynamic_cast<binarytreesearch*>(b))
            b1=dynamic_cast<binarytreesearch*>(b);
        else
            b2=dynamic_cast<binarytree*>(b);
        if(a1)
            c1=&((*a1)+(*b1));
        else
            c2=&((*a2)+(*b2));
    }
    else if(ComboListaOperazioni->currentIndex() == 1){   //differenza
        string nomeTree2 = ComboListaTree2->currentText().toStdString();
        binarytreebasic* b=mappaTree[nomeTree2];
        binarytreesearch* b1=0;
        binarytree* b2=0;
        if(dynamic_cast<binarytreesearch*>(b))
            b1=dynamic_cast<binarytreesearch*>(b);
        else
            b2=dynamic_cast<binarytree*>(b);
        if(a1)
            c1=&((*a1)-(*b1));
        else
            c2=&((*a2)-(*b2));
    }
    else if(ComboListaOperazioni->currentIndex() == 2){   //moltiplicazione
        int p=molt_div->text().toInt();
        if(a1)
            c1=&((*a1)*p);
        else
            c2=&((*a2)*p);
    }
    else{   //divisione
        int p=molt_div->text().toInt();
        if(a1)
            c1=&((*a1)/p);
        else
            c2=&((*a2)/p);
    }
    if(c1)
        c=c1;
    else
        c=c2;

    string nome_ris = "risAlbero" + mappaTree.size();
    mappaTree[nome_ris] = c;

    struttura_ris->setText(QString::fromStdString(to_string(*c)));
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

    connect(radioType[2], SIGNAL(toggled(bool)), this, SLOT(slotAggiornaCombo()));
    connect(radioType[1], SIGNAL(toggled(bool)), this, SLOT(slotAggiornaCombo()));
    connect(radioType[0], SIGNAL(toggled(bool)), this, SLOT(slotAggiornaCombo()));
    connect(ComboTree, SIGNAL(activated(int)), this, SLOT(slotComboTree()));
}
void mygui::connectComboOperazioniToSlot(){
    connect(ComboListaOperazioni, SIGNAL(activated(int)), this, SLOT(slotComboOperazioni(int)));
    connect(ComboListaTree1, SIGNAL(activated(int)), this, SLOT(slotComboTextEdit()));
    connect(ComboListaTree2, SIGNAL(activated(int)), this, SLOT(slotComboTextEdit()));
    connect(calcola, SIGNAL(clicked()), this, SLOT(slotCalcola()));
}
/*  ----------------------------------------------------    */
void mygui::creazioneNodiRaz(){
    QString text;
    double num; double den;

    text = LineEditNum->text(); text.remove( QChar( '.' ) );
    num = text.toDouble();

    text = LineEditDen->text(); text.remove( QChar( '.' ) );
    den = text.toDouble();

    if(den == 0)
        den = 1.0;

    vettoreTipo.push_back(new raz(num,den));
    LineEditNum->setText("");LineEditDen->setText("1");
    avanzaProgressBar();
    add_vet_raz_bin(text);
}
void mygui::creazioneNodiBin(){
    QString text; text = display->text(); text.remove( QChar( '.' ) );
    double val = text.toDouble();

    vettoreTipo.push_back(new bin(val));
    display->setText("1");
    avanzaProgressBar();
    add_vet_raz_bin(text);
}
void mygui::creazioneNodiVet(){
    QLineEdit* tmpLineEdit;
    int r=table->rowCount();
    int c=table->columnCount();
    int array[r*c];

    for(int i=0; i<r; ++i){
        for(int j=0; j<c; ++j){
            tmpLineEdit = qobject_cast<QLineEdit*>(table->cellWidget(i,j));
            if(tmpLineEdit)
               array[j+(i*c)] = tmpLineEdit->text().toInt();
        }
    }
    vettoreTipo.push_back(new vet(array,r,c));
    avanzaProgressBar();
    add_vet_raz_bin("");
}
void mygui::add_vet_raz_bin(QString text){
    if(progressBarStruttura->value() == progressBarStruttura->maximum()){
        if(!mainVLayout3)
            costruiciBox3();

        text = LineEditNomeTree->text();
        string nomeTree = text.toStdString();
        text = LineEditStrutturaTree->text();
        string strutturaTree = text.toStdString();

        if(ComboTree->currentText() == "Binary Tree")
            mappaTree[nomeTree] = new binarytree(vettoreTipo,strutturaTree);

        if(ComboTree->currentText() == "Binary Tree Search")
            mappaTree[nomeTree] = new binarytreesearch(vettoreTipo, strutturaTree);

        vettoreTipo.clear();
        aggiornaComboBoxListaTree();
        abi_disab_TastieraStruttura(true);
        abi_disab_go_crea(false);
        abi_disab_radioType(true);

        progressBarStruttura->setValue(0);
        LineEditNomeTree->setText("Albero" + QString::number(mappaTree.size()) );

        msgBox.setText("Hai completato la creazione dei nodi!\nAlbero creato");
        msgBox.exec();

    }
}

/*  BOX2    */
void mygui::costruiciBox2(){
    creaLayout2();
    addWidgetProgressBar();
}
void mygui::creaLayout2(){
    progressLayout = new QGridLayout();
    textEditLayout = new QGridLayout();
    mainVLayout2->addLayout(progressLayout);
    mainVLayout2->addLayout(textEditLayout);
}
void mygui::addWidgetProgressBar(){
    creaProgessBarStruttura();
    progressLayout->addWidget(labelProgessStruttura,0,0);
    progressLayout->addWidget(progressBarStruttura,0,1);

    label_struttura_tree1 = new QLabel("Struttura Albero 1:");
    label_struttura_tree2 = new QLabel("Struttura Albero 2:");

    struttura_tree1 = new QTextEdit();  struttura_tree1->setReadOnly(true);
    struttura_tree2 = new QTextEdit();  struttura_tree2->setReadOnly(true);

    textEditLayout->addWidget(label_struttura_tree1,0,0);
    textEditLayout->addWidget(struttura_tree1,1,0);
    textEditLayout->addWidget(label_struttura_tree2,2,0);
    textEditLayout->addWidget(struttura_tree2,3,0);
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
    addWidgetCalcola();
}
void mygui::creaLayout3(){
    mainVLayout3 = new QVBoxLayout();
    mainVLayout3->setContentsMargins(50,0,0,0);
    mainHLayout->addLayout(mainVLayout3);

    operaLayout = new QGridLayout();
    calcolaLayout = new QGridLayout();
    mainVLayout3->addLayout(operaLayout);
    mainVLayout3->addLayout(calcolaLayout);
}
void mygui::addWidgetOpera(){  
    ComboListaTree1 = new QComboBox();  ComboListaTree2 = new QComboBox(); ComboListaOperazioni = new QComboBox();
    ComboListaOperazioni->addItem("Somma");
    ComboListaOperazioni->addItem("Sottrazione");
    ComboListaOperazioni->addItem("Moltiplicazione");
    ComboListaOperazioni->addItem("Divisione");
    operaLayout->addWidget(ComboListaTree1,0,0);
    operaLayout->addWidget(ComboListaOperazioni,0,1);
    operaLayout->addWidget(ComboListaTree2,0,2);
}
void mygui::addWidgetCalcola(){
    calcola = new QPushButton("Calcola");
    calcolaLayout->addWidget(calcola);
    connectComboOperazioniToSlot();

    struttura_ris = new QTextEdit();
    calcolaLayout->addWidget(struttura_ris,1,0);
    struttura_ris->setReadOnly(true);
}

void mygui::add_rm_mol_div(bool flag){
    if(flag){
        if(!molt_div){
            operaLayout->removeWidget(ComboListaTree2);
            delete ComboListaTree2;
            ComboListaTree2 = 0;

            molt_div = new QLineEdit("1");
            molt_div->setAlignment(Qt::AlignRight);
            molt_div->setValidator(new QIntValidator());
            operaLayout->addWidget(molt_div,0,2);
        }
    }
    else{
        if(!ComboListaTree2){
            operaLayout->removeWidget(molt_div);
            delete molt_div;
            molt_div = 0;

            ComboListaTree2 = new QComboBox();
            aggiornaComboBoxListaTree();
            operaLayout->addWidget(ComboListaTree2,0,2);
        }
    }
}
void mygui::aggiornaComboBoxListaTree(){
    /* va fatto un cast per il tipo di albero e il tipo di nodo */
    if(mainVLayout3){
        ComboListaTree1->clear();
        ComboListaTree2->clear();
        if(ComboTree->currentText() == "Binary Tree"){
            for(std::map<string, binarytreebasic*>::iterator it=mappaTree.begin(); it!=mappaTree.end(); ++it){

                if( (dynamic_cast<binarytree*>((it->second))) && (radioType[0]->isChecked()) && (typeid(*((it->second)->tipo_tree())) == typeid(raz)) ){
                    ComboListaTree1->addItem(QString::fromStdString(it->first));
                    ComboListaTree2->addItem(QString::fromStdString(it->first));
                }
                if( (dynamic_cast<binarytree*>((it->second))) && (radioType[1]->isChecked()) && (typeid(*((it->second)->tipo_tree())) == typeid(bin)) ){
                    ComboListaTree1->addItem(QString::fromStdString(it->first));
                    ComboListaTree2->addItem(QString::fromStdString(it->first));
                }
                if( (dynamic_cast<binarytree*>((it->second))) && (radioType[2]->isChecked()) && (typeid(*((it->second)->tipo_tree())) == typeid(vet)) ){
                    ComboListaTree1->addItem(QString::fromStdString(it->first));
                    ComboListaTree2->addItem(QString::fromStdString(it->first));
                }
            }
        }
        if(ComboTree->currentText() == "Binary Tree Search"){
            for(std::map<string, binarytreebasic*>::iterator it=mappaTree.begin(); it!=mappaTree.end(); ++it){

                if( (dynamic_cast<binarytreesearch*>((it->second))) && (radioType[0]->isChecked()) && (typeid(*((it->second)->tipo_tree())) == typeid(raz)) ){
                    ComboListaTree1->addItem(QString::fromStdString(it->first));
                    ComboListaTree2->addItem(QString::fromStdString(it->first));
                }
                if( (dynamic_cast<binarytreesearch*>((it->second))) && (radioType[1]->isChecked()) && (typeid(*((it->second)->tipo_tree())) == typeid(bin)) ){
                    ComboListaTree1->addItem(QString::fromStdString(it->first));
                    ComboListaTree2->addItem(QString::fromStdString(it->first));
                }
                if( (dynamic_cast<binarytreesearch*>((it->second))) && (radioType[2]->isChecked()) && (typeid(*((it->second)->tipo_tree())) == typeid(vet)) ){
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
        for(unsigned int i=0; i<tastierinoStruttura.size(); ++i)
            tastierinoStruttura[i]->setEnabled(true);
    }
    else{
        for(unsigned int i=0; i<tastierinoStruttura.size(); ++i)
            tastierinoStruttura[i]->setDisabled(true);
    }
}
void mygui::abi_disab_go_crea(bool flag){
    if(flag)
        go->setEnabled(true);
    else
        go->setDisabled(true);
}
void mygui::abi_disab_radioType(bool flag){
    if(flag){
        for(unsigned int i=0; i<radioType.size(); ++i)
            radioType[i]->setEnabled(true);
    }
    else{
        for(unsigned int i=0; i<radioType.size(); ++i)
            radioType[i]->setDisabled(true);
    }

}
