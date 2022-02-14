#include"NodeUndoCommand.h"
//Ôö¼Ó
AddNodeCommand::AddNodeCommand(OsgContainer**viewer, osgEarth::Annotation::FeatureEditor *editor)
	:m_viewer(viewer),m_editor(editor),m_editor1(editor)
{
	
}

AddNodeCommand::AddNodeCommand(OsgContainer**viewer, osgEarth::Annotation::FeatureEditor *editor, osgEarth::Annotation::FeatureNode*node)
	: m_viewer(viewer), m_editor(editor), m_editor1(editor),m_node(node),m_node1(node)
{

}

AddNodeCommand::~AddNodeCommand()
{}
void AddNodeCommand::undo()
{
	if ((*m_viewer)->getMapNode()->findMapNode(m_editor) != NULL)
	{
		(*m_viewer)->getMapNode()->removeChild(m_editor);
		
	}
	if ((*m_viewer)->getMapNode()->findMapNode(m_node) != NULL)
	{
		(*m_viewer)->getMapNode()->removeChild(m_node);
	}

}
void AddNodeCommand::redo()
{
	
	if ((*m_viewer)->getMapNode()->findMapNode(m_editor) == NULL)
	{
		(*m_viewer)->getMapNode()->addChild(m_editor1);
	}
	if ((*m_viewer)->getMapNode()->findMapNode(m_node) == NULL)
	{
		(*m_viewer)->getMapNode()->addChild(m_node1);
	}
}

//É¾³ý
DelNodeCommand::DelNodeCommand(OsgContainer**viewer, osgEarth::Annotation::FeatureEditor *editor)
	:m_viewer(viewer), m_editor(editor), m_editor1(editor)
{

}
DelNodeCommand::DelNodeCommand(OsgContainer**viewer, osgEarth::Annotation::FeatureEditor *editor, osgEarth::Annotation::FeatureNode*node)
	: m_viewer(viewer), m_editor(editor), m_editor1(editor), m_node(node), m_node1(node)
{

}
DelNodeCommand::~DelNodeCommand()
{}
void DelNodeCommand::undo()
{
	if ((*m_viewer)->getMapNode()->findMapNode(m_editor) == NULL)
	{
		(*m_viewer)->getMapNode()->addChild(m_editor1);
	}

	if ((*m_viewer)->getMapNode()->findMapNode(m_node) == NULL)
	{
		(*m_viewer)->getMapNode()->addChild(m_node1);
	}
}
void DelNodeCommand::redo()
{
	if ((*m_viewer)->getMapNode()->findMapNode(m_editor) != NULL)
	{
		(*m_viewer)->getMapNode()->removeChild(m_editor);
	}
	if ((*m_viewer)->getMapNode()->findMapNode(m_node) != NULL)
	{
		(*m_viewer)->getMapNode()->removeChild(m_node);
	}
}
