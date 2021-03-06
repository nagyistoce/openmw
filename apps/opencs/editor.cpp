
#include "editor.hpp"

#include <sstream>

#include <QtGui/QApplication>

#include "model/doc/document.hpp"
#include "model/world/data.hpp"

CS::Editor::Editor() : mViewManager (mDocumentManager), mNewDocumentIndex (0)
{
    connect (&mViewManager, SIGNAL (newDocumentRequest ()), this, SLOT (createDocument ()));
    connect (&mViewManager, SIGNAL (loadDocumentRequest ()), this, SLOT (loadDocument ()));

    connect (&mStartup, SIGNAL (createDocument()), this, SLOT (createDocument ()));
    connect (&mStartup, SIGNAL (loadDocument()), this, SLOT (loadDocument ()));

    connect (&mOpenDialog, SIGNAL(accepted()), this, SLOT(openFiles()));
}

void CS::Editor::createDocument()
{
    mStartup.hide();

    /// \todo open the ESX picker instead

    std::ostringstream stream;

    stream << "NewDocument" << (++mNewDocumentIndex);

    std::vector<boost::filesystem::path> files;
    files.push_back (stream.str());

    CSMDoc::Document *document = mDocumentManager.addDocument (files, true);

    mViewManager.addView (document);
}

void CS::Editor::loadDocument()
{
    mStartup.hide();
    mOpenDialog.show();
    mOpenDialog.raise();
    mOpenDialog.activateWindow();
}

void CS::Editor::openFiles()
{
    std::vector<boost::filesystem::path> paths;
    mOpenDialog.getFileList(paths);
    CSMDoc::Document *document = mDocumentManager.addDocument(paths, false);

    mViewManager.addView (document);
}

int CS::Editor::run()
{
    mStartup.show();

    return QApplication::exec();
}