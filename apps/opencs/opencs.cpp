#include "opencs.hpp"
#include "ui_opencs.h"

#include <QDebug>
#include <QProcessEnvironment>

#include <QFileDialog>
#include <QDockWidget>

#include <QUndoView>

#include "model/modelitem.hpp"

#include "viewmodel/esmdatamodel.hpp"


#include "view/filter/filtertree.hpp"
#include "view/filter/filtereditor.hpp"

OpenCS::OpenCS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OpenCS)
{
    ui->setupUi(this);

    mRootItem = new ModelItem();

    setDockOptions(QMainWindow::AllowNestedDocks | QMainWindow::AllowTabbedDocks);
    setCentralWidget(NULL);

    connect(ui->actionOpen,SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionAddIdList, SIGNAL(triggered()), this, SLOT(addIdList()));

    model = new ESMDataModel(this);


    FilterEditModel *filterModel = new FilterEditModel(mRootItem, this);



    //TODO Refactor the Copy-Pastes below

    QDockWidget *idListDock = new QDockWidget("ID List", this);
    idListDock->setFeatures(QDockWidget::AllDockWidgetFeatures);

    idList = new IdList(this);
    idList->setModel(model);
    idList->setFilterModel(filterModel);
    idListDock->setWidget(idList);

    this->addDockWidget(Qt::RightDockWidgetArea, idListDock);

    //TODO Copy paste
    QDockWidget *filterTreeDock = new QDockWidget("Filter Tree", this);
    filterTreeDock->setFeatures(QDockWidget::AllDockWidgetFeatures);

    FilterTree *filterTree = new FilterTree(filterTreeDock);
    filterTree->setModel(filterModel);
    filterTreeDock->setWidget(filterTree);

    this->addDockWidget(Qt::LeftDockWidgetArea, filterTreeDock);

    //TODO Copy paste
    QDockWidget *filterEditDock = new QDockWidget("Filter Editor", this);
    filterEditDock->setFeatures(QDockWidget::AllDockWidgetFeatures);

    FilterEditor *filterEditor = new FilterEditor(filterEditDock);
    filterEditor->setModel(filterModel);
    filterEditDock->setWidget(filterEditor);

    this->addDockWidget(Qt::LeftDockWidgetArea, filterEditDock);


    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    if(env.contains("OPENCS_DEBUG_GUI")) {

        //TODO Copy paste
        QDockWidget *undoRedoDock = new QDockWidget("Undo/Redo", this);
        undoRedoDock->setFeatures(QDockWidget::AllDockWidgetFeatures);

        QUndoView *undoView = new QUndoView(undoRedoDock);
        undoView->setStack(filterModel->undoStack());
        undoRedoDock->setWidget(undoView);

        this->addDockWidget(Qt::LeftDockWidgetArea, undoRedoDock);

        //TODO Copy paste
        QDockWidget *ItemModelWidget = new QDockWidget("ItemModel", this);
        ItemModelWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);

        QTreeView *itemModelTreeView = new QTreeView(this);
        itemModelTreeView->setModel(filterModel);
        itemModelTreeView->resizeColumnToContents(0);
        ItemModelWidget->setWidget(itemModelTreeView);
        this->addDockWidget(Qt::BottomDockWidgetArea, ItemModelWidget);
    }

    connect(filterTree, SIGNAL(indexSelected(QModelIndex)), filterEditor, SLOT(setCurrentModelIndex(QModelIndex)));
}

OpenCS::~OpenCS()
{
    delete ui;
    delete mRootItem;
}

void OpenCS::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Esm"), "", tr("Esm Files (*.esm)"));
    if (!fileName.isEmpty())
    {
        model->loadEsmFile(fileName);

        idList->loadColumnConfig();
    }
}

void OpenCS::addIdList()
{
//    IdList *idList = new IdList(this);
//    idList->setModel(model);
//    this->addDockWidget(Qt::RightDockWidgetArea, idList);
}