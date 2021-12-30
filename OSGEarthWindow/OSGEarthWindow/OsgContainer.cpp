#include "OsgContainer.h"
#include <QInputEvent>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgGA/MultiTouchTrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <QApplication>

#include <Windows.h>
#include <typeinfo>
#include <osgFX/Scribe>
#include <osg/Notify>
#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>
#include <osgEarth/Registry>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/Controls>
#include <osgEarthUtil/ExampleResources>
#include <osgEarthSymbology/Color>
#include<ctime>
#include <osgParticle/PrecipitationEffect>
#include <osgParticle/FireEffect>
#include<osgParticle/ExplosionEffect>
#include<osgParticle/ExplosionDebrisEffect>
//#include<osgEarthUtil/Ephemeris>
//#include<osgEarthUtil/Sky>

#include<qdebug.h>
#include"CPickHandler.h"
OsgContainer::OsgContainer(/*osg::ArgumentParser argument,*/ QWidget *parent)
	:QOpenGLWidget(parent)/*, osgViewer::Viewer(argument)*/
{
	init3D();
	//initCowTest();
	setMouseTracking(true);
	setFocusPolicy(Qt::StrongFocus);
	
}

OsgContainer::~OsgContainer()
{
}

bool OsgContainer::event(QEvent *event) {
	switch (event->type()) {
	case QEvent::TouchBegin:
	case QEvent::TouchEnd:
	case QEvent::TouchUpdate: {
		QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
		unsigned int id = 0;
		unsigned int tapCount = touchPoints.size();

		osg::ref_ptr<osgGA::GUIEventAdapter> osgEvent(NULL);
		osgGA::GUIEventAdapter::TouchPhase phase = osgGA::GUIEventAdapter::TOUCH_UNKNOWN;
		foreach(const QTouchEvent::TouchPoint &touchPoint, touchPoints) {
			if (!osgEvent) {
				if (event->type() == QEvent::TouchBegin) {
					phase = osgGA::GUIEventAdapter::TOUCH_BEGAN;
					osgEvent = window->getEventQueue()->touchBegan(id, osgGA::GUIEventAdapter::TOUCH_BEGAN, touchPoint.pos().x(), touchPoint.pos().y());
				}
				else if (event->type() == QEvent::TouchEnd) {
					phase = osgGA::GUIEventAdapter::TOUCH_ENDED;
					osgEvent = window->getEventQueue()->touchEnded(id, osgGA::GUIEventAdapter::TOUCH_ENDED, touchPoint.pos().x(), touchPoint.pos().y(), tapCount);
				}
				else if (event->type() == QEvent::TouchUpdate) {
					phase = osgGA::GUIEventAdapter::TOUCH_MOVED;
					osgEvent = window->getEventQueue()->touchMoved(id, osgGA::GUIEventAdapter::TOUCH_MOVED, touchPoint.pos().x(), touchPoint.pos().y());
				}
			}
			else {
				osgEvent->addTouchPoint(id, osgGA::GUIEventAdapter::TOUCH_ENDED, touchPoint.pos().x(), touchPoint.pos().y());
				osgEvent->addTouchPoint(id, phase, touchPoint.pos().x(), touchPoint.pos().y());
			}
			id++;
		}
		break;
	}
	default:
		break;
	}
	return QOpenGLWidget::event(event);
}
void OsgContainer::setKeyboardModifiers(QInputEvent *event) {
	int modkey = event->modifiers() & (Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier);
	unsigned int mask = 0;
	if (modkey & Qt::ShiftModifier) {
		mask |= osgGA::GUIEventAdapter::MODKEY_SHIFT;
	}
	if (modkey & Qt::ControlModifier) {
		mask |= osgGA::GUIEventAdapter::MODKEY_CTRL;
	}
	if (modkey & Qt::AltModifier) {
		mask |= osgGA::GUIEventAdapter::MODKEY_ALT;
	}

	window->getEventQueue()->getCurrentEventState()->setModKeyMask(mask);
	
	update();
}
void OsgContainer::keyPressEvent(QKeyEvent *event) {
	setKeyboardModifiers(event);
	window->getEventQueue()->keyPress(event->key());
	
	if (event->key() == Qt::Key_H)
	{

		qDebug() << "H��";
		return;
	}
	
	QOpenGLWidget::keyPressEvent(event);
	update();
}
void OsgContainer::keyReleaseEvent(QKeyEvent *event) {
	setKeyboardModifiers(event);
	window->getEventQueue()->keyRelease(event->key());
	QOpenGLWidget::keyReleaseEvent(event);
	update();
}
void OsgContainer::mousePressEvent(QMouseEvent *event) {
	int button = 0;
	switch (event->button()) {
	case Qt::LeftButton:
		{
			button = 1; 
			/*this->getSceneData()->asGroup()->getChild(0)->setNodeMask(1);
			this->getSceneData()->asGroup()->getChild(1)->setNodeMask(1);
			qDebug() << button;*/
			Pick(event->x(), event->y());
			break; 

		}
	case Qt::MidButton: button = 2; break;
	case Qt::RightButton:
		{ 
			button = 3;
			/*this->getSceneData()->asGroup()->getChild(0)->setNodeMask(0); 
			this->getSceneData()->asGroup()->getChild(1)->setNodeMask(1);
			qDebug() << button;*/
			break;
		}
	case Qt::NoButton: button = 0; break;
	default: button = 0; break;
	}
	setKeyboardModifiers(event);
	window->getEventQueue()->mouseButtonPress(event->x(), event->y(), button);
	update();
}
void OsgContainer::mouseReleaseEvent(QMouseEvent *event) {
	int button = 0;
	switch (event->button()) {
	case Qt::LeftButton: button = 1; break;
	case Qt::MidButton: button = 2; break;
	case Qt::RightButton: button = 3; break;
	case Qt::NoButton: button = 0; break;
	default: button = 0; break;
	}
	setKeyboardModifiers(event);
	window->getEventQueue()->mouseButtonRelease(event->x(), event->y(), button);

	QOpenGLWidget::mouseReleaseEvent(event);
	update();
}
void OsgContainer::mouseDoubleClickEvent(QMouseEvent *event) {
	int button = 0;
	switch (event->button()) {
	case Qt::LeftButton: button = 1; break;
	case Qt::MidButton: button = 2; break;
	case Qt::RightButton: button = 3; break;
	case Qt::NoButton: button = 0; break;
	default: button = 0; break;
	}
	setKeyboardModifiers(event);
	window->getEventQueue()->mouseDoubleButtonPress(event->x(), event->y(), button);

	QOpenGLWidget::mouseDoubleClickEvent(event);
	update();
}
void OsgContainer::mouseMoveEvent(QMouseEvent *event) {
	setKeyboardModifiers(event);
	window->getEventQueue()->mouseMotion(event->x(), event->y());
	QOpenGLWidget::mouseMoveEvent(event);
	update();
}
void OsgContainer::wheelEvent(QWheelEvent *event) {
	setKeyboardModifiers(event);
	window->getEventQueue()->mouseScroll(
		event->orientation() == Qt::Vertical ?
		(event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN) :
		(event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_LEFT : osgGA::GUIEventAdapter::SCROLL_RIGHT));
	QOpenGLWidget::wheelEvent(event);
	update();
}
void OsgContainer::resizeEvent(QResizeEvent *event) {
	const QSize &size = event->size();
	window->resized(x(), y(), size.width(), size.height());
	window->getEventQueue()->windowResize(x(), y(), size.width(), size.height());
	window->requestRedraw();

	QOpenGLWidget::resizeEvent(event);
}
void OsgContainer::moveEvent(QMoveEvent *event) {
	const QPoint &pos = event->pos();
	window->resized(pos.x(), pos.y(), width(), height());
	window->getEventQueue()->windowResize(pos.x(), pos.y(), width(), height());

	QOpenGLWidget::moveEvent(event);
}
void OsgContainer::timerEvent(QTimerEvent *) {
	update();
}
void OsgContainer::paintGL() {
	if (isVisibleTo(QApplication::activeWindow())) {
		frame();
	}
	
}
void OsgContainer::Pick(float x, float y)
{
	// ����һ���ཻ���ԵĽ�������ж���Ļ�볡���ཻ�󣬵ó��Ľ�����������
	osgUtil::LineSegmentIntersector::Intersections intersections;
	if (computeIntersections(x, y, intersections)) {
		int n = 1;
		// ����һ��������������������ý����
		for (osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin(); hitr != intersections.end(); ++hitr) {

			// ע������ȡ���� back()
			if (!hitr->nodePath.empty() && !(hitr->nodePath.back()->getName().empty())) {

				// �õ��������е� nodepath���Դ˿����жϸ� path ���Ƿ�����Ҫ�Ľ��
				const osg::NodePath &np = hitr->nodePath;
				// ����������������Ҫ�Ľ�㣬���������ظý��
				// ������һ����̬ת�����������ת���ɹ�����ֵ��Ϊ NULL������Ϊ NULL��
				for (int i = np.size() - 1; i >= 0; --i) {

					// ���һ�� scribe ��㣬�ý���µ�ģ�ͻᱻ�Ӱ����߸�����ʾ
					osgFX::Scribe *sc = dynamic_cast<osgFX::Scribe *>(np[i]);
					if (sc != NULL) {

						if (sc->getNodeMask() != 0)
							sc->setNodeMask(0);
						
					}
				}
				
			}
			//qDebug() << x << y<<n++;;
			
		}
	}
	
}

