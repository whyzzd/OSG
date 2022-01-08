#include "OsgContainer.h"
#include <QApplication>
#include <Windows.h>
#include <typeinfo>
#include <ctime>
#include <QInputEvent>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgGA/MultiTouchTrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgFX/Scribe>
#include <osg/Notify>
#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>
#include <osgEarth/Registry>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/Controls>
#include <osgEarthUtil/ExampleResources>
#include <osgEarthSymbology/Color>
#include "DrawXXX.h"
#include<qdebug.h>
#include"CPickHandler.h"
#include"MyConvert.h"
#include<osgEarthDrivers/tms/TMSOptions>
#include<osgEarthDrivers/gdal/GDALOptions>
#include<osgEarthDrivers/xyz/XYZOptions>
#include<osgEarthDrivers/tms/TMSOptions>
#include<osgEarth/Map>
#include"XYZExSource.h"
#include<osgEarthDrivers/feature_ogr/OGRFeatureOptions>
#include<osgEarthFeatures/FeatureModelLayer>


#include<osgEarthFeatures/Feature>
#include<osgEarthAnnotation/AnnotationNode>
#include<osgEarthAnnotation/FeatureNode>
#include<osgEarthAnnotation/FeatureEditing>
#include <osgEarthAnnotation/ImageOverlay>
#include <osgEarthAnnotation/CircleNode>
#include <osgEarthAnnotation/RectangleNode>
#include <osgEarthAnnotation/EllipseNode>
#include <osgEarthAnnotation/PlaceNode>
#include <osgEarthAnnotation/LabelNode>
#include <osgEarthAnnotation/LocalGeometryNode>
#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthAnnotation/ModelNode>
#include <osgEarthAnnotation/AnnotationEditing>
#include <osgEarthAnnotation/ImageOverlayEditor>
#include <osgEarthSymbology/GeometryFactory>

OsgContainer::OsgContainer(/*osg::ArgumentParser argument,*/ QWidget *parent)
	:QOpenGLWidget(parent)/*, osgViewer::Viewer(argument)*/
{

	//initEarth1();
	initEarth2();
	//initCowTest();
	setMouseTracking(true);
	setFocusPolicy(Qt::StrongFocus);
	
	//���ص�ͼ���߳�ע��
	mWorker = new Worker;
	mWorker->moveToThread(&workerThread);
	connect(&workerThread, &QThread::finished, mWorker, &QObject::deleteLater);
	connect(this, &OsgContainer::startWork, mWorker, &Worker::doWork);
	connect(mWorker, &Worker::resultReady, this, [&](osgEarth::ImageLayer*lay){
		m_netImageLayer = lay;
		std::cout << typeid(*lay).name() <<":"<<lay<< std::endl;
		m_pMap->addLayer(m_netImageLayer);
	});
	workerThread.start();
	
}

