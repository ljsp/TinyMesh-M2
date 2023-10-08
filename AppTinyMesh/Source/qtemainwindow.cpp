#include "qte.h"
#include "implicits.h"
#include "ui_interface.h"
#include "Primitives.h"

MainWindow::MainWindow() : QMainWindow(), uiw(new Ui::Assets)
{
	// Chargement de l'interface
    uiw->setupUi(this);

	// Chargement du GLWidget
	meshWidget = new MeshWidget;
	QGridLayout* GLlayout = new QGridLayout;
	GLlayout->addWidget(meshWidget, 0, 0);
	GLlayout->setContentsMargins(0, 0, 0, 0);
    uiw->widget_GL->setLayout(GLlayout);

    uiw->meshOne_comboBox->addItem("None");
    uiw->meshOne_comboBox->addItem("Box");
    uiw->meshOne_comboBox->addItem("Sphere");
    uiw->meshOne_comboBox->addItem("Capsule");
    uiw->meshOne_comboBox->addItem("Torus");

    uiw->meshTwo_comboBox->addItem("None");
    uiw->meshTwo_comboBox->addItem("Box");
    uiw->meshTwo_comboBox->addItem("Sphere");
    uiw->meshTwo_comboBox->addItem("Capsule");
    uiw->meshTwo_comboBox->addItem("Torus");

    uiw->operator_comboBox->addItem("None");
    uiw->operator_comboBox->addItem("Union");
    uiw->operator_comboBox->addItem("Intersection");
    uiw->operator_comboBox->addItem("Subtraction");

	// Creation des connect
	CreateActions();

	meshWidget->SetCamera(Camera(Vector(10, 0, 0), Vector(0.0, 0.0, 0.0)));
}

MainWindow::~MainWindow()
{
	delete meshWidget;
}

void MainWindow::CreateActions()
{
	// Buttons
    connect(uiw->boxMesh, SIGNAL(clicked()), this, SLOT(BoxMeshExample()));
    connect(uiw->boxImplicit, SIGNAL(clicked()), this, SLOT(BoxImplicitExample()));
    connect(uiw->sphereImplicit, SIGNAL(clicked()), this, SLOT(SphereImplicitExample()));
    connect(uiw->capsuleImplicit, SIGNAL(clicked()), this, SLOT(CapsuleImplicitExample()));
    connect(uiw->torusImplicit, SIGNAL(clicked()), this, SLOT(TorusImplicitExample()));
    connect(uiw->apply_operatorButton, SIGNAL(clicked()), this, SLOT(RenderObjects()));
    connect(uiw->resetcameraButton, SIGNAL(clicked()), this, SLOT(ResetCamera()));
    connect(uiw->wireframe, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));
    connect(uiw->radioShadingButton_1, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));
    connect(uiw->radioShadingButton_2, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));

	// Widget edition
	connect(meshWidget, SIGNAL(_signalEditSceneLeft(const Ray&)), this, SLOT(editingSceneLeft(const Ray&)));
	connect(meshWidget, SIGNAL(_signalEditSceneRight(const Ray&)), this, SLOT(editingSceneRight(const Ray&)));
}

void MainWindow::editingSceneLeft(const Ray&)
{
}

void MainWindow::editingSceneRight(const Ray&)
{
}

void MainWindow::BoxMeshExample()
{
	Mesh boxMesh = Mesh(Box(1.0));

	std::vector<Color> cols;
	cols.resize(boxMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
		cols[i] = Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);

	meshColor = MeshColor(boxMesh, cols, boxMesh.VertexIndexes());
	UpdateGeometry();
}