void OsgContainer::init3D() {

	m_earthNode = osgDB::readNodeFile("gdal_multiple_files.earth");
	//osg::Node *cow = osgDB::readNodeFile("cow.osg");
	
	if (!m_earthNode)
	{
		return;
	}
	root = new osg::Group();
	
	//root->addChild(m_earthNode);
	osg::ref_ptr<osgEarth::MapNode>map = dynamic_cast<osgEarth::MapNode*>(m_earthNode);
	
	root->addChild(map);
	
	setCamera(createCamera(0, 0, width(), height()));
	//���õ��������
	em = new osgEarth::Util::EarthManipulator;
	em->setNode(map);
	setCameraManipulator(em);
	

	//�ڵ�����滭��
	/*osg::Vec3d start(116.1, 40.1, 900);
	osg::Vec3d end(116.3, 40.3, 900);
	root->addChild(createLine(start, end));
	em->setHomeViewpoint(osgEarth::Viewpoint("�ӵ�", 116.2, 40.2, 900, 0.0, -90, 7e3));*/

	/*osg::ref_ptr<osgGA::TrackballManipulator> manipulator = new osgGA::TrackballManipulator;
	setCameraManipulator(manipulator);*/
	

	createSnow();
	addEventHandler(new CPickHandler(this));
	addEventHandler(new osgViewer::WindowSizeHandler());
	addEventHandler(new osgViewer::StatsHandler);
	addEventHandler(new osgGA::StateSetManipulator(this->getCamera()->getOrCreateStateSet()));
	setSceneData(root);
	
	//setRunFrameScheme(ON_DEMAND);
	//initSky();
	
	startTimer(10);
	
}
void OsgContainer::initCowTest()
{
	m_earthNode = osgDB::readNodeFile("glider.osg"); 
	//osg::Node*axe = osgDB::readNodeFile("axes.osgt");
	
	if (!m_earthNode)
	{
		return;
	}
	root = new osg::Group();
	//root->addChild(axe);
	//ƽ�Ʋ���
	/*osg::ref_ptr<osg::MatrixTransform>trans = new osg::MatrixTransform();
	trans->setMatrix(osg::Matrix::translate(0, 0, 20));
	trans->addChild(m_earthNode);
	root->addChild(trans);*/

	//���Ų���+ƽ��
	/*osg::ref_ptr<osg::MatrixTransform>trans = new osg::MatrixTransform();
	trans->setMatrix(osg::Matrix::scale(0.5, 0.5, 0.5)*osg::Matrix::translate(-10, 0, 0));
	trans->addChild(m_earthNode);
	root->addChild(trans);*/

	//��ת����
	//osg::ref_ptr<osg::MatrixTransform>trans = new osg::MatrixTransform();
	//trans->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(90.0),1,0,0));//�ֱ��������x,y,z����ת,��������ʱ��
	//trans->addChild(m_earthNode);
	//root->addChild(trans);

	//��Ӱױ�
	/*osg::ref_ptr<osgFX::Scribe>sc = new osgFX::Scribe;
	sc->addChild(m_earthNode);
	root->addChild(sc);*/
	
	root->addChild(m_earthNode);
	
	setCamera(createCamera(0, 0, width(), height()));

	osg::ref_ptr<osgGA::TrackballManipulator> manipulator = new osgGA::TrackballManipulator;
	setCameraManipulator(manipulator);
	//createSnow();
	//createFire();
	//createExplosion();
	//crateExplosionDebris();
	
	//addEventHandler(new CPickHandler(this));//�Զ����������
	addEventHandler(new osgViewer::WindowSizeHandler());
	this->addEventHandler(new osgViewer::StatsHandler);
	addEventHandler(new osgGA::StateSetManipulator(getCamera()->getOrCreateStateSet()));
	setSceneData(root);
	
	startTimer(10);
}

