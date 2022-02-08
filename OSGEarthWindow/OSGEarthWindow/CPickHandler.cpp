#include"CPickHandler.h"
#include<iostream>

#include"OsgContainer.h"
#include"DrawXXX.h"
#include<osgEarthAnnotation/FeatureNode>
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
			//判断选择绘制类型
			if (mSelected==SelectedDraw::NONE)
			{
				//pick1(ea.getX(), ea.getY());
				
			}
			else if (mSelected==SelectedDraw::LINE)
			{ 
				
				pick(ea.getX(), ea.getY());
				if (mIsPickObject)
				{

					if (mLineN >= 2)
					{
						mLineN = 1;
						std::cout << typeid(*mViewer).name() << std::endl;//打印mViewer所指的实际类型
						OsgContainer *oc = dynamic_cast<OsgContainer*>(mViewer);
					
						mLineVec->push_back(mLonLatAlt);
						
						DrawXXX drawline(mDrawLineWid);
						
						oc->getMapNode()->addChild(drawline.createLine(mLineVec));
						//oc->getRoot()->addChild(drawline.createLine(mLineVec));
						mLineVec->clear();
						//oc->getEM()->setHomeViewpoint(osgEarth::Viewpoint("视点", (vvv[0].x()+vvv[1].x())/2, (vvv[0].y()+vvv[1].y())/2, 900, 0.0, -90, 7e3));
						//oc->getEM()->setViewpoint(osgEarth::Viewpoint("视点", (vvv[0].x() + vvv[1].x()) / 2, (vvv[0].y() + vvv[1].y()) / 2, 900, 0.0, -90, 7e3));
					}
					else
					{
						mLineVec->push_back(mLonLatAlt);
						mLineN++;	
					}
				}
			}
			else if(mSelected == SelectedDraw::TRIANGLES)
			{
				pick(ea.getX(), ea.getY());
				if (mIsPickObject)
				{
					if (mTrinangleN >= 3)
					{
						mTrinangleN = 1;
						OsgContainer *oc = dynamic_cast<OsgContainer*>(mViewer);

						mTrinangleVec->push_back(mLonLatAlt);

						DrawXXX drawTrinangle;
						oc->getMapNode()->addChild(drawTrinangle.createTrinangle(mTrinangleVec));
						//oc->getRoot()->addChild(drawTrinangle.createTrinangle(mTrinangleVec));
						mTrinangleVec->clear();
						
					}
					else
					{
						mTrinangleVec->push_back(mLonLatAlt);
						mTrinangleN++;
					}
				}
			}
			else if (mSelected == SelectedDraw::PARALLELOGRAM)
			{
				pick(ea.getX(), ea.getY());
				if (mIsPickObject)
				{
					if (mParallelogramN >= 3)
					{
						mParallelogramN = 1;
						OsgContainer *oc = dynamic_cast<OsgContainer*>(mViewer);

						mParallelogramVec->push_back(mLonLatAlt);

						DrawXXX drawQuads;
						oc->getRoot()->addChild(drawQuads.createParallelogram(mParallelogramVec));
						mParallelogramVec->clear();

					}
					else
					{
						mParallelogramVec->push_back(mLonLatAlt);
						mParallelogramN++;
					}

				}
			}
			else //无选择时
			{
				return false;
			}
			
		}
		else if (button == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
		{
			reDrawXXX();
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

		for (int i = getNodePath.size() - 1; i >=0; --i)
		{
			
			osg::MatrixTransform* mt = dynamic_cast<osg::MatrixTransform*>(getNodePath[i]);
			if (mt == NULL)
			{
				continue;
			}
			else
			{
				mIsPickObject = true;
				picked = mt;
				
			}
		}

		
		mWorld = hitr->getWorldIntersectPoint();
		
		//std::cout << "世界坐标:" << vec1.x() << " " << vec1.y() << " " << vec1.z() << std::endl;
		mLonLatAlt = mMyConv.WorldToLonLatAlt(mWorld);
		mLonLatAlt.z() = 900;
		emit signShowLonLatAlt(mLonLatAlt);
		std::cout << "经纬度:" << mLonLatAlt.x() << " " << mLonLatAlt.y() << " " << mLonLatAlt.z() << std::endl;
	}
	else
	{
		mIsPickObject = false;
	}
}

void CPickHandler::pick1(float x, float y)
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
				/*mIsPickObject = true;
				picked = mt;*/
				getNodePath[i]->setNodeMask(0);
			}
		}


		mWorld = hitr->getWorldIntersectPoint();

		//std::cout << "世界坐标:" << vec1.x() << " " << vec1.y() << " " << vec1.z() << std::endl;
		mLonLatAlt = mMyConv.WorldToLonLatAlt(mWorld);
		mLonLatAlt.z() = 900;
		emit signShowLonLatAlt(mLonLatAlt);
		std::cout << "经纬度:" << mLonLatAlt.x() << " " << mLonLatAlt.y() << " " << mLonLatAlt.z() << std::endl;
	}
	else
	{
		//mIsPickObject = false;
	}
}

void CPickHandler::reDrawXXX()
{
	mIsPickObject = false;
	mLineN = 1;
	mTrinangleN = 1;
	mParallelogramN = 1;
	mLineVec->clear();
	mTrinangleVec->clear();
	mTrinangleVec->clear();
	emit signReDefault();
}

void CPickHandler::slotGetDrawIndex(int n)
{
	mSelected = n;
}
void CPickHandler::slotDrawLineWid(float a)
{
	mDrawLineWid = a;
}