void MainWindow::BoxImplicitExample()
{
    //AnalyticScalarField implicit;
    BoxImplicit implicit(Vector(1.0));

    Mesh implicitMesh;
    implicit.Polygonize(31, implicitMesh, Box(2.0));

    std::vector<Color> cols;
    cols.resize(implicitMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(0.8, 0.8, 0.8);

    meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::SphereImplicitExample()
{
  //AnalyticScalarField implicit;
  Sphere implicit(Vector(0.0), 1.0);

  Mesh implicitMesh;
  implicit.Polygonize(31, implicitMesh, Box(2.0));

  std::vector<Color> cols;
  cols.resize(implicitMesh.Vertexes());
  for (size_t i = 0; i < cols.size(); i++)
    cols[i] = Color(0.8, 0.8, 0.8);

  meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
  UpdateGeometry();
}

void MainWindow::CapsuleImplicitExample()
{
    Capsule implicit(Vector(0.0), Vector(1.0,0.0,.0), 0.5);

    Mesh implicitMesh;
    implicit.Polygonize(31, implicitMesh, Box(2.0));

    std::vector<Color> cols;
    cols.resize(implicitMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(0.8, 0.8, 0.8);

    meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::TorusImplicitExample() {

    Torus implicit(Vector(0.0), Vector(0.5, 0.3, 0.0));

    Mesh implicitMesh;
    implicit.Polygonize(31, implicitMesh, Box(2.0));

    std::vector<Color> cols;
    cols.resize(implicitMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(0.8, 0.8, 0.8);

    meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::RenderObjects() {

    QString meshOne = uiw->meshOne_comboBox->currentText();
    QString meshTwo = uiw->meshTwo_comboBox->currentText();
    QString op = uiw->operator_comboBox->currentText();

    float meshOneSize = uiw->meshOne_sizeSpinBox->value();
    float meshTwoSize = uiw->meshTwo_sizeSpinBox->value();
    float k_value = uiw->k_valueSpinBox->value();

    Node * node1;
    Node * node2;
    Node * implicit;

    switch (meshOne[0].toLatin1()) {
    case 'B':
        node1 = new BoxImplicit(Vector(meshOneSize));
        break;
    case 'S':
        node1 = new Sphere(Vector(0.0),meshOneSize);
        break;
    case 'C':
        node1 = new Capsule(Vector(0.0), Vector(1.0, 0.0, 0.0), meshOneSize);
        break;
    case 'T':
        node1 = new Torus(Vector(0.0), Vector(meshOneSize, meshOneSize, 0.0));
        break;
    default:
        node1 = new BoxImplicit(Vector(0.0));
        break;
    }

    switch (meshTwo[0].toLatin1()) {
    case 'B':
        node2 = new BoxImplicit(Vector(meshTwoSize));
        break;
    case 'S':
        node2 = new Sphere(Vector(0.0), meshTwoSize);
        break;
    case 'C':
        node2 = new Capsule(Vector(0.0), Vector(1.0, 0.0, 0.0), meshTwoSize);
        break;
    case 'T':
        node2 = new Torus(Vector(0.0), Vector(meshTwoSize, meshTwoSize, 0.0));
        break;
    default:
        node2 = new BoxImplicit(Vector(0.0));
        break;
    }

    switch (op[0].toLatin1()) {
    case 'I':
        implicit = new SmoothIntersection(node2, node1, k_value);
        break;
    case 'S':
        implicit = new SmoothSubtraction(node2, node1, k_value);
        break;
    case 'U':
        implicit = new SmoothUnion(node2, node1, k_value);
        break;
    default:
        implicit = new Union(node2, node1);
        break;
    }

    Mesh implicitMesh;
    implicit->Polygonize(31, implicitMesh, Box(2.0));

    std::vector<Color> cols;
    cols.resize(implicitMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(0.8, 0.8, 0.8);

    meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
    UpdateGeometry();

}

void MainWindow::UpdateGeometry()
{
	meshWidget->ClearAll();
	meshWidget->AddMesh("BoxMesh", meshColor);

    uiw->lineEdit->setText(QString::number(meshColor.Vertexes()));
    uiw->lineEdit_2->setText(QString::number(meshColor.Triangles()));

	UpdateMaterial();
}

void MainWindow::UpdateMaterial()
{
    meshWidget->UseWireframeGlobal(uiw->wireframe->isChecked());

    if (uiw->radioShadingButton_1->isChecked())
		meshWidget->SetMaterialGlobal(MeshMaterial::Normal);
	else
		meshWidget->SetMaterialGlobal(MeshMaterial::Color);
}

void MainWindow::ResetCamera()
{
	meshWidget->SetCamera(Camera(Vector(-10.0), Vector(0.0)));
}
