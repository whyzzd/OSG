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
#include<osgGA/GUIEventAdapter>
#include <osgViewer/Viewer>
#include <osgEarth/Registry>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/Controls>
#include <osgEarthUtil/ExampleResources>
#include <osgEarthSymbology/Color>
#include<osgEarthSymbology/AltitudeSymbol>
#include "DrawXXX.h"
#include<qdebug.h>
#include"CPickHandler.h"
#include"MyConvert.h"
#include<osgEarthDrivers/tms/TMSOptions>
#include<osgEarthDrivers/gdal/GDALOptions>
#include<osgEarthDrivers/xyz/XYZOptions>
#include<osgEarthDrivers/tms/TMSOptions>
#include<osgEarthDrivers/agglite/AGGLiteOptions>
#include<osgEarthDrivers/engine_rex/RexTerrainEngineOptions>
#include<osgEarth/Map>
#include<osgEarthDrivers/feature_ogr/OGRFeatureOptions>
#include<osgEarthFeatures/FeatureModelLayer>
#include <osgEarth/GLUtils>
#include<osgUtil/Optimizer>
#include<osgEarthDrivers/cache_filesystem/FileSystemCache>

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
#include<osg/ImageStream>


OsgContainer::OsgContainer(osg::ArgumentParser argument, QWidget *parent)
	:QOpenGLWidget(parent),mViewerMode(STAND_ALONE)
{
	while (argument.read("-m"))mViewerMode = MASTER;
	while (argument.read("-s")) mViewerMode = SLAVE;
	while (argument.read("-d"))mViewerMode = SLAVE1;
	initInteraction();
	//initEarth1();
	initEarth2();
	//initCowTest();
	setMouseTracking(true);
	setFocusPolicy(Qt::StrongFocus);
	
	//加载地图多线程注册
	mWorker = new Worker;
	mWorker->moveToThread(&workerThread);
	connect(&workerThread, &QThread::finished, mWorker, &QObject::deleteLater);
	connect(this, &OsgContainer::startWork, mWorker, &Worker::doWork);
	connect(mWorker, &Worker::resultReady, this, [&](osgEarth::ImageLayer*lay){
		m_netImageLayer = lay;
		//std::cout << typeid(*lay).name() <<":"<<lay<< std::endl;
		m_pMap->addLayer(m_netImageLayer);
	});
	workerThread.start();
	
	m_contextMenu = new QMenu;
	m_undoAction = new QAction("撤销", this);
	m_redoAction = new QAction("重做", this);
	m_delAction = new QAction("删除", this);
	m_contextMenu->addAction(m_undoAction);
	m_contextMenu->addAction(m_redoAction);
	m_contextMenu->addAction(m_delAction);
	m_undoStack = new QUndoStack(this);
	
	//connect(this->m_undoAction, &QAction::triggered, mCPickHandler, &CPickHandler::slotActionUndo);
	//connect(this->m_redoAction, &QAction::triggered, mCPickHandler, &CPickHandler::slotActionRedo);
	//connect(this->m_delAction, &QAction::triggered, mCPickHandler, &CPickHandler::slotActionDel);

	connect(this->m_delAction, &QAction::triggered, this, &OsgContainer::slotDel);
	connect(this->m_undoAction, &QAction::triggered, this, &OsgContainer::slotUndo);
	connect(this->m_redoAction, &QAction::triggered, this, &OsgContainer::slotRedo);
}

OsgContainer::~OsgContainer()
{
	delete mCP;
	delete mCP2;
	delete mScratchPad;
	delete mScratchPad2;

	workerThread.quit();
	workerThread.wait();
}

