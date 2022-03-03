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
#include"XYZExSource.h"
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
	/*connect(this->m_undoAction, &QAction::triggered, this, &OsgContainer::slotUndo);
	connect(this->m_redoAction, &QAction::triggered, this, &OsgContainer::slotRedo);*/
	connect(this->m_undoAction, &QAction::triggered, mCPickHandler, &CPickHandler::slotActionUndo);
	connect(this->m_redoAction, &QAction::triggered, mCPickHandler, &CPickHandler::slotActionRedo);
	connect(this->m_delAction, &QAction::triggered, mCPickHandler, &CPickHandler::slotActionDel);
	

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
	mScratchPad->write(event);

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
	mScratchPad->write(event);

	mBC.setBuffer(mScratchPad->_startPtr, mScratchPad->_numBytes);
	mBC.sync();
	memset(mScratchPad->_startPtr, 0, mScratchPad->_numBytes);

	QOpenGLWidget::mouseReleaseEvent(event);
	update();
}
void OsgContainer::mouseDoubleClickEvent(QMouseEvent *event)
{
	mScratchPad->reset();
	mScratchPad->write(event);

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
		mScratchPad->write(event);

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
	mScratchPad->write(event);

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
//void OsgContainer::mousePressEvent(QMouseEvent *event) {
//	int button = 0;
//	switch (event->button()) {
//	case Qt::LeftButton:
//		{
//			button = 1; 
//			/*this->getSceneData()->asGroup()->getChild(0)->setNodeMask(1);
//			this->getSceneData()->asGroup()->getChild(1)->setNodeMask(1);
//			qDebug() << button;*/
//			break; 
//
//		}
//	case Qt::MidButton: button = 2; break;
//	case Qt::RightButton:
//		{ 
//			button = 3;
//			/*this->getSceneData()->asGroup()->getChild(0)->setNodeMask(0); 
//			this->getSceneData()->asGroup()->getChild(1)->setNodeMask(1);
//			qDebug() << button;*/
//			break;
//		}
//	case Qt::NoButton: button = 0; break;
//	default: button = 0; break;
//	}
//	
//	setKeyboardModifiers(event);
//	window->getEventQueue()->mouseButtonPress(event->x(), event->y(), button);
//	update();
//}
//void OsgContainer::mouseReleaseEvent(QMouseEvent *event) {
//	int button = 0;
//	switch (event->button()) {
//	case Qt::LeftButton: button = 1; break;
//	case Qt::MidButton: button = 2; break;
//	case Qt::RightButton: button = 3; break;
//	case Qt::NoButton: button = 0; break;
//	default: button = 0; break;
//	}
//	setKeyboardModifiers(event);
//	window->getEventQueue()->mouseButtonRelease(event->x(), event->y(), button);
//	
//	
//	QOpenGLWidget::mouseReleaseEvent(event);
//	update();
//}
//void OsgContainer::mouseDoubleClickEvent(QMouseEvent *event) {
//	int button = 0;
//	switch (event->button()) {
//	case Qt::LeftButton: button = 1; break;
//	case Qt::MidButton: button = 2; break;
//	case Qt::RightButton: button = 3; break;
//	case Qt::NoButton: button = 0; break;
//	default: button = 0; break;
//	}
//	setKeyboardModifiers(event);
//	window->getEventQueue()->mouseDoubleButtonPress(event->x(), event->y(), button);
//
//	QOpenGLWidget::mouseDoubleClickEvent(event);
//	update();
//}
//void OsgContainer::mouseMoveEvent(QMouseEvent *event) {
//	setKeyboardModifiers(event);
//	window->getEventQueue()->mouseMotion(event->x(), event->y());
//	QOpenGLWidget::mouseMoveEvent(event);
//	update();
//}
//void OsgContainer::wheelEvent(QWheelEvent *event) {
//	setKeyboardModifiers(event);
//	window->getEventQueue()->mouseScroll(
//		event->orientation() == Qt::Vertical ?
//		(event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN) :
//		(event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_LEFT : osgGA::GUIEventAdapter::SCROLL_RIGHT));
//	QOpenGLWidget::wheelEvent(event);
//	update();
//}
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
				int btn = 0, x = 0, y = 0,wheel=0;
				mScratchPad2->read(type,btn, x, y,wheel);

				//std::cout << "mouseEvent:" << ":" << x << ":" << y << std::endl;
				if (type == QEvent::Type::MouseButtonPress)
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
		else if(mViewerMode==MASTER)
		{ 
						
			mCP->readEventQueue(*this);
			if (mOperaPacket._operaType == 0)
			{
				mCP->_operaType = mOperaPacket._operaType;
				mCP->_llaX = mOperaPacket._llaX;
				mCP->_llaY = mOperaPacket._llaY;
											
			}
			else if (mOperaPacket._operaType == 1)
			{
				
				mCP->_operaType = mOperaPacket._operaType;
				mCP->_llaX = mOperaPacket._llaX;
				mCP->_llaY = mOperaPacket._llaY;
				
			}
			else if (mOperaPacket._operaType == 2)
			{
				mCP->_operaType = mOperaPacket._operaType;

				for (int i = 0; i < 2; i++)
				{
					mCP->_llaXArr[i] = mOperaPacket._llaXArr[i];
					mCP->_llaYArr[i] = mOperaPacket._llaYArr[i];
				}
				mCP->_llaSize = mOperaPacket._llaSize;
				
			}
			else if (mOperaPacket._operaType == 3)
			{
				mCP->_operaType = mOperaPacket._operaType;
				for (int i = 0; i < 3; i++)
				{
					mCP->_llaXArr[i] = mOperaPacket._llaXArr[i];
					mCP->_llaYArr[i] = mOperaPacket._llaYArr[i];
				}
				mCP->_llaSize = mOperaPacket._llaSize;
			}
			else if (mOperaPacket._operaType == 11)
			{
				mCP->_operaType = mOperaPacket._operaType;				
			}
			mOperaPacket._operaType = 0;


			mScratchPad->reset();
			mScratchPad->write(*mCP);

			mCP->_operaType = 0;
			mBC.setBuffer(mScratchPad->_startPtr, mScratchPad->_numBytes);
			mBC.sync();
			static int i = 0;
			//printf("count:%d\n", i++);
			
			mRC2.setBuffer(mScratchPad2->_startPtr, mScratchPad2->_numBytes);
			
			unsigned int readsize = mRC2.sync();
			
			mScratchPad2->reset();
			mScratchPad2->read(*mCP2);
			mCP2->writeEventQueue(*this);
			
			if (mCP2->_operaType == 1)
			{

				mCPickHandler->drawDot(mCP2->_llaX, mCP2->_llaY);

			}
			else if (mCP2->_operaType == 2)
			{
				mCPickHandler->mLineVec->clear();
				for (int i = 0; i < mCP2->_llaSize; i++)
				{
					osg::Vec3 a(mCP2->_llaXArr[i], mCP2->_llaYArr[i], 0.0);
					mCPickHandler->mLineVec->push_back(a);
				}
				mCPickHandler->drawLine();
			}
			else if (mCP2->_operaType == 3)
			{
				mCPickHandler->mLineVec->clear();
				for (int i = 0; i < mCP2->_llaSize; i++)
				{
					osg::Vec3 a(mCP2->_llaXArr[i], mCP2->_llaYArr[i], 0.0);
					mCPickHandler->mLineVec->push_back(a);
					//std::cout << mCP->_llaXArr[i] << "=" << mCP->_llaXArr[i] << std::endl;
				}
				mCPickHandler->drawTriangles();
			}
			else if (mCP2->_operaType == 11)
			{
				mCPickHandler->slotNetDel();

			}
			mCP2->_operaType = 0;
			
		}
		else if(mViewerMode==SLAVE)
		{


			mCP2->readEventQueue(*this);

			if (mOperaPacket._operaType == 0)
			{
				mCP2->_operaType = mOperaPacket._operaType;
				mCP2->_llaX = mOperaPacket._llaX;
				mCP2->_llaY = mOperaPacket._llaY;
				
			}
			else if (mOperaPacket._operaType == 1)
			{

				mCP2->_operaType = mOperaPacket._operaType;
				mCP2->_llaX = mOperaPacket._llaX;
				mCP2->_llaY = mOperaPacket._llaY;
				
			}
			else if (mOperaPacket._operaType == 2)
			{
				mCP2->_operaType = mOperaPacket._operaType;

				for (int i = 0; i < 2; i++)
				{
					mCP2->_llaXArr[i] = mOperaPacket._llaXArr[i];
					mCP2->_llaYArr[i] = mOperaPacket._llaYArr[i];
				}
				mCP2->_llaSize = mOperaPacket._llaSize;

			}
			else if (mOperaPacket._operaType == 3)
			{
				mCP2->_operaType = mOperaPacket._operaType;
				for (int i = 0; i < 3; i++)
				{
					mCP2->_llaXArr[i] = mOperaPacket._llaXArr[i];
					mCP2->_llaYArr[i] = mOperaPacket._llaYArr[i];
				}
				mCP2->_llaSize = mOperaPacket._llaSize;
			}
			else if (mOperaPacket._operaType == 11)
			{
				mCP2->_operaType = mOperaPacket._operaType;
				
			}			
			mOperaPacket._operaType = 0;

			mScratchPad2->reset();
			mScratchPad2->write(*mCP2);
			mCP2->_operaType = 0;
			mBC2.setBuffer(mScratchPad2->_startPtr, mScratchPad2->_numBytes);
			mBC2.sync();
			
			mRC.setBuffer(mScratchPad->_startPtr, mScratchPad->_numBytes);
			
			unsigned int readsize = mRC.sync();
			
			mScratchPad->reset();
			
			mScratchPad->read(*mCP);
			
			mCP->writeEventQueue(*this);
			if (mCP->_operaType == 0)
			{
				
			}
			else if (mCP->_operaType == 1)
			{
				mCPickHandler->drawDot(mCP->_llaX, mCP->_llaY);				
			}
			else if (mCP->_operaType == 2)
			{
				mCPickHandler->mLineVec->clear();
				for (int i = 0; i < mCP->_llaSize; i++)
				{
					osg::Vec3 a(mCP->_llaXArr[i], mCP->_llaYArr[i],0.0);
					mCPickHandler->mLineVec->push_back(a);
				}
				mCPickHandler->drawLine();				
			}
			else if (mCP->_operaType == 3)
			{
				mCPickHandler->mLineVec->clear();
				for (int i = 0; i < mCP->_llaSize; i++)
				{
					osg::Vec3 a(mCP->_llaXArr[i], mCP->_llaYArr[i], 0.0);
					mCPickHandler->mLineVec->push_back(a);
					//std::cout << mCP->_llaXArr[i] << "=" << mCP->_llaXArr[i] << std::endl;
				}
				mCPickHandler->drawTriangles();				
			}
			else if (mCP->_operaType == 11)
			{
				mCPickHandler->pick(mCP->_llaX, mCP->_llaY);				
				mCPickHandler->slotNetDel();
				
			}

			mCP->_operaType = 0;
		}
		else
		{

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
	imageLayerOpt.url() = osgEarth::URI("D:\\OSGCore\\Build\\OpenSceneGraph-Data\\world.tif");

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
	trans->addChild(osgDB::readNodeFile("cow.osg"));
	root->addChild(trans);

	/*osg::Node *n = createTrinangle1();
	osgEarth::Registry::objectIndex()->tagNode(n,root);
	root->addChild(n);*/

	//尝试使用api加载本地shp(疑惑:为啥加载不出来?)
	/*osgEarth::Drivers::OGRFeatureOptions ogrData;
	ogrData.url() = "D:\\OSGCore\\Build\\OpenSceneGraph-Data\\world.shp";
	FeatureSourceLayerOptions ogrLayer;
	ogrLayer.name() = "vector-data";
	ogrLayer.featureSource() = ogrData;
	m_pMap->addLayer(new osgEarth::Features::FeatureSourceLayer(ogrData));*/

	//使用api加载网络数据
	//osgEarth::Drivers::ArcGISOptions netImageLayerOpt;
	//netImageLayerOpt.url() = osgEarth::URI("https://map.geoq.cn/arcgis/rest/services/ChinaOnlineStreetWarm/MapServer");
	////netImageLayerOpt.url() = osgEarth::URI("http://services.arcgisonline.com/ArcGIS/rest/services/Reference/World_Boundaries_and_Places_Alternate/MapServer");
	//std::string netImageLayerName = "worldimage1";
	///*osg::ref_ptr<osgEarth::ImageLayer>*/netImageLayer = new osgEarth::ImageLayer(osgEarth::ImageLayerOptions(netImageLayerName, netImageLayerOpt));
	//m_pMap->addLayer(netImageLayer);

	//加载xyz格式文件
	osgEarth::Drivers::XYZOptions tileOptions;
	//高德卫星
	//tileOptions.url() = osgEarth::URI("https://webst01.is.autonavi.com/appmaptile?style=6&x={x}&y={y}&z={z}");
	//高德路线
	//tileOptions.url() = osgEarth::URI("https://wprd01.is.autonavi.com/appmaptile?x={x}&y={y}&z={z}&lang=zh_cn&size=1&scl=2&style=8&ltype=11");
	
	/*tileOptions.url() = "http://[abc].tile.openstreetmap.org/{z}/{x}/{y}.png";
	tileOptions.profile()->namedProfile() = ("spherical-mercator");
	osgEarth::ImageLayerOptions options = osgEarth::ImageLayerOptions("debug", tileOptions);
	osg::ref_ptr<osgEarth::ImageLayer> layer = new osgEarth::ImageLayer(options);
	m_pMap->addLayer(layer);*/

	//mapbox高程图(只能显示为图像,无法转换为高程)
	//osgEarth::Drivers::XYZOptions exyz;
	//exyz.url() = "http://api.mapbox.com/v4/mapbox.terrain-rgb/{z}/{x}/{y}.pngraw?access_token=pk.eyJ1IjoicXd1c2VyIiwiYSI6ImNreTN0YmhtZTAwdncyb2xtdWZ3ZWZodXEifQ.23yUvHmVWIQ8sRwy68EDlA";
	//exyz.profile()->namedProfile() = "spherical-mercator";
	///*XYZExSource *source = new XYZExSource(exyz);
	//auto estatus = source->open();*/
	//osgEarth::ImageLayerOptions options1 = osgEarth::ImageLayerOptions("mapboxEle", exyz);
	//m_pMap->addLayer(new osgEarth::ImageLayer(options1));
	

	//------------------------测试第二种方式画图(测试官方例子1)--------------------------------------
	//const osgEarth::SpatialReference* mapSRS = m_mapNode->getMapSRS();
	////osg::Group*geometryGroup = new osg::Group;
	//osgEarth::Symbology::Style geomStyle;
	///*geomStyle.getOrCreate<osgEarth::LineSymbol>()->stroke()->color() = osgEarth::Symbology::Color::Cyan;
	//geomStyle.getOrCreate<osgEarth::LineSymbol>()->stroke()->width() = 5.0f;
	//geomStyle.getOrCreate<osgEarth::LineSymbol>()->tessellationSize() = 75000;*/
	///*geomStyle.getOrCreate<osgEarth::AltitudeSymbol>()->clamping() = osgEarth::AltitudeSymbol::CLAMP_TO_TERRAIN;
	//geomStyle.getOrCreate<osgEarth::AltitudeSymbol>()->technique() = osgEarth::AltitudeSymbol::TECHNIQUE_DRAPE;*/

	//osg::ref_ptr<osgEarth::Symbology::Polygon> polygon = new osgEarth::Symbology::Polygon();
	//polygon->push_back(osg::Vec3d(0, 40, 0));
	//polygon->push_back(osg::Vec3d(-60, 40, 0));
	//polygon->push_back(osg::Vec3d(-60, 60, 0));
	////polygon->push_back(osg::Vec3d(0, 60, 0));

	//
	//osg::ref_ptr<osgEarth::Features::Feature> feature = new osgEarth::Features::Feature(polygon, mapSRS);
	//osg::ref_ptr<osgEarth::Annotation::FeatureNode> featureNode = new osgEarth::Annotation::FeatureNode(feature/*, geomStyle*/);
	////geometryGroup->addChild(featureNode);
	//osg::ref_ptr<osgEarth::Annotation::FeatureEditor> editor = new osgEarth::Annotation::FeatureEditor(featureNode);
	//m_mapNode->addChild(editor);
	////m_mapNode->addChild(featureNode);
	
	//-----------------------------------------------------------
	
	

	//----------------官方例子2(加载本地自带矢量)---------------------------------------------------
	//std::string filePath = "D:\\OSGCore\\Build\\OpenSceneGraph-Data\\world.shp";
	//osgEarth::Drivers::OGRFeatureOptions featureData;
	//featureData.url() = filePath;

	//// Make a feature source layer and add it to the Map:
	//osgEarth::Features::FeatureSourceLayerOptions ogrLayer;
	//ogrLayer.name() = filePath + "_source";
	//ogrLayer.featureSource() = featureData;
	//osgEarth::Features::FeatureSourceLayer*  featureSourceLayer = new osgEarth::Features::FeatureSourceLayer(ogrLayer);
	//m_pMap->addLayer(featureSourceLayer);
	//osgEarth::Features::FeatureSource *features = featureSourceLayer->getFeatureSource();
	//if (!features)
	//{
	//	printf(("无法打开该矢量文件！"));
	//	qDebug() << "------------";
	//	return;
	//}
	//
	////设置样式
	//osgEarth::Symbology::Style style;

	////可见性
	//osgEarth::Symbology::RenderSymbol* rs = style.getOrCreate<osgEarth::Symbology::RenderSymbol>();
	//rs->depthTest() = true;

	////贴地设置
	////osgEarth::Symbology::AltitudeSymbol* alt = style.getOrCreate<osgEarth::Symbology::AltitudeSymbol>();
	////alt->clamping() = alt->CLAMP_TO_TERRAIN;
	////alt->technique() = alt->TECHNIQUE_DRAPE;
	//
	////设置矢量面样式（包括边界线）
	//osgEarth::Symbology::LineSymbol* ls = style.getOrCreateSymbol<osgEarth::Symbology::LineSymbol>();
	//ls->stroke()->color() = osgEarth::Symbology::Color("#FA8072");
	//ls->stroke()->width() = 1.0;
	//ls->tessellationSize()->set(100, osgEarth::Units::KILOMETERS);

	//osgEarth::Symbology::PolygonSymbol *polygonSymbol = style.getOrCreateSymbol<osgEarth::Symbology::PolygonSymbol>();
	//polygonSymbol->fill()->color() = osgEarth::Symbology::Color(152.0f / 255, 251.0f / 255, 152.0f / 255, 0.8f); //238 230 133
	//polygonSymbol->outline() = true;

	////将矢量当成模型来加载才能显示
	//osgEarth::Features::FeatureModelLayerOptions fmlOpt;
	//fmlOpt.name() = filePath;
	//fmlOpt.featureSourceLayer() = filePath + "_source";
	//fmlOpt.enableLighting() = false;
	//fmlOpt.styles() = new osgEarth::Symbology::StyleSheet();
	//fmlOpt.styles()->addStyle(style);

	//osg::ref_ptr<osgEarth::Features::FeatureModelLayer> fml = new osgEarth::Features::FeatureModelLayer(fmlOpt);
	//m_pMap->addLayer(fml);
	//------------------------2 end--------------------------------------------

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
		osgDB::Registry::instance()->addFileExtensionAlias("avi", "ffmpeg");

		osg::ref_ptr<osg::Image> image;

		//本地视频(自己选择视频路径)
		image = osgDB::readImageFile("D:\\OSGCore\\Build\\OpenSceneGraph-Data\\mp4\\test.avi");

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