void OsgContainer::initSky()
{

	osgEarth::MapNode* mapNode = osgEarth::MapNode::findMapNode(m_earthNode);
	if (!mapNode)
	{
		OE_NOTICE << "Could not find MapNode" << std::endl;
		return;
	}

	// ����ʱ��;
	osgEarth::DateTime dateTime(2019, 5, 8, 9);
	osgEarth::Util::Ephemeris* ephemeris = new osgEarth::Util::Ephemeris;

	osgEarth::Util::SkyNode* m_pSkyNode = osgEarth::Util::SkyNode::create(mapNode);
	m_pSkyNode->setName("SkyNode");
	m_pSkyNode->setEphemeris(ephemeris);
	m_pSkyNode->setDateTime(dateTime);
	m_pSkyNode->attach(this, 0);
	m_pSkyNode->setLighting(true);
	m_pSkyNode->addChild(mapNode);
	root->addChild(m_pSkyNode);
}
osg::ref_ptr<osg::Camera> OsgContainer::createCamera(int x, int y, int w, int h) {
	window = new osgViewer::GraphicsWindowEmbedded(x, y, w, h);
	//    osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->windowDecoration = true;
	traits->x = x;
	traits->y = y;
	traits->width = w;
	traits->height = h;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;

	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setGraphicsContext(window);
	camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
	camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera->setProjectionMatrixAsPerspective(
		30.0f, double(traits->width) / double(traits->height), 1.0f, 10000.0f);
	camera->setClearColor(osg::Vec4(0.3, 0.3, 0.6, 0.1));

	return camera.release();
}
//��ѩ
void OsgContainer::createSnow()
{

	osg::ref_ptr<osgParticle::PrecipitationEffect> sn = new osgParticle::PrecipitationEffect;

	//����ѩ����ɫ
	sn->setParticleColor(osg::Vec4(1, 1, 1, 1));
	sn->setUseFarLineSegments(true);
	//����ѩ������
	sn->setWind(osg::Vec3(2, 0, 0));

	// ����ѩ��Ũ��
	sn->snow(0.8);

	root->addChild(sn);
	
	//this->realize();
	//this->run();
}
void OsgContainer::createFire()
{
	osg::ref_ptr<osgParticle::FireEffect> fe = new osgParticle::FireEffect(osg::Vec3(30, 30, 30), 90);
	root->addChild(fe);
}
void OsgContainer::createExplosion()
{
	osg::ref_ptr<osgParticle::ExplosionEffect> ee = new osgParticle::ExplosionEffect(osg::Vec3(30, 30, 30), 90);
	root->addChild(ee);
}
void OsgContainer::crateExplosionDebris()
{
	osg::ref_ptr<osgParticle::ExplosionDebrisEffect> ede = new osgParticle::ExplosionDebrisEffect(osg::Vec3(30, 30, 30), 9);
	root->addChild(ede);

}

void OsgContainer::slotSnow(int state)
{
	std::cout << "snow!!!!!!";
}
void OsgContainer::slotRain(int state)
{

}
void OsgContainer::slotWu(int state)
{
}
void OsgContainer::slotFire(int state)
{

}
void OsgContainer::slotBoom(int state)
{

}