bool OsgContainer::event(QEvent *event) {
	
	return QOpenGLWidget::event(event);
}
void OsgContainer::mousePressEvent(QMouseEvent *event)
{
	isPressed = true;
	mScratchPad->reset();
	mScratchPad->write(event,mSelectedDraw,mRhtClkOpt);
	
	mBC.setBuffer(mScratchPad->_startPtr, mScratchPad->_numBytes);
	mBC.sync();
	memset(mScratchPad->_startPtr, 0, mScratchPad->_numBytes);
	
	QOpenGLWidget::mousePressEvent(event);
	update();
}
void OsgContainer::mouseReleaseEvent(QMouseEvent *event)
{
	isPressed = false;
	mScratchPad->reset();
	mScratchPad->write(event, mSelectedDraw, mRhtClkOpt);

	mBC.setBuffer(mScratchPad->_startPtr, mScratchPad->_numBytes);
	mBC.sync();
	memset(mScratchPad->_startPtr, 0, mScratchPad->_numBytes);

	QOpenGLWidget::mouseReleaseEvent(event);
	update();
}
void OsgContainer::mouseDoubleClickEvent(QMouseEvent *event)
{
	mScratchPad->reset();
	mScratchPad->write(event, mSelectedDraw, mRhtClkOpt);
	
	mBC.setBuffer(mScratchPad->_startPtr, mScratchPad->_numBytes);
	mBC.sync();
	memset(mScratchPad->_startPtr, 0, mScratchPad->_numBytes);

	QOpenGLWidget::mouseDoubleClickEvent(event);
	update();
}
void OsgContainer::mouseMoveEvent(QMouseEvent *event)
{
	if (isPressed)
	{
		mScratchPad->reset();
		mScratchPad->write(event, mSelectedDraw, mRhtClkOpt);
	
		mBC.setBuffer(mScratchPad->_startPtr, mScratchPad->_numBytes);
		mBC.sync();
		memset(mScratchPad->_startPtr, 0, mScratchPad->_numBytes);
	}
	
	QOpenGLWidget::mouseMoveEvent(event);
	update();
}
void OsgContainer::wheelEvent(QWheelEvent *event)
{
	mScratchPad->reset();
	mScratchPad->write(event, mRhtClkOpt);

	mBC.setBuffer(mScratchPad->_startPtr, mScratchPad->_numBytes);
	mBC.sync();
	memset(mScratchPad->_startPtr, 0, mScratchPad->_numBytes);

	QOpenGLWidget::wheelEvent(event);
	update();
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
	//window->getEventQueue()->keyPress(event->key());
	window->getEventQueue()->keyPress((osgGA::GUIEventAdapter::KeySymbol)*(event->text().toLatin1().data()));
	
	QOpenGLWidget::keyPressEvent(event);
	update();
}
void OsgContainer::keyReleaseEvent(QKeyEvent *event) {
	setKeyboardModifiers(event);
	window->getEventQueue()->keyRelease(event->key());
	QOpenGLWidget::keyReleaseEvent(event);
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
void OsgContainer::contextMenuEvent(QContextMenuEvent *event)
{
	m_contextMenu->exec(event->globalPos());
}

void OsgContainer::paintGL() {


	if (isVisibleTo(QApplication::activeWindow())) 
	{
			
		if (mViewerMode==STAND_ALONE)
		{
			mRC2.setBuffer(mScratchPad2->_startPtr, mScratchPad2->_numBytes);

			int readsize = mRC2.sync();
						
			if (readsize != -1)
			{
				//std::cout << "readsize:" << readsize << std::endl;

				mScratchPad2->reset();
				unsigned int type = 0;
				int btn = 0, x = 0, y = 0,wheel=0,dwslt=0,rhtopt = 0;
				mScratchPad2->read(type,btn, x, y,wheel,dwslt,rhtopt);

				mCPickHandler->mSelected = dwslt;
					
				if (type == 0)
				{
					if (rhtopt == 1)
					{
						mCPickHandler->slotActionUndo(false);
					}
					else if (rhtopt == 2)
					{
						mCPickHandler->slotActionRedo(false);
					}
					else if (rhtopt == 3)
					{
						mCPickHandler->slotActionDel(false);
					}
				}
				else if (type == QEvent::Type::MouseButtonPress)
				{
					window->getEventQueue()->mouseButtonPress(x, y, btn);
					
				}
				else if (type == QEvent::Type::MouseButtonRelease)
				{
					window->getEventQueue()->mouseButtonRelease(x, y, btn);
				}
				else if (type == QEvent::Type::MouseButtonDblClick)
				{
					window->getEventQueue()->mouseDoubleButtonPress(x, y, btn);
				}
				else if (type == QEvent::Type::MouseMove)
				{
					window->getEventQueue()->mouseMotion(x, y);
				}
				else if (type == QEvent::Type::Wheel)
				{
					if (wheel > 0)
					{
						window->getEventQueue()->mouseScroll(osgGA::GUIEventAdapter::SCROLL_UP);
					}
					else
					{
						window->getEventQueue()->mouseScroll(osgGA::GUIEventAdapter::SCROLL_DOWN);
					}					
				}
				
			}
						
		}
				
		frame();
	}
	
}
void OsgContainer::initInteraction()
{
	mBC.setPort(static_cast<short int>(mSocketNumber));
	mRC.setPort(static_cast<short int>(mSocketNumber));

	mBC2.setPort(static_cast<short int>(mSocketNumber + 1));
	mRC2.setPort(static_cast<short int>(mSocketNumber + 1));
	
	mCP = new CameraPacket();
	mCP2 = new CameraPacket();

	mScratchPad = new DataConverter(mMessageSize);
	mScratchPad2 = new DataConverter(mMessageSize);
}
void OsgContainer::initEarth1()
{
	root = new osg::Group();
	m_pMap = new osgEarth::Map;//防止程序崩溃
	m_earthNode= osgDB::readNodeFile("simple.earth");
	osg::ref_ptr<osgEarth::MapNode>map = dynamic_cast<osgEarth::MapNode*>(m_earthNode);
	root->addChild(map);
	setCamera(createCamera(0, 0, width(), height()));
	//设置地球操作器
	m_EM = new osgEarth::Util::EarthManipulator;
	m_EM->setNode(map);
	setCameraManipulator(m_EM);


	mCPickHandler = new CPickHandler(this);//两个类重复包含了
	addEventHandler(mCPickHandler);
	addEventHandler(new osgViewer::WindowSizeHandler());
	addEventHandler(new osgViewer::StatsHandler);
	addEventHandler(new osgGA::StateSetManipulator(this->getCamera()->getOrCreateStateSet()));

	setSceneData(root);
	startTimer(10);
}
osg::ref_ptr<osg::EllipsoidModel>em = new osg::EllipsoidModel;
osg::Node* createTrinangle1()
{
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	osg::ref_ptr<osg::Vec3Array>vectex = new osg::Vec3Array;
	//上一个点
	osg::Vec3d FirstPoint, SecondPoint, ThirdPoint, ForthPoint;
	//第一个点经纬高转世界坐标  单位度
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(40.0), osg::DegreesToRadians(117.0), 900, FirstPoint.x(), FirstPoint.y(), FirstPoint.z());
	vectex->push_back(FirstPoint);
	//第二个点经纬高转世界坐标  单位度
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(41.0), osg::DegreesToRadians(89.0), 900, SecondPoint.x(), SecondPoint.y(), SecondPoint.z());
	vectex->push_back(SecondPoint);
	//第三个点经纬高转世界坐标  单位度
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(32.0), osg::DegreesToRadians(103.0), 900, ThirdPoint.x(), ThirdPoint.y(), ThirdPoint.z());
	vectex->push_back(ThirdPoint);
	geom->setVertexArray(vectex);

	//定义颜色数组
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
	geom->setColorArray(c.get());
	//geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	c->push_back(osg::Vec4(1.f, 0.f, 0.f, 1.f));
	//设置定点关联方式
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, 3));
	//手动定义法线
	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
	geom->setNormalArray(n.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
	//n->push_back(osg::Vec3(-2.f, -1.f, 10.f));
	n->push_back(osg::Vec3(0.f, -1.f, 0.f));

	//灯光
	//geom->getOrCreateStateSet()->setAttribute(new osg::LineWidth(3.0), osg::StateAttribute::OFF);
	geom->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	osg::Geode *geode = new osg::Geode;
	geode->addDrawable(geom.get());
	return geode;
}
void OsgContainer::initEarth2() 
{
	m_pMap = new osgEarth::Map;
	m_mapNode = new osgEarth::MapNode(m_pMap);
	
	root = new osg::Group();
	root->addChild(m_mapNode);
	
	//使用api加载本地数据
	osgEarth::Drivers::GDALOptions imageLayerOpt;
	QString applicationDirPath = QApplication::applicationDirPath();
	applicationDirPath += "/world.tif";
	imageLayerOpt.url() = osgEarth::URI(applicationDirPath.toStdString());

	std::string imageLayerName = "worldimage";
	osg::ref_ptr<osgEarth::ImageLayer>imageLayer = new osgEarth::ImageLayer(osgEarth::ImageLayerOptions(imageLayerName, imageLayerOpt));
	m_pMap->addLayer(imageLayer);
	///////////////////////////////////////////////////////////////////////////
	osg::Vec3d FirstPoint;
	//第一个点经纬高转世界坐标  单位度
	em->convertLatLongHeightToXYZ(osg::DegreesToRadians(40.0), osg::DegreesToRadians(117.0), 900, FirstPoint.x(), FirstPoint.y(), FirstPoint.z());
	//平移操作
	osg::ref_ptr<osg::MatrixTransform>trans = new osg::MatrixTransform();
	trans->setMatrix(osg::Matrix::scale(50000, 50000, 50000)*osg::Matrix::translate(FirstPoint.x(), FirstPoint.y(), FirstPoint.z()));
	//trans->addChild(osgDB::readNodeFile("cow.osg"));
	root->addChild(trans);

	setCamera(createCamera(0, 0, width(), height()));
	//设置地球操作器
	m_EM = new osgEarth::Util::EarthManipulator;
	m_EM->setNode(m_mapNode);
	setCameraManipulator(m_EM);
		
	mCPickHandler = new CPickHandler(this);//两个类重复包含了
	addEventHandler(mCPickHandler);
	addEventHandler(new osgViewer::ThreadingHandler);
	addEventHandler(new osgGA::StateSetManipulator(this->getCamera()->getOrCreateStateSet()));
	addEventHandler(new osgViewer::WindowSizeHandler());//响应f
	addEventHandler(new osgViewer::StatsHandler);//响应s,w

	//优化场景数据
	osgUtil::Optimizer optimzier;
	optimzier.optimize(root.get());
	osgEarth::GLUtils::setGlobalDefaults(getCamera()->getOrCreateStateSet());

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
	//平移操作
	/*osg::ref_ptr<osg::MatrixTransform>trans = new osg::MatrixTransform();
	trans->setMatrix(osg::Matrix::translate(0, 0, 20));
	trans->addChild(m_earthNode);
	root->addChild(trans);*/

	//缩放操作+平移
	/*osg::ref_ptr<osg::MatrixTransform>trans = new osg::MatrixTransform();
	trans->setMatrix(osg::Matrix::scale(0.5, 0.5, 0.5)*osg::Matrix::translate(-10, 0, 0));
	trans->addChild(m_earthNode);
	root->addChild(trans);*/

	//旋转操作
	//osg::ref_ptr<osg::MatrixTransform>trans = new osg::MatrixTransform();
	//trans->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(90.0),1,0,0));//分别代表绕着x,y,z轴旋转,正代表逆时针
	//trans->addChild(m_earthNode);
	//root->addChild(trans);

	//添加白边
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
	addEventHandler(mCPickHandler);//自定义类操作类
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

	// 设置时间;
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
//下雪
bool OsgContainer::createSnow()
{

	mSnowNode = new osgParticle::PrecipitationEffect;

	//设置雪花颜色
	mSnowNode->setParticleColor(osg::Vec4(1, 1, 1, 1));
	mSnowNode->setUseFarLineSegments(true);
	//设置雪花方向
	mSnowNode->setWind(osg::Vec3(2, 0, 0));

	// 设置雪花浓度
	mSnowNode->snow(0.8);

	return root->addChild(mSnowNode);
	
}
bool OsgContainer::createRain()
{
	mRainNode = new osgParticle::PrecipitationEffect;

	// 设置颜色
	mRainNode->setParticleColor(osg::Vec4(1, 1, 1, 1));
	mRainNode->setUseFarLineSegments(true);
	// iLevel參数是一个int值，表示雨的级别，一般1-10就够用了
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
	m_EM->setViewpoint(osgEarth::Viewpoint("视点", 110.0, 30.0, 900.0, 0.0, -90, 7e3));
	
	//mFireNode = new osgParticle::FireEffect(osg::Vec3(30, 30, 30), 90);
	//getEM()->setViewpoint(osgEarth::Viewpoint("视点", (, , 900, 0.0, -90, 7e3));
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
	m_EM->setViewpoint(osgEarth::Viewpoint("视点", 110.0, 30.0, 900.0, 0.0, -90, 7e3));
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
			std::cout << "雪特效创建失败";
			return;
		}
		mHaveSnow = true;
	}
	else
	{
		if (state == 0)//取消选中
		{
			mSnowNode->setNodeMask(0);
			std::cout << "取消选中 ";
		}
		else if (state == 2)//选中
		{
			mSnowNode->setNodeMask(1);
			std::cout << "选中 ";
		}
	}
}
void OsgContainer::slotRain(int state)
{
	if (!mHaveRain)
	{
		if (!createRain())
		{
			std::cout << "雨特效创建失败";
			return;
		}
		mHaveRain = true;
	}
	else
	{
		if (state == 0)//取消选中
		{
			mRainNode->setNodeMask(0);
		}
		else if (state == 2)//选中
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
		if (state == 0)//取消选中
		{
			root->getOrCreateStateSet()->setAttributeAndModes(mWuNode, osg::StateAttribute::OFF);
		}
		else if (state == 2)//选中
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
			std::cout << "火特效创建失败";
			return;
		}
		mHaveFire = true;
	}
	else
	{
		if (state == 0)//取消选中
		{
			mFireNode->setNodeMask(0);
		}
		else if (state == 2)//选中
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
			std::cout << "爆炸特效创建失败";
			return;
		}
		mHaveBoom = true;
	}
	else
	{
		if (state == 0)//取消选中
		{
			root->removeChild(mBoomNode);
			mHaveBoom = false;
		}
	}
}

