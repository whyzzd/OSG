#include"CPickHandler.h"
#include<iostream>

#include"OsgContainer.h"
#include"DrawXXX.h"
#include<osgEarthAnnotation/FeatureNode>
#include<osgEarth/Picker>
#include<NodeUndoCommand.h>
CPickHandler::CPickHandler(osgViewer::Viewer *viewer) : mViewer(viewer)
{
	mMyConv.setViewer(viewer);
	m_oc = dynamic_cast<OsgContainer*>(mViewer);
	
	//connect(m_oc->m_undoAction, &QAction::triggered, this, &CPickHandler::slotMenuAction);
	
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
			else if (mSelected == SelectedDraw::DOT)
			{
				pick(ea.getX(), ea.getY());
				if(mIsPickObject)
				{ 
					//OsgContainer *oc = dynamic_cast<OsgContainer*>(mViewer);
					const osgEarth::SpatialReference* mapSRS = m_oc->getMapNode()->getMapSRS();
					//osg::Group*geometryGroup = new osg::Group;
					osgEarth::Symbology::Style geomStyle;
					/*geomStyle.getOrCreate<osgEarth::LineSymbol>()->stroke()->color() = osgEarth::Symbology::Color::Cyan;
					geomStyle.getOrCreate<osgEarth::LineSymbol>()->stroke()->width() = 5.0f;
					geomStyle.getOrCreate<osgEarth::LineSymbol>()->tessellationSize() = 75000;*/
					/*geomStyle.getOrCreate<osgEarth::AltitudeSymbol>()->clamping() = osgEarth::AltitudeSymbol::CLAMP_TO_TERRAIN;
					geomStyle.getOrCreate<osgEarth::AltitudeSymbol>()->technique() = osgEarth::AltitudeSymbol::TECHNIQUE_DRAPE;*/

					osg::ref_ptr<osgEarth::Symbology::Geometry> polygon = new osgEarth::Symbology::Polygon();
					polygon->push_back(osg::Vec3d(mLonLatAlt.x(), mLonLatAlt.y(), 0));
					//polygon->push_back(osg::Vec3d(-60, 40, 0));
					//polygon->push_back(osg::Vec3d(-60, 60, 0));
					//polygon->push_back(osg::Vec3d(0, 60, 0));


					osg::ref_ptr<osgEarth::Features::Feature> feature = new osgEarth::Features::Feature(polygon, mapSRS);
					osg::ref_ptr<osgEarth::Annotation::FeatureNode> featureNode = new osgEarth::Annotation::FeatureNode(feature/*, geomStyle*/);
					//geometryGroup->addChild(featureNode);
					/*osg::ref_ptr<osgEarth::Annotation::FeatureEditor> editor = new osgEarth::Annotation::FeatureEditor(featureNode);*/
					osgEarth::Annotation::FeatureEditor* editor = new osgEarth::Annotation::FeatureEditor(featureNode);
					m_oc->getMapNode()->addChild(editor);
					m_oc->getUndoStack()->push(new AddNodeCommand(&m_oc, editor));
				}
			}
			else if (mSelected==SelectedDraw::LINE)
			{ 
				
				pick(ea.getX(), ea.getY());
				if (mIsPickObject)
				{
					//oldDrawLine();

					//osgEarth::Symbology::Style m_lineStyle;
					//osgEarth::Features::Feature* m_pFeature;
					//osgEarth::Annotation::FeatureNode* m_pFeatureNode;
					//m_pFeature = NULL;
					//m_pFeatureNode = NULL;

					////线的style
					//m_lineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
					//	->stroke()->color() = osgEarth::Symbology::Color::Red;
					//m_lineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
					//	->stroke()->width() = 2.0;
					//m_lineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
					//	->tessellation() = 20.0;
					//m_lineStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
					//	->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
					//m_lineStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
					//	->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_DRAPE;
					//m_lineStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()
					//	->verticalOffset() = 0.1;
					//m_lineStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()
					//	->stroke()->stipple() = 255;

					//osgEarth::Features::Feature* pFeature = new osgEarth::Features::Feature(
					//	new osgEarth::Annotation::LineString,
					//	m_oc->getMapNode()->getMapSRS(), m_lineStyle);
					//pFeature->geoInterp()= GEOINTERP_GREAT_CIRCLE;
					//m_pFeatureNode = new osgEarth::Annotation::FeatureNode(pFeature);
					//
					//osgEarth::Symbology::Geometry* pGeometry = m_pFeatureNode->getFeature()->getGeometry();
					//pGeometry->clear();
					//m_pFeatureNode->setStyle(m_lineStyle);
					//pGeometry->push_back(osg::Vec3d(mLonLatAlt.x(), mLonLatAlt.y(), 0));
					//pGeometry->push_back(osg::Vec3d(mLonLatAlt.x()+10, mLonLatAlt.y()+10, 0));
					//osgEarth::Annotation::FeatureEditor* editor = new osgEarth::Annotation::FeatureEditor(m_pFeatureNode);
					//m_oc->getMapNode()->addChild(editor);
					
					osgEarth::Annotation::FeatureNode* pathNode = 0;
					Geometry* path = new LineString();
					path->push_back(osg::Vec3d(-74, 40.714, 0));   // New York
					path->push_back(osg::Vec3d(139.75, 35.68, 0)); // Tokyo

					osgEarth::Features::Feature* pathFeature = new osgEarth::Features::Feature(path, m_oc->getMapNode()->getMapSRS());
					//pathFeature->geoInterp() = GEOINTERP_GREAT_CIRCLE;

					Style pathStyle;
					pathStyle.getOrCreate<LineSymbol>()->stroke()->color() = Color::Red;
					pathStyle.getOrCreate<LineSymbol>()->stroke()->width() = 2.0f;
					pathStyle.getOrCreate<LineSymbol>()->stroke()->smooth() = true;
					pathStyle.getOrCreate<LineSymbol>()->tessellationSize() = 75000;
					pathStyle.getOrCreate<PointSymbol>()->size() = 7;
					//pathStyle.getOrCreate<PointSymbol>()->fill()->color() = Color::Red;
					pathStyle.getOrCreate<PointSymbol>()->smooth() = true;
					pathStyle.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
					//pathStyle.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_DRAPE;
					pathStyle.getOrCreate<RenderSymbol>()->depthOffset()->enabled() = true;

					//OE_INFO << "Path extent = " << pathFeature->getExtent().toString() << std::endl;

					pathNode = new osgEarth::Annotation::FeatureNode(pathFeature, pathStyle);

					osgEarth::Annotation::FeatureEditor* editor = new osgEarth::Annotation::FeatureEditor(pathNode);
					m_oc->getMapNode()->addChild(editor);
					m_oc->getMapNode()->addChild(pathNode);
					
				}
			}
			else if(mSelected == SelectedDraw::TRIANGLES)
			{
				pick(ea.getX(), ea.getY());
				if (mIsPickObject)
				{
					//oldDrawTriangles();

					Geometry* geom = new osgEarth::Annotation::Polygon();
					geom->push_back(-160., -30.);
					geom->push_back(150., -20.);
					geom->push_back(160., -45.);
					geom->push_back(-150., -40.);
					Style geomStyle;

					osgEarth::Annotation::Feature* feature = new osgEarth::Annotation::Feature(geom, m_oc->getMapNode()->getMapSRS());
					//feature->geoInterp() = GEOINTERP_RHUMB_LINE;

					geomStyle.getOrCreate<LineSymbol>()->stroke()->color() = Color::Lime;
					geomStyle.getOrCreate<LineSymbol>()->stroke()->width() = 3.0f;
					geomStyle.getOrCreate<LineSymbol>()->tessellationSize() = 75000;
					geomStyle.getOrCreate<PolygonSymbol>()->fill()->color() = Color(Color::Red);
					geomStyle.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
					//geomStyle.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_GPU;

					
					osgEarth::Annotation::FeatureNode* gnode = new osgEarth::Annotation::FeatureNode(feature, geomStyle);
					
					osgEarth::Annotation::FeatureEditor* editor = new osgEarth::Annotation::FeatureEditor(gnode);
					
					m_oc->getMapNode()->addChild(editor);
					m_oc->getMapNode()->addChild(gnode);
					
					
				}
			}
			else if (mSelected == SelectedDraw::PARALLELOGRAM)
			{
				pick(ea.getX(), ea.getY());
				if (mIsPickObject)
				{
					//oldDrawParallelogram();
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
			pick(ea.getX(), ea.getY());

			
			
			
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
			
			
			osgEarth::Annotation::FeatureEditor *mt = dynamic_cast<osgEarth::Annotation::FeatureEditor*>(getNodePath[i]);
			osg::MatrixTransform* mt1 = dynamic_cast<osg::MatrixTransform*>(getNodePath[i]);
			osgEarth::Annotation::FeatureNode *mt2= dynamic_cast<osgEarth::Annotation::FeatureNode*>(getNodePath[i]);
			if (mt1 != NULL || mt != NULL||mt2!=NULL)
			{
				mIsPickObject = true;
			}

			if (mt == NULL&&mt2==NULL)
			{
				continue;
			}
			else
			{
				
				picked = mt;
				//break;
			}
			pickednode = mt2;
		}
		
		
		mWorld = hitr->getWorldIntersectPoint();
		
		//std::cout << "世界坐标:" << vec1.x() << " " << vec1.y() << " " << vec1.z() << std::endl;
		mLonLatAlt = mMyConv.WorldToLonLatAlt(mWorld);
		mLonLatAlt.z() = 900;
		emit signShowLonLatAlt(mLonLatAlt);
		//std::cout << "经纬度:" << mLonLatAlt.x() << " " << mLonLatAlt.y() << " " << mLonLatAlt.z() << std::endl;
	}
	else
	{
		mIsPickObject = false;
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
void CPickHandler::oldDrawLine()
{
	if (mLineN >= 2)
	{
		mLineN = 1;
		//std::cout << typeid(*mViewer).name() << std::endl;//打印mViewer所指的实际类型
		//OsgContainer *oc = dynamic_cast<OsgContainer*>(mViewer);

		mLineVec->push_back(mLonLatAlt);

		DrawXXX drawline(mDrawLineWid);


		m_oc->getMapNode()->addChild(drawline.createLine(mLineVec));
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
void CPickHandler::oldDrawTriangles()
{
	if (mTrinangleN >= 3)
	{
		mTrinangleN = 1;
		//OsgContainer *oc = dynamic_cast<OsgContainer*>(mViewer);

		mTrinangleVec->push_back(mLonLatAlt);

		DrawXXX drawTrinangle;
		m_oc->getMapNode()->addChild(drawTrinangle.createTrinangle(mTrinangleVec));
		//oc->getRoot()->addChild(drawTrinangle.createTrinangle(mTrinangleVec));
		mTrinangleVec->clear();

	}
	else
	{
		mTrinangleVec->push_back(mLonLatAlt);
		mTrinangleN++;
	}
}
void CPickHandler::oldDrawParallelogram()
{
	if (mParallelogramN >= 3)
	{
		mParallelogramN = 1;
		//OsgContainer *oc = dynamic_cast<OsgContainer*>(mViewer);

		mParallelogramVec->push_back(mLonLatAlt);

		DrawXXX drawQuads;
		m_oc->getRoot()->addChild(drawQuads.createParallelogram(mParallelogramVec));

		mParallelogramVec->clear();

	}
	else
	{
		mParallelogramVec->push_back(mLonLatAlt);
		mParallelogramN++;
	}

}

void CPickHandler::slotGetDrawIndex(int n)
{
	mSelected = n;
}
void CPickHandler::slotDrawLineWid(float a)
{
	mDrawLineWid = a;
}
void CPickHandler::slotActionUndo(bool checked)
{
	m_oc->m_undoStack->undo();
}
void CPickHandler::slotActionRedo(bool checked )
{
	m_oc->m_undoStack->redo();
}
void CPickHandler::slotActionDel(bool checked )
{
	
	if (m_oc->getMapNode()->findMapNode(picked))
	{
		//picked->setNodeMask(0);
		m_oc->getMapNode()->removeChild(picked);
		m_oc->getUndoStack()->push(new DelNodeCommand(&m_oc, picked));
		//m_oc->getMapNode()->removeChild(picked->getChild(0)); 
	}
	
	if (m_oc->getMapNode()->findMapNode(pickednode))
	{
		//pickednode->setNodeMask(0);
		m_oc->getMapNode()->removeChild(pickednode);

	}
}