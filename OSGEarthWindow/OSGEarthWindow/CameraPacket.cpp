#include"CameraPacket.h"
void CameraPacket::readEventQueue(osgViewer::Viewer& viewer)
{
	_events.clear();

	osgViewer::ViewerBase::Contexts contexts;
	viewer.getContexts(contexts);
	
	for (osgViewer::ViewerBase::Contexts::iterator citr = contexts.begin(); citr != contexts.end(); ++citr)
	{
		osgGA::EventQueue::Events gw_events;

		osgViewer::GraphicsWindow* gw = dynamic_cast<osgViewer::GraphicsWindow*>(*citr);
		if (gw)
		{
			gw->checkEvents();
			gw->getEventQueue()->copyEvents(gw_events);
		
		}
		_events.insert(_events.end(), gw_events.begin(), gw_events.end());
	}

	viewer.getEventQueue()->copyEvents(_events);

	osg::notify(osg::INFO) << "written events = " << _events.size() << std::endl;
}

void CameraPacket::writeEventQueue(osgViewer::Viewer& viewer)
{
	osg::notify(osg::INFO) << "received events = " << _events.size() << std::endl;
	
	viewer.getEventQueue()->appendEvents(_events);
	
}