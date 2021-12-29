#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/Group>
#include <osgFX/Scribe>
#include <osgGA/GUIEventHandler>
#include <osgUtil/LineSegmentIntersector> // 新增头文件
#include<qdebug.h>
#include <osg/MatrixTransform>
class CPickHandler : public osgGA::GUIEventHandler {

public:
	CPickHandler(osgViewer::Viewer *viewer) : mViewer(viewer) {
	}

	//virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa) {

	//	switch (ea.getEventType()) {

	//	case(osgGA::GUIEventAdapter::PUSH) :
	//		if (ea.getButton() == 1) {
	//			// 左键按下
	//			// 传入的两个参数分别为点击时的 XY 的屏幕坐标
	//			// 在屏幕上坐标是从 0\0 到 1\1 因此从原理上可以表示无限个点
	//			Pick(ea.getX(), ea.getY()); // 调用函数
	//		}
	//									   return true;
	//	}
	//	return false;
	//}

	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
	void pick(float x, float y);
	osg::Vec3 screen2World(float x, float y);
	bool PickObject;
	osg::ref_ptr<osg::MatrixTransform> picked;
	bool lbuttonDown;
protected:

	//void Pick(float x, float y) 
	//{

	//	// 申请一个相交测试的结果集，判断屏幕与场景相交后，得出的结果集放入此中
	//	osgUtil::LineSegmentIntersector::Intersections intersections;
	//	if (mViewer->computeIntersections(x, y, intersections)) {

	//		// 申请一个结果集遍历器，遍历该结果集
	//		for (osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin(); hitr != intersections.end(); ++hitr) {

	//			// 注意这里取的是 back()
	//			if (!hitr->nodePath.empty() && !(hitr->nodePath.back()->getName().empty())) {

	//				// 得到遍历器中的 nodepath，以此可以判断该 path 中是否有想要的结点
	//				const osg::NodePath &np = hitr->nodePath;
	//				// 如果结果集中有所需要的结点，则设置隐藏该结点
	//				// 其中有一个动态转换，如果可以转换成功则左值不为 NULL，否则为 NULL。
	//				for (int i = np.size() - 1; i >= 0; --i) {

	//					// 添加一个 scribe 结点，该结点下的模型会被加白描线高亮显示
	//					osgFX::Scribe *sc = dynamic_cast<osgFX::Scribe *>(np[i]);
	//					if (sc != NULL) {

	//						if (sc->getNodeMask() != 0)
	//							sc->setNodeMask(0);
	//					}
	//				}
	//			}
	//		}
	//	}
	//	qDebug() << 123;
	//}

	osgViewer::Viewer *mViewer; // mViewer
};