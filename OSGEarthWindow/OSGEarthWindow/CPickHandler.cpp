#include"CPickHandler.h"
#include<iostream>

#include"OsgContainer.h"
#include"DrawXXX.h"
CPickHandler::CPickHandler(osgViewer::Viewer *viewer) : mViewer(viewer)
{
	mMyConv.setViewer(viewer);
}
bool CPickHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	
	switch (ea.getEventType())
	{
	case osgGA::GUIEventAdapter::PUSH:
	{
		
		int button = ea.getButton();
		if (button == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
		{
			lbuttonDown = true;
			pick(ea.getX(), ea.getY());
			if (PickObject)
			{
				//此类中的函数
				/*osg::Vec3 vec2 = screen2World(ea.getX(), ea.getY());
				std::cout << vec2.x() << " " << vec2.y() << " " << vec2.z() << std::endl;*/

				/*MyConvert myc(mViewer);
				osg::Vec3 v(ea.getX(), ea.getY(),0);
				osg::Vec3 vec1 = myc.ScreenToWorld(v);*/
				//自定义类输出世界坐标
				//std::cout <<"世界坐标:"<< vec1.x() << " " << vec1.y() << " " << vec1.z() << std::endl;
				/*osg::Vec3 v1 = myc.WorldToLonLatAlt(vec1);
				v1.z() = 900;*/
				//自定义类输出经纬度
				//std::cout <<"经纬度:"<< v1.x() << " " << v1.y() << " " << v1.z() << std::endl;
				/*first_point = { vec1.x(), vec1.z() };
				originPos = picked->getMatrix();*/
				static osg::Vec3 vvv[2];
				static int i = 1;
				if (i >= 2)
				{
					i = 1;
					OsgContainer *oc = dynamic_cast<OsgContainer*>(mViewer);
					
					vvv[1] = mLonLatAlt;

					DrawXXX drawline;
					oc->getRoot()->addChild(drawline.createLine(vvv[0],vvv[1]));
					//oc->getEM()->setHomeViewpoint(osgEarth::Viewpoint("视点", (vvv[0].x()+vvv[1].x())/2, (vvv[0].y()+vvv[1].y())/2, 900, 0.0, -90, 7e3));
					//oc->getEM()->setViewpoint(osgEarth::Viewpoint("视点", (vvv[0].x() + vvv[1].x()) / 2, (vvv[0].y() + vvv[1].y()) / 2, 900, 0.0, -90, 7e3));
				}
				else
				{
					vvv[0] = mLonLatAlt;
					i++;
				}
			}
			
		}
		else
		{
			lbuttonDown = false;
		}
		
		return false;
	}

	default:
		return false;
	}

}

void CPickHandler::pick(float x, float y)
{
	osgUtil::LineSegmentIntersector::Intersections intersections;

	if (mViewer->computeIntersections(x, y, intersections))
	{
		osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin();
		osg::NodePath getNodePath = hitr->nodePath;

		//std::cout<<hitr->matrix.valid();

		for (int i = getNodePath.size() - 1; i >= 0; --i)
		{
			osg::MatrixTransform* mt = dynamic_cast<osg::MatrixTransform*>(getNodePath[i]);
			if (mt == NULL)
			{
				continue;
			}
			else
			{
				PickObject = true;
				picked = mt;
			}
		}

		
		mWorld = hitr->getWorldIntersectPoint();
		
		//std::cout << "世界坐标:" << vec1.x() << " " << vec1.y() << " " << vec1.z() << std::endl;
		mLonLatAlt = mMyConv.WorldToLonLatAlt(mWorld);
		mLonLatAlt.z() = 900;
		std::cout << "经纬度:" << mLonLatAlt.x() << " " << mLonLatAlt.y() << " " << mLonLatAlt.z() << std::endl;
	}
	else
	{
		PickObject = false;
	}

}
//屏幕转世界坐标
osg::Vec3 CPickHandler::screen2World(float x, float y)
{
	osg::Vec3 vec3;
	osg::ref_ptr<osg::Camera> camera = mViewer->getCamera();
	osg::Vec3 vScreen(x, y, 0);
	osg::Matrix mVPW = camera->getViewMatrix() * camera->getProjectionMatrix() * camera->getViewport()->computeWindowMatrix();
	osg::Matrix invertVPW;
	invertVPW.invert(mVPW);
	vec3 = vScreen * invertVPW;
	return vec3;

}