void OsgContainer::slotAddNetArcgis()
{
	//判断是否有网络连接
	if (m_netIsOpen)
	{
		return;
	}
	m_netIsOpen = true;	
	emit startWork();
	
	//代码,经测试可以使用
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

	//代码经测试可以使用
	//m_pMap->removeLayer(netImageLayer);
}


void OsgContainer::slotPlayVideo()
{
	if (!mHaveVideo)
	{ 
		osg::ref_ptr<osg::EllipsoidModel>em = new osg::EllipsoidModel;
		osg::Vec3d p,p1,p2,p3,p4;
		em->convertLatLongHeightToXYZ(osg::DegreesToRadians(30.0f), osg::DegreesToRadians(110.0f), 300.0f, p.x(), p.y(), p.z());

		//注册插件
		//osgDB::Registry::instance()->addFileExtensionAlias("avi", "ffmpeg");
		osgDB::Registry::instance()->addFileExtensionAlias("mp4", "ffmpeg");
		osg::ref_ptr<osg::Image> image;

		//本地视频(自己选择视频路径)
		QString applicationDirPath = QApplication::applicationDirPath();
		applicationDirPath += "/test.mp4";

		image = osgDB::readImageFile(applicationDirPath.toStdString());

		osg::ImageStream* imageStream = dynamic_cast<osg::ImageStream*>(image.get());
		if (imageStream)
			imageStream->play();

		//添加到四边形
		osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
		texture->setImage(image.get());
		osg::ref_ptr<osg::Drawable> quad = osg::createTexturedQuadGeometry(
			osg::Vec3(100.0f,0.0f,100.0f), osg::Vec3(0.0f, 0.0f, -200.0f), osg::Vec3(-200.0f, 0.0f, 0.0f));
		quad->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());

		//添加到geode
		osg::ref_ptr<osg::Geode> geode = new osg::Geode;
		geode->addDrawable(quad.get());
		geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);

		//作变换
		osg::Quat rot;
		rot.makeRotate(osg::Vec3d(0.0f, -1.0f, 0.0f),p );
		osg::PositionAttitudeTransform* pat = new osg::PositionAttitudeTransform();
		pat->setAttitude(rot);
		pat->setPosition(p);

		pat->addChild(geode);

		root->addChild(pat);

		mHaveVideo = true;
	}
	m_EM->setViewpoint(osgEarth::Viewpoint("视点", 110.0, 30.0, 300.0, -23.0, -90.0, 0.5e3));

}

void OsgContainer::slotUndo(bool checked)
{
	mScratchPad->reset();
	mScratchPad->write(0, 1);

	mBC.setBuffer(mScratchPad->_startPtr, mScratchPad->_numBytes);
	mBC.sync();
	memset(mScratchPad->_startPtr, 0, mScratchPad->_numBytes);
}
void OsgContainer::slotRedo(bool checked)
{
	mScratchPad->reset();
	mScratchPad->write(0, 2);

	mBC.setBuffer(mScratchPad->_startPtr, mScratchPad->_numBytes);
	mBC.sync();
	memset(mScratchPad->_startPtr, 0, mScratchPad->_numBytes);
}
void OsgContainer::slotDel(bool checked)
{

	mScratchPad->reset();
	mScratchPad->write(0, 3);

	mBC.setBuffer(mScratchPad->_startPtr, mScratchPad->_numBytes);
	mBC.sync();
	memset(mScratchPad->_startPtr, 0, mScratchPad->_numBytes);
}
void OsgContainer::slotGetDrawIndex(int n)
{
	mSelectedDraw = n;
}