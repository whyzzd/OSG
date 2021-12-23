#include "QWidgetImage.h"

#include <QLayout>

namespace osgQt
{
	QWidgetImage::QWidgetImage( QWidget* widget )
	{
		// make sure we have a valid QApplication before we start creating widgets.
		getOrCreateQApplication();

		_widget = widget;
		_adapter = new QGraphicsViewAdapter(this, _widget.data());
	}

	QWidgetImage::~QWidgetImage(void)
	{
	}


	bool QWidgetImage::sendFocusHint(bool focus)
	{
		QFocusEvent event(focus ? QEvent::FocusIn : QEvent::FocusOut, Qt::OtherFocusReason);
		QCoreApplication::sendEvent(_widget, &event);
		return true;
	}

	void QWidgetImage::clearWriteBuffer()
	{
		_adapter->clearWriteBuffer();
	}

	void QWidgetImage::render()
	{
		if (_adapter->requiresRendering()) _adapter->render();
	}

	void QWidgetImage::scaleImage(int s,int t,int /*r*/, GLenum /*newDataType*/)
	{
		_adapter->resize(s, t);
	}

	void QWidgetImage::setFrameLastRendered(const osg::FrameStamp* frameStamp)
	{
		_adapter->setFrameLastRendered(frameStamp);
	}

	bool QWidgetImage::sendPointerEvent(int x, int y, int buttonMask)
	{
		return _adapter->sendPointerEvent(x,y,buttonMask);
	}

	bool QWidgetImage::sendKeyEvent(int key, bool keyDown)
	{
		return _adapter->sendKeyEvent(key, keyDown);
	}



}