OsgContainer::~OsgContainer()
{
	workerThread.quit();
	workerThread.wait();
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

void OsgContainer::initEarth1()
{
	m_earthNode = osgDB::readNodeFile("gdal_multiple_files.earth");
	osg::Node*shp = osgDB::readNodeFile("D:\\OSGCore\\Build\\OpenSceneGraph-Data\\world.shp");
	//m_earthNode = osgDB::readNodeFile("zzz.earth");

	root = new osg::Group();
	root->addChild(m_earthNode);
	osg::ref_ptr<osgEarth::MapNode>map = dynamic_cast<osgEarth::MapNode*>(m_earthNode);
	root->addChild(m_earthNode);
	root->addChild(shp);
	setCamera(createCamera(0, 0, width(), height()));
	//���õ��������
	m_EM = new osgEarth::Util::EarthManipulator;
	m_EM->setNode(m_earthNode);
	setCameraManipulator(m_EM);


	mCPickHandler = new CPickHandler(this);//�������ظ�������
	addEventHandler(mCPickHandler);
	addEventHandler(new osgViewer::WindowSizeHandler());
	addEventHandler(new osgViewer::StatsHandler);
	addEventHandler(new osgGA::StateSetManipulator(this->getCamera()->getOrCreateStateSet()));

	setSceneData(root);
	startTimer(10);
}
void OsgContainer::initEarth2() 
{
	m_pMap = new osgEarth::Map;
	osgEarth::MapNode *mapNode = new osgEarth::MapNode(m_pMap);
	root = new osg::Group();
	root->addChild(mapNode);

	//ʹ��api���ر�������
	osgEarth::Drivers::GDALOptions imageLayerOpt;
	imageLayerOpt.url() = osgEarth::URI("D:\\OSGCore\\Build\\OpenSceneGraph-Data\\world.tif");
	std::string imageLayerName = "worldimage";
	osg::ref_ptr<osgEarth::ImageLayer>imageLayer = new osgEarth::ImageLayer(osgEarth::ImageLayerOptions(imageLayerName, imageLayerOpt));
	m_pMap->addLayer(imageLayer);
	
	//����ʹ��api���ر���shp(�ɻ�:Ϊɶ���ز�����?)
	/*osgEarth::Drivers::OGRFeatureOptions ogrData;
	ogrData.url() = "D:\\OSGCore\\Build\\OpenSceneGraph-Data\\world.shp";
	FeatureSourceLayerOptions ogrLayer;
	ogrLayer.name() = "vector-data";
	ogrLayer.featureSource() = ogrData;
	m_pMap->addLayer(new osgEarth::Features::FeatureSourceLayer(ogrData));*/
	

	//ʹ��api������������
	//osgEarth::Drivers::ArcGISOptions netImageLayerOpt;
	//netImageLayerOpt.url() = osgEarth::URI("https://map.geoq.cn/arcgis/rest/services/ChinaOnlineStreetWarm/MapServer");
	////netImageLayerOpt.url() = osgEarth::URI("http://services.arcgisonline.com/ArcGIS/rest/services/Reference/World_Boundaries_and_Places_Alternate/MapServer");
	//std::string netImageLayerName = "worldimage1";
	///*osg::ref_ptr<osgEarth::ImageLayer>*/netImageLayer = new osgEarth::ImageLayer(osgEarth::ImageLayerOptions(netImageLayerName, netImageLayerOpt));
	//m_pMap->addLayer(netImageLayer);

	//����xyz��ʽ�ļ�
	osgEarth::Drivers::XYZOptions tileOptions;
	//�ߵ�����
	//tileOptions.url() = osgEarth::URI("https://webst01.is.autonavi.com/appmaptile?style=6&x={x}&y={y}&z={z}");
	//�ߵ�·��
	//tileOptions.url() = osgEarth::URI("https://wprd01.is.autonavi.com/appmaptile?x={x}&y={y}&z={z}&lang=zh_cn&size=1&scl=2&style=8&ltype=11");
	
	/*tileOptions.url() = "http://[abc].tile.openstreetmap.org/{z}/{x}/{y}.png";
	tileOptions.profile()->namedProfile() = ("spherical-mercator");
	osgEarth::ImageLayerOptions options = osgEarth::ImageLayerOptions("debug", tileOptions);
	osg::ref_ptr<osgEarth::ImageLayer> layer = new osgEarth::ImageLayer(options);
	m_pMap->addLayer(layer);*/

	//mapbox�߳�ͼ(ֻ����ʾΪͼ��,�޷�ת��Ϊ�߳�)
	//osgEarth::Drivers::XYZOptions exyz;
	//exyz.url() = "http://api.mapbox.com/v4/mapbox.terrain-rgb/{z}/{x}/{y}.pngraw?access_token=pk.eyJ1IjoicXd1c2VyIiwiYSI6ImNreTN0YmhtZTAwdncyb2xtdWZ3ZWZodXEifQ.23yUvHmVWIQ8sRwy68EDlA";
	//exyz.profile()->namedProfile() = "spherical-mercator";
	///*XYZExSource *source = new XYZExSource(exyz);
	//auto estatus = source->open();*/
	//osgEarth::ImageLayerOptions options1 = osgEarth::ImageLayerOptions("mapboxEle", exyz);
	//m_pMap->addLayer(new osgEarth::ImageLayer(options1));
	

	//------------------------���Եڶ��ַ�ʽ��ͼ--------------------------------------
	/*const osgEarth::SpatialReference* mapSRS = mapNode->getMapSRS();
	osg::Group*geometryGroup = new osg::Group;
	osgEarth::Symbology::Style geomStyle;
	geomStyle.getOrCreate<osgEarth::LineSymbol>()->stroke()->color() = osgEarth::Symbology::Color::Cyan;
	geomStyle.getOrCreate<osgEarth::LineSymbol>()->stroke()->width() = 5.0f;
	geomStyle.getOrCreate<osgEarth::LineSymbol>()->tessellationSize() = 75000;
	geomStyle.getOrCreate<osgEarth::AltitudeSymbol>()->clamping() = osgEarth::AltitudeSymbol::CLAMP_TO_TERRAIN;
	geomStyle.getOrCreate<osgEarth::AltitudeSymbol>()->technique() = osgEarth::AltitudeSymbol::TECHNIQUE_DRAPE;

	osg::ref_ptr<osgEarth::Symbology::Polygon> polygon = new osgEarth::Symbology::Polygon();
	polygon->push_back(osg::Vec3d(0, 40, 0));
	polygon->push_back(osg::Vec3d(-60, 40, 0));
	polygon->push_back(osg::Vec3d(-60, 60, 0));
	polygon->push_back(osg::Vec3d(0, 60, 0));

	osg::ref_ptr<osgEarth::Features::Feature> feature = new osgEarth::Features::Feature(polygon, mapSRS);
	osg::ref_ptr<osgEarth::Annotation::FeatureNode> featureNode = new osgEarth::Annotation::FeatureNode(feature, geomStyle);
	geometryGroup->addChild(featureNode);
	osg::ref_ptr<osgEarth::Annotation::FeatureEditor> editor = new osgEarth::Annotation::FeatureEditor(featureNode);
	mapNode->addChild(editor);*/
	//-----------------------------------------------------------


	setCamera(createCamera(0, 0, width(), height()));
	//���õ��������
	m_EM = new osgEarth::Util::EarthManipulator;
	m_EM->setNode(mapNode);
	setCameraManipulator(m_EM);
	
	mCPickHandler = new CPickHandler(this);//�������ظ�������
	addEventHandler(mCPickHandler);
	addEventHandler(new osgViewer::WindowSizeHandler());
	addEventHandler(new osgViewer::StatsHandler);
	addEventHandler(new osgGA::StateSetManipulator(this->getCamera()->getOrCreateStateSet()));
	
	setSceneData(root);
	startTimer(10);	
}
void OsgContainer::initCowTest()
{
	m_earthNode = osgDB::readNodeFile("cow.osg"); 
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
	
	//root->addChild(m_earthNode);
	

	setCamera(createCamera(0, 0, width(), height()));

	osg::ref_ptr<osgGA::TrackballManipulator> manipulator = new osgGA::TrackballManipulator;
	setCameraManipulator(manipulator);
	//createSnow();
	//createFire();
	//createExplosion();
	//crateExplosionDebris();
	
	mCPickHandler = new CPickHandler(this);
	addEventHandler(mCPickHandler);//�Զ����������
	addEventHandler(new osgViewer::WindowSizeHandler());
	addEventHandler(new osgViewer::StatsHandler);
	addEventHandler(new osgGA::StateSetManipulator(getCamera()->getOrCreateStateSet()));
	setSceneData(root);
	
	/*DrawXXX sanjiao;
	root->addChild(sanjiao.createTrinangle());*/
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
bool OsgContainer::createSnow()
{

	mSnowNode = new osgParticle::PrecipitationEffect;

	//����ѩ����ɫ
	mSnowNode->setParticleColor(osg::Vec4(1, 1, 1, 1));
	mSnowNode->setUseFarLineSegments(true);
	//����ѩ������
	mSnowNode->setWind(osg::Vec3(2, 0, 0));

	// ����ѩ��Ũ��
	mSnowNode->snow(0.8);

	return root->addChild(mSnowNode);
	

}
bool OsgContainer::createRain()
{
	mRainNode = new osgParticle::PrecipitationEffect;

	// ������ɫ
	mRainNode->setParticleColor(osg::Vec4(1, 1, 1, 1));
	mRainNode->setUseFarLineSegments(true);
	// iLevel������һ��intֵ����ʾ��ļ���һ��1-10�͹�����
	mRainNode->setParticleSize(2 / 10.0);
	mRainNode->rain(1.0);
	return root->addChild(mRainNode);
}
void OsgContainer::createWu()
{
	mWuNode = new osg::Fog;
	mWuNode->setDensity(0.01);
	mWuNode->setColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	mWuNode->setMode(osg::Fog::LINEAR);  //osg::Fog::EXP  //osg::Fog::EXP2
	mWuNode->setStart(10);
	mWuNode->setEnd(50);
	root->getOrCreateStateSet()->setAttributeAndModes(mWuNode, osg::StateAttribute::ON);
	//root->addChild(mWuNode);

}
bool OsgContainer::createFire()
{
	MyConvert myc;
	osg::Vec3 lonLatAlt;
	lonLatAlt.x() = 110;
	lonLatAlt.y() = 30;
	lonLatAlt.z() = 900;
	osg::Vec3 vec =myc.LonLatAltToWorld(lonLatAlt);
	mFireNode = new osgParticle::FireEffect(osg::Vec3(vec.x(), vec.y(), vec.z()), 90);
	m_EM->setViewpoint(osgEarth::Viewpoint("�ӵ�", 110.0, 30.0, 900.0, 0.0, -90, 7e3));
	
	//mFireNode = new osgParticle::FireEffect(osg::Vec3(30, 30, 30), 90);
	//getEM()->setViewpoint(osgEarth::Viewpoint("�ӵ�", (, , 900, 0.0, -90, 7e3));
	return root->addChild(mFireNode);
}
bool OsgContainer::createBoom()
{
	MyConvert myc;
	osg::Vec3 lonLatAlt;
	lonLatAlt.x() = 110;
	lonLatAlt.y() = 30;
	lonLatAlt.z() = 900;
	osg::Vec3 vec = myc.LonLatAltToWorld(lonLatAlt);
	mBoomNode = new osgParticle::ExplosionEffect(osg::Vec3(vec.x(), vec.y(), vec.z()), 90);
	m_EM->setViewpoint(osgEarth::Viewpoint("�ӵ�", 110.0, 30.0, 900.0, 0.0, -90, 7e3));
	return root->addChild(mBoomNode);
}
//bool OsgContainer::crateExplosionDebris()
//{
//	mEDEBoomNode = new osgParticle::ExplosionDebrisEffect(osg::Vec3(30, 30, 30), 9);
//	return root->addChild(mEDEBoomNode);
//}

void OsgContainer::slotSnow(int state)
{
	if (!mHaveSnow)
	{
		if (!createSnow())
		{
			std::cout << "ѩ��Ч����ʧ��";
			return;
		}
		mHaveSnow = true;
	}
	else
	{
		if (state == 0)//ȡ��ѡ��
		{
			mSnowNode->setNodeMask(0);
			std::cout << "ȡ��ѡ�� ";
		}
		else if (state == 2)//ѡ��
		{
			mSnowNode->setNodeMask(1);
			std::cout << "ѡ�� ";
		}
	}
}
void OsgContainer::slotRain(int state)
{
	if (!mHaveRain)
	{
		if (!createRain())
		{
			std::cout << "����Ч����ʧ��";
			return;
		}
		mHaveRain = true;
	}
	else
	{
		if (state == 0)//ȡ��ѡ��
		{
			mRainNode->setNodeMask(0);
		}
		else if (state == 2)//ѡ��
		{
			mRainNode->setNodeMask(1);
		}
	}

}
void OsgContainer::slotWu(int state)
{
	if (!mHaveWu)
	{
		createWu();
		
		mHaveWu = true;
	}
	else
	{
		if (state == 0)//ȡ��ѡ��
		{
			root->getOrCreateStateSet()->setAttributeAndModes(mWuNode, osg::StateAttribute::OFF);
		}
		else if (state == 2)//ѡ��
		{
			root->getOrCreateStateSet()->setAttributeAndModes(mWuNode, osg::StateAttribute::ON);
		}
	}
	
}
void OsgContainer::slotFire(int state)
{
	if (!mHaveFire)
	{
		if (!createFire())
		{
			std::cout << "����Ч����ʧ��";
			return;
		}
		mHaveFire = true;
	}
	else
	{
		if (state == 0)//ȡ��ѡ��
		{
			mFireNode->setNodeMask(0);
		}
		else if (state == 2)//ѡ��
		{
			mFireNode->setNodeMask(1);
		}
	}
}
void OsgContainer::slotBoom(int state)
{
	if (!mHaveBoom)
	{
		if (!createBoom())
		{
			std::cout << "��ը��Ч����ʧ��";
			return;
		}
		mHaveBoom = true;
	}
	else
	{
		if (state == 0)//ȡ��ѡ��
		{
			root->removeChild(mBoomNode);
			mHaveBoom = false;
		}
	}
}

void OsgContainer::slotAddNetArcgis()
{
	//�ж��Ƿ�����������
	if (m_netIsOpen)
	{
		return;
	}
	m_netIsOpen = true;	
	emit startWork();
	

	//���´���,�����Կ���ʹ��
	//m_pMap->addLayer(m_netImageLayer);
	//osgEarth::Drivers::ArcGISOptions netImageLayerOpt;
	////netImageLayerOpt.url() = osgEarth::URI("https://map.geoq.cn/arcgis/rest/services/ChinaOnlineStreetWarm/MapServer");
	//netImageLayerOpt.url() = osgEarth::URI("http://services.arcgisonline.com/ArcGIS/rest/services/Reference/World_Boundaries_and_Places_Alternate/MapServer");
	//std::string netImageLayerName = "worldimage1";
	///*osg::ref_ptr<osgEarth::ImageLayer>*/netImageLayer = new osgEarth::ImageLayer(osgEarth::ImageLayerOptions(netImageLayerName, netImageLayerOpt));
	//m_pMap->addLayer(netImageLayer);
}
void OsgContainer::slotRemvNetArcgis()
{
	if (!m_netIsOpen)
	{
		return;
	}
	m_netIsOpen = false;
	if (m_netImageLayer)
	{ 
		m_pMap->removeLayer(m_netImageLayer);
	}

	//���´��뾭���Կ���ʹ��
	//m_pMap->removeLayer(netImageLayer);
}