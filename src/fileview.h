/*
	Author: Marco Costalba (C) 2005-2006

	Copyright: See COPYING file that comes with this distribution

*/
#ifndef FILEVIEW_H
#define FILEVIEW_H

#include <qpointer.h>
#include "ui_fileview.h" // needed by moc_* file to understand tab() function
#include "common.h"
#include "domain.h"

class Q3ListViewItem;
class ListView;
class FileContent;
class MainImpl;
class Git;
class TabFile;
class FileHistory;

class FileView: public Domain {
Q_OBJECT
public:
	FileView() {}
	FileView(MainImpl* m, Git* git);
	~FileView();
	void append(SCRef data);
	void clear(bool complete = true);
	void historyReady();
	void updateHistViewer(SCRef revSha, SCRef fileName, bool fromUpstream = true);
	void eof();
	Ui_TabFile* tab() { return fileTab; }

public slots:
	void on_toolButtonCopy_clicked();
	void on_toolButtonShowAnnotate_toggled(bool);
	void on_toolButtonFindAnnotate_toggled(bool);
	void on_toolButtonRangeFilter_toggled(bool);
	void on_toolButtonPin_toggled(bool);
	void on_toolButtonHighlightText_toggled(bool);
	void on_spinBoxRevision_valueChanged(int);
	void on_loadCompleted(const FileHistory*, const QString&);
	void on_annotationAvailable(bool);
	void on_fileAvailable(bool);
	void on_revIdSelected(int);

protected:
	virtual bool event(QEvent* e);
	virtual bool doUpdate(bool force);

private:
	friend class MainImpl;
	friend class FileHighlighter;

	void showAnnotation();
	bool goToCurrentAnnotation();
	void updateProgressBar(int annotatedNum);
	void filterOnRange(bool b);
	void updateSpinBoxValue();
	void updateEnabledButtons();

	Ui_TabFile* fileTab;
	ListView* histListView;
	FileContent* textEditFile;
	FileHistory* fh;
	bool annotateAvailable;
	bool fileAvailable;
};

#endif