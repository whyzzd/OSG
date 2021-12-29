#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/Group>
#include <osgFX/Scribe>
#include <osgGA/GUIEventHandler>
#include <osgUtil/LineSegmentIntersector> // ����ͷ�ļ�
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
	//			// �������
	//			// ��������������ֱ�Ϊ���ʱ�� XY ����Ļ����
	//			// ����Ļ�������Ǵ� 0\0 �� 1\1 ��˴�ԭ���Ͽ��Ա�ʾ���޸���
	//			Pick(ea.getX(), ea.getY()); // ���ú���
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

	//	// ����һ���ཻ���ԵĽ�������ж���Ļ�볡���ཻ�󣬵ó��Ľ�����������
	//	osgUtil::LineSegmentIntersector::Intersections intersections;
	//	if (mViewer->computeIntersections(x, y, intersections)) {

	//		// ����һ��������������������ý����
	//		for (osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin(); hitr != intersections.end(); ++hitr) {

	//			// ע������ȡ���� back()
	//			if (!hitr->nodePath.empty() && !(hitr->nodePath.back()->getName().empty())) {

	//				// �õ��������е� nodepath���Դ˿����жϸ� path ���Ƿ�����Ҫ�Ľ��
	//				const osg::NodePath &np = hitr->nodePath;
	//				// ����������������Ҫ�Ľ�㣬���������ظý��
	//				// ������һ����̬ת�����������ת���ɹ�����ֵ��Ϊ NULL������Ϊ NULL��
	//				for (int i = np.size() - 1; i >= 0; --i) {

	//					// ���һ�� scribe ��㣬�ý���µ�ģ�ͻᱻ�Ӱ����߸�����ʾ
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