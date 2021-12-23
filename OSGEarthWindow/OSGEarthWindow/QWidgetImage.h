#pragma once

#ifndef QWIDGETIMAGE_H
#define QWIDGETIMAGE_H

#include "QGraphicsViewAdapter.h"
#include <osg/Image>


namespace osgQt
{
	class QWidgetImage : public osg::Image
	{
	public:
		QWidgetImage( QWidget* widget=0 );
		~QWidgetImage(void);

		QWidget* getQWidget() { return _widget; }
		QGraphicsViewAdapter* getQGraphicsViewAdapter() { return _adapter; }

		virtual bool requiresUpdateCall() const { return true; }
		virtual void update( osg::NodeVisitor* /*nv*/ ) { render(); }

		void clearWriteBuffer();

		void render();


		/// Overridden scaleImage used to catch cases where the image is
		/// fullscreen and the window is resized.
		virtual void scaleImage(int s,int t,int r, GLenum newDataType);

		virtual bool sendFocusHint(bool focus);

		virtual bool sendPointerEvent(int x, int y, int buttonMask);

		virtual bool sendKeyEvent(int key, bool keyDown);

		virtual void setFrameLastRendered(const osg::FrameStamp* frameStamp);

	protected:

		QPointer<QGraphicsViewAdapter>  _adapter;
		QPointer<QWidget>               _widget;
	};
}








#endif