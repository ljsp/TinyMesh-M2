#ifndef __Qte__
#define __Qte__

#include <QtWidgets/qmainwindow.h>
#include "realtime.h"
#include "meshcolor.h"
#include "Node.h"

QT_BEGIN_NAMESPACE
	namespace Ui { class Assets; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT
private:
  Ui::Assets* uiw;           //!< Interface

  MeshWidget* meshWidget;   //!< Viewer
  MeshColor meshColor;		//!< Mesh.
  Node * implicit;
  std::vector<std::pair<Vector,Vector>> rays;

public:
  MainWindow();
  ~MainWindow();
  void CreateActions();
  void UpdateGeometry();

public slots:
  void editingSceneLeft(const Ray&);
  void editingSceneRight(const Ray&);
  void BoxMeshExample();
  void CustomImplicitExample();
  void BunnyImplicitExample();
  void BoxImplicitExample();
  void SphereImplicitExample();
  void CapsuleImplicitExample();
  void TorusImplicitExample();
  void BezierPatchExample();
  void RenderObjects();
  void IntersectRay();
  void ResetCamera();
  void SaveModel();
  void UpdateMaterial();
};

#endif
